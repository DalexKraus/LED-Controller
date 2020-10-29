#ifndef __LEDCONTROLLER_H
#define __LEDCONTROLLER_H

#include <string>

#include "Color.h"
#include "Serial.h"

enum LEDMode : char
{
	LED_MODE_IDLE	= 0x00,
	LED_MODE_CUSTOM = 0x01
};

class LEDController
{
	private:
		Serial*     _serial_interface;
        COLOR       _currentColor	= 0x000000ff;
		LEDMode		_led_mode		= LED_MODE_IDLE;

	public:
		 LEDController(std::string portName);
		~LEDController();

		void        applyColor(COLOR* color);
        COLOR       getColor();
		void		applyLEDMode(LEDMode ledMode);
		LEDMode		getLEDMode();
		bool        isConnected();
};

#endif