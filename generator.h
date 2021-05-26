#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <iostream>

#include <QObject>
#include <QQmlEngine>

class Generator : public QObject {
		Q_OBJECT
		QML_ELEMENT
	public:
		Generator(QObject *parent = nullptr) :
		    QObject(parent) {}
		virtual float operator()() = 0;
		Generator &operator>>(std::vector<float> &vec) {
			for (auto &element : vec)
				element = this->operator()();
			return *this;
		}
		Generator &operator+=(std::vector<float> &vec) {
			for (auto &element : vec) {
				element += this->operator()();
			}
			return *this;
		}
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
