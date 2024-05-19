#include "draw_curve.h"

void draw_tiny_seg(tile& dest, vec2 pa, vec2 pb, double thk, drect vp, dcol col) {

	int a = max(vp.left(), int(min(pa.x, pb.x) - thk) - 1);
	int b = min(vp.right(), int(max(pa.x, pb.x) + thk) + 1);
	int c = max(vp.top(), int(min(pa.y, pb.y) - thk) - 1);
	int d = min(vp.bottom(), int(max(pa.y, pb.y) + thk) + 1);
	double rr = thk * thk / 4;

	rep(i, a, b) rep(j, c, d) {
		double tmp = dist_sqr(pa, pb, vec2(i, j));
		if (tmp < rr) {
			int dp = j * dest.w + i;
			dest.cols[dp] = col; dest.as[dp] = 255;
		}
	}
}

#define TMP \
if (insd(p, vp)) {\
	int dp = p.y * dest.w + p.x;\
	dest.cols[dp] = col;\
	ds[dp] = dep;\
}

void draw_px_circle(tile& dest, dbuf& ds, double dep,
	dvec ct, int r, drect vp, dcol col) {

	int x = r, y = 0;
	int e = 3 - 2 * r;

	while (x >= y) {
		dvec p;
		p = ct + dvec(+x, +y); TMP;
		p = ct + dvec(+x, -y); TMP;
		p = ct + dvec(-x, +y); TMP;
		p = ct + dvec(-x, -y); TMP;
		p = ct + dvec(+y, +x); TMP;
		p = ct + dvec(+y, -x); TMP;
		p = ct + dvec(-y, +x); TMP;
		p = ct + dvec(-y, -x); TMP;

#undef TMP

		if (e > 0) { e += 2 * (5 - 2 * x + 2 * y);  --x; }
		else { e += 2 * (3 + 2 * y); }
		++y;
	}
}

void draw_tiny_seg_erase(tile& dest, vec2 pa, vec2 pb, double thk, drect vp) {
	int a = max(vp.left(), int(min(pa.x, pb.x) - thk) - 1);
	int b = min(vp.right(), int(max(pa.x, pb.x) + thk) + 1);
	int c = max(vp.top(), int(min(pa.y, pb.y) - thk) - 1);
	int d = min(vp.bottom(), int(max(pa.y, pb.y) + thk) + 1);
	double rr = thk * thk / 4;

	rep(i, a, b) rep(j, c, d) {
		double tmp = dist_sqr(pa, pb, vec2(i, j));
		if (tmp < rr) {
			int dp = j * dest.w + i;
			// 重置颜色主要是为了让
			dest.cols[dp] = {}; dest.as[dp] = 0;
		}
	}
}
