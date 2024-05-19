#pragma once
#include "ctrl_pnt.h"

struct Object;
struct RotCPnt : CPnt {
	RotCPnt() = default;
	void Sync(Cur& cur) override;
	void Upload(Cur& cur) override;
};
