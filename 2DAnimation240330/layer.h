#pragma once
#include "tile.h"

struct Cur;
struct Frame;
struct Object;
struct ObInfo;
struct Layer {
	dcol c;
	bool del = false;
	bool show = true;
	wstring nm;
	// 下面两项的顺序是读取和保存的顺序，不能调换。
	vector<ptr<Object>> obs;
	vector<ptr<Frame>> frs;

	Layer(Cur &cur);
	Layer(Cur& cur, FILE* f);
	void Save(FILE* f);
	int prv(int t) const;
	int nxt(int t) const;
	void NewFrame(Cur& cur, int t);
	ObInfo interp(Object* ob, int t);
};
