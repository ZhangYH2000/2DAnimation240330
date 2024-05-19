#include "ct_cpnt.h"
#include "cur.h"
#include "bgr.h"
#include "layer.h"
#include "frame.h"
#include "object.h"

#include "my_def.h"

void CtCPnt::Sync(Cur& cur) {
	o = (dvec)lysel.frs[tm]->obs[ob]->ct + bgr.tl;
}
void CtCPnt::Upload(Cur& cur) {
	if (ob->use_curve) { return; }
	lysel.frs[tm]->obs[ob]->ct = vec2(o - bgr.tl);
}
