#ifndef AMPLFIFIER_H
#define AMPLIFIER_H

#include "effect.h"
#include "constant.h"

class Amplifier : public Effect {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(Source *gain
		           READ gain
		           WRITE setGain
		           NOTIFY gainChanged)

	public:
		Amplifier(QObject *parent = nullptr);

		Source *gain() const;
		void setGain(Source *gain);

		float newSample() override;
		void reset() override;

	signals:
		void gainChanged();

	private:
		Source *_gain = new Constant (this, 1);
};


#endif // AMPLIFIER_H
