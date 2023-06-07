#ifndef PWLOSCILLATOR_H
#define PWLOSCILLATOR_H

#include <QQmlListProperty>
#include <cmath>

#include "piecewisepoint.h"
#include "oscillator.h"
#include "constant.h"

class PWLOscillator : public Oscillator {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(QQmlListProperty<PieceWisePoint> points READ points)

	public:
		PWLOscillator(QObject *parent = nullptr);

		QQmlListProperty<PieceWisePoint> points();
		void appendPoint(PieceWisePoint *point);
		qsizetype pointCount() const;
		PieceWisePoint *point(qsizetype index) const;
		void clearPoints();
		void replacePoint(qsizetype index, PieceWisePoint *point);
		void removeLastPoint();

		float newSample() override;
		void reset() override;
	private:
		QList<PieceWisePoint *> _points;
		static void appendPoint(QQmlListProperty<PieceWisePoint> *list, PieceWisePoint *point);
		static qsizetype pointCount(QQmlListProperty<PieceWisePoint> *list);
		static PieceWisePoint *point(QQmlListProperty<PieceWisePoint> *list, qsizetype index);
		static void clearPoints(QQmlListProperty<PieceWisePoint> *list);
		static void replacePoint(QQmlListProperty<PieceWisePoint> *list, qsizetype index, PieceWisePoint *point);
		static void removeLastPoint(QQmlListProperty<PieceWisePoint> *list);

		qreal _lastValue;
		int _pointIndex = 0;

		qreal stepBetweenPoints(const PieceWisePoint *p0,
		                  const PieceWisePoint *p1, const qreal frequency) const;
};

#endif // PWLOSCILLATOR_H
