/*
 *
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#include <ace/Log_Msg.h>

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>

#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>

#include "dds/DCPS/StaticIncludes.h"

#include "MessengerTypeSupportImpl.h"
#include <iostream>

//time stamp
#include <sys/time.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int
ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
  try {
    // Initialize DomainParticipantFactory
    DDS::DomainParticipantFactory_var dpf =
      TheParticipantFactoryWithArgs(argc, argv);

    // Create DomainParticipant
    DDS::DomainParticipant_var participant =
      dpf->create_participant(43,
                              PARTICIPANT_QOS_DEFAULT,
                              0,
                              OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    if (!participant) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" create_participant failed!\n")),
                       -1);
    }

    // Register TypeSupport (Messenger::Message)
    Messenger::MessageTypeSupport_var ts =
      new Messenger::MessageTypeSupportImpl;

    if (ts->register_type(participant, "") != DDS::RETCODE_OK) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" register_type failed!\n")),
                       -1);
    }


    // Create Topic (Movie Discussion List)
	std::string topic_name;
	std::cout << "topic name? \n";
	std::cin >> topic_name;
	std::cout << "topic name " << topic_name << std::endl;
    CORBA::String_var type_name = ts->get_type_name();
    DDS::Topic_var topic =
      participant->create_topic(topic_name.c_str(),
                                type_name,
                                TOPIC_QOS_DEFAULT,
                                0,
                                OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    if (!topic) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" create_topic failed!\n")),
                       -1);
    }


    // Create Publisher
    DDS::Publisher_var publisher =
      participant->create_publisher(PUBLISHER_QOS_DEFAULT,
                                    0,
                                    OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    if (!publisher) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" create_publisher failed!\n")),
                       -1);
    }
	
    DDS::DataWriter_var writer =
      publisher->create_datawriter(topic,
                                   DATAWRITER_QOS_DEFAULT,
                                   0,
                                   OpenDDS::DCPS::DEFAULT_STATUS_MASK);

    if (!writer) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" create_datawriter failed!\n")),
                       -1);
    }

    Messenger::MessageDataWriter_var message_writer =
      Messenger::MessageDataWriter::_narrow(writer);

    if (!message_writer) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" _narrow failed!\n")),
                       -1);
    }
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
	remote_addr.sin_port=htons(9808);

	if(connect(sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)
	{
		std::cout << "sock connect err" << std::endl;
		return -1;
	}
	send(sockfd,"publisher",9,0);
	//time
	struct timeval tv;
	gettimeofday(&tv,NULL);
    // Write samples
	std::string text;
	long c = 0;
	int delay_us = 100000;
	int i;
	//std::cout << "delay us" << std::endl;
	//std::cin >> delay_us;
	Messenger::Message message;
	DDS::ReturnCode_t error;
	gettimeofday(&tv,NULL);
//	t = tv.tv_sec;
	while(true)
	{
		len = recv(sockfd, buf,BUFFSIZE,0);
		if(len > 0)
		{
			std::cout <<len << " " << buf << std::endl;
			c++;
			//message.sendData = "AAAAAAAA";

			for(i=0;i<len;i++)
			{
				text += buf[i];
			}
			message.sendData = text.c_str();

			if(strcmp(buf,"exit") == 0)
			{
				error = message_writer->write(message, DDS::HANDLE_NIL);
				std::cout << "exit\n";
				break;
			}
			else if(strcmp(buf,"heartbeat")==0)
			{
				send(sockfd,"alive",5,0);
			}
			gettimeofday(&tv,NULL);
			int sec = tv.tv_sec%100;
			message.sendTime = (tv.tv_usec + sec*1000000);
			message.c = c;
			error = message_writer->write(message, DDS::HANDLE_NIL);
			  if (error != DDS::RETCODE_OK)
			  {
				ACE_ERROR((LM_ERROR,
				ACE_TEXT("ERROR: %N:%l: main() -"),
				ACE_TEXT(" write returned %d!\n"), error));
			}
			std::cout << "ok " << c  << std::endl;
			memset(buf,0,BUFFSIZE);
			text = "";
		}
		usleep(delay_us);
	}
	close(sockfd);
	message.sendData = "end";
	error = message_writer->write(message, DDS::HANDLE_NIL);
    // Wait for samples to be acknowledged
	std::cout << "end" << std::endl;	
    DDS::Duration_t timeout = { 30, 0 };
    if (message_writer->wait_for_acknowledgments(timeout) != DDS::RETCODE_OK) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" wait_for_acknowledgments failed!\n")),
                       -1);
    }
	std::cout << "clean" << std::endl;
    // Clean-up!
    participant->delete_contained_entities();
    dpf->delete_participant(participant);

    TheServiceParticipant->shutdown();

  } catch (const CORBA::Exception& e) {
    e._tao_print_exception("Exception caught in main():");
    return -1;
  }
  return 0;
}
