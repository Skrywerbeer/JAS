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
		static constexprt uint SAMPLE_RATE{48000};
#endif // Q_OS_ANDROID
		static constexpr double SAMPLE_PERIOD{1/static_cast<const double>(SAMPLE_RATE)};
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
