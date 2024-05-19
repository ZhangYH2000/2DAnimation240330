#include "bgr.h"
#include "cur.h"
#include "layer.h"
#include "frame.h"
#include "canvas.h"
#include "object.h"
#include "draw_geo.h"
#include "draw_str.h"
#include "draw_tile.h"

Bgr::Bgr(Cur& cur) {
	w = 1450; h = 860;
	tl = { 170, 0 }; dep = -100000;
	black = tile(w, h, {}, 255);
}

#include "my_def.h"

void Bgr::render(Cur& cur) {
	draw_tile_raw(scr, tl, scr.rect(), black, black.rect());
	
	auto rect = cur.rect();
	rect.tl += bgr.tl;
	draw_rect_raw(scr, rect.tl, rect.w, rect.h, bgr.vp(), dcol(255));

	if (!cur.play) {
		for (int i = cur.layers.size() - 1; i >= 0; --i) {
			auto& ly = *cur.layers[i];
			if (!ly.show) { continue; }

			if (&ly == &lysel) {
				vector<int> as = { 120, 40, 10 };
				bool is_frame = tm < lysel.frs.size() && lysel.frs[tm];
				int idx = tm;
				if (is_frame && cur.show_before && !cur.play) 
				rep(i, 0, as.size()) {
					if (idx == 0) { break; }
					idx = lysel.prv(idx - 1);
					auto& img = lysel.frs[idx]->back;
					// 这个覆盖的方向是不是其实应该反过来。
					// 但是目前的这个顺序比较好实现。
					draw_tile_cover(scr, tl, rect, img, img.rect(), as[i]);
				}

				// 我还不知道这种半透明的东西怎么处理才漂亮。
				idx = tm;
				if (is_frame && cur.show_after && !cur.play) 
				rep(i, 0, as.size()) {
					idx = lysel.nxt(idx);
					if (idx >= lysel.frs.size()) { break; }
					auto& img = lysel.frs[idx]->back;
					// 这个覆盖的方向是不是其实应该反过来。
					// 但是目前的这个顺序比较好实现。
					draw_tile_cover(scr, tl, rect, img, img.rect(), as[i]);
				}
			}

			auto& img = ly.frs[ly.prv(tm)]->back;
			draw_tile(scr, dscr, dep, tl, rect, img, img.rect());

			for (auto& ob : ly.obs) { ob->Render(cur, ly); }
			if (&ly == &lysel) {
				cur.cvs->Render(cur);
			}
		}
	} else {
		draw_tile(scr, dscr, dep, tl, 
			rect, *cur.buffer[tm], cur.buffer[tm]->rect());
	}

	draw_str(scr, dscr, 999, dbstr,
		dcol(0, 255, 0), ft, tl + dvec(10, 10), w - 20, bgr.vp());
}

void Bgr::Update(Cur& cur) {
	hovered = (hvd == this);
	wheeled = (whd == this);
	render(cur);
}
void Bgr::PreUpdate(Cur& cur) {
	bool ok = dhv <= dep && insd(msp, vp());
	if (ok) { dhv = dep; hvd = this; }

	ok = dwh <= dep && insd(msp, vp());
	if (ok) { dwh = dep; whd = this; }
}
