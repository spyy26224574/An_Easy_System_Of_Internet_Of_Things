#ifndef SONG_ESP8266
#define SONG_ESP8266
#include"song_IO.h"
#include"song_usart3.h"
#include"song_lcd.h"
#include"song_time3.h"
#include"song_molloc.h"
#include"nano_broad.h"
//返回值是null或str字符串所在的地址
u8* atk_8266_check_cmd(u8 *str);
//返回值为一表示没有回应
u8 atk_8266_send_cmd(u8 *cmd, u8 *ack, u16 waittime);
u8 atk_8266_send_data(u8 *data, u8 *ack, u16 waittime);
u8 atk_8266_quit_trans(void);
u8 atk_8266_consta_check(void);













































































#endif