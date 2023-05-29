#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H

#include <cmath>

#include "jass.h"
#include "source.h"
#include "constant.h"

class Exponential : public Source {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(Source *initial
		           READ initial
		           WRITE setInitial
		           NOTIFY initialChanged)
		Q_PROPERTY(Source *asymptote
		           READ asymptote
		           WRITE setAsymptote
		           NOTIFY asymptoteChanged)
		Q_PROPERTY(Source *timeConstant
		           READ timeConstant
		           WRITE setTimeConstant
		           NOTIFY timeConstantChanged)
	public:
		Exponential(QObject *parent = nullptr);

		Source *initial() const;
		void setInitial(Source *value);
		Source *asymptote() const;
		void setAsymptote(Source *value);
		Source *timeConstant() const;
		void setTimeConstant(Source *value);

		float newSample() override;
		void reset() override;
		bool isDependency(const Source *source) const override;

	signals:
		void initialChanged();
		void asymptoteChanged();
		void timeConstantChanged();

	private:
		int _index = 0;
		Source *_initial = new Constant(this, 0);
		Source *_asymptote = new Constant(this, 1);
		Source *_timeConstant = new Constant(this, 1);
};



#endif // EXPONENTIAL_H
