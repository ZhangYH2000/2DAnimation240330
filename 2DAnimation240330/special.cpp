#include "special.h"
#include "cur.h"
#include "bgr.h"
#include "layer.h"
#include "frame.h"

#include "my_def.h"

void Mandelbrot(Cur& cur, int len, 
	double scl, double v_scl, vec2 p, int n, int w, int h) {
	if (len > lysel.frs.size()) {
		lysel.frs.resize(n);
	}
	w = min(bgr.w, w);
	h = min(bgr.h, h);
	cur.time = 0;
	cur.t_stop = len - 1;

	rep(k, 0, len) {
		lysel.NewFrame(cur, k);
		auto& back = lysel.frs[k]->back;
		double t = (double)k / cur.frame_rate;

		rep(i, 0, w) rep(j, 0, h) {
			int id = back.w * j + i;
			back.as[id] = 255;

			vec2 u = vec2(i - w / 2, j - h / 2) / h;
			u = u * exp(-v_scl * t) / scl + p;

			vec2 w; 
			int l = 0;
			bool ok = true;
			for (; l < n;++l) {
				double tmp = w.x * w.x - w.y * w.y;
				w.y = 2 * w.x * w.y;
				w.x = tmp;
				w += u;
				if (w.lensqr() > 4) {
					ok = false; break;
				}
			}
			back.cols[id] = ok ? 
				dcol(160, 20, 30) : 
				(dcol)col3(0, 0, 0.85 * exp(-0.04 * l));
		}
	}
}
