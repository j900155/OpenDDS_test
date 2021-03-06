#include <QtGui/QtGui>
#include <QtCore/QString>

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>

#include <iostream>

#include "T1TypeSupportImpl.h"
#include "T1TypeSupportC.h"

#include "UiAction.h"
UiAction::UiAction(DDS::DomainParticipant_var participant)
{

	if(!participant)
	{
		std::cerr << "create participant fail" << std::endl;
	}
	else
	{
		std::cout << participant->get_domain_id()<<std::endl;
	}
	std::cout << "create test" << std::endl;
	thread1 = new OnSubscriber(participant,1);
	thread2 = new OnSubscriber(participant,2);
	thread3 = new OnSubscriber(participant,3);
	thread4 = new OnSubscriber(participant,4);
	std::cout << "test start" << std::endl;	
	//connect signal slot
	connect(thread1, SIGNAL(getMessage(QString, int, long)), this,SLOT(showMessage(QString, int, long)));
	connect(thread2, SIGNAL(getMessage(QString, int, long)), this,SLOT(showMessage(QString, int, long)));
	connect(thread3, SIGNAL(getMessage(QString, int, long)), this,SLOT(showMessage(QString, int, long)));
	connect(thread4, SIGNAL(getMessage(QString, int, long)), this,SLOT(showMessage(QString, int, long)));
	//connect signal slot
	ui.setupUi(this);
	thread1->start();
	thread2->start();
	thread3->start();
	thread4->start();
	std::cout << "UiAction end" << std::endl;
}

UiAction::~UiAction()
{
	std::cout << "~UiAction" << std::endl;
}

void UiAction::showMessage(QString text, int number, long get_time)
{
	std::cout <<  number <<std::endl;
	QString Stime = QString::number(get_time);
	if(number ==1)
	{
		ui.Topic1Text->setText(text);
		
		ui.time1->setText(Stime);
	}
	else if(number ==2)
	{
		ui.Topic2Text->setText(text);
		ui.time2->setText(Stime);
	}
	else if(number ==3)
	{
		ui.Topic3Text->setText(text);
		ui.time3->setText(Stime);
	}
	else if(number ==4)
	{
		ui.Topic4Text->setText(text);
		ui.time4->setText(Stime);
	}
}
