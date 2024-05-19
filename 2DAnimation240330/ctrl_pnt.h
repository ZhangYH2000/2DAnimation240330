#pragma once
#include "tile.h"

struct Cur;
struct Object;
struct CPnt {
	dvec o;
	Object* ob = NULL;
	bool hovered = false;
	bool dragged = false;

	dcol c_normal, c_frame, c_hovered, c_dragged;

	CPnt();
	virtual ~CPnt() {}
	double dep() const;
	virtual void Sync(Cur& cur) {}
	virtual void Upload(Cur& cur) {}

	void Update(Cur& cur);
	void Render(Cur& cur);
	void Discard(Cur& cur);
	void PreUpdate(Cur& cur);
};
