#include <QtCore/QThread>
#include <iostream>

#ifndef _ONSUBSCRIBER_H_
#define _ONSUBSCRIBER_H_
class OnSubscriber : public QThread
{
	Q_OBJECT

	public:
		OnSubscriber();
		void testRun();
		virtual ~OnSubscriber();
};
#endif
