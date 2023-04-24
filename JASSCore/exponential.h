#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H

#include <cmath>

#include "jass.h"
#include "source.h"


class Exponential : public Source {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(qreal initial
		           READ initial
		           WRITE setInitial
		           NOTIFY initialChanged)
		Q_PROPERTY(qreal asymptote
		           READ asymptote
		           WRITE setAsymptote
		           NOTIFY asymptoteChanged)
		Q_PROPERTY(qreal timeConstant
		           READ timeConstant
		           WRITE setTimeConstant
		           NOTIFY timeConstantChanged)
	public:
		Exponential(QObject *parent = nullptr);

		qreal initial() const;
		void setInitial(const qreal value);
		qreal asymptote() const;
		void setAsymptote(const qreal value);
		qreal timeConstant() const;
		void setTimeConstant(const qreal value);

		float newSample() override;
		void reset() override;

	signals:
		void initialChanged();
		void asymptoteChanged();
		void timeConstantChanged();

	private:
		int _index = 0;
		qreal _initial = 0;
		qreal _asymptote = 1;
		qreal _timeConstant = 1;
};



#endif // EXPONENTIAL_H
