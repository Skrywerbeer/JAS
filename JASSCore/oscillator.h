#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "source.h"
#include "constant.h"

class Oscillator : public Source {
		Q_OBJECT
		QML_ELEMENT
		QML_UNCREATABLE("This is a base class.")
		Q_PROPERTY(Source *frequency
		           READ frequency
		           WRITE setFrequency
		           NOTIFY frequencyChanged)
		Q_PROPERTY(Source *amplitude
		           READ amplitude
		           WRITE setAmplitude
		           NOTIFY amplitudeChanged)
		Q_PROPERTY(Source *offset
		           READ offset
		           WRITE setOffset
		           NOTIFY offsetChanged)
	public:
		Oscillator(QObject *parent = nullptr);

		Source *frequency() const;
		void setFrequency(Source *frequency);
		Source *amplitude() const;
		void setAmplitude(Source *amplitude);
		Source *offset() const;
		void setOffset(Source *offset);

		void reset() override;
		bool isDependency(const Source *source) const override;

	signals:
		void frequencyChanged();
		void amplitudeChanged();
		void offsetChanged();

	protected:
		Source *_frequency = new Constant(this, 440);
		Source *_amplitude = new Constant(this, 1);
		Source *_offset = new Constant(this, 0);
		int _index = 0;
};

#endif // OSCILLATOR_H
