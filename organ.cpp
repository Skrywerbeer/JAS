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

QQmlListProperty<Oscillator> Organ::generators() {
	return QQmlListProperty<Oscillator>(this, this,
	                                   &appendGenerator,
	                                   &generatorCount,
	                                   &generator,
	                                   &clearGenerators,
	                                   &replaceGenerator,
	                                   &removeLastGenerator);
}

void Organ::appendGenerator(Oscillator *gen) {
	QMutexLocker locker(&_mutex);
	_generators.push_back(gen);
	_playing.push_back(false);
	emit generatorCountChanged();
}

qsizetype Organ::generatorCount() const {
	return static_cast<qsizetype>(_generators.size());
}

Oscillator *Organ::generator(qsizetype index) const {
	return _generators.at(index);
}

void Organ::clearGenerators() {
	QMutexLocker locker(&_mutex);
	_generators.clear();
	_playing.clear();
	emit generatorCountChanged();
}

void Organ::replaceGenerator(qsizetype index, Oscillator *gen) {
	QMutexLocker locker(&_mutex);
	_generators[index] = gen;
	_playing[index] = false;
}

void Organ::removeLastGenerator() {
	QMutexLocker locker(&_mutex);
	_generators.pop_back();
	_playing.pop_back();
	emit generatorCountChanged();
}

void Organ::start(int index) {
	QMutexLocker locker(&_mutex);
	_playing.at(index) = true;
}

void Organ::stop(int index) {
	QMutexLocker locker(&_mutex);
	_playing.at(index) = false;
	_generators.at(index)->reset();
}

void Organ::appendGenerator(QQmlListProperty<Oscillator> *list, Oscillator *gen) {
	reinterpret_cast<Organ *>(list->data)->appendGenerator(gen);
}

qsizetype Organ::generatorCount(QQmlListProperty<Oscillator> *list) {
	return reinterpret_cast<Organ *>(list->data)->generatorCount();
}

Oscillator *Organ::generator(QQmlListProperty<Oscillator> *list, qsizetype index) {
	return reinterpret_cast<Organ *>(list->data)->generator(index);
}

void Organ::clearGenerators(QQmlListProperty<Oscillator> *list) {
	reinterpret_cast<Organ *>(list->data)->clearGenerators();
}

void Organ::replaceGenerator(QQmlListProperty<Oscillator> *list, qsizetype index, Oscillator *gen) {
	reinterpret_cast<Organ *>(list->data)->replaceGenerator(index, gen);
}

void Organ::removeLastGenerator(QQmlListProperty<Oscillator> *list) {
	reinterpret_cast<Organ *>(list->data)->removeLastGenerator();
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
	uint sampleRate = jass::SAMPLE_RATE;
	if (snd_pcm_hw_params_set_rate_near(_handle, _params, &sampleRate, &_dir) < 0)
		throw std::runtime_error("Failed to set sample rate.");
	if (sampleRate != jass::SAMPLE_RATE)
		std::cout << "warning: set sample rate differs from chosen rate.\n";
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
	for (int i = 0; i < _generators.size(); ++i) {
		if (_playing.at(i)) {
			scale++;
			buffer += *_generators.at(i);
		}
	}
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
#ifndef Q_OS_ANDROID
	int code = snd_pcm_writei(_handle, vec.data(), _frames);
	if (code == EPIPE)
		throw std::runtime_error("Underrun occured");
	else if (code < 0)
		throw std::runtime_error("Error during write.");
#endif // Q_OS_ANDROID
}
#endif // Q_OS_ANDROID
