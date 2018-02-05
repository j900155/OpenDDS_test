/*
 *Publisher_func.h
*/
#ifndef __PUBLISHER_FUNC_H__
#define __PUBLISHER_FUNC_H__

#include <ace/Log_Msg.h>

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>

#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>

#include "dds/DCPS/StaticIncludes.h"

#include "MessengerTypeSupportImpl.h"


class Publisher_func
{
	public:
		int publish_init(int argc, ACE_TCHAR *argv[]);
		int publish_write(char *s);
		int add(int a,int b);
	private:
		DDS::DomainParticipantFactory_var dpf;
		DDS::DomainParticipant_var participant;
		Messenger::MessageTypeSupport_var ts;
		DDS::Topic_var topic;
		DDS::Publisher_var publisher;
		DDS::DataWriter_var writer;
		Messenger::MessageDataWriter_var message_writer;


};
#endif
