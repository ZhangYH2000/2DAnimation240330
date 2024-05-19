#include "rot_cpnt.h"
#include "cur.h"
#include "bgr.h"
#include "layer.h"
#include "frame.h"
#include "object.h"

#include "my_def.h"

void RotCPnt::Sync(Cur& cur) {
	auto& tmp = *lysel.frs[tm]->obs[ob];
	o = dvec(tmp.ct + mat2::rot(tmp.ang) * vec2(40, 0)) + bgr.tl;
}
void RotCPnt::Upload(Cur& cur) {
	auto& tmp = *lysel.frs[tm]->obs[ob];
	vec2 v1 = vec2(msp - bgr.tl) - tmp.ct;
	if (v1.lensqr() < 4) { return; }

	vec2 v0 = vec2(cos(tmp.ang), sin(tmp.ang));
	v1 = v1.unit();
	double c = v0.x * v1.x + v0.y * v1.y;
	double s = v0.x * v1.y - v0.y * v1.x;
	double dif = atan2(s, c);
	tmp.ang += dif;
}
