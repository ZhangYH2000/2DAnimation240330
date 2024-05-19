#pragma once
#include "ctrl_pnt.h"

struct Object;
struct V0CPnt : CPnt {
	V0CPnt() = default;
	void Sync(Cur& cur) override;
	void Upload(Cur& cur) override;
};
