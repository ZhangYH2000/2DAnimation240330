#include "ctrl_pnt.h"
#include "cur.h"
#include "ui.h"
#include "bgr.h"
#include "draw_geo.h"
#include "draw_curve.h"
#include "fpn_object.h"

#include "my_def.h"

int constexpr rad = 7;

CPnt::CPnt() {
	c_normal = { 80, 80, 80 };
	c_hovered = { 20, 20, 255 };
	c_dragged = { 250, 20, 20 };
}
double CPnt::dep() const {
	return dragged ? 21 : 20;
}
void CPnt::Update(Cur& cur) {
	hovered = (hvd == this);

	if (dragged) {
		dragged = msd[0];
		o = msp;
		Upload(cur);
	} else {
		dragged = msc(0) && hovered;
		if (dragged && ob) { 
			posel = ob; 
			ui.fpn_object->show(cur);
		}
		Sync(cur);
	}
}
void CPnt::Render(Cur& cur) {
	dcol c =
		dragged ? c_dragged :
		hovered ? c_hovered : c_normal;
	draw_eclipse(scr, dscr, dep(), (vec2)o, rad, rad, bgr.vp(), c);
	draw_px_circle(scr, dscr, dep(), o, rad, bgr.vp(), c_frame);
}
void CPnt::Discard(Cur& cur) {
	rmv;
}
void CPnt::PreUpdate(Cur& cur) {
	bool ok =
		(msp - o).lensqr() < rad * rad &&
		dhv <= dep() && insd(msp, bgr.vp());
	if (ok) { dhv = dep(); hvd = this; }
}
