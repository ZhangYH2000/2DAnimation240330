#pragma once
#include "tile.h"

struct Bezier {
	bool closed = false;
	vector<vector<dvec>> dat;

	Bezier() = default;
	Bezier(FILE* f);
	void Save(FILE* f) const;
};

// 我觉得这里都可以优化很多，比如先生成折线再渲染之类。
void draw_bezier(tile& dest, dbuf& ds, double dep, dvec tl,
	Bezier const& bz, double thk, drect vp, dcol col);
void draw_bezier_seg(tile& dest, dbuf& ds,
	double dep, dvec tl, Bezier const& bz, drect vp);

void draw_px_bezier(tile& dest, dbuf& ds,
	double dep, dvec tl, Bezier const& bz, drect vp, dcol col);
void draw_fill_bezier(tile& dest, dbuf& ds, 
	double dep, dvec tl, Bezier const& bz, drect vp, dcol col);

void draw_bezier(tile& dest, dvec tl,
	Bezier const& bz, double thk, drect vp, dcol col);
void draw_px_bezier(tile& dest, dvec tl,
	Bezier const& bz, drect vp, dcol col);
void draw_fill_bezier(tile& dest, dvec tl,
	Bezier const& bz, drect vp, dcol col);
