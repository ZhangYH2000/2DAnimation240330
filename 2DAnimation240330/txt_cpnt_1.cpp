#include "txt_cpnt_1.h"
#include "cur.h"
#include "bgr.h"
#include "canvas.h"

#include "my_def.h"

void TxtCPnt1::Sync(Cur& cur) {
	o = cur.cvs->tl + bgr.tl + dvec(cur.cvs->w, 0);
}
void TxtCPnt1::Upload(Cur& cur) {
	cur.cvs->w = (o - cur.cvs->tl - bgr.tl).x;
}
