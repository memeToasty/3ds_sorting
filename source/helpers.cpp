#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>


int atoui(const char *str)
{
	unsigned int num = 0;
	int i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return num;
}

void ThreadSleep(unsigned int ms)
{
	svcSleepThread(1000000ULL * (u32)ms);
}