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
	// ���������˳���Ƕ�ȡ�ͱ����˳�򣬲��ܵ�����
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
