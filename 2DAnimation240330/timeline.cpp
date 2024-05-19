#include "timeline.h"
#include "cur.h"
#include "bgr.h"
#include "frame.h"
#include "layer.h"
#include "canvas.h"
#include "object.h"
#include "draw_geo.h"
#include "draw_str.h"
#include "draw_comp.h"
#include "draw_px_seg.h"

#include "my_def.h"

int constexpr wbox = 30;
int constexpr hbox = 12;
double constexpr dep = -10000;

Timeline::Timeline() {
	tl = dvec(1620, 0);
	w = 180; h = 900;
}
void Timeline::Update(Cur& cur) {
	hovered = (hvd == this);
	gd_hvd = false;

	if (hovered) {
		pgd_hv =
			(msp - tl) / dvec(wbox, hbox)
			- (dvec)tl_rel / dvec(wbox, hbox) - dvec(0, 2);
		gd_hvd = pgd_hv.x < cur.layers.size() && pgd_hv.y >= 0;
	}

	if (!dragged) {
		dragged = hovered && msc(1);
	} else {
		dragged = msd[1];
		tl_rel.y += msp.y - msp_old.y;
		tl_rel.x += msp.x - msp_old.x;
	} 
	tl_rel.x = max<int>(tl_rel.x, -wbox * (cur.layers.size() + 2) + w);
	tl_rel.x = min(tl_rel.x, 0.0);
	tl_rel.y = min(tl_rel.y, 0.0);

	if (selecting) {
		cur.time = max(0, pgd_hv.y);
		if (!msd[0]) {
			selecting = false;
		}
	} else {
		if (msc(0) && gd_hvd) {

			selecting = true;
			cur.t_sel = cur.time = pgd_hv.y;
			if (cur.play) { cur.time = min(cur.time, cur.t_stop); }
			cur.cvs->Discard(cur);
			

			auto tmp = &*cur.layers[pgd_hv.x];
			if (&lysel != tmp) {
				if (posel) { 
					osel.Discard(cur); 
					posel = NULL;
				}
				cur.layer_sel = tmp;
			}
		}
	}

	if (cur.play && cur.follow_play) {
		tl_rel.y = (-tm + 32) * hbox;
		tl_rel.y = min(tl_rel.y, 0.0);
	}
}
void Timeline::Render(Cur& cur) {
	draw_rect_raw(scr, tl, w, h, vp(), {});

	// 竖直方向减 2 主要是为了给图层显示空出位置。
	dvec ij_tl = -(dvec)tl_rel / dvec(wbox, hbox);
	int nx = w / wbox + 1;
	int ny = h / hbox + 1 - 2;
	nx = min<int>(nx, cur.layers.size() - ij_tl.x);

	// 肯定有更好的画法的，非常需要优化。
	int y = (cur.t_stop - ij_tl.y + 2) * hbox;
	draw_rect_raw(scr, tl + dvec(0, y + 1),
		w, hbox - 1, vp(), dcol(160, 160, 0));
	y = (cur.time - ij_tl.y + 2) * hbox;
	draw_rect_raw(scr, tl + dvec(0, y + 1), 
		w, hbox - 1, vp(), dcol(0, 160, 0));


	int t0 = min(cur.time, cur.t_sel);
	int t1 = max(cur.time, cur.t_sel);

	rep(i, 0, nx) rep(j, 0, ny) {
		auto pgd = dvec(i, j) + ij_tl;
		auto& ly = *cur.layers[pgd.x];

		dcol c;
		bool circ = false;
		bool xsel = &lysel == &ly;
		bool ysel = cur.time == pgd.y;
		bool mult = !cur.play &&
			pgd.y >= t0 && pgd.y <= t1;
		bool copy = cur.copy &&
			pgd.y >= cur.t0_copy && pgd.y <= cur.t1_copy;
		bool frame = pgd.y < ly.frs.size() && ly.frs[pgd.y];

		if (frame) { c = dcol(120); circ = true; }
		if (xsel) { c = frame ? dcol(200, 0, 200) : dcol(60, 0, 60); }

		if (cur.t_stop == pgd.y) { c = dcol(160, 160, 0); }
		if (ysel) { c = dcol(0, 160, 0); }
		if (xsel && copy) { 
			c = frame ? dcol(0, 120, 200) : dcol(0, 60, 100); 
		}
		if (xsel && mult) { 
			c = frame ? dcol(0, 160, 0) : dcol(0, 60, 0); 
		}
		if (xsel && ysel) { c = dcol(255, 0, 0); }
		if (gd_hvd && pgd == pgd_hv) { c = dcol(0, 0, 255); }
		dvec tl_box = tl + dvec(i * wbox, (j + 2) * hbox);
		// 下面的画框算法当然可以简化。
		draw_px_rect_framed_raw(scr, tl_box, wbox, hbox, vp(), c, dcol(70));
		if (circ) {
			vec2 ct = (vec2)tl_box + vec2(8, hbox / 2);
			draw_eclipse(scr, dscr, dep, ct, 4, 4, vp(), {});
		}
	}

	rep(j, 0, ny) {
		int id = j + ij_tl.y;
		int y = (j + 2) * hbox;
		if (id % cur.frame_rate == 0) {
			draw_px_seg(scr, dscr, 
				tl + dvec(0, y), tl + dvec(w, y), dep, vp(), dcol(150));

			wstring s = tw(id / cur.frame_rate);
			dvec tl_str = dvec(tl.x + w - 5 - str_wh(s, ft, 0).x, y + 1);
			draw_str(scr, dscr, 999, s, dcol(255), ft, tl_str, 0, vp());
		}
	}

	draw_px_rect_framed(scr, dscr, dep, tl, w, 2 * hbox, vp(), {}, dcol(150));
	rep(i, 0, nx) {
		int id = i + ij_tl.x;
		int x = i * wbox;
		draw_px_rect_framed_raw(scr, tl + dvec(x, 0), 
			wbox, 2 * hbox, vp(), cur.layers[id]->c, dcol(150));
	}

	draw_px_seg(scr, dscr,
		tl + dvec(nx * wbox, 2 * hbox), 
		tl + dvec(nx * wbox, h), dep, vp(), dcol(150));
	// 下面的一定是可以优化的。
	draw_px_rect_frame(scr, dscr, dep, tl, w, h, vp(), dcol(150));
}
void Timeline::PreUpdate(Cur& cur) {
	bool ok = dhv <= dep && insd(msp, vp());
	if (ok) { dhv = dep; hvd = this; }
}
