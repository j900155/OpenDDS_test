#include <QtGui/QtGui>
#ifndef UIACTION_H
#define UIACTION_H
#include"ui_Ui.h"


class UiAction : public QDialog
{
	Q_OBJECT

	public:
		UiAction(QDialog *parent=0);
	public slots:
		void SendButtonClicked();
		void Topic1Enable();
		void Topic2Enable();
		void Topic3Enable();
		void Topic4Enable();
	
	private:
		Ui::Dialog ui;
};
#endif
