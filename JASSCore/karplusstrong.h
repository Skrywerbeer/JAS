#ifndef KARPLUSSTRONG_H
#define KARPLUSSTRONG_H

#include <random>

#include "jass.h"
#include "oscillator.h"

class KarplusStrongOscillator : public Oscillator {
		Q_OBJECT
		QML_ELEMENT
	public:
		KarplusStrongOscillator(QObject *parent = nullptr);

		float newSample() override;
		void reset() override;

	private:
		std::mt19937 _twister;
		std::vector<qreal> _buffer;
		std::size_t _index = 0;
		bool _plucked = false;
};


#endif // KARPLUSSTRONG_H
