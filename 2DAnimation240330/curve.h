#pragma once
#include "vec2.h"

struct Cur;
struct node {
	double u = 0;
	dvec p;
};

struct curve {
	vector<node> nds;

	curve() = default;
	curve(FILE* f);
	void Save(FILE* f);
	void render(Cur& cur);

	void normalize();
	vec2 at(double t);
};
