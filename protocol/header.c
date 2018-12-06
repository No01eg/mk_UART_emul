#include "pch.h"

void pack(header * head, u8* body,  u8 lenght) {

	head->lenght = BINDER_SIZE + lenght + ((head->time_sign) ? TIME_SIZE : 0);
	u8 data[PACK_SIZE] = { 0 };
	u8* pack = data;

	//���������� ��������� � �����
	stm_memcpy(pack, (u8*)head, HEAD_SIZE);
	pack += HEAD_SIZE;


	//����� ��� ������ ���� � �����
	if (body != NULL) {
		stm_memcpy(pack, body, lenght);
		pack += lenght;
	}

	//���������� ����� �������
	if(head->time_sign){
		time t = { 0 };
		protocol_get_time(&t);
		stm_memcpy(pack, (u8*)&t, TIME_SIZE);
		pack += TIME_SIZE;
	}

	//���������� ����� ��������� ������ (���� � ������� ������ � ����� ��������� ����� ������)


	//������� CRC � ���������� � �����
	u16 crc = CRC16(data, head->lenght - 2);
	stm_memcpy(pack, (u8*)&crc, 2);

	sendpack(data, head->lenght);
}

//�������� ������ � ������� ������ �����������
void send_error(header * head, u8 error_code) {
	head->addr_dest = head->addr_dest ^ head->addr_sender;
	head->addr_sender = head->addr_dest ^ head->addr_sender;
	head->addr_dest = head->addr_dest ^ head->addr_sender;
	head->tran_dir = 1;
	head->error_sign = 1;
	pack(head, &error_code, 1);
}

void unpack(u8* data, u8 lenght) {
	header head;
	u8* pcg = data;
	stm_memcpy((u8*)&head, pcg, HEAD_SIZE);

	u16 crc;
	stm_memcpy(&crc, &data[head.lenght - CRC_SIZE], CRC_SIZE);
	pcg = data;

	if (lenght != head.lenght) {//������������ ����� ���������
		send_error(&head, 0x12);
		return;
	}

	if (crc != CRC16(pcg, head.lenght - CRC_SIZE)) {//������������ crc
		send_error(&head, 0xff);
	}

	printf("receiving pack is correct\n");
}