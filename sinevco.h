#ifndef SINEVCO_H
#define SINEVCO_H

#include "jass.h"
#include "vco.h"

class SineVCO : public VCO {
		Q_OBJECT
		QML_ELEMENT
	public:
		explicit SineVCO(QObject *parent = nullptr);

		float newSample() override;
		void reset() override;
};

#endif // SINEVCO_H
