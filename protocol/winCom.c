#include "pch.h"

HANDLE hSerial;
COMMTIMEOUTS timeouts;
DCB dcb;
DWORD dwCommModemStatus;

void initCOM(void) {
	FILE * f = fopen("com.txt", "r");
	char port[10] = "\\\\.\\";
	fgets(&port[4], 5, f);
	printf(" port is %s\n", port);
	hSerial = CreateFile(port/*"\\\\.\\COM2"*/, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hSerial == INVALID_HANDLE_VALUE) {
		printf("Error opening port\r\n");
		return -1;
	}
}

void configCOM(void) {
	GetCommState(hSerial, &dcb);
	dcb.BaudRate = CBR_9600;        //9600 Baud
	dcb.ByteSize = 8;                //8 data bits
	dcb.Parity = NOPARITY;            //no parity
	dcb.StopBits = ONESTOPBIT;        //1 stop
	SetCommState(hSerial, &dcb);

	GetCommTimeouts(hSerial, &timeouts);
	timeouts.ReadIntervalTimeout = 50; // in milliseconds
	timeouts.ReadTotalTimeoutConstant = 200; // in milliseconds
	timeouts.ReadTotalTimeoutMultiplier = 10; // in milliseconds
	timeouts.WriteTotalTimeoutConstant = 50; // in milliseconds
	timeouts.WriteTotalTimeoutMultiplier = 10; // in milliseconds

	SetCommTimeouts(hSerial, &timeouts);
}

void receiveStart(void) {
	SetCommMask(hSerial, EV_RXCHAR | EV_ERR); //receive character event
	WaitCommEvent(hSerial, &dwCommModemStatus, 0); //wait for character
}

u8 receive(u8* recvbuf, u8 lenght) {
	static u8 size = 0;
	receiveStart();
	if (dwCommModemStatus & EV_RXCHAR)
	{
		ReadFile(hSerial, recvbuf, lenght, &size, 0);
		return size;
	}
}

void sendpack(u8* data, u8 lenght) {
	WriteFile(hSerial, data, lenght, NULL, NULL);
}