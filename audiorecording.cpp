#include <QFile>
#include <QDataStream>
#include <stdexcept>
#include "audiorecording.h"

AudioRecording::AudioRecording(QObject *parent) :
    Source(parent) {}

int AudioRecording::sampleCount() const {
	return _buffer.size();
}

std::size_t AudioRecording::startingIndex() const {
	return _startingIndex;
}

void AudioRecording::setStartingIndex(std::size_t index) {
	if (index == _startingIndex)
		return;
	else if (index > _endingIndex)
		throw std::runtime_error("Attempt to set start index past end index in AudioRecording");
	else if (index > _buffer.size())
		throw std::runtime_error("Attempt to set start past end of buffer in AudioRecording.");
	_startingIndex = index;
	emit startingIndexChanged();
	if (_index < _startingIndex) {
		_index = _startingIndex;
		emit progressChanged();
	}
}

std::size_t AudioRecording::endingIndex() const {
	return _endingIndex;
}

void AudioRecording::setEndingIndex(std::size_t index) {
	if (index == _endingIndex)
		return;
	else if (index < _startingIndex)
		throw std::runtime_error("Attempt to set end index before start index in AudioRecording.");
	else if (index > _buffer.size())
		throw std::runtime_error("Attempt to set end index past end of buffer in AudioRecording.");
	_endingIndex = index;
	emit endingIndexChanged();
	if (_index > _endingIndex) {
		_index = _endingIndex;
		emit progressChanged();
	}
}

double AudioRecording::progress() {
	return static_cast<double>(_index)/static_cast<double>(_buffer.size());
}

void AudioRecording::setProgress(double progress) {
	if (progress > 1)
		throw std::runtime_error("Attempt to set recording progress to %" +
	                             std::to_string(progress));
	_index = progress*_buffer.size();
	emit progressChanged();
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
	emit progressChanged();
	if (_index == _endingIndex)
		reset();
	if (_buffer.size() > 0)
		return _buffer.at(_index++);
	else
		return 0;
}

void AudioRecording::reset() {
	_index = _startingIndex;
	emit progressChanged();
}

void AudioRecording::clear() {
	_index = 0;
	_buffer.clear();
	emit bufferChanged();
	_startingIndex = 0;
	_endingIndex = 0;
	reset();
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
	if (newData.size() > 0) {
		emit bufferChanged();
		_endingIndex = _buffer.size();
		emit endingIndexChanged();
	}
}
