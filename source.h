#ifndef SOURCE_H
#define SOURCE_H

#include <vector>
#include <iostream>

#include <QObject>
#include <QQmlEngine>

class Source : public QObject {
		Q_OBJECT
		QML_ELEMENT
		QML_UNCREATABLE("This is a abstract base class.")
		Q_PROPERTY(Type type READ type)
	public:
		enum Type {
			BaseClass,
			Constant,
			Mixer,
			Decay,
			ADSR,
			VCA,
			SineOscillator,
			SineVCO,
			TriangleOscillator,
			TriangleVCO,
			SquareOscillator,
			SquareVCO,
			WhiteNoise
		}; Q_ENUM(Type);
		explicit Source(QObject *parent = nullptr);

		Type type() const;

		virtual float operator()() = 0;
		virtual void reset() = 0;

		Source &operator>>(std::vector<float> &vec);
		Source &operator+=(std::vector<float> &vec);

		template<int size>
		Source &operator+=(float (&arr)[size]) {
			for (int i = 0; i < size; ++i)
				arr[i] += this->operator()();
			return *this;
		}
		template<int size>
		Source &operator>>(float (&arr)[size]) {
			for (int i = 0; i < size; ++i)
				arr[i] = this->operator()();
			return *this;
		}

	protected:
		Type _type;
};

#endif // SOURCE_H
