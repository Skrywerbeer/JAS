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
#include "source.h"
#include "audiorecording.h"

class Organ : public QObject {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(QQmlListProperty<Source> sources READ sources)
		Q_CLASSINFO("DefaultProperty", "sources")
		Q_PROPERTY(qsizetype sourceCount
		           READ sourceCount
		           NOTIFY sourceCountChanged)
		Q_PROPERTY(bool sourceActive
		           READ sourceActive
		           NOTIFY sourceActiveChanged)
		Q_PROPERTY(AudioRecording *lastRecording
		           READ lastRecording
		           NOTIFY lastRecordingChanged)
		Q_PROPERTY(bool recording
		           READ recording
		           WRITE setRecording
		           NOTIFY recordingChanged)
		Q_PROPERTY(bool playbackLast
		           READ playbackLast
		           WRITE setPlaybackLast
		           NOTIFY playbackLastChanged)
	public:
		Organ(QObject *parent = nullptr);
		~Organ();

		QQmlListProperty<Source> sources();
		void appendSource(Source *src);
		qsizetype sourceCount() const;
		Source *source(qsizetype index) const;
		void clearSources();
		void replaceSource(qsizetype index, Source *src);
		void removeLastSource();

		bool sourceActive() const;

		AudioRecording *lastRecording() const;
		bool recording() const;
		void setRecording(bool record);
		bool playbackLast() const;
		void setPlaybackLast(bool play);

		Q_INVOKABLE void start(int index);
		Q_INVOKABLE void stop(int index);
		Q_INVOKABLE void restart(int index);

	signals:
		void sourceCountChanged();
		void sourceActiveChanged();
		void lastRecordingChanged();
		void recordingChanged();
		void playbackLastChanged();

	private:
		static void appendSource(QQmlListProperty<Source> *list, Source *src);
		static qsizetype sourceCount(QQmlListProperty<Source> *list);
		static Source *source(QQmlListProperty<Source> *list, qsizetype index);
		static void clearSources(QQmlListProperty<Source> *list);
		static void replaceSource(QQmlListProperty<Source> *list, qsizetype index, Source *src);
		static void removeLastSource(QQmlListProperty<Source> *list);

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
		std::vector<Source *> _sources;
		std::vector<bool> _active;
		bool _recording = false;
		bool _playbackLast = false;
		AudioRecording *_lastRecording = new AudioRecording(this);
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
			for (int i = 0; i < _owner->_sources.size(); ++i) {
				if (_owner->_active.at(i)) {
					scale++;
					vec += *_owner->_sources.at(i);
				}
			}
			if (_owner->_playbackLast) {
				vec += *_owner->_lastRecording;
				scale++;
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
			if (_owner->_recording)
				*_owner->_lastRecording << vec;
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
