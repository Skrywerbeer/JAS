#ifndef PIECEWISEPOINT_H
#define PIECEWISEPOINT_H

#include <QObject>
#include <QQmlEngine>

class PieceWisePoint : public QObject {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(qreal value
		           READ value
		           WRITE setValue
		           NOTIFY valueChanged)
		Q_PROPERTY(qreal time
		           READ time
		           WRITE setTime
		           NOTIFY timeChanged)

	public:
		PieceWisePoint(QObject *parent = nullptr);

		qreal value() const;
		void setValue(const qreal value);

		qreal time() const;
		void setTime(const qreal time);

	signals:
		void valueChanged();
		void timeChanged();

	private:
		qreal _value = 0;
		qreal _time = 0;
};

#endif // PIECEWISEPOINT_H
