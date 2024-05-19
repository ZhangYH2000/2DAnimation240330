#include "fpn_layer.h"
#include "ui.h"
#include "cur.h"
#include "layer.h"
#include "frame.h"
#include "canvas.h"
#include "object.h"
#include "draw_geo.h"

#define cur (*(Cur*)&app)
#include "my_def.h"

#define lys (cur.layers)
#define ly (*lys[id])

TbLyNm::TbLyNm(int id) : id(id), Textbox(270) {}
void TbLyNm::Sync(App& app) { str = ly.nm; }
void TbLyNm::OnDone(App& app) const { ly.nm = str; }
BtDelLy::BtDelLy(int id) : id(id), BtLan(80, L"bt_del_ly") {}
void BtDelLy::OnClick(App& app) { ly.del = true; }
void BtDelLy::Update(App& app) { 
	// 这并不能保证删掉的那个图层不会被选中是吧，因为你不知道后续会有什么操作。
	// 所以需要在执行删除时着重验证。

	// 另外还有个问题就是删除的时候要不要 Discard 之类。
	enabled = cur.layer_sel != &ly; 
	BtLan::Update(app); 
}
BtLyUp::BtLyUp(int id) : id(id), BtLan(80, L"bt_ly_up") {}
void BtLyUp::Update(App& app) {
	enabled = id != 0;
	BtLan::Update(app);
}
void BtLyUp::OnClick(App& app) { swap(lys[id], lys[id - 1]); }
BtLyDown::BtLyDown(int id) : id(id), BtLan(80, L"bt_ly_down") {}
void BtLyDown::Update(App& app) {
	enabled = id != lys.size() - 1;
	BtLan::Update(app);
}
void BtLyDown::OnClick(App& app) { swap(lys[id], lys[id + 1]); }
CbLyShow::CbLyShow(int id) : id(id), CbLan(L"cb_ly_show", true) {}
void CbLyShow::Sync(App& app) { checked = ly.show; }
void CbLyShow::Upload(App& app) const { ly.show = checked; }
CbLySel::CbLySel(int id) : id(id), CbLan(L"cb_ly_sel", true) {}
void CbLySel::Sync(App& app) { checked = cur.layer_sel == &ly; }
void CbLySel::Upload(App& app) const {
	if (cur.layer_sel != &ly) {
		if (posel) {
			osel.Discard(cur);
			posel = NULL;
		}
		cur.layer_sel = &ly;
		cur.cvs->Discard(cur);
	}
}
void CbLySel::Update(App& app) {
	enabled = cur.layer_sel != &ly; 
	CbLan::Update(app);
}

ClYLayer::ClYLayer(int id) {
	vector<Control*> tmp;
	mkp(tb_nm)(id); mkp(bt_del)(id);
	tmp = { &*tb_nm, &*bt_del }; mkcl(clx_nm);
	mkp(bt_up)(id); mkp(bt_down)(id);
	mkp(cb_show)(id); mkp(cb_sel)(id);
	tmp = { &*bt_up, &*bt_down, &*cb_show, &*cb_sel };
	mkcl(clx_sel); mkp(spy)(400);
	cs = { &*clx_nm, &*clx_sel, &*spy };
}
void ClYLayers::Update(App& app) {
	cs.clear();
	rep(i, mbs.size(), lys.size()) { mbs.push_back(msh<ClYLayer>(i)); }
	rep(i, 0, lys.size()) { cs.push_back(&*mbs[i]); }
	rep(i, lys.size(), mbs.size()) { mbs[i]->Discard(app); }
	CtrlListY::Update(app);
}

BtAddLy::BtAddLy() : BtLan(200, L"bt_add_ly") {}
void BtAddLy::OnClick(App& app) { 
	cur.layers.push_back(msh<Layer>(cur));
	dcol c;
	c.r = drnd(255);
	c.g = drnd(255);
	c.b = drnd(255);
	cur.layers.back()->c = c;
}

TbLyCol::TbLyCol() : TbLan(L"tb_ly_col", 200) {}
void TbLyCol::Sync(App& app) {
	str = tw(lysel.c);
}
void TbLyCol::OnDone(App& app) const {
	lysel.c = dcol(str);
}

FPnLayer::FPnLayer(App& app) : FPnLan(app, 400, 600, L"fpn_layer") {
	vector<Control*> tmp;
	mkp(cly_layers)(); mkp(bt_add)(); mkp(tb_col)();
	tmp = { &*cly_layers, &*bt_add, &*tb_col };
	mkcl(cly); c = &*cly; Init(app);
}
