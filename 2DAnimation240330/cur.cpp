#include "cur.h"
#include "ui.h"
#include "bgr.h"
#include "par.h"
#include "anim.h"
#include "layer.h"
#include "frame.h"
#include "canvas.h"
#include "object.h"
#include "special.h"
#include "timeline.h"
#include "curve.h"
#include "curve_editor.h"
#include "draw_tile.h"
#include "anm.h"
#include "clip.h"

vector<ptr<clip>> bgms;
int id_bgm = 0;

Cur::Cur() {
	w = 1800; h = 900; set_locale();
	print_console(L"���ڼ�������...");
	App::Init();
	print_console(L"����������.", true);
	print_console(L"���ڼ��ؿؼ�...");
	big_ft.h = 60;
	big_ft.init();
	mkp(ui)(*this); ui->Init(*this);
	mkp(bgr)(*this); Reset();
	print_console(L"�ؼ��������.", true);

	print_console(L"���ڼ�������...");
	rep(i, 0, 2) {
		auto path = L"music/bgm" + tw(i) + L".clip";
		auto cl = msh<clip>(path);
		bgms.push_back(cl);
	}
	print_console(L"���ּ������.", true);
}

#define cur (*this)
#include "my_def.h"

void Cur::Save(wstring const& nm) const {
	FILE* f = wfopen(nm, L"wb");
	if (!f) { return; }
	int sz = 0; fwtv(cmd); save_par(f);

	fwt(t_stop); fwt(frame_rate);
	fwt(left); fwt(top); fwt(right); fwt(bottom);

	sz = layers.size(); fwt(sz);
	for (auto& ly : layers) { ly->Save(f); }

	sz = curves.size(); fwt(sz);
	for (auto& cv : curves) {
		fwtv(cv.first);
		cv.second->Save(f);
	}

	fclose(f);
}
void Cur::Load(wstring const& nm) {
	FILE* f = wfopen(nm, L"rb");
	if (!f) { return; } Reset();
	int sz = 0; frdv(cmd); 
	tmp_cmd = cmd; load_par(f);

	frd(t_stop); frd(frame_rate);
	frd(left); frd(top); frd(right); frd(bottom);

	frd(sz); layers.clear();
	rep(i, 0, sz) {
		layers.push_back(msh<Layer>(cur, f));
	}
	layer_sel = &*layers.front();

	frd(sz);
	rep(i, 0, sz) {
		wstring nm; frdv(nm);
		curves[nm] = msh<curve>(f);
	}

	Execute(gl, Compile(cmd)); fclose(f);
}
void Cur::Output(wstring const& nm)  {
	prepare_buffer();
	if (left < right && top < bottom) {
		anim a(right - left, bottom - top, frame_rate);
		rep(i, 0, buffer.size()) {
			tile t(a.w, a.h, *buffer[i], cur.rect());
			a.ts.push_back(t);
		}
		a.save(nm);
	}
}
void Cur::Input(wstring const& nm) {
	bool ok = true;
	anim a(nm, &ok);
	if (a.ts.empty()) { return; }

	Reset();
	// ��� 2 ��һ�����������á�
	frame_rate = max(2, a.frame_rate);
	lysel.frs.resize(a.ts.size());
	rep(i, 0, a.ts.size()) {
		lysel.frs[i] = msh<Frame>(cur);
		// ����ĳߴ�϶���Ҫ�ĵġ�
		lysel.frs[i]->back = tile(bgr.w, bgr.h);
		auto& back = lysel.frs[i]->back;
		draw_tile(back, {}, back.rect(), a.ts[i], a.ts[i].rect());
	}
	left = top = 0;
	right = a.ts[0].w; bottom = a.ts[0].h;
	// ����Ҫע��Ǹ����͵ķ������⣬�һ�û����ر������
	t_stop = max(0, (int)a.ts.size() - 1);
}
void Cur::OutputCmp(wstring const& nm) {
	prepare_buffer();
	if (left < right && top < bottom) {
		anim a(right - left, bottom - top, frame_rate);
		rep(i, 0, buffer.size()) {
			tile t(a.w, a.h, *buffer[i], cur.rect());
			a.ts.push_back(t);
		}
		// �ظ��Ĵ����������Ժϲ��ģ������������ˡ�
		anm(a).save(nm);
	}
}
void Cur::InputCmp(wstring const& nm) {
	bool ok = true;
	anm cmp_a(nm, &ok);
	anim a(cmp_a);
	if (a.ts.empty()) { return; }

	// �ظ��Ĵ����������Ժϲ��ģ������������ˡ�
	Reset();
	// ��� 2 ��һ�����������á�
	frame_rate = max(2, a.frame_rate);
	lysel.frs.resize(a.ts.size());
	rep(i, 0, a.ts.size()) {
		lysel.frs[i] = msh<Frame>(cur);
		// ����ĳߴ�϶���Ҫ�ĵġ�
		lysel.frs[i]->back = tile(bgr.w, bgr.h);
		auto& back = lysel.frs[i]->back;
		draw_tile(back, {}, back.rect(), a.ts[i], a.ts[i].rect());
	}
	left = top = 0;
	right = a.ts[0].w; bottom = a.ts[0].h;
	// ����Ҫע��Ǹ����͵ķ������⣬�һ�û����ر������
	t_stop = max(0, (int)a.ts.size() - 1);
}
void Cur::Reset() {
	gl.clear(); init_def_fun(); pars.clear();

	play = false;
	time = 0;
	t_sel = 0;
	t_stop = 0;
	t_remain = 0;
	frame_rate = 8;
	buffer.clear();

	left = top = 0;
	right = bottom = bgr.h;

	ob_sel = NULL;
	mkp(cvs)();
	mkp(tmline)();
	layers.clear(); layers.push_back(msh<Layer>(cur));
	layer_sel = &*layers.front();

	mkp(cv_editor)(); curves.clear();
}
void Cur::Update() {
	bgr.PreUpdate(*this);
	cvs->PreUpdate(*this);
	cv_editor->PreUpdate(cur);

	for (auto& ob : lysel.obs) { ob->PreUpdate(*this, lysel); }

	tmline->PreUpdate(*this);
	ui.PreUpdate(*this);
	basic_update();

	if (!bgms.empty()) {
		auto& cl = *bgms[id_bgm];
		if (cl.csp >= cl.n()) {
			cl.csp = 0;
			id_bgm = (id_bgm + 1) % bgms.size();
		}

		if (!mute) {
			auto& cl = *bgms[id_bgm];
			cl.play(wv.wvin);
		}
	}

	if (!kb) {
		if (kbc(L'F')) {
			auto& ly = *layer_sel;
			rep(i, ly.frs.size(), time + 1) {
				ly.frs.push_back(NULL);
			}
			ly.NewFrame(cur, tm);
			cvs->Discard(cur);
			if (posel) { osel.Discard(cur); }
		}
		if (kbc(L'I')) {
			lysel.frs.push_back(NULL);
			// ����ȷʵ�Ǽ� 2��ûë����
			for (int i = lysel.frs.size() - 2; i >= tm; --i) {
				lysel.frs[i + 1] = lysel.frs[i];
			}

			lysel.frs[tm] = tm == 0 ?
				msh<Frame>(*lysel.frs[0]) : NULL;
			if (t_stop >= tm) { t_stop += 1; }
		}
		if (kbc(L'R')) {
			rep(i, tm, lysel.frs.size() - 1) {
				if (i == 0 && !lysel.frs[1]) { continue; }
				lysel.frs[i] = lysel.frs[i + 1];
			}
			if (lysel.frs.size() > tm && tm > 0) {
				lysel.frs.pop_back();
			}
			if (t_stop >= tm) { t_stop = max(0, t_stop - 1); }
		}
		if (kbc(L' ')) { play_pause(); }
		if (kbc(L'S')) {
			if (!cur.play) { t_stop = tm; }
		}
		if (kbc(L'C') && kbd[VK_CONTROL]) {
			if (!play) {
				copy = true;
				t0_copy = min(t_sel, time);
				t1_copy = max(t_sel, time);
			}
		}
		if (kbc(L'X') && kbd[VK_CONTROL]) {
			// ���������ʵ�Ƿǳ��ļ��ߡ�
			// �������︴���ǰ���ʱ�临�ƣ��޷�ʵ�ּ����Ĺ��ܡ�
			copy = false;
		}
		if (kbc(L'V') && kbd[VK_CONTROL]) {
			// ��ʵҲ���Ը�һ��ȫ�ָ��ƣ���������ͼ��ȫ�����ơ�
			if (copy && !play) {
				auto& ly = *layer_sel;
				rep(i, ly.frs.size(), time + t1_copy - t0_copy + 1) {
					ly.frs.push_back(NULL);
				}
				rep(i, 0, t1_copy - t0_copy + 1) {
					if (tm + i == 0 && !ly.frs[t0_copy]) {
						ly.NewFrame(cur, 0);
						continue;
					}
					ly.frs[tm + i] = ly.frs[t0_copy + i] ? 
						msh<Frame>(*ly.frs[t0_copy + i]) : NULL;
				}
			}
		}
		if (kbc(VK_DELETE)) {
			if (!play) {
				int t0 = min(tm, t_sel);
				int t1 = max(tm, t_sel);
				rep(t, t0, t1 + 1) { del_frame(t); }
				cvs->Discard(cur);
				if (posel) { osel.Discard(cur); }
			}
		}
	}

	if (play) {
		t_remain -= dt;
		if (t_remain < 0) {
			t_remain += 1.0 / frame_rate;
			t_remain = max(0.0, t_remain);
			tm = (tm + 1) % (t_stop + 1);
		}
		tm = min(tm, t_stop);
	}

	// ���� canvas �� bgr ��˳��Ҫע�⣬��֪����������ô�ġ�
	cvs->Update(*this);
	bgr.Update(*this);
	
	for (auto& ob : lysel.obs) { ob->Update(*this, lysel); }

	lysel.del = false;
	layers.erase(remove_if(layers.begin(), layers.end(),
		[](ptr<Layer>& ly) { return ly->del; }), layers.end());

	if (posel && osel.del) { posel = NULL; }
	for (auto& ly : layers) {
		for (auto& fr : ly->frs) if (fr) {
			auto& obs = fr->obs;
			for (auto it = obs.begin(); it != obs.end();) {
				if (it->first->del) { it = obs.erase(it); }
				else { ++it; }
			}
		}

		auto& obs = ly->obs;
		obs.erase(remove_if(obs.begin(), obs.end(),
			[](ptr<Object>& ob) { return ob->del; }), obs.end());
	}

	tmline->Update(*this);
	tmline->Render(*this);
	cv_editor->Update(cur);
	ui.Update(*this);
}

