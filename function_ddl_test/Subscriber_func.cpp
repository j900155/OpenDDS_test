#include "Subscriber_func.h"
#include <fstream>

int Subscriber_func::subscriber_init(int argc, char *argv[])
{
	dpf = TheParticipantFactoryWithArgs(argc, argv);
	participant = dpf-> create_participant(43,
	PARTICIPANT_QOS_DEFAULT,
	0,
	OpenDDS::DCPS::DEFAULT_STATUS_MASK);

	std::cout << "participant" << participant->get_domain_id() << std::endl;

	ts = new Messenger::MessageTypeSupportImpl;
	if (ts->register_type(participant, "") != DDS::RETCODE_OK)
	{
		std::cerr <<"create ts fail"<< std::endl;
	}
	CORBA::String_var type_name = ts->get_type_name();
	std::cout << "get_type_name" << type_name << std::endl;
	//topic
	
	DDS::TopicQos topic_Qos;
	participant->get_default_topic_qos(topic_Qos);
	DDS::Topic_var topic = participant->create_topic("A",
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

	subscriber = participant->create_subscriber(sub_qos,
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
	reader1 = subscriber->create_datareader(
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
	dataReader = Messenger::MessageDataReader::_narrow(reader1);
	if(!dataReader)
	{
		std::cerr <<"create dataReader fail"<< std::endl;
	}

	std::cout<< "topic name " << topic->get_name() << std::endl;
	return 0;
}
int Subscriber_func::subscriber_read()
{
	DDS::ReturnCode_t error;
	DDS::SampleInfo info;
	Messenger::Message message;
	int get_count = 0;
	bool get_status=1;
	while(get_status)
	{
		error = dataReader->take_next_sample(message, info);

		if(error == DDS::RETCODE_OK)
		{
			//std::cout << "SampleInfo.sample_rank = " << info.sample_rank << std::endl;
		 //   std::cout << "SampleInfo.instance_state = " << info.instance_state << std::endl;
			if(info.valid_data)	
			{		
				get_count ++;
				//std::cout<< "topic name " << topic->get_name() << std::endl;
				std::cout << "message count " << message.c;
				std::cout << ";message data " << message.sendData << std::endl;
				std::cout << "get_count" << get_count << std::endl;
				//fp << "message_data " << message.sendData << " message_time " << diff  << std::endl;
				get_status = 0;
			}
		}
	}
    // Clean-up!
    participant->delete_contained_entities();
    dpf->delete_participant(participant);

    TheServiceParticipant->shutdown();

	return 0;
}

