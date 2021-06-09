#ifndef TRIANGLEVCO_H
#define TRIANGLEVCO_H

#include "vco.h"

class TriangleVCO : public VCO {
		Q_OBJECT
		QML_ELEMENT
		// The ratio of the rising slew rate to the falling slew rate.
		Q_PROPERTY(double slewRatio
		           READ slewRatio
		           WRITE setSlewRatio
		           NOTIFY slewRatioChanged)
	public:
		explicit TriangleVCO(QObject *parent = nullptr);

		double slewRatio() const;
		void setSlewRatio(double ratio);

		float operator()() override;
		void reset() override;

	signals:
		void slewRatioChanged();

	private:
		double _slewRatio = 0.5;
		int _risingSampleCount = static_cast<double>(JASS::SAMPLE_RATE)*_slewRatio/_frequency;
};

#endif // TRIANGLEVCO_H
