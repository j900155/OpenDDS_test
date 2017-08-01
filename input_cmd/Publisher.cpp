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

//time stamp
//#include <sys/time.h>
#include < time.h >
#include <windows.h> 

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif



struct timezone
{
	int  tz_minuteswest; /* minutes W of Greenwich */
	int  tz_dsttime;     /* type of dst correction */
};

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
	FILETIME ft;
	unsigned __int64 tmpres = 0;
	static int tzflag;

	if (NULL != tv)
	{
		GetSystemTimeAsFileTime(&ft);

		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;

		/*converting file time to unix epoch*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS;
		tmpres /= 10;  /*convert into microseconds*/
		tv->tv_sec = (long)(tmpres / 1000000UL);
		tv->tv_usec = (long)(tmpres % 1000000UL);
	}

	if (NULL != tz)
	{
		if (!tzflag)
		{
			_tzset();
			tzflag++;
		}
		tz->tz_minuteswest = _timezone / 60;
		tz->tz_dsttime = _daylight;
	}

	return 0;
}

#include <iostream>
int
ACE_TMAIN(int argc, ACE_TCHAR *argv[])
{
  try {
    // Initialize DomainParticipantFactory
    DDS::DomainParticipantFactory_var dpf =
      TheParticipantFactoryWithArgs(argc, argv);

    // Create DomainParticipant
    DDS::DomainParticipant_var participant =
      dpf->create_participant(42,
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
	std::cout << "topic name? ";
	std::cin >> topic_name;
	//std::cin.clear();
	//std::cin.ignore(INT_MAX, '\n');
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

    // Block until Subscriber is available
    DDS::StatusCondition_var condition = writer->get_statuscondition();
    condition->set_enabled_statuses(DDS::PUBLICATION_MATCHED_STATUS);

    DDS::WaitSet_var ws = new DDS::WaitSet;

	//time
	struct timeval tv;
	gettimeofday(&tv,NULL);
    // Write samples
	std::string text;
    Messenger::Message message;
	while(true)
	{
		message.sendData = "";
		std::cout << "send data"<< std::endl;
		getline(std::cin, text);
		if(text == "exit")
		{
			std::cout << "exit" << std::endl;
			break;
		}
		message.sendData = text.c_str();
		gettimeofday(&tv, NULL);
		message.sendTime = tv.tv_usec;
	      DDS::ReturnCode_t error = message_writer->write(message, DDS::HANDLE_NIL);
	      if (error != DDS::RETCODE_OK)
		  {
		    ACE_ERROR((LM_ERROR,
            ACE_TEXT("ERROR: %N:%l: main() -"),
            ACE_TEXT(" write returned %d!\n"), error));
		}
	}
    // Wait for samples to be acknowledged
    DDS::Duration_t timeout = { 30, 0 };
    if (message_writer->wait_for_acknowledgments(timeout) != DDS::RETCODE_OK) {
      ACE_ERROR_RETURN((LM_ERROR,
                        ACE_TEXT("ERROR: %N:%l: main() -")
                        ACE_TEXT(" wait_for_acknowledgments failed!\n")),
                       -1);
    }

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
