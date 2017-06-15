#include <QtGui/QtGui>
#include <QtCore/QString>

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>

#include <iostream>

#include "T1TypeSupportImpl.h"

#include "UiAction.h"
#include "time.h"
UiAction::UiAction(DDS::DomainParticipant_var participant)
: participant_(participant)
{
	id = 0;
	std::cout << participant->get_domain_id()<<std::endl;

	mT1::T1TypeSupport_var ts = new mT1::T1TypeSupportImpl;
	if (ts->register_type(participant, "") != DDS::RETCODE_OK)
	{
		std::cerr <<"create ts fail"<< std::endl;
	}
	CORBA::String_var type_name = ts->get_type_name();
	std::cout << "get_type_name" << type_name << std::endl;
	
	DDS::TopicQos topic_Qos;
	participant->get_default_topic_qos(topic_Qos);

	//topic1
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
	//topic2
	topic2 = participant->create_topic("Topic2",
										type_name,
										topic_Qos,
										0,
										OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!topic2)
	{
		std::cerr <<"create topic2 fail"<< std::endl;
	}
	//topic2 end
	//topic3
	topic3 = participant->create_topic("Topic3",
										type_name,
										topic_Qos,
										0,
										OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!topic3)
	{
		std::cerr <<"create topic3 fail"<< std::endl;
	}
	//topic3 end
	//topic4
	topic4 = participant->create_topic("Topic4",
										type_name,
										topic_Qos,
										0,
										OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!topic4)
	{
		std::cerr <<"create topic2 fail"<< std::endl;
	}
	//topic4 end

	//publish
	DDS::PublisherQos pub_qos;
	participant->get_default_publisher_qos(pub_qos);

	publisher = participant->create_publisher(pub_qos,
			0,
			OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!publisher)
	{
		std::cerr <<"create publisher fail"<< std::endl;
	}
	else
	{
		publisher->get_default_datawriter_qos(writerQos);
	}
	//publish end
	//datawirter1
	DDS::DataWriter_var writer1 = publisher->create_datawriter(topic1,
															writerQos,
															0,
															OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!writer1)
	{
		std::cerr <<"create writer1 fail"<< std::endl;
	}
	dw1 = mT1::T1DataWriter::_narrow(writer1);
	if(!dw1)
	{
		std::cerr <<"narrow dw1  fail"<< std::endl;
	}
	//datawriter1 end
	//datawirter2
	DDS::DataWriter_var writer2 = publisher->create_datawriter(topic2,
															writerQos,
															0,
															OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!writer2)
	{
		std::cerr <<"create writer2 fail"<< std::endl;
	}
	dw2 = mT1::T1DataWriter::_narrow(writer2);
	if(!dw2)
	{
		std::cerr <<"narrow dw2  fail"<< std::endl;
	}

	//datawriter2 end
	//datawirter3
	DDS::DataWriter_var writer3 = publisher->create_datawriter(topic3,
															writerQos,
															0,
															OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!writer3)
	{
		std::cerr <<"create writer3 fail"<< std::endl;
	}
	dw3 = mT1::T1DataWriter::_narrow(writer3);
	if(!dw3)
	{
		std::cerr <<"narrow dw3  fail"<< std::endl;
	}

	//datawriter3 end
	//datawirter4
	DDS::DataWriter_var writer4 = publisher->create_datawriter(topic4,
															writerQos,
															0,
															OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!writer4)
	{
		std::cerr <<"create writer3 fail"<< std::endl;
	}
	dw4 = mT1::T1DataWriter::_narrow(writer4);
	if(!dw4)
	{
		std::cerr <<"narrow dw3  fail"<< std::endl;
	}

	//datawriter3 end


	ui.setupUi(this);
//	qDebug()<< "start";
}

UiAction::~UiAction()
{
	std::cout << "~UiAction" << std::endl;
}

void UiAction::SendButtonClicked()
{
	std::cout << "Bueetonclicked" << std::endl;
	time_t get_time;
	get_time = time(NULL);
	//write data1
	if(!dw1)
	{
		std::cerr <<"narrow dw1  fail"<< std::endl;
	}
	QString qs = ui.Topic1Text->text();
	std::string s = qs.toStdString();
	std::cout << "message1 " <<s << std::endl;
	mT1::T1 message1;
	message1.T1_id = id;
	message1.T1_S = s.c_str();
	message1.T1_time = get_time;
	if(topicCheck1)
	{
		std::cout << "topic " << dw1->get_topic() << std::endl;
		dw1->write(message1, DDS::HANDLE_NIL);
	}
	//write data1 end
	//write data2
	if(!dw2)
	{
		std::cerr <<"narrow dw2  fail"<< std::endl;
	}
	qs = ui.Topic2Text->text();
	s = qs.toStdString();
	std::cout <<"message2 " << s << std::endl;
	mT1::T1 message2;
	message2.T1_id = id;
	message2.T1_S = s.c_str();
	message2.T1_time = get_time;
	if(topicCheck2)
	{
		std::cout << "topic " << dw2->get_topic() << std::endl;
		dw2->write(message2, DDS::HANDLE_NIL);
	}
	//write data2 end
	//write data3
	if(!dw3)
	{
		std::cerr <<"narrow dw3  fail"<< std::endl;
	}
	qs = ui.Topic3Text->text();
	s = qs.toStdString();
	std::cout <<"message3 " << s << std::endl;
	mT1::T1 message3;
	message3.T1_id = id;
	message3.T1_S = s.c_str();
	message3.T1_time = get_time;
	if(topicCheck3)
	{
		std::cout << "topic " << dw3->get_topic() << std::endl;
		dw3->write(message3, DDS::HANDLE_NIL);
	}
	//write data3 end
	//write data4
	if(!dw4)
	{
		std::cerr <<"narrow dw4  fail"<< std::endl;
	}
	qs = ui.Topic4Text->text();
	s = qs.toStdString();
	std::cout <<"message4 " << s << std::endl;
	mT1::T1 message4;
	message4.T1_id = id;
	message4.T1_S = s.c_str();
	message4.T1_time = get_time;
	if(topicCheck4)
	{
		std::cout << "topic " << dw4->get_topic() << std::endl;
		dw4->write(message4, DDS::HANDLE_NIL);
	}
	//write data4 end

	id++;
}

void UiAction::Topic1Enable()
{
	topicCheck1 = ui.Topic1->isChecked();
}
void UiAction::Topic2Enable()
{
	topicCheck2 = ui.Topic2->isChecked();
}
void UiAction::Topic3Enable()
{
	topicCheck3 = ui.Topic3->isChecked();
}
void UiAction::Topic4Enable()
{
	topicCheck4 = ui.Topic4->isChecked();
}
