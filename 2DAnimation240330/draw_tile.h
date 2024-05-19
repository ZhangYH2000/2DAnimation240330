#pragma once
#include "vec2.h"
#include "tile.h"

// ���� vp_dest �������죬���� vp_src ���������졣
void draw_tile_raw
(tile& dest, dvec tl, drect vp_dest, tile const& src, drect vp_src);
void draw_tile(tile& dest, dbuf& ds, double dep, dvec tl,
	drect vp_dest, tile const& src, drect vp_src);
bool hit_tile(dvec p, dvec tl, tile const& src, drect vp_src);
void draw_tile_cover(tile& dest, dvec tl,
	drect vp_dest, tile const& src, drect vp_src, BYTE alpha);

void draw_tile(tile& dest, dvec tl, drect vp_dest, tile const& src, drect vp_src);
void draw_tile(tile& dest, vec2 ct, double w, double h, 
	mat2 tsf, drect vp_dest, tile const& src, drect vp_src);