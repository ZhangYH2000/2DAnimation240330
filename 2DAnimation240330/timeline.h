#pragma once
#include "tile.h"

struct Cur;
struct Timeline {
	dvec tl;
	int w = 0;
	int h = 0;
	vec2 tl_rel;

	bool hovered = false;
	bool dragged = false;
	bool selecting = false;

	dvec pgd_hv;
	bool gd_hvd = false;

	Timeline();
	drect vp() const { return { tl, w, h }; }
	void Update(Cur& cur);
	void Render(Cur& cur);
	void PreUpdate(Cur& cur);
};
