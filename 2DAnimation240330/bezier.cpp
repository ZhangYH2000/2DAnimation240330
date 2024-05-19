#include "bezier.h"
#include "draw_fill.h"
#include "draw_curve.h"
#include "draw_px_seg.h"

Bezier::Bezier(FILE* f) {
	int sz = 0;
	frd(closed);
	frd(sz); dat.resize(sz);
	for (auto& vs : dat) { frdv(vs); }
}
void Bezier::Save(FILE* f) const {
	int sz = 0;
	fwt(closed);
	sz = dat.size(); fwt(sz);
	for (auto& vs : dat) { fwtv(vs); }
}

// 因为使用还是不适用深度缓冲区的区别，这里要分两个版本，不知道怎么简化。
void draw_bezier(tile& dest, dbuf& ds, double dep, dvec tl,
	Bezier const& bz, double thk, drect vp, dcol col) {

	int n = 40;
	int sz = bz.dat.size();
	// 这里应该也会有非负整数取负数值的隐患。
	rep(i, 0, bz.closed ? sz : sz - 1) {
		int j = (i + 1) % sz;
		vector<vec2> vs;
		for (auto v : bz.dat[i]) { vs.push_back((vec2)v); }
		vs.push_back((vec2)bz.dat[j][0]);

		rep(i, 0, n) {
			double t0 = double(i) / n;
			double t1 = double(i + 1) / n;
			vec2 v0 = bezier(vs, t0) + vec2(tl);
			vec2 v1 = bezier(vs, t1) + vec2(tl);
			// 其实这里没有用到深度是吧，不知道搞了些啥。
			draw_tiny_seg(dest, v0, v1, thk, vp, col);
		}
	}
}

void draw_bezier_seg(tile& dest, dbuf& ds,
	double dep, dvec tl, Bezier const& bz, drect vp) {
	dcol c0 = dcol(0, 0, 0);
	dcol c1 = dcol(220);

	int sz = bz.dat.size();
	// 这里应该也会有非负整数取负数值的隐患。
	rep(i, 0, bz.closed ? sz : sz - 1) {
		int j = (i + 1) % sz;
		rep(k, 1, bz.dat[i].size() - 1) {
			draw_px_seg(dest, ds,
				bz.dat[i][k] + tl, bz.dat[i][k + 1] + tl, dep, vp, c1);
		}
		if (bz.dat[i].size() > 1) {
			draw_px_seg(dest, ds, 
				bz.dat[i][0] + tl, bz.dat[i][1] + tl, dep, vp, c0);
		}
		draw_px_seg(dest, ds, 
			bz.dat[i].back() + tl, bz.dat[j][0] + tl, dep, vp, c0);
	}
}

void draw_px_bezier(tile& dest, dbuf& ds, 
	double dep, dvec tl, Bezier const& bz, drect vp, dcol col) {

	int n = 40;
	int sz = bz.dat.size();
	// 这里应该也会有非负整数取负数值的隐患。
	rep(i, 0, bz.closed ? sz : sz - 1) {
		int j = (i + 1) % sz;
		vector<vec2> vs;
		for (auto v : bz.dat[i]) { vs.push_back((vec2)v); }
		vs.push_back((vec2)bz.dat[j][0]);

		rep(i, 0, n) {
			double t0 = double(i) / n;
			double t1 = double(i + 1) / n;
			vec2 v0 = bezier(vs, t0) + (vec2)tl;
			vec2 v1 = bezier(vs, t1) + (vec2)tl;
			draw_px_seg(dest, ds, v0, v1, dep, vp, col);
		}
	}
}
void draw_fill_bezier(tile& dest, dbuf& ds,
	double dep, dvec tl, Bezier const& bz, drect vp, dcol col) {
	vector<dvec> dvs;

	int n = 40;
	int sz = bz.dat.size();
	// 这里应该也会有非负整数取负数值的隐患。
	rep(i, 0, sz) {
		int j = (i + 1) % sz;
		vector<vec2> vs;
		for (auto v : bz.dat[i]) { vs.push_back((vec2)v); }
		vs.push_back((vec2)bz.dat[j][0]);

		rep(i, 0, n) {
			double t0 = double(i) / n;
			vec2 v0 = bezier(vs, t0) + (vec2)tl;
			dvs.push_back((dvec)v0);
		}
	}

	draw_fill_poly(dest, ds, dep, dvs, vp, col);
}

void draw_bezier(tile& dest, dvec tl,
	Bezier const& bz, double thk, drect vp, dcol col) {

	int n = 40;
	int sz = bz.dat.size();
	// 这里应该也会有非负整数取负数值的隐患。
	rep(i, 0, bz.closed ? sz : sz - 1) {
		int j = (i + 1) % sz;
		vector<vec2> vs;
		for (auto v : bz.dat[i]) { vs.push_back((vec2)v); }
		vs.push_back((vec2)bz.dat[j][0]);

		rep(i, 0, n) {
			double t0 = double(i) / n;
			double t1 = double(i + 1) / n;
			vec2 v0 = bezier(vs, t0) + (vec2)tl;
			vec2 v1 = bezier(vs, t1) + (vec2)tl;
			draw_tiny_seg(dest, v0, v1, thk, vp, col);
		}
	}
}
void draw_px_bezier(tile& dest, dvec tl,
	Bezier const& bz, drect vp, dcol col) {

	int n = 40;
	int sz = bz.dat.size();
	// 这里应该也会有非负整数取负数值的隐患。
	rep(i, 0, bz.closed ? sz : sz - 1) {
		int j = (i + 1) % sz;
		vector<vec2> vs;
		for (auto v : bz.dat[i]) { vs.push_back((vec2)v); }
		vs.push_back((vec2)bz.dat[j][0]);

		rep(i, 0, n) {
			double t0 = double(i) / n;
			double t1 = double(i + 1) / n;
			vec2 v0 = bezier(vs, t0) + (vec2)tl;
			vec2 v1 = bezier(vs, t1) + (vec2)tl;
			draw_px_seg(dest, (dvec)v0, (dvec)v1, vp, col);
		}
	}
}
void draw_fill_bezier(tile& dest, dvec tl,
	Bezier const& bz, drect vp, dcol col) {
	vector<dvec> dvs;

	int n = 40;
	int sz = bz.dat.size();
	// 这里应该也会有非负整数取负数值的隐患。
	rep(i, 0, sz) {
		int j = (i + 1) % sz;
		vector<vec2> vs;
		for (auto v : bz.dat[i]) { vs.push_back((vec2)v); }
		vs.push_back((vec2)bz.dat[j][0]);

		rep(i, 0, n) {
			double t0 = double(i) / n;
			vec2 v0 = bezier(vs, t0) + (vec2)tl;
			dvs.push_back((dvec)v0);
		}
	}

	draw_fill_poly(dest, dvs, vp, col);
}
