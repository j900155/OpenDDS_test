#include <QtGui/QApplication>
#include "UiAction.h"

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>
#include <dds/DdsDcpsSubscriptionC.h>

#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>

#include <ace/Argv_Type_Converter.h>

#include <iostream>

int main(int argc, ACE_TCHAR *argv[])
{

	DDS::DomainParticipantFactory_var dpf = 
		TheParticipantFactoryWithArgs(argc, argv);

	DDS::DomainParticipant_var participant = 
		dpf->create_participant(43,
								PARTICIPANT_QOS_DEFAULT,
								0,
								OpenDDS::DCPS::DEFAULT_STATUS_MASK);

	if(!participant)
	{
		std::cerr << "create participant fail" << std::endl;
	}
	else
	{
		std::cout << participant->get_domain_id()<<std::endl;
	}
	ACE_Argv_Type_Converter atc(argc, argv);
	QApplication app(argc, atc.get_ASCII_argv());
	UiAction  ui(participant);
	ui.show();

	int retval = -1;
	retval =  app.exec();
	participant->delete_contained_entities();
	dpf->delete_participant(participant);


	TheServiceParticipant->shutdown();
	return retval;
}
