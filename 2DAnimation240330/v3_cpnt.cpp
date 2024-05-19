#include "v3_cpnt.h"
#include "cur.h"
#include "bgr.h"
#include "layer.h"
#include "frame.h"
#include "object.h"

#include "my_def.h"

void V3CPnt::Sync(Cur& cur) {
	auto& tmp = *lysel.frs[tm]->obs[ob];
	o = dvec(tmp.ct + mat2::rot(tmp.ang) * vec2(-tmp.w, +tmp.h) / 2) + bgr.tl;
}
void V3CPnt::Upload(Cur& cur) {
	auto& tmp = *lysel.frs[tm]->obs[ob];
	vec2 v = vec2(+tmp.w, -tmp.h) / 2;
	vec2 u = mat2::rot(-tmp.ang) * (vec2(msp - bgr.tl) - tmp.ct);
	tmp.w = v.x - u.x;
	tmp.h = u.y - v.y;
	tmp.ct += mat2::rot(tmp.ang) * (v - vec2(+tmp.w, -tmp.h) / 2);
}