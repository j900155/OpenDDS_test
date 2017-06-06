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
#include "OnSubscriber.h"

UiAction::UiAction(DDS::DomainParticipant_var participant)
: participant_(participant),
	timer(this)
{

	std::cout << participant->get_domain_id()<<std::endl;

	mT1::T1TypeSupport_var ts = new mT1::T1TypeSupportImpl;
	if (ts->register_type(participant, "") != DDS::RETCODE_OK)
	{
		std::cerr <<"create ts fail"<< std::endl;
	}
	CORBA::String_var type_name = ts->get_type_name();
	std::cout << "get_type_name" << type_name << std::endl;
	//topic1
	DDS::TopicQos topic_Qos;
	participant->get_default_topic_qos(topic_Qos);
	topic1 = participant->create_topic("Topic1",
										type_name,
										topic_Qos,
										0,
										OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!topic1)
	{
		std::cerr <<"create topic1 fail"<< std::endl;
	}
	//topic1 end
	//subscriber
	DDS::SubscriberQos sub_qos;
	participant->get_default_subscriber_qos(sub_qos);

	subscriber = participant->create_subscriber(sub_qos,
			0,
			OpenDDS::DCPS::DEFAULT_STATUS_MASK);
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
			topic1,
			readerQos,
			0,
			OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!reader1)
	{
		std::cerr <<"create reader fail"<< std::endl;
	}
	//reader end
	//datareader
	mT1::T1DataReader_var dr1 = mT1::T1DataReader::_narrow(reader1);
	if(!dr1)
	{
		std::cerr <<"create rdr1 fail"<< std::endl;
	}
	//datareader end
	//read sample
	mT1::T1 message;
	//mT1::T1Seq info;
	DDS::SampleInfo info;
	DDS::ReturnCode_t error = dr1->take_next_sample(message, info);
	if(error == DDS::RETCODE_OK)
	{
		if(info.valid_data)
		{
			std::cout << message.T1_S << std::endl;
		}
	}
	std::cout << "end" << std::endl;
	OnSubscriber test;
	test.testRun();
	//read samplei end
	ui.setupUi(this);
//	qDebug()<< "start";
}

UiAction::~UiAction()
{
	std::cout << "~UiAction" << std::endl;
}
