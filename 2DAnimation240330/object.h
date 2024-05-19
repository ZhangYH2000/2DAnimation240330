#pragma once
#include "tile.h"

struct Cur;
struct anim;
struct CPnt;
struct Layer;
struct Bezier;

int constexpr OB_BEZIER = 0;
int constexpr OB_ANIM = 1;
int constexpr OB_ELLIPSE = 2;

struct Object {
	int typ = 0;
	bool del = false;
	bool show = true;
	wstring nm;
	vector<ptr<CPnt>> cpnts;

	dcol c_inner, c_border;
	int thick = 0;
	bool single_px = false;
	bool draw_inner = true;
	bool draw_border = true;

	bool use_curve = false;
	wstring nm_curve;

	// 为了方便读取和保存的话，搞个动画库可能更好。
	ptr<anim> an;
	double speed = 1;

	Object();
	Object(FILE* f);
	void Save(FILE* f) const;
	void Load(Cur& cur, Layer& ly);
	void Update(Cur& cur, Layer& ly);
	void Render(Cur& cur, Layer& ly);
	void Render(Cur& cur, Layer& ly, int t, tile& dest);
	void Discard(Cur& cur);
	void PreUpdate(Cur& cur, Layer& ly);
};

struct ObInfo {
	ptr<Bezier> bz;

	bool show = true;
	vec2 ct;
	double ang = 0;
	double w = 0, h = 0;
	double t_curve = 0;

	ObInfo() = default;
	ObInfo(ObInfo const& ob);
	ObInfo(FILE* f);
	void Save(FILE* f) const;
};
