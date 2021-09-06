#ifndef ADSR_H
#define ADSR_H

#include "jass.h"
#include "source.h"

class ADSR : public Source {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(int attack
		           READ attack
		           WRITE setAttack
		           NOTIFY attackChanged)
		Q_PROPERTY(int decay
		           READ decay
		           WRITE setDecay
		           NOTIFY decayChanged)
		Q_PROPERTY(int sustain
		           READ sustain
		           WRITE setSustain
		           NOTIFY sustainChanged)
		Q_PROPERTY(double sustainLevel
		           READ sustainLevel
		           WRITE setSustainLevel
		           NOTIFY sustainChangedLevel)
		Q_PROPERTY(int release
		           READ release
		           WRITE setRelease
		           NOTIFY releaseChanged)
	public:
		enum State {
			Attacking,
			Decaying,
			Sustaining,
			Releasing,
			Finished
		};
		explicit ADSR(QObject *parent = nullptr);

		int attack() const;
		void setAttack(int ms);
		int decay() const;
		void setDecay(int ms);
		int sustain() const;
		void setSustain(int ms);
		double sustainLevel() const;
		void setSustainLevel(double value);
		int release() const;
		void setRelease(int ms);

		State currentState() const;

		float newSample() override;
		void reset() override;

	signals:
		void attackChanged();
		void decayChanged();
		void sustainChanged();
		void sustainChangedLevel();
		void releaseChanged();

	private:
		int _attack = 100;
		int _decay = 100;
		int _sustain = 100;
		double _sustainLevel = 0.5;
		int _release = 100;
		int _index = 0;
};

#endif // ADSR_H
