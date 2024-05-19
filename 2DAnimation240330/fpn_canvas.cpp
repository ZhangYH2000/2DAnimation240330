#include "fpn_canvas.h"
#include "ui.h"
#include "cur.h"
#include "anm.h"
#include "anim.h"
#include "bezier.h"
#include "canvas.h"
#include "draw_geo.h"

#define cur (*(Cur*)&app)
#include "my_def.h"

int constexpr min_thick = 5;
int constexpr max_thick = 60;

DbXRBorder::DbXRBorder() : DbXLan(L"dbx_r_border", 240) {}
void DbXRBorder::Sync(App& app) {
	double tmp = cur.cvs->c_border.r / 255.0;
	set_nx_rel(tmp);
}
void DbXRBorder::Upload(App& app) const {
	cur.cvs->c_border.r = 255 * uval();
}
TbRBorder::TbRBorder() : Textbox(50) {}
void TbRBorder::Sync(App& app) {
	str = tw(cur.cvs->c_border.r);
}
void TbRBorder::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, 0, 255);
	cur.cvs->c_border.r = tmp;
}
DbXGBorder::DbXGBorder() : DbXLan(L"dbx_g_border", 240) {}
void DbXGBorder::Sync(App& app) {
	double tmp = cur.cvs->c_border.g / 255.0;
	set_nx_rel(tmp);
}
void DbXGBorder::Upload(App& app) const {
	cur.cvs->c_border.g = 255 * uval();
}
TbGBorder::TbGBorder() : Textbox(50) {}
void TbGBorder::Sync(App& app) {
	str = tw(cur.cvs->c_border.g);
}
void TbGBorder::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, 0, 255);
	cur.cvs->c_border.g = tmp;
}
DbXBBorder::DbXBBorder() : DbXLan(L"dbx_b_border", 240) {}
void DbXBBorder::Sync(App& app) {
	double tmp = cur.cvs->c_border.b / 255.0;
	set_nx_rel(tmp);
}
void DbXBBorder::Upload(App& app) const {
	cur.cvs->c_border.b = 255 * uval();
}
TbBBorder::TbBBorder() : Textbox(50) {}
void TbBBorder::Sync(App& app) {
	str = tw(cur.cvs->c_border.b);
}
void TbBBorder::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, 0, 255);
	cur.cvs->c_border.b = tmp;
}
OtBorder::OtBorder() {
	gap = { 10, 10 }; dep = 1000;
	w = 150; h = 30;
}
int OtBorder::GetW() const { return w + gap.x; }
int OtBorder::GetH() const { return h + gap.y; }
void OtBorder::render(App& app) {
	draw_rect_raw(scr, tl, w, h, vp, cur.cvs->c_border);
}
void OtBorder::Update(App& app) {
	render(app);
}

DbXThick::DbXThick() : DbXLan(L"dbx_thick", 240) {}
void DbXThick::Sync(App& app) {
	double tmp =
		double(cur.cvs->thick - min_thick) / (max_thick - min_thick);
	set_nx_rel(tmp);
}
void DbXThick::Upload(App& app) const {
	int tmp =
		min_thick + (max_thick - min_thick) * uval();
	cur.cvs->thick = tmp;
}
TbThick::TbThick() : Textbox(50) {}
void TbThick::Sync(App& app) {
	str = tw(cur.cvs->thick);
}
void TbThick::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, min_thick, max_thick);
	cur.cvs->thick = tmp;
}
CbSinglePx::CbSinglePx() : CbLan(L"cb_single_px") {}
void CbSinglePx::Sync(App& app) {
	checked = cur.cvs->single_px;
}
void CbSinglePx::Upload(App& app) const {
	cur.cvs->single_px = checked;
}

