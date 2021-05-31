#ifndef SOURCE_H
#define SOURCE_H

#include <vector>
#include <iostream>

#include <QObject>
#include <QQmlEngine>

class Source : public QObject {
		Q_OBJECT
		QML_ELEMENT
		QML_UNCREATABLE("This is a abstract base class.")
	public:
		explicit Source(QObject *parent = nullptr);
		virtual float operator()() = 0;
		virtual void reset() = 0;

		Source &operator>>(std::vector<float> &vec);
		Source &operator+=(std::vector<float> &vec);

		template<int size>
		Source &operator+=(float (&arr)[size]) {
			for (int i = 0; i < size; ++i)
				arr[i] += this->operator()();
			return *this;
		}
		template<int size>
		Source &operator>>(float (&arr)[size]) {
			for (int i = 0; i < size; ++i)
				arr[i] = this->operator()();
			return *this;
		}

	signals:

};

#endif // SOURCE_H
