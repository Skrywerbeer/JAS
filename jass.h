#ifndef JASS_H
#define JASS_H

#include <QtGlobal>
#include <vector>
#include <iostream>

#include "source.h"

class JASS : public QObject {
		Q_OBJECT
		QML_ELEMENT
		QML_SINGLETON
	public:
		JASS(QObject *parent = nullptr) : QObject(parent) {}

		Q_INVOKABLE int samplesToMs(int sampleCount) {
			const int MS_PER_SEC = 1000;
			return MS_PER_SEC*SAMPLE_PERIOD*sampleCount;
		}
		Q_INVOKABLE int samplesPerMs() const {
			const int MS_PER_SEC = 1000;
			return SAMPLE_RATE/MS_PER_SEC;
		}
		Q_INVOKABLE static double rms(const std::vector<float> &vec,
		                              const std::vector<float>::size_type start,
		                              const std::vector<float>::size_type count) {
			double sum = 0;
			for (std::vector<float>::size_type i = 0; i < count; ++i)
				sum += vec.at(start + i)*vec.at(start + i);
			sum /= count;
			return std::sqrt(sum);
		}

		static constexpr float TAU{6.283185};
#ifndef Q_OS_ANDROID
		static constexpr uint SAMPLE_RATE{44100};
#endif // Q_OS_ANDROID
#ifdef Q_OS_ANDROID
		static constexpr uint SAMPLE_RATE{48000};
#endif // Q_OS_ANDROID
		static constexpr double SAMPLE_PERIOD{1/static_cast<const double>(SAMPLE_RATE)};
		static constexpr double SAMPLES_PER_MS{static_cast<const double>(SAMPLE_RATE)/1.0e-3};
		static constexpr double SAMPLES_PER_US{static_cast<const double>(SAMPLE_RATE/1.0e-6)};
};

class DelayBuffer {
	public:
		DelayBuffer(std::size_t size) : _samples(size) {}
		void resize(std::size_t size) {
			// TODO: handle the samples when resizing.
			_index = 0;
			_samples.resize(size);
		}
		[[nodiscard]] float operator<<(float newValue) {
			if (_index == _samples.size())
				_index = 0;
			const float ret = _samples.at(_index);
			_samples[_index] = newValue;
			_index++;
			return ret;
		}
		void zero() {
			for (auto &sample : _samples)
				sample = 0;
			_index = 0;
		}
	private:
		std::vector<float> _samples;
		std::size_t _index = 0;
};

inline void operator+=(std::vector<float> &vec, Source &gen) {
	for (auto &element : vec)
		element += gen();
}

inline std::ostream &operator<<(std::ostream &os, const std::vector<float> &vec) {
	for (std::vector<float>::size_type i = 0; i < vec.size(); ++i)
		os << vec.at(i) << '\n';
	return os;
}

inline void fade(std::vector<float> &vec, float start, float decay = 0.999) {
	const float THRESHOLD = 0.001;
	if ((start < 0) && (start > -THRESHOLD))
		return;
	else if ((start > 0) && (start < THRESHOLD))
		return;
	vec[0] = start;
	for (std::vector<float>::size_type i = 1; i < vec.size(); ++i)
		vec[i] = vec[i - 1]*decay;
}

#endif // JASS_H
