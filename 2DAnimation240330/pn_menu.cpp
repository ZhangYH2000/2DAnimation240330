#include "pn_menu.h"
#include "ui.h"
#include "cur.h"
#include "canvas.h"
#include "fpn_global.h"
#include "fpn_cmd.h"
#include "fpn_par.h"
#include "fpn_lang.h"
#include "fpn_about.h"
#include "fpn_curve.h"
#include "fpn_canvas.h"
#include "fpn_object.h"
#include "fpn_layer.h"
#include "fpn_objects.h"

#define cur (*(Cur*)&app)
#include "my_def.h"
#define mkbt(nm) mkp(bt_##nm)(&*ui.fpn_##nm);

BtPause::BtPause() : Button(150) {}
void BtPause::Update(App& app) {
	txt = !cur.play ? loc(L"start") : loc(L"pause");
	Button::Update(app);
}
void BtPause::OnClick(App& app) { cur.play_pause(); }

BtMute::BtMute() : Button(150) {}
void BtMute::Update(App& app) {
	txt = cur.mute ? loc(L"unmute") : loc(L"mute");
	Button::Update(app);
}
void BtMute::OnClick(App& app) { cur.mute = !cur.mute; }

BtMainMenu::BtMainMenu() : BtLan(150, L"bt_main_menu") {}
void BtMainMenu::OnClick(App& app) {
	ui.pn_menu->set_c(app, &*ui.pn_menu->cly_main);
}

BtCanvas::BtCanvas() : BtLan(150, L"bt_canvas") {}
void BtCanvas::OnClick(App& app) {
	ui.pn_menu->set_c(app, &*ui.pn_menu->cly_canvas);
	ui.fpn_canvas->show(app);
}

BtCvsBrush::BtCvsBrush() : BtLan(150, L"bt_cvs_brush") {}
void BtCvsBrush::Update(App& app) {
	c_normal = cur.cvs->mode == CVS_BRUSH ? 
		dcol(60, 150, 60) : dcol(80);
	BtLan::Update(app);
}
void BtCvsBrush::OnClick(App& app) {
	cur.cvs->mode = CVS_BRUSH;
	ui.fpn_canvas->show(app);
}
BtCvsBezier::BtCvsBezier() : BtLan(150, L"bt_cvs_bezier") {}
void BtCvsBezier::Update(App& app) {
	c_normal = cur.cvs->mode == CVS_BEZIER ?
		dcol(60, 150, 60) : dcol(80);
	BtLan::Update(app);
}
void BtCvsBezier::OnClick(App& app) {
	cur.cvs->mode = CVS_BEZIER;
	ui.fpn_canvas->show(app);
}
BtCvsAnim::BtCvsAnim() : BtLan(150, L"bt_cvs_anim") {}
void BtCvsAnim::Update(App& app) {
	c_normal = cur.cvs->mode == CVS_ANIM ?
		dcol(60, 150, 60) : dcol(80);
	BtLan::Update(app);
}
void BtCvsAnim::OnClick(App& app) {
	cur.cvs->mode = CVS_ANIM;
	ui.fpn_canvas->show(app);
}
BtCvsText::BtCvsText() : BtLan(150, L"bt_cvs_text") {}
void BtCvsText::Update(App& app) {
	c_normal = cur.cvs->mode == CVS_TEXT ?
		dcol(60, 150, 60) : dcol(80);
	BtLan::Update(app);
}
void BtCvsText::OnClick(App& app) {
	cur.cvs->mode = CVS_TEXT;
	ui.fpn_canvas->show(app);
}
BtCvsEllipse::BtCvsEllipse() : BtLan(150, L"bt_cvs_ellipse") {}
void BtCvsEllipse::Update(App& app) {
	c_normal = cur.cvs->mode == CVS_ELLIPSE ?
		dcol(60, 150, 60) : dcol(80);
	BtLan::Update(app);
}
void BtCvsEllipse::OnClick(App& app) {
	cur.cvs->mode = CVS_ELLIPSE;
	ui.fpn_canvas->show(app);
}
BtCvsEraser::BtCvsEraser() : BtLan(150, L"bt_cvs_eraser") {}
void BtCvsEraser::Update(App& app) {
	c_normal = cur.cvs->mode == CVS_ERASE ?
		dcol(60, 150, 60) : dcol(80);
	BtLan::Update(app);
}
void BtCvsEraser::OnClick(App& app) {
	cur.cvs->mode = CVS_ERASE;
	ui.fpn_canvas->show(app);
}
BtCvsFill::BtCvsFill() : BtLan(150, L"bt_cvs_fill") {}
void BtCvsFill::Update(App& app) {
	c_normal = cur.cvs->mode == CVS_FILL ?
		dcol(60, 150, 60) : dcol(80);
	BtLan::Update(app);
}
void BtCvsFill::OnClick(App& app) {
	cur.cvs->mode = CVS_FILL;
	ui.fpn_canvas->show(app);
}

PnMenu::PnMenu(App& app) : Panel(Panel::menu(app)) {
	vector<Control*> tmp;
	mkp(bt_pause)();
	mkp(bt_mute)();
	mkbt(global);
	mkp(bt_canvas)(); 
	mkbt(object); mkbt(objects);
	mkbt(layer);
	mkbt(curve);
	mkbt(cmd); mkbt(par);
	mkbt(lang); mkbt(about);

	tmp = { &*bt_pause, &*bt_mute,
	&*bt_global, &*bt_canvas, &*bt_object, 
	&*bt_objects, &*bt_layer, &*bt_curve,
	&*bt_cmd, &*bt_par, &*bt_lang, &*bt_about };
	mkcl(cly_main);

	mkp(bt_main_menu)();
	mkp(bt_brush)();
	mkp(bt_bezier)();
	mkp(bt_anim)();
	mkp(bt_text)();
	mkp(bt_ellipse)();
	mkp(bt_eraser)();
	mkp(bt_fill)();
	tmp = { &*bt_main_menu, &*bt_brush, &*bt_bezier,
		&*bt_anim, &*bt_text, &*bt_ellipse, &*bt_eraser, &*bt_fill };
	mkcl(cly_canvas);

	cly = cly_main; c = &*cly; Init(app);
}
