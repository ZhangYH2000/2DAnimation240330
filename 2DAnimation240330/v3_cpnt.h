#pragma once
#include "ctrl_pnt.h"

struct Object;
struct V3CPnt : CPnt {
	V3CPnt() = default;
	void Sync(Cur& cur) override;
	void Upload(Cur& cur) override;
};
