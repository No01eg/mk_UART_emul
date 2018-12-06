#ifndef __HEADER__
#define __HEADER__

#define HEAD_SIZE 5
#define TIME_SIZE	5
//������� ������ (��������� + crc [2 byte])
#define CRC_SIZE 2
#define BINDER_SIZE (HEAD_SIZE+CRC_SIZE)
//��������� ��������� ������ ���������
//����������� ������� � ������ ������� � 2 �����
//(�������� ����� :255 - 7 ���� (������� [���������+CRC]) | - 1 ���� ���� split = 1 | - 5 ���� (����� �������) time_sign = 1;
// ����� 255 - 7 - 1 - 5 = 242 ���� ��� "body" ���� ������������ ��� ����
// 1. addr_dest - ������ ���������� (0-255)
// 2. addr_sender - ������ ����������� (0-255)
// 3. func - ������� (0 - 3ff (1023))
// 4. split - 0 - ����� ����������, 1 - ���������� ����������� ����� ��������
// 5. reserve = 0;
// 6. time_sign - 1 - ����� body ����������� ��������� ����� ������� (5 ����)
// 7. error_sign - 1 - ������
// 8. train_dir - 0 - ������, 1 - �����
// 9. lenght - ����� ������ ������� header, [body,] [time,] [splitinfo,] CRC
typedef struct {
	u8 addr_dest;
	u8 addr_sender;
	//------------- 2 ����� ������� + ������
	u16 func			: 10;
	u16 split			: 1;
	u16 reserve		: 2;
	u16 time_sign : 1;
	u16 error_sign: 1;
	u16 tran_dir	: 1;
	//-------------
	u8 lenght;				
}header;

// ����� �������
// ����������� � ����� ����� "body" ��� time_sign = 1;
typedef struct {
	u16 seconds : 6;
	u16 minuts  : 6;
	u16 hours		: 5;
	u16 days		: 5;
	u16 months	: 4;
	u8 years		: 8;
}time;

//����� ������ ��� ���������
// 127 ������� �������� � 1 �������� (���������� ��)
// ����������� � ����� ����� "CRC ��������" ��� split = 1;
typedef struct {
	u8 num_pack  : 7;
	u8 last_pack : 1;
}packetInfo;


void pack(header* head, u8* body, u8 lenght);
void unpack(u8* data, u8 lenght);

#endif //!__HEADER__
