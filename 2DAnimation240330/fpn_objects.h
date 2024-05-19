#pragma once
#include "label.h"
#include "button.h"
#include "textbox.h"
#include "dragbar.h"
#include "checkbox.h"
#include "separator.h"
#include "ctrl_list.h"
#include "float_panel.h"

struct TbObNm : Textbox {
	int id = 0;
	TbObNm(int id);
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct BtDelOb : BtLan {
	int id = 0;
	BtDelOb(int id);
	void OnClick(App& app) override;
};
struct BtObUp : BtLan {
	int id = 0;
	BtObUp(int id);
	void Update(App& app) override;
	void OnClick(App& app) override;
};
struct BtObDown : BtLan {
	int id = 0;
	BtObDown(int id);
	void Update(App& app) override;
	void OnClick(App& app) override;
};
struct CbObShow : CbLan {
	int id = 0;
	CbObShow(int id);
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct CbObSel : CbLan {
	int id = 0;
	CbObSel(int id);
	void Sync(App& app) override;
	void Upload(App& app) const override;
};

struct ClYObject : CtrlListY {
	ptr<TbObNm> tb_nm;
	ptr<BtDelOb> bt_del;
	ptr<CtrlListX> clx_nm;
	ptr<BtObUp> bt_up;
	ptr<BtObDown> bt_down;
	ptr<CbObShow> cb_show;
	ptr<CbObSel> cb_sel;
	ptr<CtrlListX> clx_sel;
	ptr<SeparatorY> spy;
	ClYObject(int id);
};
struct ClYObjects : CtrlListY {
	vector<ptr<ClYObject>> mbs;
	void Update(App& app) override;
};

struct FPnObjects : FPnLan {
	ptr<ClYObjects> cly_objects;
	ptr<CtrlListY> cly;
	FPnObjects(App& app);
};
