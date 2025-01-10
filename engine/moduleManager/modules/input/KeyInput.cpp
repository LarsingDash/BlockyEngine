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
		case SDLK_UP: return KeyInput::KEY_UP;
		case SDLK_DOWN: return KeyInput::KEY_DOWN;
		case SDLK_LEFT: return KeyInput::KEY_LEFT;
		case SDLK_RIGHT: return KeyInput::KEY_RIGHT;
		case SDLK_F1: return KeyInput::KEY_F1;
		case SDLK_F2: return KeyInput::KEY_F2;
		case SDLK_F3: return KeyInput::KEY_F3;
		case SDLK_F4: return KeyInput::KEY_F4;
		case SDLK_F5: return KeyInput::KEY_F5;
		case SDLK_F6: return KeyInput::KEY_F6;
		case SDLK_F7: return KeyInput::KEY_F7;
		case SDLK_F8: return KeyInput::KEY_F8;
		case SDLK_F9: return KeyInput::KEY_F9;
		case SDLK_F10: return KeyInput::KEY_F10;
		case SDLK_F11: return KeyInput::KEY_F11;
		case SDLK_F12: return KeyInput::KEY_F12;
		case SDLK_1: return KeyInput::KEY_1;
		case SDLK_2: return KeyInput::KEY_2;
		case SDLK_3: return KeyInput::KEY_3;
		case SDLK_4: return KeyInput::KEY_4;
		case SDLK_5: return KeyInput::KEY_5;
		case SDLK_6: return KeyInput::KEY_6;
		case SDLK_7: return KeyInput::KEY_7;
		case SDLK_8: return KeyInput::KEY_8;
		case SDLK_9: return KeyInput::KEY_9;
		case SDLK_0: return KeyInput::KEY_0;
		case SDLK_KP_1: return KeyInput::KEY_NUMPAD_1;
		case SDLK_KP_2: return KeyInput::KEY_NUMPAD_2;
		case SDLK_KP_3: return KeyInput::KEY_NUMPAD_3;
		case SDLK_KP_4: return KeyInput::KEY_NUMPAD_4;
		case SDLK_KP_5: return KeyInput::KEY_NUMPAD_5;
		case SDLK_KP_6: return KeyInput::KEY_NUMPAD_6;
		case SDLK_KP_7: return KeyInput::KEY_NUMPAD_7;
		case SDLK_KP_8: return KeyInput::KEY_NUMPAD_8;
		case SDLK_KP_9: return KeyInput::KEY_NUMPAD_9;
		case SDLK_KP_0: return KeyInput::KEY_NUMPAD_0;
		case SDLK_KP_ENTER: return KeyInput::KEY_NUMPAD_ENTER;
		case SDLK_KP_PLUS: return KeyInput::KEY_NUMPAD_PLUS;
		case SDLK_KP_MINUS: return KeyInput::KEY_NUMPAD_MINUS;
		case SDLK_KP_MULTIPLY: return KeyInput::KEY_NUMPAD_MULTIPLY;
		case SDLK_KP_DIVIDE: return KeyInput::KEY_NUMPAD_DIVIDE;
		case SDLK_KP_PERIOD: return KeyInput::KEY_NUMPAD_PERIOD;
		case SDLK_KP_COMMA: return KeyInput::KEY_NUMPAD_COMMA;
		case SDLK_LCTRL: return KeyInput::KEY_LCTRL;
		case SDLK_RCTRL: return KeyInput::KEY_RCTRL;
		case SDLK_LSHIFT: return KeyInput::KEY_LSHIFT;
		case SDLK_RSHIFT: return KeyInput::KEY_RSHIFT;
		case SDLK_TAB: return KeyInput::KEY_TAB;
		case SDLK_CAPSLOCK: return KeyInput::KEY_CAPSLOCK;

		default: return KeyInput::KEY_UNKNOWN;
	}
}