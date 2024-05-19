#pragma once
#include "app.h"
#include "var.h"

struct Layer;
struct Canvas;
struct Object;
struct Timeline;
struct curve;
struct CurveEditor;

struct UI;
struct Bgr;
struct param;
struct Cur : App {
	bool play = false;
	int time = 0;
	int t_sel = 0;
	int t_stop = 0;
	int frame_rate = 0;

	bool mute = false;

	int left = 0;
	int right = 0;
	int top = 0;
	int bottom = 0;

	// 按照时间复制会带来非常多的问题，比如在复制区域有重叠的时候。
	// 但是对这个程序来说复制不是很重要的事情，不知道专门对待。
	bool copy = false;
	int t0_copy = 0;
	int t1_copy = 0;

	font big_ft;

	double t_remain = 0;
	vector<ptr<tile>> buffer;

	ptr<Canvas> cvs;
	ptr<Timeline> tmline;
	vector<ptr<Layer>> layers;
	ptr<CurveEditor> cv_editor;
	map<wstring, ptr<curve>> curves;
	
	Object* ob_sel = NULL;
	Layer* layer_sel = NULL;

	bool follow_play = false;
	bool show_before = false;
	bool show_after = false;
	bool edit_all = false;

	ptr<UI> ui;
	ptr<Bgr> bgr;

	Scope gl;
	wstring dbstr, cmd, tmp_cmd;
	vector<ptr<param>> pars;

	Cur();
	void Save(wstring const& nm) const;
	void Load(wstring const& nm);
	void Output(wstring const& nm);
	void Input(wstring const& nm);
	void OutputCmp(wstring const& nm);
	void InputCmp(wstring const& nm);
	void Reset();
	void Update() override;

	void play_pause();
	drect rect() const;
	void prepare_buffer();
	void del_frame(int t);

	void save_par(FILE* f) const;
	void load_par(FILE* f);
	void init_def_fun();
	void basic_update();
};
