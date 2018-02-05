/*
 * Publisher.cpp
 */
#include "Publisher_func.h"
#include <iostream>
int main(int argc, char *argv[])
{
	Publisher_func writer1;
	//writer1.publish_init(argc, argv);
	//std::cout << writer1.add(2,3) << std::endl;
	writer1.publish_init(argc, argv);
	writer1.publish_write("test");
	std::cout << "test" << std::endl;
	return 0;
}
