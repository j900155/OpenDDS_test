#ifndef _ONSUBSCRIBER_H_
#define _ONSUBSCRIBER_H_
#include "ui_Ui.h"
#include <QtCore/QThread>
#include <QtGui/QtGui>
#include <QtCore/QString>
#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>
#include <iostream>
#include "T1TypeSupportImpl.h"
#include "T1TypeSupportC.h"
class OnSubscriber : public QThread
{
	Q_OBJECT

	public:
		OnSubscriber(DDS::DomainParticipant_var participant, char *get_topic);
		virtual ~OnSubscriber();
	protected:
		void run();

	signals:
		void getMessage();
	private:
		DDS::Topic_var topic;
		DDS::Subscriber_var subscriber;
		mT1::T1DataReader_var dataReader;

};
#endif
