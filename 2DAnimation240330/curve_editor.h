#pragma once
#include "utils.h"

struct Cur;
struct curve;

struct CurveEditor {
	bool valid = false;
	bool edit = false;
	bool hovered = false;
	bool drawing = false;

	ptr<curve> cv;

	CurveEditor();
	void Update(Cur& cur);
	void Discard(Cur& cur);
	void PreUpdate(Cur& cur);
};
