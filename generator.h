#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <iostream>

#include <QObject>
#include <QQmlEngine>

class Generator : public QObject {
		Q_OBJECT
		QML_ELEMENT
		QML_UNCREATABLE("This is a base class.")
		Q_PROPERTY(float frequency
		           READ frequency
		           WRITE setFrequency
		           NOTIFY frequencyChanged)
		Q_PROPERTY(float amplitude
		          READ amplitude
		          WRITE setAmplitude
		          NOTIFY amplitudeChanged)
	public:
		Generator(QObject *parent = nullptr);
//		Generator(float frequency = 440,
//		          float amplitude = 1,
//		          QObject *parent = nullptr);

		float frequency() const;
		void setFrequency(float frequency);
		float amplitude() const;
		void setAmplitude(float amplitude);

		virtual float operator()() = 0;
		Generator &operator>>(std::vector<float> &vec);
		Generator &operator+=(std::vector<float> &vec);

		template<int size>
		Generator &operator+=(float (&arr)[size]) {
			for (int i = 0; i < size; ++i)
				arr[i] += this->operator()();
			return *this;
		}
		template<int size>
		Generator &operator>>(float (&arr)[size]) {
			for (int i = 0; i < size; ++i)
				arr[i] = this->operator()();
			return *this;
		}

	signals:
		void frequencyChanged();
		void amplitudeChanged();

	protected:
		static const float TAU;
		float _frequency = 440;
		float _amplitude = 1;
		uint _index = 0;
#ifndef Q_OS_ANDROID
		uint _sampleRate = 44100;
#endif // Q_OS_ANDROID
#ifdef Q_OS_ANDROID
		uint _sampleRate = 48000;
#endif // Q_OS_ANDROID
};

inline void operator+=(std::vector<float> &vec, Generator &gen) {
	for (auto &element : vec)
		element += gen();
}

inline std::ostream &operator<<(std::ostream &os, const std::vector<float> &vec) {
	for (std::vector<float>::size_type i = 0; i < vec.size(); ++i)
		os << i << ", " << vec.at(i) << '\n';
	return os;
}
#endif // GENERATOR_H
