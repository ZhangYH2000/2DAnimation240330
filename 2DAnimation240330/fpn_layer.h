#pragma once
#include "label.h"
#include "button.h"
#include "textbox.h"
#include "dragbar.h"
#include "checkbox.h"
#include "ctrl_list.h"
#include "separator.h"
#include "float_panel.h"

struct TbLyNm : Textbox {
	int id = 0;
	TbLyNm(int id);
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct BtDelLy : BtLan {
	int id = 0;
	BtDelLy(int id);
	void OnClick(App& app) override;
	void Update(App& app) override;
};
struct BtLyUp : BtLan {
	int id = 0;
	BtLyUp(int id);
	void Update(App& app) override;
	void OnClick(App& app) override;
};
struct BtLyDown : BtLan {
	int id = 0;
	BtLyDown(int id);
	void Update(App& app) override;
	void OnClick(App& app) override;
};
struct CbLyShow : CbLan {
	int id = 0;
	CbLyShow(int id);
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct CbLySel : CbLan {
	int id = 0;
	CbLySel(int id);
	void Sync(App& app) override;
	void Upload(App& app) const override;
	void Update(App& app) override;
};

struct ClYLayer : CtrlListY {
	ptr<TbLyNm> tb_nm;
	ptr<BtDelLy> bt_del;
	ptr<CtrlListX> clx_nm;
	ptr<BtLyUp> bt_up;
	ptr<BtLyDown> bt_down;
	ptr<CbLyShow> cb_show;
	ptr<CbLySel> cb_sel;
	ptr<CtrlListX> clx_sel;
	ptr<SeparatorY> spy;
	ClYLayer(int id);
};
struct ClYLayers : CtrlListY {
	vector<ptr<ClYLayer>> mbs;
	void Update(App& app) override;
};

struct BtAddLy : BtLan {
	BtAddLy();
	void OnClick(App& app) override;
};
struct TbLyCol : TbLan {
	TbLyCol();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};

struct FPnLayer : FPnLan {
	ptr<ClYLayers> cly_layers;
	ptr<BtAddLy> bt_add;
	ptr<TbLyCol> tb_col;
	ptr<CtrlListY> cly;
	FPnLayer(App& app);
};
