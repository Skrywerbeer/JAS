#include <QFile>
#include <QDataStream>
#include <stdexcept>
#include "audiorecording.h"

AudioRecording::AudioRecording(QObject *parent) :
    Source(parent) {}

int AudioRecording::sampleCount() const {
	return _buffer.size();
}

int AudioRecording::startingIndex() const {
	return _startingIndex;
}

void AudioRecording::setStartingIndex(int index) {
	qDebug() << "stub";
}

int AudioRecording::endingIndex() const {
	return _endingIndex;
}

void AudioRecording::setEndingIndex(int index) {
	qDebug() << "stub";
}

std::vector<qreal> AudioRecording::buffer() const {
	std::vector<qreal> ret;
	const int inc = (JASS::SAMPLE_RATE/1000)*5;
	for (std::vector<float>::size_type i = 0; i < _buffer.size(); i += inc)
		ret.push_back(_buffer.at(i));
	return ret;
}

float AudioRecording::operator()() {
	// Loop or finish?
	if (_index == _buffer.size())
		reset();
	if (_buffer.size() > 0)
		return _buffer.at(_index++);
	else
		return 0;
}

void AudioRecording::reset() {
	_index = 0;
}

void AudioRecording::clear() {
	_index = 0;
	_buffer.clear();
	emit bufferChanged();
}

void AudioRecording::save(const QString &filename) const {
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly))
		std::runtime_error("Failed to open \"" +
		                   filename.toStdString() +
		                   "\" for writing.");
	QDataStream stream(&file);
	for (const auto &element : _buffer)
		stream << element;
	file.close();
}

void AudioRecording::operator<<(const std::vector<float> &newData) {
	for (const auto &element :newData)
		_buffer.push_back(element);
	if (newData.size() > 0)
		emit bufferChanged();
}
