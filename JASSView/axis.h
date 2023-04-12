#ifndef AXIS_H
#define AXIS_H

#include <QObject>
#include <QQmlEngine>
#include <QColor>

#include "axisticks.h"

class Axis : public QObject {
		Q_OBJECT
		QML_ELEMENT
		QML_UNCREATABLE("Axis is meant to be used as a property.")
		Q_PROPERTY(bool visible
		           READ visible
		           WRITE setVisible
		           NOTIFY visibleChanged)
		Q_PROPERTY(QColor color
		           READ color
		           WRITE setColor
		           NOTIFY colorChanged)
		Q_PROPERTY(Position position
		           READ position
		           WRITE setPosition
		           NOTIFY positionChanged)
		Q_PROPERTY(AxisTicks* majorTicks
		           READ majorTicks)
		Q_PROPERTY(AxisTicks *minorTicks
		           READ minorTicks)
	public:
		enum Position {
			Start = 0,
			Center,
			End
		}; Q_ENUM(Position)

		Axis(QObject *parent = nullptr);

		bool visible() const;
		void setVisible(bool value);
		QColor color() const;
		void setColor(const QColor &color);
		Position position() const;
		void setPosition(const Position pos);

		AxisTicks *majorTicks() const;
		AxisTicks *minorTicks() const;

	signals:
		void changed();
		void visibleChanged();
		void colorChanged();
		void positionChanged();

	private:
		bool _visible = false;
		// NOTE: Check for leaks.
		AxisTicks *_majorTicks = new AxisTicks(this);
		AxisTicks *_minorTicks = new AxisTicks(this);
		QColor _color = Qt::white;
		Position _position = Position::Start;
};

#endif // AXIS_H
