#ifndef PADDING_H
#define PADDING_H

#include <QObject>
#include <QQmlEngine>

class Padding : public QObject {
		Q_OBJECT
		QML_ELEMENT
		QML_UNCREATABLE("Padding is meant to be used as a property.")
		Q_PROPERTY(qreal left
		           READ left
		           WRITE setLeft
		           NOTIFY leftChanged)
		Q_PROPERTY(qreal right
		           READ right
		           WRITE setRight
		           NOTIFY rightChanged)
		Q_PROPERTY(qreal top
		           READ top
		           WRITE setTop
		           NOTIFY topChanged)
		Q_PROPERTY(qreal bottom
		           READ bottom
		           WRITE setBottom
		           NOTIFY bottomChanged)
	public:
		Padding(QObject *parent = nullptr);

		qreal left() const;
		void setLeft(const qreal padding);
		qreal right() const;
		void setRight(const qreal padding);
		qreal top() const;
		void setTop(const qreal padding);
		qreal bottom() const;
		void setBottom(const qreal padding);

	signals:
		void changed();
		void leftChanged();
		void rightChanged();
		void topChanged();
		void bottomChanged();

	private:
		qreal _left = 0;
		qreal _right = 0;
		qreal _top = 0;
		qreal _bottom = 0;
};


#endif // PADDING_H
