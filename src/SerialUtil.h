#ifndef __SERIAL_UTIL_H
#define __SERIAL_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

#define ARDUINO_WAIT_TIME_SEC	2
#define MAX_DATA_LEN		    256

class Serial
{
	private:
        int         _serial_port;
		std::string	_deviceName;
		bool		_isConnected = false;

	public:
		Serial();
		~Serial();
	
		void			connect(std::string deviceName);
		void			disconnect();
		void			pwrite(void* buffer, size_t buffer_size);
		void			flush();
		bool			isConnected()	{ return _isConnected;	}
        std::string*	getDeviceName()	{ return &_deviceName;	}
};


#endif // SERIAL_UTIL_H