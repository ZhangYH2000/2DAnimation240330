#pragma once
#include "vec2.h"

struct Cur;
void Mandelbrot(Cur& cur, int len, 
	double scl, double v_scl, vec2 p, int n, int w, int h);
