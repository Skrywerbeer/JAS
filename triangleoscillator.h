#ifndef TRIANGLEOSCILLATOR_H
#define TRIANGLEOSCILLATOR_H

#include "oscillator.h"
#include "jass.h"

class TriangleOscillator : public Oscillator {
		Q_OBJECT
		QML_ELEMENT
		// The ratio of the rising slew rate to the falling slew rate.
		Q_PROPERTY(double slewRatio
		           READ slewRatio
		           WRITE setSlewRatio
		           NOTIFY slewRatioChanged)
	public:
		explicit TriangleOscillator(QObject *parent = nullptr);
		~TriangleOscillator();

		double slewRatio() const;
		void setSlewRatio(double ratio);

		float operator()() override;
		void reset() override;

	signals:
		void slewRatioChanged();

	private:
		double _slewRatio = 0.5;
		int _risingSampleCount = static_cast<double>(jass::SAMPLE_RATE)*_slewRatio/_frequency;
		double _risingDelta = 2.0*_frequency*jass::SAMPLE_PERIOD/_slewRatio;
		int _fallingSampleCount = static_cast<double>(jass::SAMPLE_RATE)*(1.0 - _slewRatio)/_frequency;
		double _fallingDelta = 2.0*_frequency*jass::SAMPLE_PERIOD/(1.0 - _slewRatio);

	private slots:
		void calculateConstants();

};

#endif // TRIANGLEOSCILLATOR_H
