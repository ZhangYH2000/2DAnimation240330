#pragma once
#include "label.h"
#include "button.h"
#include "textbox.h"
#include "dragbar.h"
#include "checkbox.h"
#include "ctrl_list.h"
#include "float_panel.h"

struct BtCancelOb : BtLan {
	BtCancelOb();
	void Update(App& app) override;
	void OnClick(App& app) override;
};

struct DbXRBorderOb : DbXLan {
	DbXRBorderOb();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbRBorderOb : Textbox {
	TbRBorderOb();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct DbXGBorderOb : DbXLan {
	DbXGBorderOb();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbGBorderOb : Textbox {
	TbGBorderOb();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct DbXBBorderOb : DbXLan {
	DbXBBorderOb();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbBBorderOb : Textbox {
	TbBBorderOb();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct OtBorderOb : Control {
	dvec gap;
	double dep = 0;
	int w = 0, h = 0;

	OtBorderOb();
	int GetW() const override;
	int GetH() const override;
	void render(App& app);
	void Update(App& app) override;
};
struct DbXThickOb : DbXLan {
	DbXThickOb();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbThickOb : Textbox {
	TbThickOb();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct CbSinglePxOb : CbLan {
	CbSinglePxOb();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};

struct DbXRInnerOb : DbXLan {
	DbXRInnerOb();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbRInnerOb : Textbox {
	TbRInnerOb();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct DbXGInnerOb : DbXLan {
	DbXGInnerOb();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbGInnerOb : Textbox {
	TbGInnerOb();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct DbXBInnerOb : DbXLan {
	DbXBInnerOb();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbBInnerOb : Textbox {
	TbBInnerOb();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct OtInnerOb : Control {
	dvec gap;
	double dep = 0;
	int w = 0, h = 0;

	OtInnerOb();
	int GetW() const override;
	int GetH() const override;
	void render(App& app);
	void Update(App& app) override;
};

struct CbDrawInnerOb : CbLan {
	CbDrawInnerOb();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct CbDrawBorderOb : CbLan {
	CbDrawBorderOb();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};

struct CbCurveOb : CbLan {
	CbCurveOb();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbCurveOb : TbLan {
	TbCurveOb();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};

struct TbSpeedOb : TbLan {
	TbSpeedOb();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};

struct DgObject : Delegate {
	ptr<DbXRBorderOb> dbx_r_border;
	ptr<TbRBorderOb> tb_r_border;
	ptr<CtrlListX> clx_r_border;
	ptr<DbXGBorderOb> dbx_g_border;
	ptr<TbGBorderOb> tb_g_border;
	ptr<CtrlListX> clx_g_border;
	ptr<DbXBBorderOb> dbx_b_border;
	ptr<TbBBorderOb> tb_b_border;
	ptr<CtrlListX> clx_b_border;
	ptr<OtBorderOb> ot_border;
	ptr<DbXThickOb> dbx_thick;
	ptr<TbThickOb> tb_thick;
	ptr<CtrlListX> clx_thick;
	ptr<CbSinglePxOb> cb_single_px;

	ptr<DbXRInnerOb> dbx_r_inner;
	ptr<TbRInnerOb> tb_r_inner;
	ptr<CtrlListX> clx_r_inner;
	ptr<DbXGInnerOb> dbx_g_inner;
	ptr<TbGInnerOb> tb_g_inner;
	ptr<CtrlListX> clx_g_inner;
	ptr<DbXBInnerOb> dbx_b_inner;
	ptr<TbBInnerOb> tb_b_inner;
	ptr<CtrlListX> clx_b_inner;
	ptr<OtInnerOb> ot_inner;
	ptr<CbDrawInnerOb> cb_draw_inner;
	ptr<CbDrawBorderOb> cb_draw_border;

	ptr<CbCurveOb> cb_curve;
	ptr<TbCurveOb> tb_curve;
	ptr<TbSpeedOb> tb_speed;

	ptr<CtrlListY> cly_bezier;
	ptr<CtrlListY> cly_anim;
	ptr<CtrlListY> cly_ellipse;

	DgObject();
	void Update(App& app) override;
};

struct CbShowOb : CbLan {
	CbShowOb();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};

struct DbXTCurveOb : DbXLan {
	DbXTCurveOb();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbTCurveOb : Textbox {
	TbTCurveOb();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct DgObInfo : Delegate {
	ptr<CbShowOb> cb_show;
	ptr<DbXTCurveOb> dbx_t_curve;
	ptr<TbTCurveOb> tb_t_curve;
	ptr<CtrlListX> clx_t_curve;
	ptr<CtrlListY> cly;

	DgObInfo();
	void Update(App& app) override;
};

struct FPnObject : FPnLan {
	ptr<BtCancelOb> bt_cancel;
	ptr<DgObject> dg_object;
	ptr<DgObInfo> dg_ob_info;
	
	ptr<CtrlListY> cly;
	FPnObject(App& app);
};
