#include "fpn_curve.h"
#include "ui.h"
#include "cur.h"
#include "curve.h"
#include "curve_editor.h"

#define cur (*(Cur*)&app)
#include "my_def.h"
#define edi (*cur.cv_editor)

CbValidCurve::CbValidCurve() : CbLan(L"cb_valid_curve") {}
void CbValidCurve::Sync(App& app) {
	checked = edi.valid;
}
void CbValidCurve::Upload(App& app) const {
	edi.valid = checked;
	edi.Discard(cur);
}

#define nm (ui.fpn_curve->dg_curve->tb_nm->str)
BtLoadCurve::BtLoadCurve() : BtLan(120, L"bt_load_curve") {}
void BtLoadCurve::OnClick(App& app) {
	if (cur.curves.find(nm) != cur.curves.end()) {
		mkp(edi.cv)(*cur.curves[nm]);
	}
}
BtSaveCurve::BtSaveCurve() : BtLan(120, L"bt_save_curve") {}
void BtSaveCurve::OnClick(App& app) {
	mkp(cur.curves[nm])(*edi.cv);
}
BtEditCurve::BtEditCurve() : BtLan(120, L"bt_edit_curve") {}
void BtEditCurve::Update(App& app) {
	enabled = !edi.edit;
	BtLan::Update(app);
}
void BtEditCurve::OnClick(App& app) {
	if (!edi.edit) {
		edi.edit = true; mkp(edi.cv)();
	}
}
BtDelCurve::BtDelCurve() : BtLan(120, L"bt_del_curve") {}
void BtDelCurve::OnClick(App& app) {

}

RLbCurve::RLbCurve() : RichLabel(250) {}
void RLbCurve::Sync(App& app) {
	txt = loc(L"curves_saved");
	for (auto& cv : cur.curves) { txt += cv.first + L","; }
}

DgCurve::DgCurve() {
	vector<Control*> tmp;
	mkp(bt_load)(); mkp(bt_save)();
	tmp = { &*bt_load, &*bt_save };
	mkcl(clx_load);
	mkp(bt_edit)(); mkp(bt_del)();
	tmp = { &*bt_edit, &*bt_del };
	mkcl(clx_edit);
	mkp(tb_nm)(L"tb_nm_curve", 190);
	mkp(rlb_curve)();
	tmp = { &*clx_load, &*clx_edit, &*tb_nm, &*rlb_curve };
	mkcl(cly);
}
void DgCurve::Update(App& app) {
	set_c(app, edi.valid ? &*cly : NULL);
	Delegate::Update(app);
}

FPnCurve::FPnCurve(App& app) : FPnLan(app, 290, 300, L"fpn_curve") {
	vector<Control*> tmp;
	mkp(cb_valid)(); mkp(dg_curve)();
	tmp = { &*cb_valid, &*dg_curve };
	mkcl(cly); c = &*cly; Init(app);
}
