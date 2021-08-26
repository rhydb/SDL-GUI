#include "text_handling.hpp"


unsigned long long
strgetmblen(const char* str)
{
  unsigned long long count = 0;
  for (unsigned long long i = 0; 
      str[i] != '\0'; 
      i++) {
    if (IS_NOT_START_BYTE(str[i])) {
      continue; // in the middle of a multibyte char
    }
    count++;
  }
  return count;
}