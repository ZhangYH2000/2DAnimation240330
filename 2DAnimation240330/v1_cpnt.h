#pragma once
#include "ctrl_pnt.h"

struct Object;
struct V1CPnt : CPnt {
	V1CPnt() = default;
	void Sync(Cur& cur) override;
	void Upload(Cur& cur) override;
};
