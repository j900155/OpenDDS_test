#include <iostream>
#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>

#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>

#include "dds/DCPS/StaticIncludes.h"

#include "MessengerTypeSupportImpl.h"


int ACE_TMAIN(int argc, char *argv[])
{
	DDS::DomainParticipantFactory_var dpf = TheParticipantFactoryWithArgs(argc, argv);
	DDS::DomainParticipant_var participant = dpf-> create_participant(43,
																	PARTICIPANT_QOS_DEFAULT,
																	0,
																	OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	std::cout << "participant" << participant->get_domain_id() << std::endl;

	Messenger::MessageTypeSupport_var ts = new Messenger::MessageTypeSupportImpl;
	if (ts->register_type(participant, "") != DDS::RETCODE_OK)
	{
		std::cerr <<"create ts fail"<< std::endl;
	}
	CORBA::String_var type_name = ts->get_type_name();
	std::cout << "get_type_name" << type_name << std::endl;
	//topic
	
	std::string topic_name;
	std::cout << "topic name?" << std::endl;
	std::cin >> topic_name;
	std::cout << "topic name " << topic_name << std::endl;

	DDS::TopicQos topic_Qos;
	participant->get_default_topic_qos(topic_Qos);
	DDS::Topic_var topic = participant->create_topic(topic_name.c_str(),
										type_name,
										topic_Qos,
										0,
										OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!topic)
	{
		std::cerr <<"create topic fail"<< std::endl;
	}
	//topic end
	//subscriber
	DDS::SubscriberQos sub_qos;
	participant->get_default_subscriber_qos(sub_qos);

	DDS::Subscriber_var subscriber = 
			participant->create_subscriber(sub_qos,
				0,
				OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	DDS::DataReaderQos readerQos;
	if(!subscriber)
	{
		std::cerr <<"create subcriber fail"<< std::endl;
	}
	else
	{
		subscriber->get_default_datareader_qos(readerQos);
	}
	//subscriber end
	//reader
	DDS::DataReader_var reader1 = subscriber->create_datareader(
			topic,
	readerQos,
			0,
			OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!reader1)
	{
		std::cerr <<"create reader fail"<< std::endl;
	}
	//reader end
	//datareader
	Messenger::MessageDataReader_var dataReader = Messenger::MessageDataReader::_narrow(reader1);
	if(!dataReader)
	{
		std::cerr <<"create dataReader fail"<< std::endl;
	}

	std::cout<< "topic name " << topic->get_name() << std::endl;

	DDS::ReturnCode_t error;
	DDS::SampleInfo info;
	Messenger::Message message;
	while(true)
	{
		error = dataReader->take_next_sample(message, info);
		if(error == DDS::RETCODE_OK)
		{
			std::cout << "SampleInfo.sample_rank = " << info.sample_rank << std::endl;
		    std::cout << "SampleInfo.instance_state = " << info.instance_state << std::endl;
			if(info.valid_data)	
			{
				std::cout<< "topic name " << topic->get_name() << std::endl;
				std::cout << "message data " << message.sendData << std::endl;
				std::cout << "message count " << message.c << std::endl;
				std::cout << "message time " << message.sendTime << std::endl;
			}
		}
		usleep(10);

	}
	return 0;
}

