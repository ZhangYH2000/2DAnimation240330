#pragma once
#include "ctrl_pnt.h"

struct TxtCPnt1 : CPnt {
	TxtCPnt1() = default;
	void Sync(Cur& cur) override;
	void Upload(Cur& cur) override;
};
