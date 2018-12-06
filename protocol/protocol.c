#include "pch.h"


int main()
{
	u8 recv[256] = { 0 };
	u8 size = 0;

	initCOM();
	configCOM();

	while (1) {
		size = receive(recv, 255);

		if (size > 0)
		{
			for (u8 i = 0; i < 7; i++) {
				printf("%#x\t", recv[i]);
			}
			
			printf("\n");

			unpack(recv, size);
			size = 0;
		}
	}
}
