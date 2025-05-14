#include "Include.h"

short pad[16];
short ThumbLX = 0;
short ThumbLY = 0;
short judgeThumbLX = 0;
short judgeThumbLY = 0;

int PadInput() {
	static XINPUT_STATE xinput;
	GetJoypadXInputState(DX_INPUT_PAD1, &xinput);

	// アナログスティック

	ThumbLX = xinput.ThumbLX;
	ThumbLY = xinput.ThumbLY;

	// ボタン

	for (int i = 0; i < 16; i++) {
		if (xinput.Buttons[i] != 0) {
			if (pad[i] != 60) {
				pad[i]++;
			}
		}
		else {
			pad[i] = 0;
		}
	}
	return 0;

}

short JudgeThumbLX()
{

	if (ThumbLX < -20000) {
		judgeThumbLX--;
	}
	else if (ThumbLX > 20000) {
		judgeThumbLX++;
	}
	else {
		judgeThumbLX = 0;
	}

	return 0;
}
