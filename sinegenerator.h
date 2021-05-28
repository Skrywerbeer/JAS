#ifndef SINEGENERATOR_H
#define SINEGENERATOR_H

#include <cmath>

#include "generator.h"

class SineGenerator : public Generator {
		Q_OBJECT
		QML_ELEMENT
	public:
		SineGenerator(QObject *parent = nullptr);
//		SineGenerator(float frequency = 440,
//		              float amplitude = 1,
//		              QObject *parent = nullptr);
		float operator()() override;
};

#endif // SINEGENERATOR_H
