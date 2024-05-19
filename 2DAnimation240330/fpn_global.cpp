#include "fpn_global.h"
#include "ui.h"
#include "cur.h"
#include "bgr.h"
#include "layer.h"
#include "frame.h"

#define cur (*(Cur*)&app)
#include "my_def.h"

BtSave::BtSave() : BtLan(80, L"bt_save") {}
void BtSave::OnClick(App& app) { 
	auto nm = ui.fpn_global->tb_save->str;
	auto typ = ext_nm(nm);
	if (typ == L"anm") { cur.OutputCmp(nm); }
	else if (typ == L"anim") { cur.Output(nm); }
	else { cur.Save(nm); }
}
BtLoad::BtLoad() : BtLan(80, L"bt_load") {}
void BtLoad::OnClick(App& app) { 
	auto nm = ui.fpn_global->tb_load->str;
	auto typ = ext_nm(nm);
	if (typ == L"anm") { cur.InputCmp(nm); }
	else if (typ == L"anim") { cur.Input(nm); }
	else { cur.Load(nm); }
}

BtReset::BtReset() : BtLan(200, L"bt_reset") {}
void BtReset::OnClick(App& app) { cur.Reset(); }

DbXLeft::DbXLeft() : DbXLan(L"dbx_left", 240) {}
void DbXLeft::Sync(App& app) {
	set_nx_rel((double)cur.left / bgr.w);
}
void DbXLeft::Upload(App& app) const {
	cur.left = uval() * bgr.w;
}
TbLeft::TbLeft() : Textbox(50) {}
void TbLeft::Sync(App& app) {
	str = tw(cur.left);
}
void TbLeft::OnDone(App& app) const {
	cur.left = clmp<int>(wtof(str), 0, bgr.w);
}

DbXRight::DbXRight() : DbXLan(L"dbx_right", 240) {}
void DbXRight::Sync(App& app) {
	set_nx_rel((double)cur.right / bgr.w);
}
void DbXRight::Upload(App& app) const {
	cur.right = uval() * bgr.w;
}
TbRight::TbRight() : Textbox(50) {}
void TbRight::Sync(App& app) {
	str = tw(cur.right);
}
void TbRight::OnDone(App& app) const {
	cur.right = clmp<int>(wtof(str), 0, bgr.w);
}

DbXTop::DbXTop() : DbXLan(L"dbx_top", 240) {}
void DbXTop::Sync(App& app) {
	set_nx_rel((double)cur.top / bgr.h);
}
void DbXTop::Upload(App& app) const {
	cur.top = uval() * bgr.h;
}
TbTop::TbTop() : Textbox(50) {}
void TbTop::Sync(App& app) {
	str = tw(cur.top);
}
void TbTop::OnDone(App& app) const {
	cur.top = clmp<int>(wtof(str), 0, bgr.h);
}

DbXBottom::DbXBottom() : DbXLan(L"dbx_bottom", 240) {}
void DbXBottom::Sync(App& app) {
	set_nx_rel((double)cur.bottom / bgr.h);
}
void DbXBottom::Upload(App& app) const {
	cur.bottom = uval() * bgr.h;
}
TbBottom::TbBottom() : Textbox(50) {}
void TbBottom::Sync(App& app) {
	str = tw(cur.bottom);
}
void TbBottom::OnDone(App& app) const {
	cur.bottom = clmp<int>(wtof(str), 0, bgr.h);
}

CbFollowPlay::CbFollowPlay() : CbLan(L"cb_follow_play") {}
void CbFollowPlay::Sync(App& app) {
	checked = cur.follow_play;
}
void CbFollowPlay::Upload(App& app) const {
	cur.follow_play = checked;
}

CbShowBefore::CbShowBefore() : CbLan(L"cb_show_before") {}
void CbShowBefore::Sync(App& app) {
	checked = cur.show_before;
}
void CbShowBefore::Upload(App& app) const {
	cur.show_before = checked;
}
CbShowAfter::CbShowAfter() : CbLan(L"cb_show_after") {}
void CbShowAfter::Sync(App& app) {
	checked = cur.show_after;
}
void CbShowAfter::Upload(App& app) const {
	cur.show_after = checked;
}
CbEditAll::CbEditAll() : CbLan(L"cb_edit_all") {}
void CbEditAll::Sync(App& app) {
	checked = cur.edit_all;
}
void CbEditAll::Upload(App& app) const {
	cur.edit_all = checked;
}

