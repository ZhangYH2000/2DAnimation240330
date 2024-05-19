#include "txt_cpnt_0.h"
#include "cur.h"
#include "bgr.h"
#include "canvas.h"

#include "my_def.h"

void TxtCPnt0::Sync(Cur& cur) {
	o = cur.cvs->tl + bgr.tl;
}
void TxtCPnt0::Upload(Cur& cur) {
	cur.cvs->tl = o - bgr.tl;
}
