#include <iostream>
#include <stdio.h>

#include "LEDController.h"
#include "Config.h"
#include "server/Server.h"

int main()
{
    Config cfg;
    if (!cfg.loadConfig("settings.conf"))
        return -1;

    int server_port = atoi(cfg.getConfigEntry("bind_port").c_str());
    if (server_port < 1024)
    {
        printf("[ERROR] The bind port must not be below 1024!\n");
        printf("Please check the configuration file.\n");
        return -1;
    }

    //Device ttyACM0 is associated with the connected arduino
	LEDController* controller = new LEDController("/dev/ttyACM0");
    Server server;
    server.start(server_port, controller);

	COLOR color = 0x00;

	controller->applyColor(&color);
	sleep(2);

	while (controller->isConnected())
	{
		for (int i = 0; i < 360 * 36; i += 15)
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
