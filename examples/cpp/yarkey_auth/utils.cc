
#include "utils.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

char * yarkey::randStr(char *str, const int len) {
	srand(time(NULL));
	int i;
	for (i = 0; i < len; ++i) {
		switch ((rand() % 3)) {
		case 1:
			str[i] = 'A' + rand() % 26;
			break;
		case 2:
			str[i] = 'a' + rand() % 26;
			break;
		default:
			str[i] = '0' + rand() % 10;
			break;
		}
	}
	str[++i] = '\0';
	return str;
};