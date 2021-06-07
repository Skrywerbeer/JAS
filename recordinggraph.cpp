#include "recordinggraph.h"

RecordingGraph::RecordingGraph(QQuickItem *parent) :
    QQuickPaintedItem(parent) {}

AudioRecording *RecordingGraph::recording() const {
	return _recording;
}

void RecordingGraph::setRecording(const AudioRecording *recording) {
	if (recording == _recording)
		return;
	if (_recording != nullptr)
		disconnectFromRecording();
	_recording = const_cast<AudioRecording *>(recording);
	emit recordingChanged();
	connectToRecording();
}

QColor RecordingGraph::color() const {
	return _color;
}

void RecordingGraph::setColor(const QColor &color) {
	if (color == _color)
		return;
	_color = color;
	emit colorChanged();
}

void RecordingGraph::paint(QPainter *painter) {
	painter->setPen(_color);
	rasterGraph(painter);
}

void RecordingGraph::drawVertical(QPainter *painter, int x, qreal ascent) {
	painter->drawLine(x, (height() - ascent)/2,
	                  x, (height() + ascent)/2);
}

void RecordingGraph::rasterGraph(QPainter *painter) {
	const int PIXELS_IN_WIDTH = static_cast<int>(width());
	const int SAMPLE_COUNT = _recording->_buffer.size();
	const int INC = SAMPLE_COUNT/PIXELS_IN_WIDTH;
	for (int i = 0; i < PIXELS_IN_WIDTH; ++i)
		drawVertical(painter, i, height()*JASS::rms(_recording->_buffer, i*INC, INC));
}

void RecordingGraph::connectToRecording() {
	connect(_recording, &AudioRecording::bufferChanged, [this]() {
		update();
	});
}

void RecordingGraph::disconnectFromRecording() {
	disconnect(SIGNAL(AudioRecording::bufferChanged()));
}

