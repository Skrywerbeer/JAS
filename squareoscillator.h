#ifndef SQUAREOSCILLATOR_H
#define SQUAREOSCILLATOR_H

#include "jass.h"
#include "oscillator.h"

class SquareOscillator : public Oscillator {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(double dutyCycle
		           READ dutyCycle
		           WRITE setDutyCycle
		           NOTIFY dutyCycleChanged)
	public:
		explicit SquareOscillator(QObject *parent = nullptr);

		double dutyCycle() const;
		void setDutyCycle(double duty);

		float operator()();
		void reset();

	signals:
		void dutyCycleChanged();

	private:
		double _dutyCycle = 0.5;
};

#endif // SQUAREOSCILLATOR_H
