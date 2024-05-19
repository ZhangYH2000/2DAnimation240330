#pragma once
#include "ctrl_pnt.h"

struct TxtCPnt0 : CPnt {
	TxtCPnt0() = default;
	void Sync(Cur& cur) override;
	void Upload(Cur& cur) override;
};
