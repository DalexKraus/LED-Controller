#include <iostream>
#include <stdio.h>

#include "LEDController.h"

int main()
{
    //Device ttyACM0 is associated with the connected arduino
	LEDController* controller = new LEDController("/dev/ttyACM0");
	COLOR color = 0x00;

	while (true)
	{
		for (int i = 0; i < 360 * 36 && controller->isConnected(); i++)
		{
			double rad = (2 * 3.14159) / 360;
			double rad_val = rad * (i / 36);

			int sinVal = ((std::sin(rad_val) + 1) / 2) * 255;
			int cosVal = ((std::cos(rad_val) + 1) / 2) * 255;

			const COLOR_COMPONENT r(255 - cosVal);
			const COLOR_COMPONENT g(sinVal);
			const COLOR_COMPONENT b(cosVal);

			color = createColor(true, &r, &g, &b);
			controller->applyColor(&color);
		}
	}

	delete controller;
	return EXIT_SUCCESS;
}
