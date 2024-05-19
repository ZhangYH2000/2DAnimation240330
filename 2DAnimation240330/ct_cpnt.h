#pragma once
#include "ctrl_pnt.h"

struct Object;
struct CtCPnt : CPnt {
	CtCPnt() = default;
	void Sync(Cur& cur) override;
	void Upload(Cur& cur) override;
};

