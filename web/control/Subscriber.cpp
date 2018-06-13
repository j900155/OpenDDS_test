#include <iostream>
#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>

#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>

#include "dds/DCPS/StaticIncludes.h"

#include "MessengerTypeSupportImpl.h"

#include <fstream>

#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>

int ACE_TMAIN(int argc, char *argv[])
{
	DDS::DomainParticipantFactory_var dpf = TheParticipantFactoryWithArgs(argc, argv);
	DDS::DomainParticipant_var participant = dpf-> 
		create_participant(
				43,
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

	DDS::ReturnCode_t error;
	DDS::SampleInfo info;
	Messenger::Message message;
	struct timeval tv;
	int get_count = 0;
	int delay_us = 1000;
	std::cout << "delay us" << std::endl;
	std::cin >> delay_us;
	fstream fp;
	std::string fileName;
	std::cout << "file name" << std::endl;
	std::cin >> fileName;
	fileName +=".txt";
	fp.open(fileName, std::fstream::in | std::fstream::app);
	//socket create
	std::cout << "socket start" << std::endl;
	int sockfd = 0;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd ==-1)
	{
		std::cout << "create socket error \n";
		return -1;
	}
	struct sockaddr_in remote_addr;
	const int BUFFSIZE = 200;
	char buf[BUFFSIZE];
	int len;
	memset(&remote_addr,0,sizeof(remote_addr));
	memset(buf,0,sizeof(buf));
	remote_addr.sin_family=AF_INET;
	remote_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	remote_addr.sin_port=htons(9807);

	if(connect(sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)
	{
		std::cout << "sock connect err" << std::endl;
		return -1;
	}
	std::string text;
	text = "subscriber";
	send(sockfd,text.c_str(),text.length(),0);
	while(true)
	{
		error = dataReader->take_next_sample(message, info);

		if(error == DDS::RETCODE_OK)
		{
			if(info.valid_data)	
			{		
				text = message.sendData;
				if("exit" == text)
				{
				    std::cout << "exit" << std::endl;
				    break;
				}
				std::cout << "to string " << text.c_str() << std::endl;
				send(sockfd,text.c_str(),text.length(),0);
				get_count ++;
				gettimeofday(&tv,NULL);
				long nowTime = tv.tv_sec;
				std::cout<< "topic name " << topic->get_name() << std::endl;
				std::cout << "message count " << message.c;
				std::cout << ";message time " << message.sendTime;
				std::cout << ";message data " << message.sendData << std::endl;
				std::cout << "get_count" << get_count << std::endl;
				fp << "message_data," << message.sendData << ",message_time," << message.sendTime  << std::endl;

			}
		}
		usleep(delay_us);

	}
	close(sockfd);
    // Clean-up!
    participant->delete_contained_entities();
    dpf->delete_participant(participant);

    TheServiceParticipant->shutdown();

	return 0;
}