void Cur::play_pause() {
	if (play) {
		play = false;
		t_sel = time;
		cvs->Discard(cur);
		if (posel) { osel.Discard(cur); }
	} else {
		t_remain = 1.0 / frame_rate;
		play = true;
		prepare_buffer();
		cvs->Discard(cur);
		if (posel) { osel.Discard(cur); }
	}
}

drect Cur::rect() const {
	if (left >= right || top >= bottom) { return {}; }
	return { { left, top }, right - left, bottom - top };
}
void Cur::prepare_buffer() {
	buffer.clear();
	rep(i, 0, t_stop + 1) {
		// �Ժ���������Ϊ��׼��С�ˡ�
		buffer.push_back(msh<tile>(bgr.w, bgr.h));
	}

	rep(j, 0, buffer.size()) {
		for (int i = cur.layers.size() - 1; i >= 0; --i) {
			auto& ly = *cur.layers[i];
			if (!ly.show) { continue; }
			auto& img = ly.frs[ly.prv(j)]->back;
			draw_tile(*buffer[j], {}, buffer[j]->rect(), img, img.rect());
			for (auto& ob : ly.obs) { ob->Render(cur, ly, j, *buffer[j]); }
		}
	}
}
void Cur::del_frame(int t) {
	auto& ly = lysel;
	if (t >= ly.frs.size()) { return; }
	if (t == 0) {
		ly.NewFrame(cur, 0); return;
	}

	ly.frs[t] = NULL;
}

