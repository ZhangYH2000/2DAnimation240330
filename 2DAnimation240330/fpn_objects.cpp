#include "fpn_objects.h"
#include "ui.h"
#include "cur.h"
#include "layer.h"
#include "frame.h"
#include "object.h"
#include "draw_geo.h"

#define cur (*(Cur*)&app)
#include "my_def.h"

#define obs (lysel.obs)
#define ob (*obs[id])

TbObNm::TbObNm(int id) : id(id), Textbox(270) {}
void TbObNm::Sync(App& app) { str = ob.nm; }
void TbObNm::OnDone(App& app) const { ob.nm = str; }
BtDelOb::BtDelOb(int id) : id(id), BtLan(80, L"bt_del_ob") {}
void BtDelOb::OnClick(App& app) { ob.del = true; }
BtObUp::BtObUp(int id) : id(id), BtLan(80, L"bt_ob_up") {}
void BtObUp::Update(App& app) { 
	enabled = id != 0; 
	BtLan::Update(app);
}
void BtObUp::OnClick(App& app) { swap(obs[id], obs[id - 1]); }
BtObDown::BtObDown(int id) : id(id), BtLan(80, L"bt_ob_down") {}
void BtObDown::Update(App& app) {
	enabled = id != obs.size() - 1;
	BtLan::Update(app);
}
void BtObDown::OnClick(App& app) { swap(obs[id], obs[id + 1]); }
CbObShow::CbObShow(int id) : id(id), CbLan(L"cb_ob_show", true) {}
void CbObShow::Sync(App& app) { checked = ob.show; }
void CbObShow::Upload(App& app) const { ob.show = checked; }
CbObSel::CbObSel(int id) : id(id), CbLan(L"cb_ob_sel", true) {}
void CbObSel::Sync(App& app) { checked = posel == &ob; }
void CbObSel::Upload(App& app) const {
	if (posel) { osel.Discard(cur); }
	posel = checked ? &ob : NULL;
}

ClYObject::ClYObject(int id) {
	vector<Control*> tmp;
	mkp(tb_nm)(id); mkp(bt_del)(id);
	tmp = { &*tb_nm, &*bt_del }; mkcl(clx_nm);
	mkp(bt_up)(id); mkp(bt_down)(id);
	mkp(cb_show)(id); mkp(cb_sel)(id);
	tmp = { &*bt_up, &*bt_down, &*cb_show, &*cb_sel };
	mkcl(clx_sel); mkp(spy)(400);
	cs = { &*clx_nm, &*clx_sel, &*spy };
}
void ClYObjects::Update(App& app) {
	cs.clear();
	rep(i, mbs.size(), obs.size()) { mbs.push_back(msh<ClYObject>(i)); }
	rep(i, 0, obs.size()) { cs.push_back(&*mbs[i]); }
	rep(i, obs.size(), mbs.size()) { mbs[i]->Discard(app); }
	CtrlListY::Update(app);
}

FPnObjects::FPnObjects(App& app) : FPnLan(app, 400, 600, L"fpn_objects") {
	vector<Control*> tmp;
	mkp(cly_objects)();
	tmp = { &*cly_objects };
	mkcl(cly); c = &*cly; Init(app);
}
