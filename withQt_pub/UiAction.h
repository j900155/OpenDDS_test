#ifndef _ISUI_H
#define _ISUI_H
#include <QtGui/QtGui>
#include"ui_Ui.h"
#include "T1TypeSupportC.h"
class UiAction : public QDialog{
	Q_OBJECT
	public:
		//UiAction(QDialog *parent=0);
		UiAction(DDS::DomainParticipant_var participant);
		virtual ~UiAction();
	public slots:
		virtual void SendButtonClicked();
		virtual void Topic1Enable();
		virtual	void Topic2Enable();
		virtual	void Topic3Enable();
		virtual	void Topic4Enable();
	private:
		Ui::Dialog ui;

		DDS::DataWriterQos   writerQos;

		DDS::Topic_var             topic1;
		DDS::Topic_var             topic2;
		DDS::Topic_var             topic3;
		DDS::Topic_var             topic4;
		DDS::DomainParticipant_var participant_;
		DDS::Publisher_var         publisher;
		DDS::Subscriber_var        subscriber;
};
#endif
