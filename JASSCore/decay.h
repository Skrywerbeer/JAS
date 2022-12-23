#ifndef DECAYEFFECT_H
#define DECAYEFFECT_H

#include "jass.h"
#include "effect.h"

class Decay : public Effect {
		Q_OBJECT
		QML_ELEMENT
		// The the time in milliseconds for the output to reach halve of the input.
		Q_PROPERTY(int rate
		           READ rate
		           WRITE setRate
		           NOTIFY rateChanged)
	public:
		explicit Decay(QObject *parent = nullptr);

		int rate() const;
		void setRate(int rate);

		float newSample() override;
		void reset() override;

	signals:
		void rateChanged();

	private:
		int _rate = 1000;
		int _index = 0;
		long double _factor;
};

#endif // DECAYEFFECT_H
