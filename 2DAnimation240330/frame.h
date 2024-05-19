#pragma once
#include "tile.h"

struct Cur;
struct Layer;
struct Object;
struct ObInfo;

struct Frame {
	tile back;
	map<Object*, ptr<ObInfo>> obs;

	Frame(Cur& cur);
	Frame(Frame const& fr);
	Frame(Layer& ly, FILE* f);
	void Save(Layer& ly, FILE* f) const;
};
