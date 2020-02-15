#include "SerialUtil.h"

#include <string.h> /* Required for strerror */

/**
 * Function for printing error messages containing
 * the latest error number and error string. 
 */
void printError(const char* msg)
{
    printf("[ERROR] %s\n", msg);
    printf("Error: %d, %s\n", errno, strerror(errno));
}

Serial::Serial()
{
    printf("[INFO] Created new Serial-Port interface - Awaiting connect-call.\n");
}

Serial::~Serial()
{
	disconnect();
}

void Serial::connect(std::string deviceName)
{
    //Disconnect if already connected
	disconnect();

	//Copy port name
    _deviceName = deviceName;

    //Open serial port 'file'
    _serial_port = open(_deviceName.c_str(), O_RDWR);
    if (_serial_port < 0)
    {
        printError("Unable to connect to device!");
        return;
    }
    
    /* --- --- --- Serial configuration --- --- --- */
    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if (tcgetattr(_serial_port, &tty) != 0)
    {
        printError("Unable to retrieve current serial configuration!");
        return;
    }

    tty.c_cflag &=  ~PARENB;
    tty.c_cflag |=   CS8;
    tty.c_cflag &=  ~CRTSCTS;
    tty.c_cflag &=  ~CSTOPB;
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    //Apply configuration
    if (tcsetattr(_serial_port, TCSANOW, &tty) != 0)
    {
        printError("Serial configuration could not be set!");
        return;
    }

    //We need to sleep 2000ms = 2s, as arduino requires it.
    sleep(ARDUINO_WAIT_TIME_SEC);
    /* --- --- --- End of configuration --- --- --- */

    _isConnected = true;
    printf("[INFO] Connection to device '%s' established.\n", _deviceName.c_str());
}

void Serial::disconnect()
{
	if (isConnected())
	{
        close(_serial_port);
		_isConnected = false;
        printf("[INFO] Connection to device '%s' closed.\n", _deviceName.c_str());
	}
}

void Serial::pwrite(void* buffer, size_t buffer_size)
{
    write(_serial_port, buffer, buffer_size);
}

void Serial::flush()
{
    tcflush(_serial_port, TCIOFLUSH);
}