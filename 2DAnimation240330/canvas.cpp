#include "canvas.h"
#include "cur.h"
#include "bgr.h"
#include "anim.h"
#include "frame.h"
#include "layer.h"
#include "bezier.h"
#include "object.h"
#include "timeline.h"
#include "draw_str.h"
#include "draw_geo.h"
#include "draw_tile.h"
#include "draw_fill.h"
#include "draw_curve.h"
#include "txt_cpnt_0.h"
#include "txt_cpnt_1.h"

#include "my_def.h"

double constexpr dep = 10;

Canvas::Canvas() {
	mkp(bz)();
	thick = 20;
	h_text = 20;

	mkp(cp0)(); mkp(cp1)();
}
void Canvas::Update(Cur& cur) {
	hovered = (hvd == this);
	wheeled = (whd == this);

	if (!moved) {
		moved = wheeled && msc(1);
	} else {
		moved = msd[1];
		bool ok = posel &&
			tm < lysel.frs.size() && lysel.frs[tm];
		if (ok) {
			auto& ob = *lysel.frs[tm]->obs[posel];
			if (ob.bz) {
				for (auto& vs : ob.bz->dat) for (auto& v : vs) {
					v += msp - msp_old;
				}
			}
			ob.ct += vec2(msp - msp_old);
		}
	}

	if (mode == CVS_BRUSH) {
		if (!brushed) {
			brushed = hovered && msc(0) && !cur.play;
		} else {
			brushed = msd[0];
			vec2 pa = (vec2)(msp_old - bgr.tl);
			vec2 pb = (vec2)(msp - bgr.tl);
			if (tm < lysel.frs.size() && lysel.frs[tm]) {
				draw_tiny_seg(lysel.frs[tm]->back, pa, pb,
					thick, lysel.frs[tm]->back.rect(), c_border);
				// 这里刷子的轨迹能不能搞得更精细一点，不知道之前贴图编辑器是怎么做的。
				// 我感觉是不是要直接处理 MouseMove Event 才行。
			}
		}
	}
	if (mode == CVS_ERASE) {
		if (!brushed) {
			brushed = hovered && msc(0) && !cur.play;
		} else {
			brushed = msd[0];
			vec2 pa = (vec2)(msp_old - bgr.tl);
			vec2 pb = (vec2)(msp - bgr.tl);
			if (tm < lysel.frs.size() && lysel.frs[tm]) {
				draw_tiny_seg_erase(lysel.frs[tm]->back, pa, pb,
					thick, lysel.frs[tm]->back.rect());
				// 这里刷子的轨迹能不能搞得更精细一点，不知道之前贴图编辑器是怎么做的。
			}
		}
	}
	if (mode == CVS_FILL) {
		if (hovered && msc(0) && !cur.play) {
			if (tm < lysel.frs.size() && lysel.frs[tm]) {
				// 不知道如果初始位置在视口外面能不能正常工作。
				// 这里我们规避这种情况。
				if (insd(msp, cur.rect())) {
					draw_fill(lysel.frs[tm]->back,
						msp - bgr.tl, cur.rect(), c_inner);
				}
			}
		}
	}
	if (mode == CVS_BEZIER) {
		if (hovered && msc(0) && !cur.play) {
			bool add =
				bz->dat.empty() || (!kb && kbd[L'N']);
			if (add) {
				bz->dat.push_back({ msp - bgr.tl });
			} else {
				bz->dat.back().push_back(msp - bgr.tl);
			}
		}

		if (!kb) {
			if (kbc(L'C') && !kbd[VK_CONTROL]) {
				bz->closed = !bz->closed;
			}
			if (kbc(VK_ESCAPE)) { bz->dat.clear(); }
			if (kbc(VK_RETURN)) {
				if (!bz->dat.empty()) {
					bool add =
						!bz->closed || (!kb && kbd[L'N']);
					if (add) {
						bz->dat.push_back({ msp - bgr.tl });
					} else {
						bz->dat.back().push_back(msp - bgr.tl);
					}

					auto ob = msh<Object>();
					for (auto& fr : lysel.frs) if (fr) {
						auto info = msh<ObInfo>();
						info->bz = msh<Bezier>(*bz);
						fr->obs[&*ob] = info;
					}
					ob->c_border = c_border;
					ob->c_inner = c_inner;
					ob->thick = thick;
					ob->single_px = single_px;
					ob->draw_border = draw_border;
					ob->draw_inner = draw_inner;
					ob->nm = loc(L"unnamed");
					ob->Load(cur, lysel);
					posel = &*ob;
					lysel.obs.push_back(ob);
					bz->dat.clear();
				}
			}
		}
	}
	if (mode == CVS_ELLIPSE) {
		if (ready) {
			w = (msp - bgr.tl - tl).x;
			h = (msp - bgr.tl - tl).y;

			if (!msd[0]) {
				ready = false;
				if (abs(w) >= 10 && abs(h) >= 10) {
					auto ob = msh<Object>();
					for (auto& fr : lysel.frs) if (fr) {
						auto info = msh<ObInfo>();
						info->ct = (vec2)tl + vec2(w, h) / 2;
						info->w = w; info->h = h;
						fr->obs[&*ob] = info;
					}
					ob->typ = OB_ELLIPSE;
					ob->c_border = c_border;
					ob->c_inner = c_inner;
					ob->thick = thick;
					ob->single_px = single_px;
					ob->draw_border = draw_border;
					ob->draw_inner = draw_inner;
					ob->nm = loc(L"unnamed");
					ob->Load(cur, lysel);
					posel = &*ob;
					lysel.obs.push_back(ob);
				}
			}
		} else {
			if (hovered && msc(0) && !cur.play) {
				// 以后这里准备加一个展开放缩的过程。
				// 这里用 tl 而不是 ct 主要是不会有旋转。
				ready = true;
				w = 0; h = 0;
				tl = msp - bgr.tl;
			}
		}
	}
	if (mode == CVS_ANIM) {
		if (ready) {
			w = (msp - bgr.tl - tl).x;
			h = (msp - bgr.tl - tl).y;

			if (!msd[0]) {
				ready = false;
				if (abs(w) >= 10 && abs(h) >= 10) {
					auto ob = msh<Object>();
					for (auto& fr : lysel.frs) if (fr) {
						auto info = msh<ObInfo>();
						info->ct = (vec2)tl + vec2(w, h) / 2;
						info->w = w; info->h = h;
						fr->obs[&*ob] = info;
					}
					ob->typ = OB_ANIM;
					ob->an = msh<anim>(*an);
					ob->nm = loc(L"unnamed");
					ob->Load(cur, lysel);
					posel = &*ob;
					lysel.obs.push_back(ob);
				}
			}
		} else {
			if (hovered && msc(0) && an && !cur.play) {
				// 以后这里准备加一个展开放缩的过程。
				// 这里用 tl 而不是 ct 主要是不会有旋转。
				ready = true;
				w = 0; h = 0;
				tl = msp - bgr.tl;
			}
		}
	}
	if (mode == CVS_TEXT) {
		if (stage == 0) {
			if (hovered && msc(0) && !cur.play) {
				tl = msp - bgr.tl; stage = 1;
			}
		} else if (stage == 1) {
			w = msp.x - bgr.tl.x - tl.x;
			if (!msd[0]) {
				stage = 2;
			}
		} else if (stage == 2) {
			cp0->Update(cur);
			cp1->Update(cur);

			if (!kb && kbc(VK_ESCAPE)) {
				stage = 0;
			} else if (msc(0) && hovered) {
				// 这个条件在之前也应该体现。
				stage = 0;
				if (tm < lysel.frs.size() && lysel.frs[tm]) {
					auto& dest = lysel.frs[tm]->back;
					draw_str(dest, text, c_border,
						cur.big_ft, tl, w, dest.rect(), h_text);
				}
			}
		}
	}
}
void Canvas::Render(Cur& cur) {
	if (mode == CVS_BRUSH) {
		// 可以再加一些条件。比如正在画图中，或者鼠标悬浮。
		draw_eclipse(scr, dscr, dep,
			(vec2)msp, thick / 2, thick / 2, bgr.vp(), c_border);
	}
	if (mode == CVS_ERASE) {
		draw_px_circle(scr, dscr, dep, msp, thick / 2, bgr.vp(), dcol(0));
	}
	if (mode == CVS_BEZIER && !bz->dat.empty()) {
		auto tmp = *bz;
		bool add =
			!tmp.closed || (!kb && kbd[L'N']);
		if (add) {
			tmp.dat.push_back({ msp - bgr.tl });
		} else {
			tmp.dat.back().push_back(msp - bgr.tl);
		}

		if (draw_inner) {
			draw_fill_bezier(scr, dscr,
				dep, bgr.tl, tmp, bgr.vp(), c_inner);
		}
		if (draw_border) {
			if (single_px) {
				draw_px_bezier(scr, dscr,
					dep, bgr.tl, tmp, bgr.vp(), c_border);
			}
			else {
				draw_bezier(scr, dscr,
					dep, bgr.tl, tmp, thick, bgr.vp(), c_border);
			}
		}
		draw_bezier_seg(scr, dscr, dep, bgr.tl, tmp, bgr.vp());
	}
	if (mode == CVS_ELLIPSE && ready) {
		vec2 ct = (vec2)(bgr.tl + tl) + vec2(w, h) / 2;
		if (draw_inner) {
			draw_eclipse(scr, ct,
				w / 2, h / 2, 0, bgr.vp(), c_inner);
		}
		if (draw_border) {
			if (single_px) {
				draw_px_eclipse_frame(scr, ct, 
					w / 2, h / 2, 0, bgr.vp(), c_border);
			} else {
				draw_eclipse_frame(scr, ct, 
					w / 2, h / 2, 0, bgr.vp(), thick, c_border);
			}
		}
	}
	if (mode == CVS_ANIM && ready) {
		vec2 ct = (vec2)(bgr.tl + tl) + vec2(w, h) / 2;
		int t = (tm * an->frame_rate / cur.frame_rate) % an->frame_rate;
		// 我感觉这种涉及到旋转的其实很影响帧率的啊，不知道有什么好的优化方法。
		draw_tile(scr, ct, w, h,
			mat2::id(), bgr.vp(), an->ts[t], an->ts[t].rect());
	}
	if (mode == CVS_TEXT && stage != 0) {
		draw_str(scr, text, c_border,
			cur.big_ft, tl + bgr.tl, w, bgr.vp(), h_text);

		if (stage == 2) {
			cp0->Render(cur); cp1->Render(cur);
		}
	}
}
void Canvas::Discard(Cur& cur) {
	moved = brushed = hovered = wheeled = ready = false;
	stage = 0;
	bz->dat.clear();
	cp0->Discard(cur); cp1->Discard(cur);
}
void Canvas::PreUpdate(Cur& cur) {
	bool ok = dhv <= dep && insd(msp, bgr.vp());
	if (ok) { dhv = dep; hvd = this; }

	ok = dwh <= dep && insd(msp, bgr.vp());
	if (ok) { dwh = dep; whd = this; }

	if (mode == CVS_TEXT && stage == 2) {
		cp0->PreUpdate(cur); cp1->PreUpdate(cur);
	}
}
