#ifndef AXISTICKS_H
#define AXISTICKS_H

#include <QObject>
#include <QQmlEngine>
#include <QColor>

class AxisTicks : public QObject {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(QColor color
		           READ color
		           WRITE setColor
		           NOTIFY colorChanged)
		Q_PROPERTY(int count
		           READ count
		           WRITE setCount
		           NOTIFY countChanged)
		Q_PROPERTY(qreal width
		           READ width
		           WRITE setWidth
		           NOTIFY widthChanged)
		Q_PROPERTY(qreal length
		           READ length
		           WRITE setLength
		           NOTIFY lengthChanged)

	public:
		AxisTicks(QObject *parent = nullptr);

		QColor color() const;
		void setColor(const QColor &color);
		int count() const;
		void setCount(int count);
		qreal width() const;
		void setWidth(qreal width);
		qreal length() const;
		void setLength(qreal length);

	signals:
		void changed();
		void colorChanged();
		void countChanged();
		void widthChanged();
		void lengthChanged();

	private:
		QColor _color = Qt::white;
		int _count = 4;
		qreal _width = 1.0;
		qreal _length = 10.0;
};


#endif // AXISTICKS_H
