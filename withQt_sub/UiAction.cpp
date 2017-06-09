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
	//create reader
	
	//end reader
	//OnSubscriber reader1(participant ,"Topic1");
	thread1 = new OnSubscriber(participant,"Topic1");
	thread2 = new OnSubscriber(participant,"Topic2");
	std::cout << "test start" << std::endl;	


	ui.setupUi(this);
	//reader1.start();
	thread1->start();
	thread2->start();
	std::cout << "UiAction end" << std::endl;
}

UiAction::~UiAction()
{
	std::cout << "~UiAction" << std::endl;
}

void UiAction::showMessage(QString text, int number)
{
	switch(number)
	{
		case 1:
			ui.Topic1Text->setText(text);
		break;
		case 2:
			ui.Topic2Text->setText(text);
		break;
		case 3:
			ui.Topic3Text->setText(text);
		break;
		case 4:
			ui.Topic4Text->setText(text);
		break;
	}	
}
