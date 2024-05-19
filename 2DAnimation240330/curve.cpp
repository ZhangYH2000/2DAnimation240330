#include "curve.h"
#include "cur.h"
#include "bgr.h"
#include "draw_px_seg.h"

#include "my_def.h"

curve::curve(FILE* f) {
	int sz = 0;
	frdv(nds);
}
void curve::Save(FILE* f) {
	int sz = 0;
	fwtv(nds);
}
void curve::render(Cur& cur) {
	if (nds.empty()) { return; }
	rep(i, 0, nds.size() - 1) {
		dvec p0 = bgr.tl + nds[i].p;
		dvec p1 = bgr.tl + nds[i + 1].p;

		draw_px_seg(scr, dscr, p0, p1, 200, bgr.vp(), dcol(255, 0, 0));
	}
}

void curve::normalize() {
	// 默认了 nds[0].u == 0.

	if (nds.empty()) { return; }
	double sum = 0;
	rep(i, 0, nds.size() - 1) {
		sum += sqrt((nds[i + 1].p - nds[i].p).lensqr());
		nds[i + 1].u = sum;
	}
	for (auto& nd : nds) {
		nd.u /= sum;
	}
}
vec2 curve::at(double t) {
	if (nds.empty()) { return {}; }

	// 不知道下面会不会需要无符号整型的问题。
	rep(i, 0, nds.size() - 1) {
		if (nds[i + 1].u <= t) { continue; }
		vec2 p = (vec2)nds[i].p * (nds[i + 1].u - t);
		p += (vec2)nds[i + 1].p * (t - nds[i].u);
		p /= nds[i + 1].u - nds[i].u;
		return p;
	}

	return (vec2)nds.back().p;
}
