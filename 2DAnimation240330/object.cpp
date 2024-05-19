#include "object.h"
#include "cur.h"
#include "bgr.h"
#include "anm.h"
#include "anim.h"
#include "frame.h"
#include "layer.h"
#include "curve.h"
#include "bezier.h"
#include "ct_cpnt.h"
#include "v0_cpnt.h"
#include "v1_cpnt.h"
#include "v2_cpnt.h"
#include "v3_cpnt.h"
#include "bz_cpnt.h"
#include "rot_cpnt.h"
#include "timeline.h"
#include "draw_geo.h"
#include "draw_tile.h"
#include "draw_curve.h"

#include "my_def.h"

double constexpr dep = 10;

Object::Object() {
	thick = 20;
}
Object::Object(FILE* f) {
	int sz = 0;
	frd(typ); frdv(nm);
	frd(c_inner); frd(c_border);
	frd(thick); frd(single_px);
	frd(draw_inner); frd(draw_border);
	frd(use_curve); frdv(nm_curve);

	frd(sz);
	if (sz) { 
		mkp(an)((anim)(anm)f);
	}
	frd(speed);
}
void Object::Save(FILE* f) const {
	int sz = 0;
	fwt(typ); fwtv(nm);
	fwt(c_inner); fwt(c_border); 
	fwt(thick); fwt(single_px);
	fwt(draw_inner); fwt(draw_border);
	fwt(use_curve); fwtv(nm_curve);

	sz = (bool)an; fwt(sz);
	if (an) { anm(*an).save(f); }
	fwt(speed);
}
void Object::Load(Cur& cur, Layer& ly) {
	if (typ == OB_BEZIER) {
		auto bz = ly.frs[0]->obs[this]->bz;
		rep(i, 0, bz->dat.size()) {
			auto& vs = bz->dat[i];
			rep(j, 0, vs.size()) {
				auto cp = msh<BzCPnt>();
				cp->ob = this;
				cp->id_vs = i; cp->id_v = j;
				cpnts.push_back(cp);
			}
		}
	}
	if (typ == OB_ANIM || typ == OB_ELLIPSE) {
		{
			auto cp = msh<CtCPnt>();
			cp->ob = this;
			cpnts.push_back(cp);
		}
		{
			auto cp = msh<V0CPnt>();
			cp->ob = this;
			cpnts.push_back(cp);
		}
		{
			auto cp = msh<V1CPnt>();
			cp->ob = this;
			cpnts.push_back(cp);
		}
		{
			auto cp = msh<V2CPnt>();
			cp->ob = this;
			cpnts.push_back(cp);
		}
		{
			auto cp = msh<V3CPnt>();
			cp->ob = this;
			cpnts.push_back(cp);
		}
		{
			auto cp = msh<RotCPnt>();
			cp->ob = this;
			cpnts.push_back(cp);
		}
	}
}
void Object::Update(Cur& cur, Layer& ly) {
	bool valid =
		&ly == &lysel && !cur.play &&
		tm < ly.frs.size() && ly.frs[tm] &&
		(cur.edit_all || posel == this);
	if (!valid) { return; }
	auto& ob = *ly.frs[tm]->obs[this];

	bool seg = typ == OB_BEZIER;
	if (seg) {
		auto& bz = *ob.bz;
		draw_bezier_seg(scr, dscr, dep, bgr.tl, bz, bgr.vp());
	}

	bool rect = typ == OB_ANIM;
	if (rect) {
		// 下面可以优化。
		dvec p0 = dvec(ob.ct + mat2::rot(ob.ang) *
			vec2(-ob.w, -ob.h) / 2) + bgr.tl;
		dvec p1 = dvec(ob.ct + mat2::rot(ob.ang) *
			vec2(+ob.w, -ob.h) / 2) + bgr.tl;
		dvec p2 = dvec(ob.ct + mat2::rot(ob.ang) *
			vec2(+ob.w, +ob.h) / 2) + bgr.tl;
		dvec p3 = dvec(ob.ct + mat2::rot(ob.ang) *
			vec2(-ob.w, +ob.h) / 2) + bgr.tl;

		draw_px_segstrip(scr, dscr, dep,
			{ p0, p1, p2, p3, p0 }, bgr.vp(), dcol());
	}

	bool cv = use_curve &&
		cur.curves.find(nm_curve) != cur.curves.end();
	if (cv) {
		ob.ct = cur.curves[nm_curve]->at(ob.t_curve);
		cur.curves[nm_curve]->render(cur);
	}

	for (auto& cp : cpnts) { 
		// 这里控制点的渲染不放到渲染方法里面去，否则会在 bgr 里面执行。
		cp->Update(cur);  cp->Render(cur);
	}
}
void Object::Render(Cur& cur, Layer& ly) {
	auto ob = ly.interp(this, tm);
	if (!ob.show || !show) { return; }

	bool cv = use_curve &&
		cur.curves.find(nm_curve) != cur.curves.end();
	if (cv) { 
		ob.ct = cur.curves[nm_curve]->at(ob.t_curve);
	}

	if (typ == OB_BEZIER) {
		if (draw_inner) {
			draw_fill_bezier(scr, dscr, dep, 
				bgr.tl, *ob.bz, bgr.vp(), c_inner);
		}
		if (draw_border) {
			if (single_px) {
				draw_px_bezier(scr, dscr, dep, 
					bgr.tl, *ob.bz, bgr.vp(), c_border);
			} else {
				draw_bezier(scr, dscr, dep, 
					bgr.tl, *ob.bz, thick, bgr.vp(), c_border);
			}
		}
	}
	if (typ == OB_ANIM) {
		int id = speed * tm * an->frame_rate / cur.frame_rate;
		id %= an->ts.size();
		draw_tile(scr, ob.ct + (vec2)bgr.tl, ob.w, ob.h, 
			mat2::rot(ob.ang), bgr.vp(), an->ts[id], an->ts[id].rect());

	}
	if (typ == OB_ELLIPSE) {
		if (draw_inner) {
			draw_eclipse(scr, ob.ct + (vec2)bgr.tl,
				ob.w / 2, ob.h / 2, ob.ang, bgr.vp(), c_inner);
		}
		if (draw_border) {
			if (single_px) {
				draw_px_eclipse_frame(scr, ob.ct + (vec2)bgr.tl,
					ob.w / 2, ob.h / 2, ob.ang, bgr.vp(), c_border);
			}
			else {
				draw_eclipse_frame(scr, ob.ct + (vec2)bgr.tl,
					ob.w / 2, ob.h / 2, ob.ang, bgr.vp(), thick, c_border);
			}
		}
	}
}
void Object::Render(Cur& cur, Layer& ly, int t, tile& dest) {
	auto ob = ly.interp(this, t);
	if (!ob.show || !show) { return; }

	bool cv = use_curve &&
		cur.curves.find(nm_curve) != cur.curves.end();
	if (cv) {
		ob.ct = cur.curves[nm_curve]->at(ob.t_curve);
	}

	if (typ == OB_BEZIER) {
		if (draw_inner) {
			draw_fill_bezier(dest, {}, *ob.bz, dest.rect(), c_inner);
		}
		if (draw_border) {
			if (single_px) {
				draw_px_bezier(dest, {}, *ob.bz, dest.rect(), c_border);
			} else {
				draw_bezier(dest, {}, *ob.bz, thick, dest.rect(), c_border);
			}
		}
	}
	if (typ == OB_ANIM) {
		int id = speed * t * an->frame_rate / cur.frame_rate;
		id %= an->ts.size();
		draw_tile(dest, ob.ct, ob.w, ob.h, 
			mat2::rot(ob.ang), dest.rect(), an->ts[id], an->ts[id].rect());
	}
	if (typ == OB_ELLIPSE) {
		if (draw_inner) {
			draw_eclipse(dest, ob.ct,
				ob.w / 2, ob.h / 2, ob.ang, dest.rect(), c_inner);
		}
		if (draw_border) {
			if (single_px) {
				draw_px_eclipse_frame(dest, ob.ct,
					ob.w / 2, ob.h / 2, ob.ang, dest.rect(), c_border);
			} else {
				draw_eclipse_frame(dest, ob.ct,
					ob.w / 2, ob.h / 2, ob.ang, dest.rect(), thick, c_border);
			}
		}
	}
}
void Object::Discard(Cur& cur) {
	for (auto& cpnt : cpnts) { cpnt->Discard(cur); }
}
void Object::PreUpdate(Cur& cur, Layer& ly) {
	bool valid =
		&ly == &lysel && !cur.play &&
		tm < ly.frs.size() && ly.frs[tm] &&
		(cur.edit_all || posel == this);
	if (valid) for (auto& cp : cpnts) { cp->PreUpdate(cur); }
}


ObInfo::ObInfo(ObInfo const& ob) {
	if (ob.bz) {
		bz = msh<Bezier>(*ob.bz);
	}

	show = ob.show;
	ct = ob.ct; 
	ang = ob.ang;
	w = ob.w; h = ob.h;
	t_curve = ob.t_curve;
}
ObInfo::ObInfo(FILE* f) {
	int sz = 0;
	frd(sz); 
	if (sz) { mkp(bz)(f); }

	frd(show); frd(ct);
	frd(ang); frd(w); frd(h);
	frd(t_curve);
}
void ObInfo::Save(FILE* f) const {
	int sz = 0;
	sz = (bool)bz; fwt(sz);
	if (bz) { bz->Save(f); }

	fwt(show); fwt(ct);
	fwt(ang); fwt(w); fwt(h);
	fwt(t_curve);
}
