#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "source.h"

class Oscillator : public Source {
		Q_OBJECT
		QML_ELEMENT
		QML_UNCREATABLE("This is a base class.")
		Q_PROPERTY(double frequency
		           READ frequency
		           WRITE setFrequency
		           NOTIFY frequencyChanged)
		Q_PROPERTY(double amplitude
		           READ amplitude
		           WRITE setAmplitude
		           NOTIFY amplitudeChanged)
		Q_PROPERTY(double offset
		           READ offset
		           WRITE setOffset
		           NOTIFY offsetChanged)
	public:
		Oscillator(QObject *parent = nullptr);

		double frequency() const;
		void setFrequency(double frequency);
		double amplitude() const;
		void setAmplitude(double amplitude);
		double offset() const;
		void setOffset(double offset);

	signals:
		void frequencyChanged();
		void amplitudeChanged();
		void offsetChanged();

	protected:

		double _frequency = 440;
		double _amplitude = 1;
		double _offset = 0;
		int _index = 0;
};

#endif // OSCILLATOR_H
