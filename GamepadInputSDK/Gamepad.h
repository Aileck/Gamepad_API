#pragma once
#include <string>

class Gamepad
{
public:
	Gamepad();
	virtual ~Gamepad();

	virtual void initialize();
	virtual void release();

private:
	std::string gamepadName;
	int sessionID;
};

