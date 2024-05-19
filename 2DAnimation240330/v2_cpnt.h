#pragma once
#include "ctrl_pnt.h"

struct Object;
struct V2CPnt : CPnt {
	V2CPnt() = default;
	void Sync(Cur& cur) override;
	void Upload(Cur& cur) override;
};
