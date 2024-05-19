#include "bz_cpnt.h"
#include "cur.h"
#include "bgr.h"
#include "frame.h"
#include "layer.h"
#include "object.h"
#include "bezier.h"

#include "my_def.h"

void BzCPnt::Sync(Cur& cur) {
	o = lysel.frs[tm]->obs[ob]->bz->dat[id_vs][id_v] + bgr.tl;
}
void BzCPnt::Upload(Cur& cur) {
	lysel.frs[tm]->obs[ob]->bz->dat[id_vs][id_v] = o - bgr.tl;
}