void Cur::save_par(FILE* f) const {
	int sz = pars.size(); fwt(sz);
	for (auto p : pars) { p->save(f); }
}
void Cur::load_par(FILE* f) {
	int sz = 0; frd(sz);
	rep(i, 0, sz) { pars.push_back(msh<param>(f)); }
}
void Cur::init_def_fun() {
	{
		auto f = [this](vector<ptr<Var>> const& in) {
			if (in.size() >= 6) {
				int len = in[0]->num;
				double scl = in[1]->num;
				double v_scl = in[2]->num;
				int n = in[3]->num;
				int w = in[4]->num;
				int h = in[5]->num;
				Mandelbrot(cur, len, scl, v_scl,
					vec2(-1.401155, 0), n, w, h);
			}
			return msh<Var>();
		};
		gl[L"Mandelbrot"] = msh<Var>(f);
	}

	{
		auto f = [this](vector<ptr<Var>> const& in) {
			if (in.size() >= 0) {
				for (auto &ly : layers)
				for (auto& fr : ly->frs) if (fr) {
					fr->back = flip_x(fr->back);
				}
			}
			return msh<Var>();
		};
		gl[L"flip_x"] = msh<Var>(f);
	}
}
void Cur::basic_update() {
	title = loc(L"title");
	if (gl.find(L"dbstr") != gl.end()) { dbstr = gl[L"dbstr"]->str; }
	if (gl.find(L"update") != gl.end()) {
		auto f = gl[L"update"];  Execute(gl, f->procs);
	}

	pars.erase(remove_if(pars.begin(), pars.end(),
		[](ptr<param> p) { return p->del; }), pars.end());
	for (auto& p : pars) { gl[p->nm] = msh<Var>(p->val); }
}
