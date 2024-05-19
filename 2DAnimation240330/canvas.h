#pragma once
#include "tile.h"

struct Cur;
struct anim;
struct Bezier;

struct TxtCPnt0;
struct TxtCPnt1;

int constexpr CVS_BRUSH = 0;
int constexpr CVS_BEZIER = 1;
int constexpr CVS_ANIM = 2;
int constexpr CVS_TEXT = 3;
int constexpr CVS_ELLIPSE = 4;
int constexpr CVS_ERASE = 5;
int constexpr CVS_FILL = 6;

struct Canvas {
	int mode = 0;
	bool moved = false;
	bool brushed = false;
	bool hovered = false;
	bool wheeled = false;
	int stage = 0;
	// stage 和 brushed 其实有重合的地方。

	dcol c_inner, c_border;
	int thick = 0;
	bool single_px = false;
	bool draw_inner = true;
	bool draw_border = true;
	ptr<Bezier> bz;

	ptr<TxtCPnt0> cp0;
	ptr<TxtCPnt1> cp1;

	dvec tl;
	int w = 0, h = 0;
	wstring nm_an;
	ptr<anim> an;
	bool ready = false;

	int h_text = 0;
	wstring text;

	Canvas();
	void Update(Cur& cur);
	void Render(Cur& cur);
	void Discard(Cur& cur);
	void PreUpdate(Cur& cur);
};
