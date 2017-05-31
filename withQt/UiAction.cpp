#include <QtGui>
#include <QDebug>

#include "UiAction.h"
UiAction::UiAction(QDialog *parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	qDebug()<< "start";	
}

void UiAction::SendButtonClicked()
{
	qDebug()<< "test";	
}

void UiAction::Topic1Enable(){};
void UiAction::Topic2Enable(){};
void UiAction::Topic3Enable(){};
void UiAction::Topic4Enable(){};
