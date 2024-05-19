#include "curve_editor.h"
#include "cur.h"
#include "bgr.h"
#include "curve.h"

#include "my_def.h"

double constexpr dep = 500;

CurveEditor::CurveEditor() {
	mkp(cv)();
}
void CurveEditor::Update(Cur& cur) {
	if (!valid) { return; }
	hovered = (hvd == this);

	if (edit) {
		if (drawing) {
			if (msd[0]) {
				auto ok = 
					cv->nds.back().p != msp - bgr.tl;
				if (ok) {
					cv->nds.push_back({ 0, msp - bgr.tl });
				}
			} else {
				cv->normalize();
				edit = false;
				drawing = false;
			}
		} else {
			if (msc(0) && hovered) { 
				drawing = true; 
				cv->nds.push_back({ 0, msp - bgr.tl });
			}
		}
	}

	if (edit) {
		cv->nds.push_back({ 0, msp - bgr.tl });
		cv->render(cur);
		cv->nds.pop_back();
	} else {
		cv->render(cur);
	}
}
void CurveEditor::Discard(Cur& cur) {
	edit = hovered = drawing = false;
}
void CurveEditor::PreUpdate(Cur& cur) {
	if (!valid) { return; }
	bool ok = edit && 
		dhv <= dep && insd(msp, bgr.vp());
	if (ok) { dhv = dep; hvd = this; }
}
