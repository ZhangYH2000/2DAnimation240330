#pragma once
#include "ctrl_pnt.h"

struct Object;
struct BzCPnt : CPnt {
	int id_vs = 0, id_v = 0;

	BzCPnt() = default;
	void Sync(Cur& cur) override;
	void Upload(Cur& cur) override;
};
