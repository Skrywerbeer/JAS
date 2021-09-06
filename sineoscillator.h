#ifndef SINEGENERATOR_H
#define SINEGENERATOR_H

#include <cmath>

#include "oscillator.h"

class SineOscillator : public Oscillator {
		Q_OBJECT
		QML_ELEMENT
	public:
		SineOscillator(QObject *parent = nullptr);

		float newSample() override;
		void reset() override;
};

#endif // SINEGENERATOR_H
