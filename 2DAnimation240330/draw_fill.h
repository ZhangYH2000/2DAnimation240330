#pragma once
#include "tile.h"

void draw_fill_poly(tile& dest, dbuf& ds,
	double dep, vector<dvec> const& vs, drect vp, dcol col);
void draw_fill_poly(tile& dest, vector<dvec> const& vs, drect vp, dcol col);

// ��Ȼ��ȫ����ʵ�֣��������ﻹ��û�п���͸������䡣
void draw_fill(tile& dest, dvec p, drect vp, dcol c);
