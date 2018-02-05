#include <iostream>
#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>

#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>

#include "dds/DCPS/StaticIncludes.h"

#include "MessengerTypeSupportImpl.h"

class Subscriber_func
{
	public:
		int subscriber_init(int argc,ACE_TCHAR *argv[]);
		int subscriber_read();
		int subscriber_clean();
	private:
		DDS::DomainParticipantFactory_var dpf;
		DDS::DomainParticipant_var participant; 
		Messenger::MessageTypeSupport_var ts; 
		DDS::Subscriber_var subscriber;
		DDS::DataReader_var reader1;
		Messenger::MessageDataReader_var dataReader; 
};
