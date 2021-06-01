#ifndef DECAYEFFECT_H
#define DECAYEFFECT_H

#include "jass.h"
#include "source.h"

class Decay : public Source {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(Source *input
		           READ input
		           WRITE setInput
		           NOTIFY inputChanged
		           REQUIRED)
		Q_CLASSINFO("DefaultProperty", "input")
		// The the time in milliseconds for the output to reach halve of the input.
		Q_PROPERTY(int rate
		           READ rate
		           WRITE setRate
		           NOTIFY rateChanged)
	public:
		explicit Decay(QObject *parent = nullptr);

		Source *input() const;
		void setInput(const Source *input);
		int rate() const;
		void setRate(int rate);

		float operator()() override;
		void reset();

	signals:
		void inputChanged();
		void rateChanged();

	private:
		Source *_input = nullptr;
		int _rate = 1000;
		int _index = 1;
		long double _factor;
};

#endif // DECAYEFFECT_H
