#ifndef PIECEWISEFUNCTION_H
#define PIECEWISEFUNCTION_H

#include "jass.h"
#include "source.h"
#include "piecewisepoint.h"

class PieceWiseFunction : public Source {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(QQmlListProperty<PieceWisePoint> points READ points)

	public:
		PieceWiseFunction(QObject *parent = nullptr);

		QQmlListProperty<PieceWisePoint> points();
		void appendPoint(PieceWisePoint *value);
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

		int _sampleIndex = 0;
		int _pointIndex = 0;
};

#endif // PIECEWISEFUNCTION_H
