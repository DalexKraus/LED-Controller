#ifndef __LEDCONTROLLER_H
#define __LEDCONTROLLER_H

#include <string>

#include "Color.h"
#include "Serial.h"

class LEDController
{
	private:
		Serial*     _serial_interface;
        COLOR       _currentColor = 0x000000ff;

	public:
		 LEDController(std::string portName);
		~LEDController();

		void        applyColor(COLOR* color);
        COLOR       getColor();
		bool        isConnected();
};

#endif