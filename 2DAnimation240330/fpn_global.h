#pragma once
#include "label.h"
#include "button.h"
#include "textbox.h"
#include "dragbar.h"
#include "checkbox.h"
#include "ctrl_list.h"
#include "float_panel.h"

struct BtSave : BtLan {
	BtSave();
	void OnClick(App& app) override;
};
struct BtLoad : BtLan {
	BtLoad();
	void OnClick(App& app) override;
};
struct BtReset : BtLan {
	BtReset();
	void OnClick(App& app) override;
};

struct DbXLeft : DbXLan {
	DbXLeft();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbLeft : Textbox {
	TbLeft();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct DbXRight : DbXLan {
	DbXRight();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbRight : Textbox {
	TbRight();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct DbXTop : DbXLan {
	DbXTop();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbTop : Textbox {
	TbTop();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct DbXBottom : DbXLan {
	DbXBottom();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct TbBottom : Textbox {
	TbBottom();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};

struct CbFollowPlay : CbLan {
	CbFollowPlay();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct CbShowBefore : CbLan {
	CbShowBefore();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct CbShowAfter : CbLan {
	CbShowAfter();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};
struct CbEditAll : CbLan {
	CbEditAll();
	void Sync(App& app) override;
	void Upload(App& app) const override;
};

struct TbFrameRate : TbLan {
	TbFrameRate();
	void Sync(App& app) override;
	void OnDone(App& app) const override;
};
struct BtDoubleFrames : BtLan {
	BtDoubleFrames();
	void Update(App& app) override;
	void OnClick(App& app) override;

};
struct BtHalfFrames : BtLan {
	BtHalfFrames();
	void Update(App& app) override;
	void OnClick(App& app) override;
};

struct FPnGlobal : FPnLan {
	ptr<Textbox> tb_save;
	ptr<BtSave> bt_save;
	ptr<CtrlListX> clx_save;
	ptr<Textbox> tb_load;
	ptr<BtLoad> bt_load;
	ptr<CtrlListX> clx_load;
	ptr<BtReset> bt_reset;
	
	ptr<DbXLeft> dbx_left;
	ptr<TbLeft> tb_left;
	ptr<CtrlListX> clx_left;
	ptr<DbXRight> dbx_right;
	ptr<TbRight> tb_right;
	ptr<CtrlListX> clx_right;
	ptr<DbXTop> dbx_top;
	ptr<TbTop> tb_top;
	ptr<CtrlListX> clx_top;
	ptr<DbXBottom> dbx_bottom;
	ptr<TbBottom> tb_bottom;
	ptr<CtrlListX> clx_bottom;

	ptr<CbFollowPlay> cb_follow_play;
	ptr<CbShowBefore> cb_show_before;
	ptr<CbShowAfter> cb_show_after;
	ptr<CbEditAll> cb_edit_all;

	ptr<TbFrameRate> tb_frame_rate;
	ptr<BtDoubleFrames> bt_double_frames;
	ptr<BtHalfFrames> bt_half_frames;
	ptr<CtrlListX> clx_frames;

	ptr<CtrlListY> cly;
	FPnGlobal(App& app);
};
