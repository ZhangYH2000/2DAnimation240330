#pragma once
#include "tile.h"

void draw_tiny_seg(tile& dest, vec2 pa, vec2 pb, double thk, drect vp, dcol col);
void draw_px_circle(tile& dest, dbuf& ds, double dep,
	dvec ct, int r, drect vp, dcol col);

void draw_tiny_seg_erase(tile& dest, vec2 pa, vec2 pb, double thk, drect vp);
