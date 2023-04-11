#ifndef INTERVAL_H
#define INTERVAL_H

#include <QObject>
#include <QQmlEngine>

class Interval : public QObject {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(qreal lowerBound
		           READ lowerBound
		           WRITE setLowerBound
		           NOTIFY lowerBoundChanged)
		Q_PROPERTY(qreal upperBound
		           READ upperBound
		           WRITE setUpperBound
		           NOTIFY upperBoundChanged)

	public:
		Interval(QObject *parent = nullptr);

		qreal lowerBound() const;
		void setLowerBound(qreal value);
		qreal upperBound() const;
		void setUpperBound(qreal value);

		qreal normailzed(const qreal x) const;
		qreal width() const;

	signals:
		void changed();
		void lowerBoundChanged();
		void upperBoundChanged();

	private:
		qreal _lowerBound = 0;
		qreal _upperBound = 1;

		void swapBounds();
};


#endif // INTERVAL_H
