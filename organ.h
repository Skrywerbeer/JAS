#ifndef ORGAN_H
#define ORGAN_H

#include <vector>
#include <stdexcept>

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
#endif // Q_OS_ANDROID

class Generator;

class Organ : public QObject {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(QQmlListProperty<Generator> generators READ generators)
		Q_CLASSINFO("DefaultProperty", "generators")
	public:
		Organ(QObject *parent = nullptr);
		~Organ();

		QQmlListProperty<Generator> generators();
		void appendGenerator(Generator *gen);
		qsizetype generatorCount() const;
		Generator *generator(qsizetype index) const;
		void clearGenerators();
		void replaceGenerator(qsizetype index, Generator *gen);
		void removeLastGenerator();

		Q_INVOKABLE void start(int index);
		Q_INVOKABLE void stop(int index);

	private:
		static void appendGenerator(QQmlListProperty<Generator> *list, Generator *gen);
		static qsizetype generatorCount(QQmlListProperty<Generator> *list);
		static Generator *generator(QQmlListProperty<Generator> *list, qsizetype index);
		static void clearGenerators(QQmlListProperty<Generator> *list);
		static void replaceGenerator(QQmlListProperty<Generator> *list, qsizetype index, Generator *gen);
		static void removeLastGenerator(QQmlListProperty<Generator> *list);

		void startAudio();
		void stopAudio();
		void audioLoop();
		void fillBuffer(std::vector<float> &vec);
		void writeBuffer(const std::vector<float> &vec);
		bool _finished = false;

		QFuture<void> _audioLoop;
		QMutex _mutex;
#ifndef Q_OS_ANDROID
		snd_pcm_t *_handle;
		snd_pcm_hw_params_t *_params;
		snd_pcm_uframes_t _frames = 256;
		int _dir;
		uint _sampleRate = 44100;
#endif // Q_OS_ANDROID

		std::vector<Generator *> _generators;
		std::vector<bool> _playing;
		std::vector<float> _buffer;
};

#endif // ORGAN_H
