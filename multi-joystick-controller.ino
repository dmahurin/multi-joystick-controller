#include <Joystick.h>

#define JOYSTICK_COUNT 2
#define BUTTON_COUNT 24

Joystick_ Joystick[JOYSTICK_COUNT] = {
	Joystick_(0x03, JOYSTICK_TYPE_GAMEPAD,  8, 0, true, true, false, false, false, false, false, false, false, false, false),
	Joystick_(0x04, JOYSTICK_TYPE_GAMEPAD,  8, 0, true, true, false, false, false, false, false, false, false, false, false),
};

void setup() {
	pinMode(0, INPUT_PULLUP);
	pinMode(1, INPUT_PULLUP);
	pinMode(2, INPUT_PULLUP);
	pinMode(3, INPUT_PULLUP);
	pinMode(4, INPUT_PULLUP);
	pinMode(5, INPUT_PULLUP);
	pinMode(6, INPUT_PULLUP);
	pinMode(7, INPUT_PULLUP);

	pinMode(8, INPUT_PULLUP);
	pinMode(9, INPUT_PULLUP);
	pinMode(10, INPUT_PULLUP);
	pinMode(11, INPUT_PULLUP);
	pinMode(12, INPUT_PULLUP);
	pinMode(13, INPUT_PULLUP);

	pinMode(A0, INPUT_PULLUP);
	pinMode(A1, INPUT_PULLUP);
	pinMode(A2, INPUT_PULLUP);
	pinMode(A3, INPUT_PULLUP);
	pinMode(A4, INPUT_PULLUP);
	pinMode(A5, INPUT_PULLUP);

	for (int i = 0; i < JOYSTICK_COUNT; i++) {
		Joystick[i].begin();
		Joystick[i].setXAxisRange(-1, 1);
		Joystick[i].setYAxisRange(-1, 1);
	}
}

int lastButtonState[BUTTON_COUNT] = {0};

int pin_map[BUTTON_COUNT] = {2,3,4,5,12,13,8,9,10,11,6,7,A0,A1,A2,A3,A5,-1,A4,-1,1,0,-1,-1};

enum buttons {P1UP,P1DOWN,P1LEFT,P1RIGHT,P1B1,P1B2,P2UP,P2DOWN,P2LEFT,P2RIGHT,P2B1,P2B2,P1B3,P1B4,P2B3,P2B4,P1B5,P1B6,P2B5,P2B6,P1,P2,P1X,P2X};

void loop() {
	for (int index = 0; index < BUTTON_COUNT; index++) {
		if(pin_map[index] < 0) continue;

		int currentButtonState = !digitalRead(pin_map[index]);

		if ((!currentButtonState) == (!lastButtonState[index]))
			continue;

		switch (index) {
		case P1UP:
			if (currentButtonState == 1) {
				Joystick[0].setYAxis(-1);
			} else {
				Joystick[0].setYAxis(0);
			}
			break;
		case P1DOWN:
			if (currentButtonState == 1) {
				Joystick[0].setYAxis(1);
			} else {
				Joystick[0].setYAxis(0);
			}
			break;
		case P1LEFT:
			if (currentButtonState == 1) {
				Joystick[0].setXAxis(-1);
			} else {
				Joystick[0].setXAxis(0);
			}
			break;
		case P1RIGHT:
			if (currentButtonState == 1) {
				Joystick[0].setXAxis(1);
			} else {
				Joystick[0].setXAxis(0);
			}
			break;
		case P1B1:
			Joystick[0].setButton(0, currentButtonState);
			break;
		case P1B2:
			Joystick[0].setButton(1, currentButtonState);
			break;
		case P2UP:
			if (currentButtonState == 1) {
				Joystick[1].setYAxis(-1);
			} else {
				Joystick[1].setYAxis(0);
			}
			break;
		case P2DOWN:
			if (currentButtonState == 1) {
				Joystick[1].setYAxis(1);
			} else {
				Joystick[1].setYAxis(0);
			}
			break;
		case P2LEFT:
			if (currentButtonState == 1) {
				Joystick[1].setXAxis(-1);
			} else {
				Joystick[1].setXAxis(0);
			}
			break;
		case P2RIGHT:
			if (currentButtonState == 1) {
				Joystick[1].setXAxis(1);
			} else {
				Joystick[1].setXAxis(0);
			}
			break;
		case P2B1:
			Joystick[1].setButton(0, currentButtonState);
			break;
		case P2B2:
			Joystick[1].setButton(1, currentButtonState);
			break;
		case P1B3:
			Joystick[0].setButton(2, currentButtonState);
			break;
		case P1B4:
			Joystick[0].setButton(3, currentButtonState);
			break;
		case P2B3:
			Joystick[1].setButton(2, currentButtonState);
			break;
		case P2B4:
			Joystick[1].setButton(3, currentButtonState);
			break;
		case P1B5:
			Joystick[0].setButton(4, currentButtonState);
			break;
		case P2B5:
			Joystick[1].setButton(4, currentButtonState);
			break;
		case P1B6:
			Joystick[0].setButton(5, currentButtonState);
			break;
		case P2B6:
			Joystick[1].setButton(5, currentButtonState);
			break;
		case P1: // SELECT,START (P1)
			if(pin_map[P2X] >= 0 || pin_map[P1X] >= 0 || lastButtonState[P1B5]) { // have real SELECT button
				Joystick[0].setButton(7, currentButtonState);
			// otherwise use SELECT button state as P1 START+SELECT press
			} else if(lastButtonState[P2] && currentButtonState && !lastButtonState[P1X]) {
				Joystick[1].setButton(6, 1);
				lastButtonState[P2X] = 1;
			} else if(lastButtonState[P2X] && !currentButtonState) {
				Joystick[1].setButton(6, 0);
				if(!lastButtonState[P2]) lastButtonState[P2X] = 0;
			} else { // otherwise this is P1 SELECT then P1 START
				Joystick[0].setButton(6, currentButtonState);
				if(!lastButtonState[P2]) {
					if(lastButtonState[P1X]) {
						lastButtonState[P1X] = currentButtonState;
					} else if(!currentButtonState) {
 			 			delay(50);
						Joystick[0].setButton(7, 1);
 			 			delay(50);
						Joystick[0].setButton(7, 0);
					}
				}
			}
			break;
		case P2: // SELECT,START (P2)
			if(pin_map[P1X] >= 0 || pin_map[P2X] >= 0 || lastButtonState[P2B5]) { // have real SELECT/COIN button, or bypass SELECT+START with B5
				Joystick[1].setButton(7, currentButtonState);
			// otherwise use SELECT button state as P1 START+SELECT press
			} else if(lastButtonState[P1] && currentButtonState && !lastButtonState[P2X]) {
				Joystick[0].setButton(7, 1);
				lastButtonState[P1X] = 1;
			} else if(lastButtonState[P1X] && !currentButtonState) {
				Joystick[0].setButton(7, 0);
				if(!lastButtonState[P1]) lastButtonState[P1X] = 0;
			} else { // otherwise this is P1 SELECT then P1 START
				Joystick[1].setButton(7, currentButtonState);
				if(!lastButtonState[P1]) {
					if(lastButtonState[P2X]) {
						lastButtonState[P2X] = currentButtonState;
					} else if(!currentButtonState) {
 			 			delay(50);
						Joystick[1].setButton(6, 1);
 				 		delay(50);
						Joystick[1].setButton(6, 0);
					}
				}
			}
			break;
		}
		lastButtonState[index] = currentButtonState;
	}

	delay(10);
}

