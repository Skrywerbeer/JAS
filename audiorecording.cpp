#include <QFile>
#include <QDataStream>
#include <stdexcept>
#include "audiorecording.h"

AudioRecording::AudioRecording(QObject *parent) :
    Source(parent) {}

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
}
