#pragma once
#include "label.h"
#include "button.h"
#include "textbox.h"
#include "dragbar.h"
#include "checkbox.h"
#include "ctrl_list.h"
#include "float_panel.h"
#include "rich_textbox.h"

struct DbXRBorder : DbXLan {
	DbXRBorder();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbRBorder : Textbox {
	TbRBorder();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct DbXGBorder : DbXLan {
	DbXGBorder();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbGBorder : Textbox {
	TbGBorder();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct DbXBBorder : DbXLan {
	DbXBBorder();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbBBorder : Textbox {
	TbBBorder();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct OtBorder : Control {
	dvec gap;
	double dep = 0;
	int w = 0, h = 0;

	OtBorder();
	int GetW() const override;
	int GetH() const override;
	void render(App& app);
	void Update(App& app) override;
};
struct DbXThick : DbXLan {
	DbXThick();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbThick : Textbox {
	TbThick();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct CbSinglePx : CbLan {
	CbSinglePx();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};

struct DbXRInner : DbXLan {
	DbXRInner();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbRInner : Textbox {
	TbRInner();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct DbXGInner : DbXLan {
	DbXGInner();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbGInner : Textbox {
	TbGInner();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct DbXBInner : DbXLan {
	DbXBInner();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbBInner : Textbox {
	TbBInner();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct OtInner : Control {
	dvec gap;
	double dep = 0;
	int w = 0, h = 0;

	OtInner();
	int GetW() const override;
	int GetH() const override;
	void render(App& app);
	void Update(App& app) override;
};

struct CbDrawInner : CbLan {
	CbDrawInner();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct CbDrawBorder : CbLan {
	CbDrawBorder();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};

struct BtNmAnim : BtLan {
	BtNmAnim();
	void OnClick(App& app) override;
};
struct LbNmAnim : Label {
	LbNmAnim() = default;
	void Sync(App& app) override;
};

struct DbXHText : DbXLan {
	DbXHText();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbHText : Textbox {
	TbHText();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};

struct RTbText : RichTextbox {
	RTbText();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};

struct CbClosedCurve : CbLan {
	CbClosedCurve();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};

struct DgCanvas : Delegate {
	ptr<DbXRBorder> dbx_r_border;
	ptr<TbRBorder> tb_r_border;
	ptr<CtrlListX> clx_r_border;
	ptr<DbXGBorder> dbx_g_border;
	ptr<TbGBorder> tb_g_border;
	ptr<CtrlListX> clx_g_border;
	ptr<DbXBBorder> dbx_b_border;
	ptr<TbBBorder> tb_b_border;
	ptr<CtrlListX> clx_b_border;
	ptr<OtBorder> ot_border;
	ptr<DbXThick> dbx_thick;
	ptr<TbThick> tb_thick;
	ptr<CtrlListX> clx_thick;
	ptr<CbSinglePx> cb_single_px;

	ptr<DbXRInner> dbx_r_inner;
	ptr<TbRInner> tb_r_inner;
	ptr<CtrlListX> clx_r_inner;
	ptr<DbXGInner> dbx_g_inner;
	ptr<TbGInner> tb_g_inner;
	ptr<CtrlListX> clx_g_inner;
	ptr<DbXBInner> dbx_b_inner;
	ptr<TbBInner> tb_b_inner;
	ptr<CtrlListX> clx_b_inner;
	ptr<OtInner> ot_inner;
	ptr<CbDrawInner> cb_draw_inner;
	ptr<CbDrawBorder> cb_draw_border;

	ptr<Textbox> tb_nm_anim;
	ptr<BtNmAnim> bt_nm_anim;
	ptr<LbNmAnim> lb_nm_anim;
	ptr<CtrlListX> clx_nm_anim;

	ptr<DbXHText> dbx_h_text;
	ptr<TbHText> tb_h_text;
	ptr<CtrlListX> clx_h_text;
	ptr<RTbText> rtb_text;

	ptr<CbClosedCurve> cb_closed_curve;

	ptr<CtrlListY> cly_brush;
	ptr<CtrlListY> cly_bezier;
	ptr<CtrlListY> cly_anim;
	ptr<CtrlListY> cly_text;
	ptr<CtrlListY> cly_ellipse;
	ptr<CtrlListY> cly_eraser;
	ptr<CtrlListY> cly_fill;

	DgCanvas();
	void Update(App& app) override;
};

struct FPnCanvas : FPnLan {
	ptr<DgCanvas> dg_canvas;
	
	ptr<CtrlListY> cly;
	FPnCanvas(App& app);
};
