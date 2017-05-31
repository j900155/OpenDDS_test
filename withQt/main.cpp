#include <QApplication>
#ifndef UIACTION_H
#include "UiAction.h"
#endif

#include <iostream>
#include <dds/DdsDcpInfrastructureC.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	UiAction  ui;
	ui.show();


	return app.exec();
}
