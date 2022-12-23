#ifndef VCO_H
#define VCO_H

#include "jass.h"
#include "oscillator.h"
// TODO: create base VoltageControlledSource class
class VCO : public Oscillator {
		Q_OBJECT
		Q_PROPERTY(Source *cv
		           READ cv
		           WRITE setCV
		           NOTIFY cvChanged
		           REQUIRED)
		Q_PROPERTY(double deviation
		           READ deviation
		           WRITE setDeviation
		           NOTIFY deviationChanged)
	public:
		explicit VCO(QObject *parent = nullptr);

		Source *cv() const;
		void setCV(Source *cv);
		double deviation() const;
		void setDeviation(double deviation);

	signals:
		void cvChanged();
		void deviationChanged();

	protected:
		Source *_cv = nullptr;
		double _deviation = 0;
};

#endif // VCO_H
