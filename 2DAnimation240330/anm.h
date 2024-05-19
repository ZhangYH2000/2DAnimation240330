#pragma once
#include "tile.h"

struct anim;

struct col_seg {
	dcol c;
	BYTE a = 0;
	int n = 0;

	col_seg() = default;
	col_seg(dcol c, BYTE a) : c(c), a(a), n(1) {}
	col_seg(FILE* f);
	void save(FILE* f) const;
};

struct tle {
	int w = 0;
	int h = 0;
	vector<col_seg> cs;

	tle() = default;
	explicit tle(tile const& t);
	explicit operator tile();
	tle(FILE* f);
	void save(FILE* f) const;
};

// ��ʵѹ�������Ƶ��ȡ�ٶ�Ҳ���ӿ졣
// ��֪��ԭʼ��Ƶ�ļ���ʽ����ɶ��ֵ��
struct anm {
	int w = 0;
	int h = 0;
	int frame_rate = 0;
	vector<tle> ts;

	anm() = default;
	anm(FILE* f);
	explicit anm(anim const& an);
	explicit operator anim();
	anm(wstring const& nm, bool* ok = NULL);
	void save(FILE* f);
	void save(wstring const& nm);
};
