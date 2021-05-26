#ifndef SINEGENERATOR_H
#define SINEGENERATOR_H

#include <vector>
#include <cmath>

#include <QQmlEngine>

#include "generator.h"

class SineGenerator : public Generator {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(float frequency
		           READ frequency
		           WRITE setFrequency
		           NOTIFY frequencyChanged)
		Q_PROPERTY(float amplitude
		          READ amplitude
		          WRITE setAmplitude
		          NOTIFY amplitudeChanged)
	public:
		SineGenerator(float frequency = 440,
		              float amplitude = 1,
		              uint sampleRate = 44100);
		virtual float operator()() override;
		void setSampleRate(uint value);
		float frequency() const;
		void setFrequency(float freq);
		float amplitude() const;
		void setAmplitude(float amplitude);

	signals:
		void frequencyChanged();
		void amplitudeChanged();

	private:
		const float TAU = 6.283185f;
		float _frequency = 440;
		float _amplitude = 1;
		uint _sampleRate = 44100;
		uint _index = 0;;
};

#endif // SINEGENERATOR_H
