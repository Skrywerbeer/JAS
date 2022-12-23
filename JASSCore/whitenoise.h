#ifndef WHITENOISE_H
#define WHITENOISE_H

#include <random>

#include "source.h"

class WhiteNoise : public Source {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(double amplitude
		           READ amplitude
		           WRITE setAmplitude
		           NOTIFY amplitudeChanged)
	public:
		explicit WhiteNoise(QObject *parent = nullptr);

		double amplitude() const;
		void setAmplitude(double amplitude);

		float newSample() override;
		void reset() override;

	signals:
		void amplitudeChanged();

	private:
		double _amplitude = 1.0;
		std::mt19937 _twister;
};

#endif // WHITENOISE_H
