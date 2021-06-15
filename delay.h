#ifndef DELAY_H
#define DELAY_H

#include <vector>
#include "jass.h"
#include "effect.h"

class Delay : public Effect {
		Q_OBJECT
		QML_ELEMENT
		// The delay in us.
		Q_PROPERTY(int delay
		           READ delay
		           WRITE setDelay
		           NOTIFY delayChanged)
	public:
		explicit Delay(QObject *parent = nullptr);

		int delay() const;
		void setDelay(int delay);

		float operator()() override;
		void reset() override;

	signals:
		void delayChanged();

	private:
		int _delay = 5000;
		DelayBuffer _buffer;
};

#endif // DELAY_H
