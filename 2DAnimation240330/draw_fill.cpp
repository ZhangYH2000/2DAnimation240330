#include "draw_fill.h"

void draw_fill_poly(tile& dest, dbuf& ds,
	double dep, vector<dvec> const& vs, drect vp, dcol col) {
	int a = INT_MAX, c = INT_MAX;
	int b = INT_MIN, d = INT_MIN;
	for (auto v : vs) {
		a = min(a, v.x); b = max(b, v.x);
		c = min(c, v.y); d = max(d, v.y);
	}
	a = max(a, vp.left()); b = min(b, vp.right());
	c = max(c, vp.top()); d = min(d, vp.bottom());
	if (a > b || c > d) { return; }

	rep(y, c, d) {
		vector<int> xs;
		rep(i, 0, vs.size()) {
			int j = (i + 1) % vs.size();
			dvec v0 = vs[i], v1 = vs[j];

			// 下面是为了避免出现退化的情形，具体我还没有证明的。
			if (v0.y == v1.y) { continue; }
			if (v0.y > y && v1.y > y) { continue; }
			if (v0.y < y && v1.y < y) { continue; }
			if (v1.y > v0.y && v0.y == y) { continue; }
			if (v1.y < v0.y && v1.y == y) { continue; }

			double x =
				v0.x * (v1.y - y) + v1.x * (y - v0.y);
			x /= v1.y - v0.y;
			xs.push_back(x);
		}

		sort(xs.begin(), xs.end());
		rep(i, 0, xs.size() / 2) {
			int x0 = xs[2 * i];
			// 下面的 +1 是为了防止出现空隙。
			int x1 = xs[2 * i + 1] + 1;
			rep(x, max(x0, a), min(x1, b)) {
				int dp = y * dest.w + x;
				if (ds[dp] <= dep) {
					ds[dp] = dep; dest.cols[dp] = col;
				}
			}
		}
	}
}

void draw_fill_poly(tile& dest, vector<dvec> const& vs, drect vp, dcol col) {
	int a = INT_MAX, c = INT_MAX;
	int b = INT_MIN, d = INT_MIN;
	for (auto v : vs) {
		a = min(a, v.x); b = max(b, v.x);
		c = min(c, v.y); d = max(d, v.y);
	}
	a = max(a, vp.left()); b = min(b, vp.right());
	c = max(c, vp.top()); d = min(d, vp.bottom());
	if (a > b || c > d) { return; }

	rep(y, c, d) {
		vector<int> xs;
		rep(i, 0, vs.size()) {
			int j = (i + 1) % vs.size();
			dvec v0 = vs[i], v1 = vs[j];

			// 下面是为了避免出现退化的情形，具体我还没有证明的。
			if (v0.y == v1.y) { continue; }
			if (v0.y > y && v1.y > y) { continue; }
			if (v0.y < y && v1.y < y) { continue; }
			if (v1.y > v0.y && v0.y == y) { continue; }
			if (v1.y < v0.y && v1.y == y) { continue; }

			double x =
				v0.x * (v1.y - y) + v1.x * (y - v0.y);
			x /= v1.y - v0.y;
			xs.push_back(x);
		}

		sort(xs.begin(), xs.end());
		rep(i, 0, xs.size() / 2) {
			int x0 = xs[2 * i];
			// 下面的 +1 是为了防止出现空隙。
			int x1 = xs[2 * i + 1] + 1;
			rep(x, max(x0, a), min(x1, b)) {
				int dp = y * dest.w + x;
				dest.as[dp] = 255; dest.cols[dp] = col;
			}
		}
	}
}

bool same_col(dcol c0, BYTE a0, dcol c1, BYTE a1) {
	return (a0 == 0 && a1 == 0) ||
		(c0 == c1 && a0 != 0 && a1 != 0);
}

struct fill_info {
	dvec p;
	int direction = 0;
};
void sub_fill(tile& dest, vector<fill_info>& stack, drect const& vp,
	dcol c_before, BYTE a_before, dcol c_after, BYTE a_after) {

	fill_info& f = stack.back();
	dvec p = f.p;

	switch (f.direction) {
	case 0: p += { 1, 0 }; break;
	case 1: p += { 0, 1 }; break;
	case 2: p += { -1, 0 }; break;
	case 3: p += { 0, -1 }; break;
	}

	int id = p.y * dest.w + p.x;
	bool should_cover = insd(p, vp) &&
		same_col(dest.cols[id], dest.as[id], c_before, a_before);

	if (should_cover) {
		dest.cols[id] = c_after; dest.as[id] = a_after;
		stack.push_back({ p, 0 });
	} else {
		++f.direction;
		if (f.direction == 4) { stack.pop_back(); }
	}
}

void draw_fill(tile& dest, dvec p, drect vp, dcol c) {
	if (!insd(p, vp)) { return; }
	int dp = p.y * dest.w + p.x;
	dcol c_before = dest.cols[dp];
	BYTE a_before = dest.as[dp];

	bool end =
		same_col(c_before, a_before, c, 255);
	if (end) { return; }

	dest.cols[dp] = c; dest.as[dp] = 255;
	vector<fill_info> stack = { { p, 0 } };
	while (!stack.empty()) {
		sub_fill(dest, stack, vp, c_before, a_before, c, 255);
	}
}
