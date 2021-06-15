#ifndef SPLITTER_H
#define SPLITTER_H

#include "effect.h"

class Splitter : public Effect {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(int outputCount
		           READ outputCount
		           WRITE setOutputCount
		           NOTIFY outputCountChanged)
	public:
		explicit Splitter(QObject *parent = nullptr);

		int outputCount() const;
		void setOutputCount(int count);

		float operator()() override;
		void reset() override;

	signals:
		void outputCountChanged();

	private:
		float _latestValue = 0;
		int _outputCount = 1;
		int _outputIndex = 0;
};

#endif // SPLITTER_H
