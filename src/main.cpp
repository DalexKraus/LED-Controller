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

    double sleepTime = 5 / 1000; //Time for each iteration, in milliseconds
    double one_rad = (2 * 3.14159) / 360;

    while (controller->isConnected())
	{
		// Display a simple fading light if the led mode is set to IDLE.
		for (double deg = 0; deg < 360; deg += 0.1) 
		{
			// Stop when the led mode is not set to IDLE
			while (controller->getLEDMode() != LED_MODE_IDLE)
				sleep(0.02); // 20 milliseconds

			double rad_val = deg * one_rad;
			int sinVal = ((std::sin(rad_val) + 1) / 2) * 255;
			int cosVal = ((std::cos(rad_val) + 1) / 2) * 255;

			const COLOR_COMPONENT r(255 - cosVal);
			const COLOR_COMPONENT g(sinVal);
			const COLOR_COMPONENT b(cosVal);

			color = createColor(true, &r, &g, &b);
			controller->applyColor(&color);
            sleep(sleepTime);
		}
	}
	
    getchar();
    
	delete controller;
	return EXIT_SUCCESS;
}
