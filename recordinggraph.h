#ifndef RECORDINGGRAPH_H
#define RECORDINGGRAPH_H

#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QQmlEngine>
#include <QPainter>

#include "JASSCore/jass.h"
#include "JASSCore/audiorecording.h"

class RecordingGraph : public QQuickPaintedItem {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(AudioRecording *recording
		           READ recording
		           WRITE setRecording
		           NOTIFY recordingChanged)
		Q_PROPERTY(QColor color
		           READ color
		           WRITE setColor
		           NOTIFY colorChanged)
	public:
		RecordingGraph(QQuickItem *parent = nullptr);

		AudioRecording *recording() const;
		void setRecording(const AudioRecording *recording);
		QColor color() const;
		void setColor(const QColor &color);

		void paint(QPainter *painter) override;

	signals:
		void recordingChanged();
		void colorChanged();

	private:
		AudioRecording *_recording = nullptr;
		QColor _color = QColor(Qt::black);

		void drawVertical(QPainter *painter, int x, qreal ascent);
		void rasterGraph(QPainter *painter);
		void connectToRecording();
		void disconnectFromRecording();
};

#endif // RECORDINGGRAPH_H
