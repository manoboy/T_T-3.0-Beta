#include "Globals.h"


namespace Offsets
{
	DWORD ViewMatrix = 0x04a0e164;
	DWORD LocalPlayer = 0x00a76cdc;
	DWORD EntityList = 0x04a18bd4;
	DWORD RadarBaseOffset = 0x04a4d86c;
	DWORD SensivityAddress = 0x00a7c474;
	DWORD AttackAddres = 0x02e8aaec;
	DWORD RadarBaseAddress = 0x0;
}

namespace GlobalVariables
{
	bool ExitCheat = false;

	DWORD ClientAddress = NULL;

	int MaxPlayers = 64;

	float MouseMultiplyer = 1.0f;

}

void MouseMove(float x, float y)
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dx = (LONG)x;
	Input.mi.dy = (LONG)y;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &Input, sizeof(INPUT));
}
void MouseButton(int Type)
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = Type;
	::SendInput(1, &Input, sizeof(INPUT));
}
void MouseUP(int Type)
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = Type;
	::SendInput(1, &Input, sizeof(INPUT));
}


char *AimBonesNames[4] = { _OnceXOR("Head"), _OnceXOR("Neck"), _OnceXOR("Chest"), _OnceXOR("Stomach") };

char *KeyNames[256] = {
	_OnceXOR("No HotKey"),
	_OnceXOR("Left button"),
	_OnceXOR("Right button"),
	_OnceXOR("Control-break"),
	_OnceXOR("Middle button"),
	_OnceXOR("X1 button"),
	_OnceXOR("X2 button"),
	_OnceXOR("Undefined"),//7
	_OnceXOR("BACKSPACE"),
	_OnceXOR("TAB"),
	_OnceXOR("Reserved"),//10
	_OnceXOR("Reserved"),//11
	_OnceXOR("CLEAR"),
	_OnceXOR("ENTER"),
	_OnceXOR("Undefined"),//14
	_OnceXOR("Undefined"),//15
	_OnceXOR("SHIFT"),
	_OnceXOR("CTRL"),
	_OnceXOR("ALT"),
	_OnceXOR("PAUSE"),
	_OnceXOR("CAPS LOCK"),
	_OnceXOR("IME Kana"),
	_OnceXOR("Undefined"),//22
	_OnceXOR("IME Junja"),
	_OnceXOR("IME final"),
	_OnceXOR("IME Hanja"),
	_OnceXOR("Undefined"),//26
	_OnceXOR("ESC"),
	_OnceXOR("IME convert"),
	_OnceXOR("IME nonconvert"),
	_OnceXOR("IME accept"),
	_OnceXOR("IME mode change request"),
	_OnceXOR("SPACEBAR"),
	_OnceXOR("PAGE UP"),
	_OnceXOR("PAGE DOWN"),
	_OnceXOR("END"),
	_OnceXOR("HOME"),
	_OnceXOR("LEFT ARROW"),
	_OnceXOR("UP ARROW"),
	_OnceXOR("RIGHT ARROW"),
	_OnceXOR("DOWN ARROW"),
	_OnceXOR("SELECT"),
	_OnceXOR("PRINT"),
	_OnceXOR("EXECUTE"),
	_OnceXOR("PRINT SCREEN"),
	_OnceXOR("INS"),
	_OnceXOR("DEL"),
	_OnceXOR("HELP"),
	_OnceXOR("0"),
	_OnceXOR("1"),
	_OnceXOR("2"),
	_OnceXOR("3"),
	_OnceXOR("4"),
	_OnceXOR("5"),
	_OnceXOR("6"),
	_OnceXOR("7"),
	_OnceXOR("8"),
	_OnceXOR("9"),
	_OnceXOR("Undefined"), //58
	_OnceXOR("Undefined"), //59
	_OnceXOR("Undefined"),//60
	_OnceXOR("Undefined"),//61
	_OnceXOR("Undefined"),//62
	_OnceXOR("Undefined"),//63
	_OnceXOR("Undefined"),//64
	_OnceXOR("A"),
	_OnceXOR("B"),
	_OnceXOR("C"),
	_OnceXOR("D"),
	_OnceXOR("E"),
	_OnceXOR("F"),
	_OnceXOR("G"),
	_OnceXOR("H"),
	_OnceXOR("I"),
	_OnceXOR("J"),
	_OnceXOR("K"),
	_OnceXOR("L"),
	_OnceXOR("M"),
	_OnceXOR("N"),
	_OnceXOR("O"),
	_OnceXOR("P"),
	_OnceXOR("Q"),
	_OnceXOR("R"),
	_OnceXOR("S"),
	_OnceXOR("T"),
	_OnceXOR("U"),
	_OnceXOR("V"),
	_OnceXOR("W"),
	_OnceXOR("X"),
	_OnceXOR("Y"),
	_OnceXOR("Z"),
	_OnceXOR("Left Windows"),
	_OnceXOR("Right Windows"),
	_OnceXOR("Applications"),
	_OnceXOR("Reserved"),//94
	_OnceXOR("Computer Sleep"),
	_OnceXOR("NUMPAD 0"),
	_OnceXOR("NUMPAD 1"),
	_OnceXOR("NUMPAD 2"),
	_OnceXOR("NUMPAD 3"),
	_OnceXOR("NUMPAD 4"),
	_OnceXOR("NUMPAD 5"),
	_OnceXOR("NUMPAD 6"),
	_OnceXOR("NUMPAD 7"),
	_OnceXOR("NUMPAD 8"),
	_OnceXOR("NUMPAD 9"),
	_OnceXOR("Multiply"),
	_OnceXOR("Add"),
	_OnceXOR("Separator"),
	_OnceXOR("Subtract"),
	_OnceXOR("Decimal"),
	_OnceXOR("Divide"),
	_OnceXOR("F1"),
	_OnceXOR("F2"),
	_OnceXOR("F3"),
	_OnceXOR("F4"),
	_OnceXOR("F5"),
	_OnceXOR("F6"),
	_OnceXOR("F7"),
	_OnceXOR("F8"),
	_OnceXOR("F9"),
	_OnceXOR("F10"),
	_OnceXOR("F11"),
	_OnceXOR("F12"),
	_OnceXOR("F13"),
	_OnceXOR("F14"),
	_OnceXOR("F15"),
	_OnceXOR("F16"),
	_OnceXOR("F17"),
	_OnceXOR("F18"),
	_OnceXOR("F19"),
	_OnceXOR("F20"),
	_OnceXOR("F21"),
	_OnceXOR("F22"),
	_OnceXOR("F23"),
	_OnceXOR("F24"),
	_OnceXOR("Unassigned"),//136
	_OnceXOR("Unassigned"),//137
	_OnceXOR("Unassigned"),//138
	_OnceXOR("Unassigned"),//139
	_OnceXOR("Unassigned"),//140
	_OnceXOR("Unassigned"),//141
	_OnceXOR("Unassigned"),//142
	_OnceXOR("Unassigned"),//143
	_OnceXOR("NUM LOCK"),
	_OnceXOR("SCROLL LOCK"),
	_OnceXOR("OEM specific"),//146
	_OnceXOR("OEM specific"),//147
	_OnceXOR("OEM specific"),//148
	_OnceXOR("OEM specific"),//149
	_OnceXOR("OEM specific"),//150
	_OnceXOR("Unassigned"),//151
	_OnceXOR("Unassigned"),//152
	_OnceXOR("Unassigned"),//153
	_OnceXOR("Unassigned"),//154
	_OnceXOR("Unassigned"),//155
	_OnceXOR("Unassigned"),//156
	_OnceXOR("Unassigned"),//157
	_OnceXOR("Unassigned"),//158
	_OnceXOR("Unassigned"),//159
	_OnceXOR("Left SHIFT"),
	_OnceXOR("Right SHIFT"),
	_OnceXOR("Left CONTROL"),
	_OnceXOR("Right CONTROL"),
	_OnceXOR("Left MENU"),
	_OnceXOR("Right MENU"),
	_OnceXOR("Browser Back"),
	_OnceXOR("Browser Forward"),
	_OnceXOR("Browser Refresh"),
	_OnceXOR("Browser Stop"),
	_OnceXOR("Browser Search"),
	_OnceXOR("Browser Favorites"),
	_OnceXOR("Browser Start and Home"),
	_OnceXOR("Volume Mute"),
	_OnceXOR("Volume Down"),
	_OnceXOR("Volume Up"),
	_OnceXOR("Next Track"),
	_OnceXOR("Previous Track"),
	_OnceXOR("Stop Media"),
	_OnceXOR("Play/Pause Media"),
	_OnceXOR("Start Mail"),
	_OnceXOR("Select Media"),
	_OnceXOR("Start Application 1"),
	_OnceXOR("Start Application 2"),
	_OnceXOR("Reserved"),//184
	_OnceXOR("Reserved"),//185
	_OnceXOR(";"),
	_OnceXOR("+"),
	_OnceXOR(","),
	_OnceXOR("-"),
	_OnceXOR("."),
	_OnceXOR("/"),
	_OnceXOR("`"),
	_OnceXOR("Reserved"),//193
	_OnceXOR("Reserved"),//194
	_OnceXOR("Reserved"),//195
	_OnceXOR("Reserved"),//196
	_OnceXOR("Reserved"),//197
	_OnceXOR("Reserved"),//198
	_OnceXOR("Reserved"),//199
	_OnceXOR("Reserved"),//200
	_OnceXOR("Reserved"),//201
	_OnceXOR("Reserved"),//202
	_OnceXOR("Reserved"),//203
	_OnceXOR("Reserved"),//204
	_OnceXOR("Reserved"),//205
	_OnceXOR("Reserved"),//206
	_OnceXOR("Reserved"),//207
	_OnceXOR("Reserved"),//208
	_OnceXOR("Reserved"),//209
	_OnceXOR("Reserved"),//210
	_OnceXOR("Reserved"),//211
	_OnceXOR("Reserved"),//212
	_OnceXOR("Reserved"),//213
	_OnceXOR("Reserved"),//214
	_OnceXOR("Reserved"),//215
	_OnceXOR("Unassigned"),//216
	_OnceXOR("Unassigned"),//217
	_OnceXOR("Unassigned"),//218
	_OnceXOR("["),
	_OnceXOR("\\"),
	_OnceXOR("]"),
	_OnceXOR("\""),
	_OnceXOR("Unknown"),
	_OnceXOR("Reserved"),//224
	_OnceXOR("OEM specific"),
	_OnceXOR("Unknown"),
	_OnceXOR("OEM specific"),
	_OnceXOR("OEM specific"),
	_OnceXOR("IME PROCESS"),
	_OnceXOR("OEM specific"),
	_OnceXOR("VK_PACKET"),
	_OnceXOR("Unassigned"),//232
	_OnceXOR("OEM specific"),//233
	_OnceXOR("OEM specific"),//234
	_OnceXOR("OEM specific"),//235
	_OnceXOR("OEM specific"),//236
	_OnceXOR("OEM specific"),//237
	_OnceXOR("OEM specific"),//238
	_OnceXOR("OEM specific"),//239
	_OnceXOR("OEM specific"),//240
	_OnceXOR("OEM specific"),//241
	_OnceXOR("OEM specific"),//242
	_OnceXOR("OEM specific"),//243
	_OnceXOR("OEM specific"),//244
	_OnceXOR("OEM specific"),//245
	_OnceXOR("Attn"),
	_OnceXOR("CrSel"),
	_OnceXOR("ExSel"),
	_OnceXOR("Erase EOF"),
	_OnceXOR("Play"),
	_OnceXOR("Zoom"),
	_OnceXOR("Reserved"),
	_OnceXOR("PA1"),
	_OnceXOR("Clear")
};
