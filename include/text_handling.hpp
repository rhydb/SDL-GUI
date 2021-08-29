#pragma once
#define IS_NOT_START_BYTE(x) (((x & 0b10000000) != 0) && ((x & 0b01000000) == 0))
#define IS_MB_START_BYTE(x) ((x & 0b11000000) == 0b11000000)
unsigned long long strgetmblen(const char* str);