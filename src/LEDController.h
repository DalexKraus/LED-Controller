#ifndef __LEDCONTROLLER_H
#define __LEDCONTROLLER_H

#include <string>

#include "Color.h"
#include "SerialUtil.h"


class LEDController
{
	private:
		Serial* _serial_interface;

	public:
		 LEDController(std::string portName);
		~LEDController();

		void applyColor(COLOR* color);
		bool isConnected();
};

#endif