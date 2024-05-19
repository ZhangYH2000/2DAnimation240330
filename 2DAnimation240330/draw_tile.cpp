#include "draw_tile.h"

void draw_tile_raw
(tile& dest, dvec tl, drect vp_dest, tile const& src, drect vp_src) {
	int a = max(vp_dest.left(), tl.x);
	int b = min(vp_dest.right(), tl.x + vp_src.w);
	int c = max(vp_dest.top(), tl.y);
	int d = min(vp_dest.bottom(), tl.y + vp_src.h);
	if (a >= b || c >= d) { return; }

	rep(j, c, d) {
		int dp = j * dest.w + a;
		int sp = (j - tl.y + vp_src.top()) * src.w +
			(a - tl.x + vp_src.left());
		int sz_row = sizeof(dcol) * (b - a);
		memcpy(dest.cols.data() + dp, src.cols.data() + sp, sz_row);
	}
}
void draw_tile(tile& dest, dbuf& ds, double dep, dvec tl,
	drect vp_dest, tile const& src, drect vp_src) {
	int a = max(vp_dest.left(), tl.x);
	int b = min(vp_dest.right(), tl.x + vp_src.w);
	int c = max(vp_dest.top(), tl.y);
	int d = min(vp_dest.bottom(), tl.y + vp_src.h);
	if (a >= b || c >= d) { return; }

	rep(j, c, d) {
		int dp = j * dest.w + a;
		int sp = (j - tl.y + vp_src.top()) * src.w +
			(a - tl.x + vp_src.left());
		rep(i, a, b) {
			if (ds[dp] <= dep && src.as[sp] != 0) {
				ds[dp] = dep; dest.cols[dp] = src.cols[sp];
			} dp++; sp++;
		}
	}
}
bool hit_tile(dvec p, dvec tl, tile const& src, drect vp_src) {
	dvec s_pnt = vp_src.tl + p - tl;
	int sp = s_pnt.y * src.w + s_pnt.x;
	return insd(s_pnt, vp_src) && src.as[sp] != 0;
}

void draw_tile_cover(tile& dest, dvec tl,
	drect vp_dest, tile const& src, drect vp_src, BYTE alpha) {
	int a = max(vp_dest.left(), tl.x);
	int b = min(vp_dest.right(), tl.x + vp_src.w);
	int c = max(vp_dest.top(), tl.y);
	int d = min(vp_dest.bottom(), tl.y + vp_src.h);
	if (a >= b || c >= d) { return; }
	rep(j, c, d) {
		int dp = j * dest.w + a;
		int sp = (j - tl.y + vp_src.top()) * src.w +
			(a - tl.x + vp_src.left());
		rep(i, a, b) {
			// 他这里其实是统一的 alpha 值，以后可能改掉。
			if (src.as[sp] != 0) {
				cover(dest.cols[dp], dest.as[dp], src.cols[sp], alpha);
			} dp++; sp++;
		}
	}
}

void draw_tile(tile& dest, dvec tl, drect vp_dest, tile const& src, drect vp_src) {
	int a = max(vp_dest.left(), tl.x);
	int b = min(vp_dest.right(), tl.x + vp_src.w);
	int c = max(vp_dest.top(), tl.y);
	int d = min(vp_dest.bottom(), tl.y + vp_src.h);
	if (a >= b || c >= d) { return; }

	rep(j, c, d) {
		int dp = j * dest.w + a;
		int sp = (j - tl.y + vp_src.top()) * src.w +
			(a - tl.x + vp_src.left());
		rep(i, a, b) {
			if (src.as[sp] != 0) {
				// 这个跟画屏幕的版本比多了改变 alpha，这个是必要的。
				dest.as[dp] = 255;
				dest.cols[dp] = src.cols[sp];
			} dp++; sp++;
		}
	}
}

void draw_tile(tile& dest, vec2 ct, double w, double h,
	mat2 tsf, drect vp_dest, tile const& src, drect vp_src) {
	if (w < 0) { w = -w; tsf = tsf * mat2(-1, 0, 0, 1); }
	if (h < 0) { h = -h; tsf = tsf * mat2(1, 0, 0, -1); }

	mat2 inv_tsf = tsf.inv();
	vec2 hwh_tsf = tsf.abs() * vec2(w, h) / 2;

	// 我不知道这里余量应该留多少，只是猜的。
	int a = max(vp_dest.left(), int(ct.x - hwh_tsf.x) - 1);
	int b = min(vp_dest.right(), int(ct.x + hwh_tsf.x) + 1);
	int c = max(vp_dest.top(), int(ct.y - hwh_tsf.y) - 1);
	int d = min(vp_dest.bottom(), int(ct.y + hwh_tsf.y) + 1);
	if (a >= b || c >= d) return;

	rep(i, a, b) rep(j, c, d) {
		// 下面的 0.5 是整体一半的意思，不是像素一半的意思。
		// 这里是先放缩到 w * h 的尺寸再旋转。
		// 下面的变换考虑逆过程可能直观一点。
		dvec d_pnt(i, j);
		vec2 tmp = vec2(0.5) +
			inv_tsf * (vec2(d_pnt) - ct) / vec2(w, h);
		dvec s_pnt = vp_src.tl +
			dvec(vec2(vp_src.w, vp_src.h) * tmp);

		if (insd(s_pnt, vp_src)) {
			int dp = d_pnt.y * dest.w + d_pnt.x;
			int sp = s_pnt.y * src.w + s_pnt.x;

			if (src.as[sp] != 0) {
				dest.as[dp] = 255; 
				dest.cols[dp] = src.cols[sp];
			}
		}
	}
}
