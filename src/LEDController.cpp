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

	//Shift color components as required by arduino
	//// Required by Arduino:
	//// 0xff000000 = red
	//// 0x00ff0000 = green
	//// 0x0000ff00 = blue
	////
	//// Current arrangement (GDI):
	//// 0x000000ff = red
	//// 0x0000ff00 = green
	//// 0x00ff0000 = blue
	//// -----
	COLOR_COMPONENT r = (*color << 24) >> 24;
	COLOR_COMPONENT g = (*color << 16) >> 24;
	COLOR_COMPONENT b = (*color << 8)  >> 24;
	COLOR arduinoColor = b << 16 | g << 8 | r;

//	_serial_interface->pwrite(&arduinoColor, sizeof(COLOR));
	_serial_interface->pwrite(color, sizeof(COLOR));
    _currentColor = *color;
}

COLOR LEDController::getColor()
{
    return _currentColor;
}

LEDMode	LEDController::getLEDMode()
{
	return _led_mode;
}

void LEDController::applyLEDMode(LEDMode ledMode)
{
	_led_mode = ledMode;
}

bool LEDController::isConnected()
{
	return _serial_interface->isConnected();
}
