#include "frame.h"
#include "cur.h"
#include "bgr.h"
#include "anm.h"
#include "layer.h"
#include "object.h"

#include "my_def.h"

Frame::Frame(Cur& cur) {
	back = tile(bgr.w, bgr.h, dcol(255));
}
Frame::Frame(Frame const& fr) {
	back = fr.back;
	for(auto& ob : fr.obs) {
		obs[ob.first] = msh<ObInfo>(*ob.second);
	}
}
Frame::Frame(Layer& ly, FILE* f) {
	// back = tile(f);
	back = tile((tle)f);
	for (auto& ob : ly.obs) {
		obs[&*ob] = msh<ObInfo>(f);
	}
}
void Frame::Save(Layer& ly, FILE* f) const {
	tle(back).save(f);
	for (auto& ob : ly.obs) {
		obs.at(&*ob)->Save(f);
	}
}
