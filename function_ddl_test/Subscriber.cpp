#include <iostream>

#include <fstream>

#include "Subscriber_func.h"
int main(int argc, char *argv[])
{
	Subscriber_func sub;
	sub.subscriber_init(argc,argv);
	sub.subscriber_read();
	return 0;
}

