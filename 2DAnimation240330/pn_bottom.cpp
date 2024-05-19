#include "pn_bottom.h"
#include "cur.h"
#include "bgr.h"

#define cur (*(Cur*)&app)
#include "my_def.h"

LbFPS::LbFPS() { w = 450; fixed_w = true; }
void LbFPS::Sync(App& app) {
	txt = loc(L"frm_tm") + tw2(cur.fps.frm_time * 1000) +
		L", FPS: " + tw2(cur.fps.fps);
}

LbMouse::LbMouse() { w = 300; fixed_w = true; }
void LbMouse::Sync(App& app) {
	txt = loc(L"lb_mouse") + tw(msp - bgr.tl);
}

LbTime::LbTime() { w = 300; fixed_w = true; }
void LbTime::Sync(App& app) {
	int t0 = cur.time / cur.frame_rate;
	int t1 = cur.time % cur.frame_rate;
	txt = loc(L"lb_time") + tw(t0) + 
		L"(" + tw(t1) + L"/" + tw(cur.frame_rate) + L")";
}

PnBottom::PnBottom(App& app) : Panel(Panel::bottom(app)) {
	w -= 180;
	// 收缩了一下长度。
	
	vector<Control*> tmp;
	mkp(lb_fps)(); mkp(lb_mouse)(); mkp(lb_time)();
	tmp = { &*lb_fps, &*lb_mouse, &*lb_time };
	mkcl(clx); c = &*clx; Init(app);
}
