#ifndef _UIACTION_H_
#define _UIACTION_H_
#include <QtGui/QtGui>
#include"ui_Ui.h"
#include "T1TypeSupportC.h"
class UiAction : public QDialog
{
	Q_OBJECT
	public:
		//UiAction(QDialog *parent=0);
		UiAction(DDS::DomainParticipant_var participant);
		virtual ~UiAction();

	private:
		Ui::Dialog                 ui;

		DDS::DataReaderQos         readerQos;

		DDS::Topic_var             topic1;
		DDS::Topic_var             topic2;
		DDS::Topic_var             topic3;
		DDS::Topic_var             topic4;
		DDS::DomainParticipant_var participant_;
		DDS::Subscriber_var        subscriber;
		QTimer                     timer;
	
};
#endif
