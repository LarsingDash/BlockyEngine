//
// Created by 11896 on 26/11/2024.
//
#include "KeyInput.hpp"

KeyInput SDLKeyToCustomKey(SDL_Keycode sdlKey) {
	switch (sdlKey) {
		case SDLK_a: return KeyInput::KEY_A;
		case SDLK_b: return KeyInput::KEY_B;
		case SDLK_c: return KeyInput::KEY_C;
		case SDLK_d: return KeyInput::KEY_D;
		case SDLK_e: return KeyInput::KEY_E;
		case SDLK_f: return KeyInput::KEY_F;
		case SDLK_g: return KeyInput::KEY_G;
		case SDLK_h: return KeyInput::KEY_H;
		case SDLK_i: return KeyInput::KEY_I;
		case SDLK_j: return KeyInput::KEY_J;
		case SDLK_k: return KeyInput::KEY_K;
		case SDLK_l: return KeyInput::KEY_L;
		case SDLK_m: return KeyInput::KEY_M;
		case SDLK_n: return KeyInput::KEY_N;
		case SDLK_o: return KeyInput::KEY_O;
		case SDLK_p: return KeyInput::KEY_P;
		case SDLK_q: return KeyInput::KEY_Q;
		case SDLK_r: return KeyInput::KEY_R;
		case SDLK_s: return KeyInput::KEY_S;
		case SDLK_t: return KeyInput::KEY_T;
		case SDLK_u: return KeyInput::KEY_U;
		case SDLK_v: return KeyInput::KEY_V;
		case SDLK_w: return KeyInput::KEY_W;
		case SDLK_x: return KeyInput::KEY_X;
		case SDLK_y: return KeyInput::KEY_Y;
		case SDLK_z: return KeyInput::KEY_Z;
		case SDLK_SPACE: return KeyInput::KEY_SPACE;
		case SDLK_RETURN: return KeyInput::KEY_ENTER;
		case SDLK_ESCAPE: return KeyInput::KEY_ESCAPE;
		default: return KeyInput::KEY_UNKNOWN;
	}
}