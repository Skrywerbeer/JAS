#ifndef CONSTANT_H
#define CONSTANT_H

#include "jass.h"
#include "source.h"

class Constant : public Source {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(double value
		           READ value
		           WRITE setValue
		           NOTIFY valueChanged)
	public:
		explicit Constant(QObject *parent = nullptr);

		double value() const;
		void setValue(double value);

		float operator()() override;
		void reset() override;

	signals:
		void valueChanged();

	private:
		double _value = 0;
};

#endif // CONSTANT_H
