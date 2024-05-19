#include "fpn_object.h"
#include "ui.h"
#include "cur.h"
#include "layer.h"
#include "frame.h"
#include "object.h"
#include "draw_geo.h"

#define cur (*(Cur*)&app)
#include "my_def.h"

int constexpr min_thick = 5;
int constexpr max_thick = 60;

BtCancelOb::BtCancelOb() : BtLan(200, L"bt_cancel_ob") {}
void BtCancelOb::Update(App& app) {
	enabled = posel;
	BtLan::Update(app);
}
void BtCancelOb::OnClick(App& app) {
	if (posel) {
		osel.Discard(cur);
		posel = NULL;
	}
}

DbXRBorderOb::DbXRBorderOb() : DbXLan(L"dbx_r_border", 240) {}
void DbXRBorderOb::Sync(App& app) {
	double tmp = osel.c_border.r / 255.0;
	set_nx_rel(tmp);
}
void DbXRBorderOb::Upload(App& app) const {
	osel.c_border.r = 255 * uval();
}
TbRBorderOb::TbRBorderOb() : Textbox(50) {}
void TbRBorderOb::Sync(App& app) {
	str = tw(osel.c_border.r);
}
void TbRBorderOb::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, 0, 255);
	osel.c_border.r = tmp;
}
DbXGBorderOb::DbXGBorderOb() : DbXLan(L"dbx_g_border", 240) {}
void DbXGBorderOb::Sync(App& app) {
	double tmp = osel.c_border.g / 255.0;
	set_nx_rel(tmp);
}
void DbXGBorderOb::Upload(App& app) const {
	osel.c_border.g = 255 * uval();
}
TbGBorderOb::TbGBorderOb() : Textbox(50) {}
void TbGBorderOb::Sync(App& app) {
	str = tw(osel.c_border.g);
}
void TbGBorderOb::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, 0, 255);
	osel.c_border.g = tmp;
}
DbXBBorderOb::DbXBBorderOb() : DbXLan(L"dbx_b_border", 240) {}
void DbXBBorderOb::Sync(App& app) {
	double tmp = osel.c_border.b / 255.0;
	set_nx_rel(tmp);
}
void DbXBBorderOb::Upload(App& app) const {
	osel.c_border.b = 255 * uval();
}
TbBBorderOb::TbBBorderOb() : Textbox(50) {}
void TbBBorderOb::Sync(App& app) {
	str = tw(osel.c_border.b);
}
void TbBBorderOb::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, 0, 255);
	osel.c_border.b = tmp;
}
OtBorderOb::OtBorderOb() {
	gap = { 10, 10 }; dep = 1000;
	w = 150; h = 30;
}
int OtBorderOb::GetW() const { return w + gap.x; }
int OtBorderOb::GetH() const { return h + gap.y; }
void OtBorderOb::render(App& app) {
	draw_rect_raw(scr, tl, w, h, vp, osel.c_border);
}
void OtBorderOb::Update(App& app) {
	render(app);
}

DbXThickOb::DbXThickOb() : DbXLan(L"dbx_thick", 240) {}
void DbXThickOb::Sync(App& app) {
	double tmp =
		double(osel.thick - min_thick) / (max_thick - min_thick);
	set_nx_rel(tmp);
}
void DbXThickOb::Upload(App& app) const {
	int tmp =
		min_thick + (max_thick - min_thick) * uval();
	osel.thick = tmp;
}
TbThickOb::TbThickOb() : Textbox(50) {}
void TbThickOb::Sync(App& app) {
	str = tw(osel.thick);
}
void TbThickOb::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, min_thick, max_thick);
	osel.c_inner.b = tmp;
}
CbSinglePxOb::CbSinglePxOb() : CbLan(L"cb_single_px") {}
void CbSinglePxOb::Sync(App& app) {
	checked = osel.single_px;
}
void CbSinglePxOb::Upload(App& app) const {
	osel.single_px = checked;
}

DbXRInnerOb::DbXRInnerOb() : DbXLan(L"dbx_r_inner", 240) {}
void DbXRInnerOb::Sync(App& app) {
	double tmp = osel.c_inner.r / 255.0;
	set_nx_rel(tmp);
}
void DbXRInnerOb::Upload(App& app) const {
	osel.c_inner.r = 255 * uval();
}
TbRInnerOb::TbRInnerOb() : Textbox(50) {}
void TbRInnerOb::Sync(App& app) {
	str = tw(osel.c_inner.r);
}
void TbRInnerOb::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, 0, 255);
	osel.c_inner.r = tmp;
}
DbXGInnerOb::DbXGInnerOb() : DbXLan(L"dbx_g_inner", 240) {}
void DbXGInnerOb::Sync(App& app) {
	double tmp = osel.c_inner.g / 255.0;
	set_nx_rel(tmp);
}
void DbXGInnerOb::Upload(App& app) const {
	osel.c_inner.g = 255 * uval();
}
TbGInnerOb::TbGInnerOb() : Textbox(50) {}
void TbGInnerOb::Sync(App& app) {
	str = tw(osel.c_inner.g);
}
void TbGInnerOb::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, 0, 255);
	osel.c_inner.g = tmp;
}
DbXBInnerOb::DbXBInnerOb() : DbXLan(L"dbx_b_inner", 240) {}
void DbXBInnerOb::Sync(App& app) {
	double tmp = osel.c_inner.b / 255.0;
	set_nx_rel(tmp);
}
void DbXBInnerOb::Upload(App& app) const {
	osel.c_inner.b = 255 * uval();
}
TbBInnerOb::TbBInnerOb() : Textbox(50) {}
void TbBInnerOb::Sync(App& app) {
	str = tw(osel.c_inner.b);
}
void TbBInnerOb::OnDone(App& app) const {
	int tmp = wtof(str);
	tmp = clmp(tmp, 0, 255);
	osel.c_inner.b = tmp;
}

