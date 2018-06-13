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
#ifdef linux
#include <sys/time.h>
#include <unistd.h>
#endif

#ifdef _WIN32
#include <windows.h> 
#include <time.h>


/* FILETIME of Jan 1 1970 00:00:00. */
static const unsigned __int64 epoch = ((unsigned __int64)116444736000000000ULL);

/*
* timezone information is stored outside the kernel so tzp isn't used anymore.
*
* Note: this function is not for Win32 high precision timing purpose. See
* elapsed_time().
*/
int
gettimeofday(struct timeval * tp, struct timezone * tzp)
{
	FILETIME    file_time;
	SYSTEMTIME  system_time;
	ULARGE_INTEGER ularge;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	ularge.LowPart = file_time.dwLowDateTime;
	ularge.HighPart = file_time.dwHighDateTime;

	tp->tv_sec = (long)((ularge.QuadPart - epoch) / 10000000L);
	tp->tv_usec = (long)(system_time.wMilliseconds * 1000);

	return 0;
}

void usleep(__int64 usec)
{
	HANDLE timer;
	LARGE_INTEGER ft;

	ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}
#endif


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


	//time
	struct timeval tv;
	gettimeofday(&tv,NULL);
    // Write samples
	std::string text;
	long c = 0;
	int delay_us = 100000;
	std::cout << "delay us" << std::endl;
	std::cin >> delay_us;
	std::cout << "send data"<< std::endl;
	std::cin >> text;
    Messenger::Message message;
	DDS::ReturnCode_t error;
	//wait for subscriber
	while(true)
	{
		DDS::PublicationMatchedStatus matches;
		if(writer->get_publication_matched_status(matches) != DDS::RETCODE_OK)
		{
			 ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" get_publication_matched_status faild!\n")),
                       -1);
	
		}
		if(matches.current_count >=1)
		{
			break;
		}
	}
	long t;
	gettimeofday(&tv,NULL);
	t = tv.tv_sec;
	while(true)
	{
	
		//std::cin.ignore();
		//std::cout << "send count"<< std::endl;
		//std::cin >> c;
		//std::cout << "c" << c << std::endl;
		c++;
		//message.sendData = "AAAAAAAA";
		if(text == "exit")
		{
	        //error = message_writer->write(message, DDS::HANDLE_NIL);
			std::cout << "exit\n";
			break;
		}
		
		if((tv.tv_sec - t) > 5)
		{
			break;
		}
		
		message.sendData = text.c_str();
		/*
		if(c > 100)
		{
		    message.sendData = "exit";
			message.c = -1;
	        error = message_writer->write(message, DDS::HANDLE_NIL);
			std::cout << "exit" << std::endl;
			break;
		}*/
	    //message.sendTime  = 0;
		gettimeofday(&tv,NULL);
		message.sendTime = (tv.tv_usec+ (tv.tv_sec%100)*1000000);
		message.c = c;
	    error = message_writer->write(message, DDS::HANDLE_NIL);
	      if (error != DDS::RETCODE_OK)
		  {
		    ACE_ERROR((LM_ERROR,
            ACE_TEXT("ERROR: %N:%l: main() -"),
            ACE_TEXT(" write returned %d!\n"), error));
		}
		std::cout << "ok " << c  << std::endl;
		usleep(delay_us);
	}
	message.sendData = "end";
	message.c = -1;
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
