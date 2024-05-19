#pragma once
#include "button.h"
#include "textbox.h"
#include "checkbox.h"
#include "ctrl_list.h"
#include "rich_label.h"
#include "float_panel.h"

struct CbValidCurve : CbLan {
	CbValidCurve();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};

struct BtLoadCurve : BtLan {
	BtLoadCurve();
	void OnClick(App& app) override;
};
struct BtSaveCurve : BtLan {
	BtSaveCurve();
	void OnClick(App& app) override;
};
struct BtEditCurve : BtLan {
	BtEditCurve();
	void Update(App& app) override;
	void OnClick(App& app) override;
};
struct BtDelCurve : BtLan {
	BtDelCurve();
	void OnClick(App& app) override;
};

struct RLbCurve : RichLabel {
	RLbCurve();
	void Sync(App& app) override;
};

struct DgCurve : Delegate {
	ptr<BtLoadCurve> bt_load;
	ptr<BtSaveCurve> bt_save;
	ptr<CtrlListX> clx_load;
	ptr<BtEditCurve> bt_edit;
	ptr<BtDelCurve> bt_del;
	ptr<CtrlListX> clx_edit;
	ptr<TbLan> tb_nm;
	ptr<RLbCurve> rlb_curve;
	ptr<CtrlListY> cly;

	DgCurve();
	void Update(App& app) override;
};

struct FPnCurve : FPnLan {
	ptr<CbValidCurve> cb_valid;
	ptr<DgCurve> dg_curve;

	ptr<CtrlListY> cly;
	FPnCurve(App& app);
};
