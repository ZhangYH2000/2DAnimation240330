#include "v0_cpnt.h"
#include "cur.h"
#include "bgr.h"
#include "layer.h"
#include "frame.h"
#include "object.h"

#include "my_def.h"

void V0CPnt::Sync(Cur& cur) {
	auto& tmp = *lysel.frs[tm]->obs[ob];
	o = dvec(tmp.ct + mat2::rot(tmp.ang) * vec2(-tmp.w, -tmp.h) / 2) + bgr.tl;
}
void V0CPnt::Upload(Cur& cur) {
	auto& tmp = *lysel.frs[tm]->obs[ob];
	vec2 v = vec2(+tmp.w, +tmp.h) / 2;
	vec2 u = mat2::rot(-tmp.ang) * (vec2(msp - bgr.tl) - tmp.ct);
	tmp.w = v.x - u.x;
	tmp.h = v.y - u.y;
	tmp.ct += mat2::rot(tmp.ang) * (v - vec2(+tmp.w, +tmp.h) / 2);
}
