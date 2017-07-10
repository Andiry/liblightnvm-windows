#include<stdio.h>
#include<stdint.h>
#include "../include/liblightnvm.h"

int main(void)
{
	struct nvm_dev *dev;
	
	dev = nvm_dev_open("\\\\.\\PHYSICALDRIVE2");

	nvm_dev_close(dev);

	return 0;
}