TbFrameRate::TbFrameRate() : TbLan(L"tb_frame_rate", 80) {}
void TbFrameRate::Sync(App& app) {
	str = tw(cur.frame_rate);
}
void TbFrameRate::OnDone(App& app) const {
	cur.frame_rate = max<int>(2, wtof(str));
}
BtDoubleFrames::BtDoubleFrames() : BtLan(150, L"bt_double_frames") {}
void BtDoubleFrames::Update(App& app) {
	enabled = !cur.play;
	BtLan::Update(app);
}
void BtDoubleFrames::OnClick(App& app) {
	if (cur.play) { return; }

	cur.frame_rate *= 2;
	// time 和 t_stop 变化不一样纯属个人审美考量，不重要。
	cur.time *= 2;
	cur.t_sel = cur.time;
	cur.t_stop = 2 * (cur.t_stop + 1) - 1;
	for (auto& ly : cur.layers) {
		vector<ptr<Frame>> tmp;
		tmp.resize(ly->frs.size() * 2);
		rep(i, 0, ly->frs.size()) {
			tmp[2 * i] = ly->frs[i];
		} ly->frs = tmp;
	}
}
BtHalfFrames::BtHalfFrames() : BtLan(150, L"bt_half_frames") {}
void BtHalfFrames::Update(App& app) {
	enabled = !cur.play &&
		cur.frame_rate >= 4 && cur.frame_rate % 2 == 0;
	BtLan::Update(app);
}
void BtHalfFrames::OnClick(App& app) {
	bool ok = !cur.play &&
		cur.frame_rate >= 4 && cur.frame_rate % 2 == 0;
	if (!ok) { return; }

	cur.frame_rate /= 2;
	cur.time /= 2;
	cur.t_sel = cur.time;
	cur.t_stop /= 2;
	for (auto& ly : cur.layers) {
		vector<ptr<Frame>> tmp;
		int sz = (ly->frs.size() - 1) / 2 + 1;
		tmp.resize(sz);
		rep(i, 0, sz) {
			tmp[i] = ly->frs[2 * i];
		} ly->frs = tmp;
	}
}

FPnGlobal::FPnGlobal(App& app) : FPnLan(app, 400, 600, L"fpn_global") {
	vector<Control*> tmp;
	mkp(tb_save)(270); mkp(bt_save)();
	tmp = { &*tb_save, &*bt_save }; mkcl(clx_save);
	mkp(tb_load)(270); mkp(bt_load)();
	tmp = { &*tb_load, &*bt_load }; mkcl(clx_load);
	mkp(bt_reset)();

	mkp(dbx_left)(); mkp(tb_left)();
	tmp = { &*dbx_left, &*tb_left };
	mkcl(clx_left);
	mkp(dbx_right)(); mkp(tb_right)();
	tmp = { &*dbx_right, &*tb_right };
	mkcl(clx_right);
	mkp(dbx_top)(); mkp(tb_top)();
	tmp = { &*dbx_top, &*tb_top };
	mkcl(clx_top);
	mkp(dbx_bottom)(); mkp(tb_bottom)();
	tmp = { &*dbx_bottom, &*tb_bottom };
	mkcl(clx_bottom);

	mkp(cb_follow_play)();
	mkp(cb_show_before)();
	mkp(cb_show_after)();
	mkp(cb_edit_all)();

	mkp(tb_frame_rate)();
	mkp(bt_double_frames)(); mkp(bt_half_frames)();
	tmp = { &*bt_double_frames, &*bt_half_frames };
	mkcl(clx_frames);

	tmp = { &*clx_save, &*clx_load, &*bt_reset, 
		&*clx_left, &*clx_top, &*clx_right, &*clx_bottom,
		&*cb_follow_play,
		&*cb_show_before, &*cb_show_after, &*cb_edit_all,
		&*tb_frame_rate, &*clx_frames };
	mkcl(cly); c = &*cly; Init(app);
}
