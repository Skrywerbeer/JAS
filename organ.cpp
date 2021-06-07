#include "organ.h"

#ifndef Q_OS_ANDROID
Organ::Organ(QObject *parent) :
    QObject(parent) {
	startAudio();
	_audioLoop = QtConcurrent::run(&Organ::audioLoop, this);
}
#endif // Q_OS_ANDROID
#ifdef Q_OS_ANDROID
Organ::Organ(QObject *parent) :
    QObject(parent), _callback(new Callback(this)) {
	startAudio();
}
#endif // Q_OS_ANDROID

Organ::~Organ() {
#ifndef Q_OS_ANDROID
	_mutex.lock();
	_finished = true;
	_mutex.unlock();
	_audioLoop.waitForFinished();
#endif // Q_OS_ANDROID
#ifdef Q_OS_ANDROID
#endif // Q_OS_ANDROID
	stopAudio();
}

QQmlListProperty<Source> Organ::sources() {
	return QQmlListProperty<Source>(this, this,
	                                   &appendSource,
	                                   &sourceCount,
	                                   &source,
	                                   &clearSources,
	                                   &replaceSource,
	                                   &removeLastSource);
}

void Organ::appendSource(Source *gen) {
	QMutexLocker locker(&_mutex);
	_sources.push_back(gen);
	_active.push_back(false);
	emit sourceCountChanged();
}

qsizetype Organ::sourceCount() const {
	return static_cast<qsizetype>(_sources.size());
}

Source *Organ::source(qsizetype index) const {
	return _sources.at(index);
}

void Organ::clearSources() {
	QMutexLocker locker(&_mutex);
	_sources.clear();
	_active.clear();
	emit sourceCountChanged();
}

void Organ::replaceSource(qsizetype index, Source *src) {
	QMutexLocker locker(&_mutex);
	_sources[index] = src;
	_active[index] = false;
}

void Organ::removeLastSource() {
	QMutexLocker locker(&_mutex);
	_sources.pop_back();
	_active.pop_back();
	emit sourceCountChanged();
}

bool Organ::sourceActive() const {
	bool ret = false;
	for (const auto &active : _active)
		if (active)
			ret = true;
	return ret;
}

AudioRecording *Organ::lastRecording() const {
	return _lastRecording;
}

bool Organ::recording() const {
	return _recording;
}

void Organ::setRecording(bool record) {
	if (record == _recording)
		return;
	if (record)
		_lastRecording->clear();
	_recording = record;
	emit recordingChanged();
}

bool Organ::playbackLast() const {
	return _playbackLast;
}

void Organ::setPlaybackLast(bool play) {
	if (play == _playbackLast)
		return;
	_playbackLast = play;
	emit playbackLastChanged();
}

void Organ::start(int index) {
	QMutexLocker locker(&_mutex);
	_active.at(index) = true;
	emit sourceActiveChanged();
}

void Organ::stop(int index) {
	QMutexLocker locker(&_mutex);
	_active.at(index) = false;
	_sources.at(index)->reset();
	emit sourceActiveChanged();
}

void Organ::restart(int index) {
	_sources.at(index)->reset();
}

void Organ::appendSource(QQmlListProperty<Source> *list, Source *src) {
	reinterpret_cast<Organ *>(list->data)->appendSource(src);
}

qsizetype Organ::sourceCount(QQmlListProperty<Source> *list) {
	return reinterpret_cast<Organ *>(list->data)->sourceCount();
}

Source *Organ::source(QQmlListProperty<Source> *list, qsizetype index) {
	return reinterpret_cast<Organ *>(list->data)->source(index);
}

void Organ::clearSources(QQmlListProperty<Source> *list) {
	reinterpret_cast<Organ *>(list->data)->clearSources();
}

void Organ::replaceSource(QQmlListProperty<Source> *list, qsizetype index, Source *gen) {
	reinterpret_cast<Organ *>(list->data)->replaceSource(index, gen);
}

void Organ::removeLastSource(QQmlListProperty<Source> *list) {
	reinterpret_cast<Organ *>(list->data)->removeLastSource();
}

