#include "anim.h"

anim::anim(FILE* f) {
	int sz = 0;
	frd(w); frd(h); frd(frame_rate);
	frd(sz);
	rep(i, 0, sz) {
		tile t(w, h);
		rep(i, 0, w * h) { frd(t.cols[i]); }
		rep(i, 0, w * h) { frd(t.as[i]); }
		ts.push_back(t);
	}
}
void anim::save(FILE* f) const {
	int sz = 0;
	fwt(w); fwt(h); fwt(frame_rate);
	sz = ts.size(); fwt(sz);
	for (auto& t : ts) {
		rep(i, 0, w * h) { fwt(t.cols[i]); }
		rep(i, 0, w * h) { fwt(t.as[i]); }
	}
}
anim::anim(wstring const& nm, bool* ok) {
	FILE* f = wfopen(nm, L"rb");
	if (ok) { *ok = f; }
	if (!f) { return; }

	int sz = 0;
	frd(w); frd(h); frd(frame_rate);
	frd(sz);
	rep(i, 0, sz) {
		tile t(w, h);
		rep(i, 0, w * h) { frd(t.cols[i]); }
		rep(i, 0, w * h) { frd(t.as[i]); }
		ts.push_back(t);
	} fclose(f);
}
void anim::save(wstring const& nm) {
	FILE* f = wfopen(nm, L"wb");
	if (!f) { return; }

	int sz = 0;
	fwt(w); fwt(h); fwt(frame_rate);
	sz = ts.size(); fwt(sz);
	for (auto& t : ts) {
		rep(i, 0, w * h) { fwt(t.cols[i]); }
		rep(i, 0, w* h) { fwt(t.as[i]); }
	} fclose(f);
}
