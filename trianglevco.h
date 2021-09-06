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

		float newSample() override;
		void reset() override;

	signals:
		void slewRatioChanged();

	private:
		double _slewRatio = 0.5;
		double _lastValue = 0;
};

#endif // TRIANGLEVCO_H
