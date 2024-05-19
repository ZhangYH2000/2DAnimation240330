#pragma once
#include "tile.h"

void draw_fill_poly(tile& dest, dbuf& ds,
	double dep, vector<dvec> const& vs, drect vp, dcol col);
void draw_fill_poly(tile& dest, vector<dvec> const& vs, drect vp, dcol col);

// 虽然完全可以实现，但是这里还是没有考虑透明的填充。
void draw_fill(tile& dest, dvec p, drect vp, dcol c);
