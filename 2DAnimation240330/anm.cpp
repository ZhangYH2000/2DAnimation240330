#include "anm.h"
#include "anim.h"

col_seg::col_seg(FILE* f) {
	frd(c); frd(a); frd(n);
}
void col_seg::save(FILE* f) const {
	fwt(c); fwt(a); fwt(n);
}

tle::tle(tile const& t) {
	w = t.w; h = t.h;
	if (!t.n()) { return; }
	col_seg c(t.cols[0], t.as[0]);
	for (int i = 1; i < t.n(); ++i) {
		auto tc = t.cols[i];
		auto ta = t.as[i];

		if (c.c == tc && c.a == ta) {
			++c.n;
		} else {
			cs.push_back(c);
			c = col_seg(tc, ta);
		}
	} cs.push_back(c);
}
tle::operator tile() {
	tile t(w, h);

	int id = 0;
	for (auto& c : cs) {
		rep(i, 0, c.n) {
			t.cols[id] = c.c;
			t.as[id] = c.a;
			++id;
		}
	} return t;
}
tle::tle(FILE* f) {
	int sz = 0;
	frd(w); frd(h);
	frd(sz);
	rep(i, 0, sz) {
		cs.push_back(col_seg(f));
	}
}
void tle::save(FILE* f) const {
	int sz = 0;
	fwt(w); fwt(h);
	sz = cs.size(); fwt(sz);
	for (auto& c : cs) { c.save(f); }
}

anm::anm(anim const& an) {
	w = an.w;
	h = an.h;
	frame_rate = an.frame_rate;
	for (auto& t : an.ts) {
		ts.push_back((tle)t);
	}
}
anm::anm(FILE* f) {
	int sz = 0;
	frd(w); frd(h); frd(frame_rate);
	frd(sz);
	rep(i, 0, sz) {
		// 不想专门省去 w, h 的空间了。
		tle t(f);
		ts.push_back(t);
	}
}
anm::operator anim() {
	anim an(w, h, frame_rate);
	for (auto& t : ts) {
		an.ts.push_back((tile)t);
	} return an;
}
anm::anm(wstring const& nm, bool *ok) {
	FILE* f = wfopen(nm, L"rb");
	if (ok) { *ok = f; }
	if (!f) { return; }

	int sz = 0;
	frd(w); frd(h); frd(frame_rate);
	frd(sz);
	rep(i, 0, sz) {
		// 不想专门省去 w, h 的空间了。
		tle t(f);
		ts.push_back(t);
	} fclose(f);
}
// 重复的代码可以合并。
void anm::save(FILE* f) {
	int sz = 0;
	fwt(w); fwt(h); fwt(frame_rate);
	sz = ts.size(); fwt(sz);
	for (auto& t : ts) {
		// 不想专门省去 w, h 的空间了。
		t.save(f);
	}
}
void anm::save(wstring const& nm) {
	FILE* f = wfopen(nm, L"wb");
	if (!f) { return; }

	int sz = 0;
	fwt(w); fwt(h); fwt(frame_rate);
	sz = ts.size(); fwt(sz);
	for (auto& t : ts) {
		// 不想专门省去 w, h 的空间了。
		t.save(f);
	} fclose(f);
}