DbXRInner::DbXRInner() : DbXLan(L"dbx_r_inner", 240) {}
void DbXRInner::Sync(App& app) {
	double tmp = cur.cvs->c_inner.r / 255.0;
	set_nx_rel(tmp);
}
void DbXRInner::Upload(App& app) const {
	cur.cvs->c_inner.r = 255 * uval();
}
TbRInner::TbRInner() : Textbox(50) {}
void TbRInner::Sync(App& app) {
	str = tw(cur.cvs->c_inner.r);
}
void TbRInner::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, 0, 255);
	cur.cvs->c_inner.r = tmp;
}
DbXGInner::DbXGInner() : DbXLan(L"dbx_g_inner", 240) {}
void DbXGInner::Sync(App& app) {
	double tmp = cur.cvs->c_inner.g / 255.0;
	set_nx_rel(tmp);
}
void DbXGInner::Upload(App& app) const {
	cur.cvs->c_inner.g = 255 * uval();
}
TbGInner::TbGInner() : Textbox(50) {}
void TbGInner::Sync(App& app) {
	str = tw(cur.cvs->c_inner.g);
}
void TbGInner::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, 0, 255);
	cur.cvs->c_inner.g = tmp;
}
DbXBInner::DbXBInner() : DbXLan(L"dbx_b_inner", 240) {}
void DbXBInner::Sync(App& app) {
	double tmp = cur.cvs->c_inner.b / 255.0;
	set_nx_rel(tmp);
}
void DbXBInner::Upload(App& app) const {
	cur.cvs->c_inner.b = 255 * uval();
}
TbBInner::TbBInner() : Textbox(50) {}
void TbBInner::Sync(App& app) {
	str = tw(cur.cvs->c_inner.b);
}
void TbBInner::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, 0, 255);
	cur.cvs->c_inner.b = tmp;
}

OtInner::OtInner() {
	gap = { 10, 10 }; dep = 1000;
	w = 150; h = 30;
}
int OtInner::GetW() const { return w + gap.x; }
int OtInner::GetH() const { return h + gap.y; }
void OtInner::render(App& app) {
	draw_rect_raw(scr, tl, w, h, vp, cur.cvs->c_inner);
}
void OtInner::Update(App& app) {
	render(app);
}

CbDrawInner::CbDrawInner() : CbLan(L"cb_draw_inner") {}
void CbDrawInner::Sync(App& app) {
	checked = cur.cvs->draw_inner;
}
void CbDrawInner::Upload(App& app) const {
	cur.cvs->draw_inner = checked;
}
CbDrawBorder::CbDrawBorder() : CbLan(L"cb_draw_border") {}
void CbDrawBorder::Sync(App& app) {
	checked = cur.cvs->draw_border;
}
void CbDrawBorder::Upload(App& app) const {
	cur.cvs->draw_border = checked;
}

BtNmAnim::BtNmAnim() : BtLan(80, L"bt_nm_anim") {}
void BtNmAnim::OnClick(App& app) {
	auto path = ui.fpn_canvas->dg_canvas->tb_nm_anim->str;
	anim t;
	auto typ = ext_nm(path);
	if (typ == L"anm") {
		t = anim(anm(path));
	} else {
		t = anim(path);
	}

	if (t.w && t.h && !t.ts.empty() && t.frame_rate >= 2) { 
		// 这个 name 只是显示用的，不知道显示完整路径是不是最好的选择。
		// 其实显示当前时刻也不是不行啊，这里可以考虑改的。
		
		cur.cvs->nm_an = path;
		cur.cvs->an = msh<anim>(t);
		
		
	}
}
void LbNmAnim::Sync(App& app) {
	if (!cur.cvs->an) { txt = loc(L"no_anim"); }
	else {
		txt = loc(L"loaded_anim") + cur.cvs->nm_an;
	}
}

int constexpr min_h_text = 5;
int constexpr max_h_text = 120;

DbXHText::DbXHText() : DbXLan(L"dbx_h_text", 240) {}
void DbXHText::Sync(App& app) {
	double tmp =
		double(cur.cvs->h_text - min_h_text) /
		(max_h_text - min_h_text);
	set_nx_rel(tmp);
}
void DbXHText::Upload(App& app) const {
	int tmp = min_h_text +
		uval() * (max_h_text - min_h_text);
	cur.cvs->h_text = tmp;
}
TbHText::TbHText() : Textbox(50) {}
void TbHText::Sync(App& app) {
	str = tw(cur.cvs->h_text);
}
void TbHText::OnDone(App& app) const {
	cur.cvs->h_text = 
		clmp<int>(wtof(str), min_h_text, max_h_text);
}

RTbText::RTbText() : RichTextbox(360, 200) {}
void RTbText::Sync(App& app) {
	str = cur.cvs->text;
}
void RTbText::Upload(App& app) const {
	cur.cvs->text = str;
}

CbClosedCurve::CbClosedCurve() : CbLan(L"cb_closed_curve") {}
void CbClosedCurve::Sync(App& app) {
	checked = cur.cvs->bz->closed;
}
void CbClosedCurve::Upload(App& app) const {
	cur.cvs->bz->closed = checked;
}

