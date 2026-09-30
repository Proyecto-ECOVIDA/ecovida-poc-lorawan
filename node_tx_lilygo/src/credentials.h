#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <lmic.h>
#include <hal/hal.h>

// 1. AppEUI (o Join EUI) en formato LSB (Least Significant Byte)
static const u1_t PROGMEM APPEUI[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8); }

// 2. DevEUI en formato LSB
static const u1_t PROGMEM DEVEUI[8] = { 0x39, 0x0d, 0x43, 0xce, 0xf5, 0x72, 0x3b, 0x22 };
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8); }

// 3. AppKey en formato MSB (Most Significant Byte)
static const u1_t PROGMEM APPKEY[16] = { 0x6b, 0x70, 0x1b, 0xe2, 0xb5, 0x05, 0x9c, 0x92, 0xe6, 0x22, 0xfa, 0x98, 0x09, 0x4d, 0xd5, 0x6e };
void os_getDevKey (u1_t* buf) { memcpy_P(buf, APPKEY, 16); }

#endif