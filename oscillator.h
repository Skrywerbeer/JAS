#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "source.h"

class Oscillator : public Source {
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
		Oscillator(QObject *parent = nullptr);

		float frequency() const;
		void setFrequency(float frequency);
		float amplitude() const;
		void setAmplitude(float amplitude);

	signals:
		void frequencyChanged();
		void amplitudeChanged();

	protected:

		float _frequency = 440;
		float _amplitude = 1;
		uint _index = 0;
};

inline void operator+=(std::vector<float> &vec, Oscillator &gen) {
	for (auto &element : vec)
		element += gen();
}

inline std::ostream &operator<<(std::ostream &os, const std::vector<float> &vec) {
	for (std::vector<float>::size_type i = 0; i < vec.size(); ++i)
		os << i << ", " << vec.at(i) << '\n';
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
#endif // OSCILLATOR_H
