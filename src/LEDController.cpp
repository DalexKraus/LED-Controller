#include "LEDController.h"

#include <stdio.h>

LEDController::LEDController(std::string portName)
{
	_serial_interface = new Serial();
	_serial_interface->connect(portName);
}

LEDController::~LEDController()
{
	delete _serial_interface;
}

void LEDController::applyColor(COLOR* color)
{
	if (!isConnected())
		return;

	_serial_interface->pwrite(color, sizeof(COLOR));
}

bool LEDController::isConnected()
{
	return _serial_interface->isConnected();
}