void Organ::startAudio() {
#ifndef Q_OS_ANDROID
	if (snd_pcm_open(&_handle,
	                 "default",
	                 SND_PCM_STREAM_PLAYBACK,
	                 0) < 0)
		throw std::runtime_error("Failed to open PCM stream for playback.");
	snd_pcm_hw_params_alloca(&_params);
	if (snd_pcm_hw_params_any(_handle, _params) < 0)
		throw std::runtime_error("Failed to retrieve hardware parameters.");
	if (snd_pcm_hw_params_set_access(_handle, _params, SND_PCM_ACCESS_RW_INTERLEAVED) < 0)
		throw std::runtime_error("Failed to set PCM access.");
	if (snd_pcm_hw_params_set_format(_handle, _params, SND_PCM_FORMAT_FLOAT) < 0)
		throw std::runtime_error("Failed to set PCM format.");
	if (snd_pcm_hw_params_set_channels(_handle, _params, 1) < 0)
		throw std::runtime_error("Failed to set PCM channel count.");
	uint sampleRate = JASS::SAMPLE_RATE;
	if (snd_pcm_hw_params_set_rate_near(_handle, _params, &sampleRate, &_dir) < 0)
		throw std::runtime_error("Failed to set sample rate.");
	if (sampleRate != JASS::SAMPLE_RATE) {
		std::cout << "warning: set sample rate differs from chosen rate. "
		          << "set: " << JASS::SAMPLE_RATE << " got: " << sampleRate << '\n';
	}
	if (snd_pcm_hw_params_set_period_size_near(_handle, _params, &_frames, &_dir) < 0)
		throw std::runtime_error("Failed to set frame count.");
	if (snd_pcm_hw_params(_handle, _params) < 0)
		throw std::runtime_error("Failed to write parameters.");
	if (snd_pcm_hw_params_get_period_size(_params, &_frames, &_dir) < 0)
		throw std::runtime_error("Failed to retrieve period size.");
	_buffer.resize(_frames);
#endif // Q_OS_ANDROID
#ifdef Q_OS_ANDROID
	_builder.setDirection(oboe::Direction::Output);
	_builder.setSharingMode(oboe::SharingMode::Shared);
	_builder.setFormat(oboe::AudioFormat::Float);
	_builder.setSampleRate(jass::SAMPLE_RATE);
	_builder.setDeviceId(0);
	_builder.setChannelCount(oboe::ChannelCount::Mono);
	_builder.setDataCallback(_callback);
//	_builder.setDataCallback(&call);
	if (_builder.openStream(_stream) != oboe::Result::OK)
		throw std::runtime_error("Failed to open audio stream.");
	_stream->requestStart();
#endif // Q_OS_ANDROID
}

void Organ::stopAudio() {
#ifndef Q_OS_ANDROID
	snd_pcm_close(_handle);
#endif // Q_OS_ANDROID
#ifdef Q_OS_ANDROID
	_stream->close();
#endif // Q_OS_ANDROID
}

#ifndef Q_OS_ANDROID
void Organ::audioLoop() {
	while (1) {
		if (_finished)
			break;
		fillBuffer(_buffer);
		writeBuffer(_buffer);
	}
}

void Organ::fillBuffer(std::vector<float> &vec) {
	std::vector<float> buffer(vec.size(), 0);
	static float lastSample = 0;
	int scale = 0;
	for (std::vector<bool>::size_type i = 0; i < _sources.size(); ++i) {
		if (_active.at(i)) {
			scale++;
			buffer += *_sources.at(i);
		}
	}
	/////////////////////////
	if (_playbackLast) {
		buffer += *_lastRecording;
		scale++;
	}
	/////////////////////////
	if (scale > 1)
		for (auto &element : buffer)
			element /= scale;
	if (scale != 0) {
		lastSample = buffer.back();
	}
	else {
		fade(buffer, lastSample, 0.8);
		lastSample = buffer.back();
	}
	vec = buffer;
}

void Organ::writeBuffer(const std::vector<float> &vec) {
	/////////////////////////
	if (_recording)
		*_lastRecording << vec;
	/////////////////////////
	int code = snd_pcm_writei(_handle, vec.data(), _frames);
	if (code == EPIPE)
		throw std::runtime_error("Underrun occured");
	else if (code < 0)
		throw std::runtime_error("Error during write.");
}
#endif // Q_OS_ANDROID