OtInnerOb::OtInnerOb() {
	gap = { 10, 10 }; dep = 1000;
	w = 150; h = 30;
}
int OtInnerOb::GetW() const { return w + gap.x; }
int OtInnerOb::GetH() const { return h + gap.y; }
void OtInnerOb::render(App& app) {
	draw_rect_raw(scr, tl, w, h, vp, osel.c_inner);
}
void OtInnerOb::Update(App& app) {
	render(app);
}

CbDrawInnerOb::CbDrawInnerOb() : CbLan(L"cb_draw_inner") {}
void CbDrawInnerOb::Sync(App& app) {
	checked = osel.draw_inner;
}
void CbDrawInnerOb::Upload(App& app) const {
	osel.draw_inner = checked;
}
CbDrawBorderOb::CbDrawBorderOb() : CbLan(L"cb_draw_border") {}
void CbDrawBorderOb::Sync(App& app) {
	checked = osel.draw_border;
}
void CbDrawBorderOb::Upload(App& app) const {
	osel.draw_border = checked;
}

CbCurveOb::CbCurveOb() : CbLan(L"cb_curve_ob") {}
void CbCurveOb::Sync(App& app) {
	checked = osel.use_curve;
}
void CbCurveOb::Upload(App& app) const {
	osel.use_curve = checked;
}
TbCurveOb::TbCurveOb() : TbLan(L"tb_curve_ob", 200) {}
void TbCurveOb::Sync(App& app) {
	str = osel.nm_curve;
}
void TbCurveOb::OnDone(App& app) const {
	osel.nm_curve = str;
}

TbSpeedOb::TbSpeedOb() : TbLan(L"tb_speed_ob", 80) {}
void TbSpeedOb::Sync(App& app) {
	str = tw2(osel.speed);
}
void TbSpeedOb::OnDone(App& app) const {
	osel.speed = max(0.0, wtof(str));
}

DgObject::DgObject() {
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

	mkp(cb_curve)(); mkp(tb_curve)(); mkp(tb_speed)();

	tmp = { &*cb_draw_border,
		&*clx_r_border, &*clx_g_border, &*clx_b_border,
		&*ot_border, &*cb_single_px, &*clx_thick,
		&*cb_draw_inner,
		&*clx_r_inner, &*clx_g_inner, &*clx_b_inner,
		&*ot_inner };
	mkcl(cly_bezier);
	tmp = { &*cb_curve, &*tb_curve, &*tb_speed };
	mkcl(cly_anim);
	tmp = { &*cb_draw_border,
		&*clx_r_border, &*clx_g_border, &*clx_b_border,
		&*ot_border, &*cb_single_px, &*clx_thick,
		&*cb_draw_inner,
		&*clx_r_inner, &*clx_g_inner, &*clx_b_inner,
		&*ot_inner };
	mkcl(cly_ellipse);
}
void DgObject::Update(App& app) {
	if (!posel) { set_c(app, NULL); }
	else {
		switch (osel.typ) {
		case OB_BEZIER: set_c(app, &*cly_bezier); break;
		case OB_ANIM: set_c(app, &*cly_anim); break;
		case OB_ELLIPSE: set_c(app, &*cly_ellipse); break;
		}
	}
	Delegate::Update(app);
}

#define obif (*lysel.frs[tm]->obs[posel])

CbShowOb::CbShowOb() : CbLan(L"cb_show_ob") {}
void CbShowOb::Sync(App& app) {
	checked = obif.show;
}
void CbShowOb::Upload(App& app) const {
	obif.show = checked;
}

DbXTCurveOb::DbXTCurveOb() : DbXLan(L"dbx_t_curve_ob", 240) {}
void DbXTCurveOb::Sync(App& app) {
	set_nx_rel(obif.t_curve);
}
void DbXTCurveOb::Upload(App& app) const {
	obif.t_curve = uval();
}
TbTCurveOb::TbTCurveOb() : Textbox(50) {}
void TbTCurveOb::Sync(App& app) {
	str = tw2(obif.t_curve);
}
void TbTCurveOb::OnDone(App& app) const {
	obif.t_curve = wtof(str);
}

DgObInfo::DgObInfo() {
	vector<Control*> tmp;

	mkp(cb_show)(); 
	mkp(dbx_t_curve)();
	mkp(tb_t_curve)();
	tmp = { &*dbx_t_curve, &*tb_t_curve };
	mkcl(clx_t_curve);
	tmp = { &*cb_show, &*clx_t_curve };
	mkcl(cly);
}
void DgObInfo::Update(App& app) {
	bool ok = posel && !cur.play &&
		tm < lysel.frs.size() && lysel.frs[tm];
	set_c(app, ok ? &*cly : NULL);
	Delegate::Update(app);
}

FPnObject::FPnObject(App& app) : FPnLan(app, 400, 600, L"fpn_object") {
	vector<Control*> tmp;
	mkp(bt_cancel)();
	mkp(dg_object)();
	mkp(dg_ob_info)();
	tmp = { &*bt_cancel, &*dg_object, &*dg_ob_info };

	mkcl(cly); c = &*cly; Init(app);
}
