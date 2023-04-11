#ifndef PLOT_H
#define PLOT_H

#include <QObject>
#include <QQmlEngine>
#include <QColor>

#include "../JASSCore/source.h"


class Plot : public QObject {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(Source *input
		           READ input
		           WRITE setInput
		           NOTIFY inputChanged)
		Q_PROPERTY(QColor color
		           READ color
		           WRITE setColor
		           NOTIFY colorChanged)
		Q_PROPERTY(qreal width
		           READ width
		           WRITE setWidth
		           NOTIFY widthChanged)
		// TODO: gradient
	public:
		Plot(QObject *parent = nullptr);
		~Plot();

		Source *input() const;
		void setInput(Source *input);

		QColor color() const;
		void setColor(const QColor &color);

		qreal width() const;
		void setWidth(qreal width);

//		QGradient gradient() const;
//		void setGradient(QGradient gradient);

	signals:
		void changed();
		void inputChanged();
		void colorChanged();
		void widthChanged();
//		void gradientChanged();

	private:
		Source *_input = nullptr;
		QColor _color = Qt::white;
		qreal _width = 1.0;
//		QGradient _gradient;
};


#endif // PLOT_H
