#pragma once
#include "tile.h"

struct anim {
	int w = 0, h = 0;
	int frame_rate = 0;
	vector<tile> ts;

	anim() = default;
	anim(FILE* f);
	void save(FILE* f) const;
	anim(int w, int h, int fr) : w(w), h(h), frame_rate(fr) {}
	anim(wstring const &nm, bool* ok = NULL);
	void save(wstring const &nm);
};
