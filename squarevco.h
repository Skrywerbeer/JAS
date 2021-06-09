#ifndef SQUAREVCO_H
#define SQUAREVCO_H

#include "vco.h"

class SquareVCO : public VCO {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(double dutyCycle
		           READ dutyCycle
		           WRITE setDutyCycle
		           NOTIFY dutyCycleChanged)
	public:
		explicit SquareVCO(QObject *parent = nullptr);

		double dutyCycle() const;
		void setDutyCycle(double duty);

		float operator()() override;
		void reset() override;

	signals:
		void dutyCycleChanged();

	private:
		double _dutyCycle = 0.5;
};

#endif // SQUAREVCO_H
