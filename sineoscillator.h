#ifndef SINEGENERATOR_H
#define SINEGENERATOR_H

#include <cmath>

#include "oscillator.h"

class SineGenerator : public Oscillator {
		Q_OBJECT
		QML_ELEMENT
	public:
		SineGenerator(QObject *parent = nullptr);

		float operator()() override;
		void reset() override;
};

#endif // SINEGENERATOR_H
