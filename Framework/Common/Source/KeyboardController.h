#ifndef KEYBOARD_CONTROLLER_H
#define KEYBOARD_CONTROLLER_H

#include "SingletonTemplate.h"
#include <bitset>
#include <windows.h>

class KeyboardController : public Singleton<KeyboardController>
{
	friend Singleton<KeyboardController>;
public:
	const static int MAX_KEYS = 256;

	// System Interface
	void UpdateKeyboardStatus(unsigned char _slot, bool _isPressed);
	void EndFrameUpdate();
	
	// User Interface
	bool IsKeyDown(unsigned char _slot);
	bool IsKeyUp(unsigned char _slot);
	bool IsKeyPressed(unsigned char _slot);
	bool IsKeyReleased(unsigned char _slot);

private:
	KeyboardController();
	~KeyboardController();

	std::bitset<MAX_KEYS> currStatus, prevStatus;
};

#endif // KEYBOARD_CONTROLLER_H