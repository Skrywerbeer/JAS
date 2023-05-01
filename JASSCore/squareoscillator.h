#ifndef SQUAREOSCILLATOR_H
#define SQUAREOSCILLATOR_H

#include "jass.h"
#include "oscillator.h"

class SquareOscillator : public Oscillator {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(Source *dutyCycle
		           READ dutyCycle
		           WRITE setDutyCycle
		           NOTIFY dutyCycleChanged)
	public:
		explicit SquareOscillator(QObject *parent = nullptr);

		Source *dutyCycle() const;
		void setDutyCycle(Source *duty);

		float newSample() override;
		void reset() override;

	signals:
		void dutyCycleChanged();

	private:
		Source *_dutyCycle = new Constant(this, 0.5);
};

#endif // SQUAREOSCILLATOR_H
