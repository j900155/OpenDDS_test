#ifndef READ_H_
#define READ_H_
#include <QtCore/QThread>
class Reader :public QThread
{
	Q_OBJECT
	public:
		void run();
};
#endif
