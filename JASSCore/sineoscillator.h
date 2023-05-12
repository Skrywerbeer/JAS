#ifndef SINEGENERATOR_H
#define SINEGENERATOR_H

#include <cmath>
#include <complex>

#include "oscillator.h"

class SineOscillator : public Oscillator {
		Q_OBJECT
		QML_ELEMENT
	public:
		SineOscillator(QObject *parent = nullptr);

		float newSample() override;
		void reset() override;

	private:
		std::complex<double> _last = 1;

};

#endif // SINEGENERATOR_H
