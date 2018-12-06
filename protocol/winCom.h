#ifndef __WINCOM__
#define __WINCOM__
extern HANDLE hSerial;
extern DWORD dwCommModemStatus;

void initCOM(void);
void configCOM(void);
u8 receive(u8* recvbuf, u8 lenght);
void sendpack(u8* data, u8 lenght);
#endif //!__WINCOM__
