#include <QtGui/QtGui>
#include <QtCore/QString>

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>

#include <iostream>

#include "T1TypeSupportImpl.h"

#include "UiAction.h"
UiAction::UiAction(DDS::DomainParticipant_var participant)
: participant_(participant)
{

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
	//datawirter1
	DDS::DataWriter_var writer1 = publisher->create_datawriter(topic1,
															writerQos,
															0,
															OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!writer1)
	{
		std::cerr <<"create writer1 fail"<< std::endl;
	}
	mT1::T1DataWriter_var dw1 = mT1::T1DataWriter::_narrow(writer1);
	if(!dw1)
	{
		std::cerr <<"narrow dw1  fail"<< std::endl;
	}
	QString qs = ui.Topic1Text->text();
	std::string s = qs.toStdString();
	std::cout << s << std::endl;
	mT1::T1 message1;
	message1.T1_id = 0;
	message1.T1_S = s.c_str();
	dw1->write(message1, DDS::HANDLE_NIL);

//datawriter1 end

//datawirter2
	DDS::DataWriter_var writer2 = publisher->create_datawriter(topic2,
															writerQos,
															0,
															OpenDDS::DCPS::DEFAULT_STATUS_MASK);
	if(!writer2)
	{
		std::cerr <<"create writer1 fail"<< std::endl;
	}
	mT1::T1DataWriter_var dw2 = mT1::T1DataWriter::_narrow(writer2);
	if(!dw2)
	{
		std::cerr <<"narrow dw2  fail"<< std::endl;
	}
	qs = ui.Topic2Text->text();
	s = qs.toStdString();
	std::cout << s << std::endl;
	mT1::T1 message2;
	message2.T1_id = 0;
	message2.T1_S = s.c_str();
	dw2->write(message1, DDS::HANDLE_NIL);

//datawriter1 end


}

void UiAction::Topic1Enable(){}
void UiAction::Topic2Enable(){}
void UiAction::Topic3Enable(){}
void UiAction::Topic4Enable(){}
