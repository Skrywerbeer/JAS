#ifndef EFFECT_H
#define EFFECT_H

#include "source.h"

class Effect : public Source {
		Q_OBJECT
		Q_PROPERTY(Source *input
		           READ input
		           WRITE setInput
		           NOTIFY inputChanged
		           REQUIRED)
		Q_CLASSINFO("DefaultProperty", "input")
	public:
		explicit Effect(QObject *parent = nullptr);

		Source *input() const;
		void setInput(Source *input);

		void reset() override;
		bool isDependency(const Source *source) const override;
	signals:
		void inputChanged();

	protected:
		Source *_input = nullptr;
		bool _feedbackInput = false;
};

#endif // EFFECT_H
