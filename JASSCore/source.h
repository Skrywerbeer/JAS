#ifndef SOURCE_H
#define SOURCE_H

#include <vector>
#include <iostream>
#include <stdexcept>

#include <QObject>
#include <QQmlEngine>

class Source : public QObject {
		Q_OBJECT
		QML_ELEMENT
		QML_UNCREATABLE("This is a abstract base class.")
		Q_PROPERTY(Type type READ type)
		// NOTE: Other QObject types could be handy as children.
		Q_PROPERTY(QObject *stateGroup
		           READ stateGroup
		           WRITE setStateGroup
		           NOTIFY stateGroupChanged)
	public:
		enum Type {
			BaseClass,
//			Constant,
			PatchBoard,
			Mixer,
			Decay,
			Delay,
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

		QObject *stateGroup() const;
		void setStateGroup(QObject *group);

		float operator()();
		virtual float newSample() = 0;
		virtual void reset() = 0;

		void incRefCount();
		void decRefCount();

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
		int _refCount = 0;
		int _refIndex = 0;
		float _latestSample = 0;

	private:
		QObject *_stateGroup;
	signals:
		void stateGroupChanged();
};

#endif // SOURCE_H
