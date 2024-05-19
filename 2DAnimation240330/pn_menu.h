#pragma once
#include "panel.h"
#include "button.h"
#include "ctrl_list.h"

struct BtPause : Button {
	BtPause();
	void Update(App& app) override;
	void OnClick(App& app) override;
};
struct BtMute : Button {
	BtMute();
	void Update(App& app) override;
	void OnClick(App& app) override;
};

struct BtMainMenu : BtLan {
	BtMainMenu();
	void OnClick(App& app) override;
};

struct BtCanvas : BtLan {
	BtCanvas();
	void OnClick(App& app) override;
};

struct BtCvsBrush : BtLan {
	BtCvsBrush();
	void Update(App& app) override;
	void OnClick(App& app) override;
};
struct BtCvsBezier : BtLan {
	BtCvsBezier();
	void Update(App& app) override;
	void OnClick(App& app) override;
};
struct BtCvsAnim : BtLan {
	BtCvsAnim();
	void Update(App& app) override;
	void OnClick(App& app) override;
};
struct BtCvsText : BtLan {
	BtCvsText();
	void Update(App& app) override;
	void OnClick(App& app) override;
};
struct BtCvsEllipse : BtLan {
	BtCvsEllipse();
	void Update(App& app) override;
	void OnClick(App& app) override;
};
struct BtCvsEraser : BtLan {
	BtCvsEraser();
	void Update(App& app) override;
	void OnClick(App& app) override;
};
struct BtCvsFill : BtLan {
	BtCvsFill();
	void Update(App& app) override;
	void OnClick(App& app) override;
};

struct PnMenu : Panel {
	ptr<BtPause> bt_pause;
	ptr<BtMute> bt_mute;
	ptr<BtFPn> bt_global;
	ptr<BtCanvas> bt_canvas;
	ptr<BtFPn> bt_object;
	ptr<BtFPn> bt_objects;
	ptr<BtFPn> bt_layer;
	ptr<BtFPn> bt_curve;
	ptr<BtFPn> bt_cmd;
	ptr<BtFPn> bt_par;
	ptr<BtFPn> bt_lang;
	ptr<BtFPn> bt_about;
	ptr<CtrlListY> cly_main;

	ptr<BtMainMenu> bt_main_menu;
	ptr<BtCvsBrush> bt_brush;
	ptr<BtCvsBezier> bt_bezier;
	ptr<BtCvsAnim> bt_anim;
	ptr<BtCvsText> bt_text;
	ptr<BtCvsEllipse> bt_ellipse;
	ptr<BtCvsEraser> bt_eraser;
	ptr<BtCvsFill> bt_fill;
	ptr<CtrlListY> cly_canvas;

	ptr<CtrlListY> cly;
	PnMenu(App& app);
};
