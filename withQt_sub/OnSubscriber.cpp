#include <iostream>
#include "OnSubscriber.h"
#include <QtCore/QDebug>

#include "T1TypeSupportC.h"
#include "T1TypeSupportImpl.h"

OnSubscriber::OnSubscriber(DDS::DomainParticipant_var participant, char *get_topic)
{
	std::cout<< "run1" << std::endl;
	std::cout << "participant" << participant->get_domain_id() << std::endl;
	mT1::T1TypeSupport_var ts = new mT1::T1TypeSupportImpl;
	if (ts->register_type(participant, "") != DDS::RETCODE_OK)
	{
		std::cerr <<"create ts fail"<< std::endl;
	}
	CORBA::String_var type_name = ts->get_type_name();
	std::cout << "get_type_name" << type_name << std::endl;
	//topic
	DDS::TopicQos topic_Qos;
	participant->get_default_topic_qos(topic_Qos);
	topic = participant->create_topic(get_topic,
										type_name,
										topic_Qos,
										0,
										OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!topic)
	{
		std::cerr <<"create topic fail"<< std::endl;
	}
	std::cout << "get_topic " << get_topic << std::endl;
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
	dataReader = mT1::T1DataReader::_narrow(reader1);
	if(!dataReader)
	{
		std::cerr <<"create dataReader fail"<< std::endl;
	}

	std::cout<< "topic name " << topic->get_name() << std::endl;

};
OnSubscriber::~OnSubscriber()
{
	std::cout<< "thread quit" << std::endl;
	quit();
	//wait();

};
void OnSubscriber::run()
{
	DDS::ReturnCode_t error;
	DDS::SampleInfo info;
	mT1::T1 message;
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
				std::cout << "message id " << message.T1_id << std::endl;
				std::cout << "message data " << message.T1_S << std::endl;
			}
		}
		usleep(10);

	}

}

void getMessage()
{

}