DgCanvas::DgCanvas() {
	vector<Control*> tmp;
	mkp(dbx_r_border)(); mkp(tb_r_border)();
	tmp = { &*dbx_r_border, &*tb_r_border };
	mkcl(clx_r_border);
	mkp(dbx_g_border)(); mkp(tb_g_border)();
	tmp = { &*dbx_g_border, &*tb_g_border };
	mkcl(clx_g_border);
	mkp(dbx_b_border)(); mkp(tb_b_border)();
	tmp = { &*dbx_b_border, &*tb_b_border };
	mkcl(clx_b_border);
	mkp(ot_border)();

	mkp(dbx_thick)(); mkp(tb_thick)();
	tmp = { &*dbx_thick, &*tb_thick };
	mkcl(clx_thick);
	mkp(cb_single_px)();

	mkp(dbx_r_inner)(); mkp(tb_r_inner)();
	tmp = { &*dbx_r_inner, &*tb_r_inner };
	mkcl(clx_r_inner);
	mkp(dbx_g_inner)(); mkp(tb_g_inner)();
	tmp = { &*dbx_g_inner, &*tb_g_inner };
	mkcl(clx_g_inner);
	mkp(dbx_b_inner)(); mkp(tb_b_inner)();
	tmp = { &*dbx_b_inner, &*tb_b_inner };
	mkcl(clx_b_inner);
	mkp(ot_inner)();
	mkp(cb_draw_inner)(); mkp(cb_draw_border)();

	mkp(tb_nm_anim)(270); mkp(bt_nm_anim)();
	tmp = { &*tb_nm_anim, &*bt_nm_anim };
	mkcl(clx_nm_anim);
	mkp(lb_nm_anim)();

	mkp(dbx_h_text)(); mkp(tb_h_text)();
	tmp = { &*dbx_h_text, &*tb_h_text };
	mkcl(clx_h_text);
	mkp(rtb_text)();

	mkp(cb_closed_curve)();

	tmp = { &*clx_r_border, &*clx_g_border, &*clx_b_border,
		&*ot_border, &*clx_thick, &*cb_single_px };
	mkcl(cly_brush);
	tmp = { &*cb_draw_border,
		&*clx_r_border, &*clx_g_border, &*clx_b_border,
		&*ot_border, &*clx_thick, &*cb_single_px,
		&*cb_draw_inner,
		&*clx_r_inner, &*clx_g_inner, &*clx_b_inner,
		&*ot_inner, &*cb_closed_curve };
	mkcl(cly_bezier);
	tmp = { &*clx_nm_anim, &*lb_nm_anim };
	mkcl(cly_anim);
	tmp = { &*clx_r_border, &*clx_g_border, &*clx_b_border,
		&*ot_border, &*clx_h_text, &*rtb_text };
	mkcl(cly_text);
	tmp = { &*clx_r_border, &*clx_g_border, &*clx_b_border,
		&*ot_border, &*clx_thick, &*cb_single_px,
		&*clx_r_inner, &*clx_g_inner, &*clx_b_inner,
		&*ot_inner,&*cb_draw_inner, &*cb_draw_border };
	mkcl(cly_ellipse);
	tmp = { &*clx_thick };
	mkcl(cly_eraser);
	tmp = { &*clx_r_inner, &*clx_g_inner, &*clx_b_inner, &*ot_inner};
	mkcl(cly_fill);
}
void DgCanvas::Update(App& app) {
	switch (cur.cvs->mode) {
	case CVS_BRUSH: set_c(app, &*cly_brush); break;
	case CVS_BEZIER: set_c(app, &*cly_bezier); break;
	case CVS_ANIM: set_c(app, &*cly_anim); break;
	case CVS_TEXT: set_c(app, &*cly_text); break;
	case CVS_ELLIPSE: set_c(app, &*cly_ellipse); break;
	case CVS_ERASE: set_c(app, &*cly_eraser); break;
	case CVS_FILL: set_c(app, &*cly_fill); break;
	} Delegate::Update(app);
}

FPnCanvas::FPnCanvas(App& app) : FPnLan(app, 400, 600, L"fpn_canvas") {
	vector<Control*> tmp;
	mkp(dg_canvas)();

	tmp = { &*dg_canvas };
	mkcl(cly); c = &*cly; Init(app);
}
