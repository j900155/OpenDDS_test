#ifndef _UIACTION_H_
#define _UIACTION_H_
#include <QtGui/QtGui>
#include <QtCore/QString>
#include"ui_Ui.h"
#include "T1TypeSupportC.h"
#include "OnSubscriber.h"
class UiAction : public QDialog
{
	Q_OBJECT
	public:
		UiAction(DDS::DomainParticipant_var participant);
		virtual ~UiAction();

	public slots:
		void showMessage(QString text, int number);

	private:
		Ui::Dialog	ui;
		OnSubscriber *thread1;
		OnSubscriber *thread2;
	
};
#endif
