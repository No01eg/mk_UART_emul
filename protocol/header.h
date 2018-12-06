#ifndef __HEADER__
#define __HEADER__

#define HEAD_SIZE 5
#define TIME_SIZE	5
//обвязка пакета (заголовок + crc [2 byte])
#define CRC_SIZE 2
#define BINDER_SIZE (HEAD_SIZE+CRC_SIZE)
//структура заголовка пакета протокола
//объединение статуса и номера функции в 2 байта
//(максимум длины :255 - 7 байт (обвязка [заголовок+CRC]) | - 1 байт если split = 1 | - 5 байт (метка времени) time_sign = 1;
// итого 255 - 7 - 1 - 5 = 242 байт под "body" если используются все поля
// 1. addr_dest - адресс получателя (0-255)
// 2. addr_sender - адресс отправителя (0-255)
// 3. func - команда (0 - 3ff (1023))
// 4. split - 0 - пакет монолитный, 1 - информация раздроблена между пакетами
// 5. reserve = 0;
// 6. time_sign - 1 - после body добавляется структура метки времени (5 байт)
// 7. error_sign - 1 - ошибка
// 8. train_dir - 0 - запрос, 1 - ответ
// 9. lenght - длина пакета включая header, [body,] [time,] [splitinfo,] CRC
typedef struct {
	u8 addr_dest;
	u8 addr_sender;
	//------------- 2 байта команда + статус
	u16 func			: 10;
	u16 split			: 1;
	u16 reserve		: 2;
	u16 time_sign : 1;
	u16 error_sign: 1;
	u16 tran_dir	: 1;
	//-------------
	u8 lenght;				
}header;

// метка времени
// добавляется в пакет после "body" при time_sign = 1;
typedef struct {
	u16 seconds : 6;
	u16 minuts  : 6;
	u16 hours		: 5;
	u16 days		: 5;
	u16 months	: 4;
	u8 years		: 8;
}time;

//метка пакета при разбиении
// 127 пакетов максимум в 1 простыню (достаточно ли)
// добавляется в пакет перед "CRC цепочкой" при split = 1;
typedef struct {
	u8 num_pack  : 7;
	u8 last_pack : 1;
}packetInfo;


void pack(header* head, u8* body, u8 lenght);
void unpack(u8* data, u8 lenght);

#endif //!__HEADER__
