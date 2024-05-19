#include "layer.h"
#include "cur.h"
#include "frame.h"
#include "bezier.h"
#include "object.h"

#include "my_def.h"

Layer::Layer(Cur& cur) {
	nm = loc(L"unnamed");
	frs.push_back(msh<Frame>(cur));
}
Layer::Layer(Cur& cur, FILE* f) {
	int sz = 0;
	frd(c); frdv(nm);
	frd(sz); 
	rep(i, 0, sz) {
		obs.push_back(msh<Object>(f));
	}
	frd(sz); 
	rep(i, 0, sz) {
		frd(sz);
		frs.push_back(sz ? msh<Frame>(*this, f) : NULL);
	}

	for (auto& ob : obs) { ob->Load(cur, *this); }
}
void Layer::Save(FILE* f) {
	int sz = 0;
	fwt(c); fwtv(nm);
	sz = obs.size(); fwt(sz);
	for (auto& ob : obs) { ob->Save(f); }
	sz = frs.size(); fwt(sz);
	for (auto& fr : frs) {
		sz = (bool)fr;
		fwt(sz);
		if (fr) { fr->Save(*this, f); }
	}
}
int Layer::prv(int t) const {
	t = min<int>(t, frs.size() - 1);
	while (!frs[t]) { --t; }
	return t;
}
int Layer::nxt(int t) const {
	do { ++t; } while (t < frs.size() && !frs[t]);
	return t;
}

void Layer::NewFrame(Cur& cur, int t) {
	if (t == 0) { 
		frs[0]->back.fill({}, 0);
		return; 
	}

	frs[t] = NULL;
	auto fr = msh<Frame>(cur);
	auto ref = frs[prv(t)];
	for (auto& op : ref->obs) {
		fr->obs[op.first] = msh<ObInfo>(interp(op.first, t));
	}
	frs[t] = fr;
}
ObInfo Layer::interp(Object* ob, int t) {
	int t0 = prv(t), t1 = nxt(t);
	if (t1 >= frs.size()) { return *frs[t0]->obs[ob]; }
	auto& ob0 = *frs[t0]->obs[ob];
	auto& ob1 = *frs[t1]->obs[ob];
	ObInfo tmp;

	
	if (ob0.bz) {
		auto bz = msh<Bezier>(*ob0.bz);
		rep(i, 0, bz->dat.size()) {
			auto vs = bz->dat[i];
			rep(j, 0, vs.size()) {
				bz->dat[i][j] *= t1 - t;
				bz->dat[i][j] += ob1.bz->dat[i][j] * (t - t0);
				bz->dat[i][j] /= t1 - t0;
			}
		} tmp.bz = bz;
	}

	tmp.w = ob0.w * (t1 - t) + ob1.w * (t - t0);
	tmp.h = ob0.h * (t1 - t) + ob1.h * (t - t0);
	tmp.ct = ob0.ct * (t1 - t) + ob1.ct * (t - t0);
	tmp.ang = ob0.ang * (t1 - t) + ob1.ang * (t - t0);
	tmp.w /= t1 - t0; tmp.h /= t1 - t0;
	tmp.ct /= t1 - t0; tmp.ang /= t1 - t0;

	tmp.t_curve = ob0.t_curve * (t1 - t) + ob1.t_curve * (t - t0);
	tmp.t_curve /= t1 - t0;

	tmp.show = ob0.show;
	return tmp;
}
