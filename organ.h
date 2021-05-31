#ifndef ORGAN_H
#define ORGAN_H

#include <vector>
#include <stdexcept>
#include <memory>

#include <QtGlobal>
#include <QObject>
#include <QQmlEngine>
#include <QQmlListProperty>
#include <QFuture>
#include <QPromise>
#include <QMutex>
#include <QMutexLocker>
#include <QtConcurrent>

#ifndef Q_OS_ANDROID
#include <alsa/asoundlib.h>
#endif // Q_OS_LINUX
#ifdef Q_OS_ANDROID
#include <oboe/Oboe.h>
class Callback;
#endif // Q_OS_ANDROID

#include "jass.h"
#include "oscillator.h"
#include "sineoscillator.h"

class Organ : public QObject {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(QQmlListProperty<Oscillator> generators READ generators)
		Q_CLASSINFO("DefaultProperty", "generators")
		Q_PROPERTY(qsizetype generatorCount
		           READ generatorCount
		           NOTIFY generatorCountChanged)
	public:
		Organ(QObject *parent = nullptr);
		~Organ();

		QQmlListProperty<Oscillator> generators();
		void appendGenerator(Oscillator *gen);
		qsizetype generatorCount() const;
		Oscillator *generator(qsizetype index) const;
		void clearGenerators();
		void replaceGenerator(qsizetype index, Oscillator *gen);
		void removeLastGenerator();

		Q_INVOKABLE void start(int index);
		Q_INVOKABLE void stop(int index);

	signals:
		void generatorCountChanged();

	private:
		static void appendGenerator(QQmlListProperty<Oscillator> *list, Oscillator *gen);
		static qsizetype generatorCount(QQmlListProperty<Oscillator> *list);
		static Oscillator *generator(QQmlListProperty<Oscillator> *list, qsizetype index);
		static void clearGenerators(QQmlListProperty<Oscillator> *list);
		static void replaceGenerator(QQmlListProperty<Oscillator> *list, qsizetype index, Oscillator *gen);
		static void removeLastGenerator(QQmlListProperty<Oscillator> *list);

		void startAudio();
		void stopAudio();

		QMutex _mutex;
#ifndef Q_OS_ANDROID
		void audioLoop();
		void fillBuffer(std::vector<float> &vec);
		void writeBuffer(const std::vector<float> &vec);
		QFuture<void> _audioLoop;
		snd_pcm_t *_handle;
		snd_pcm_hw_params_t *_params;
		snd_pcm_uframes_t _frames = 256;
		int _dir;
		bool _finished = false;
		std::vector<float> _buffer;
#endif // Q_OS_ANDROID
#ifdef Q_OS_ANDROID
		oboe::AudioStreamBuilder _builder;
		std::shared_ptr<oboe::AudioStream> _stream;
		friend Callback;
		Callback *_callback = nullptr;
#endif // Q_OS_ANDROID
		std::vector<Oscillator *> _generators;
		std::vector<bool> _playing;
};
#ifdef Q_OS_ANDROID
class Callback : public oboe::AudioStreamDataCallback {
	public:
		Callback(Organ *organ) : _owner(organ) {}
		oboe::DataCallbackResult onAudioReady(oboe::AudioStream *stream, void *data, int32_t frames) {
			static float lastSample = 0;
			QMutexLocker locker(&_owner->_mutex);
			std::vector<float> vec(frames, 0);
			int scale = 0;
			for (int i = 0; i < _owner->_generators.size(); ++i) {
				if (_owner->_playing.at(i)) {
					scale++;
					vec += *_owner->_generators.at(i);
				}
			}
			if (scale > 1)
				for (auto &element : vec)
					element /= scale;
			if (scale >= 1) {
				lastSample = vec.back();
			}
			else {
				fade(vec, lastSample);
				lastSample = vec.back();
			}
			float *dataf = static_cast<float *>(data);
			for (int32_t i = 0; i < frames; ++i)
				dataf[i] = vec[i];
			return oboe::DataCallbackResult::Continue;
		}
	private:
		Organ *_owner;
};
#endif // Q_OS_ANDROID
#endif // ORGAN_H
