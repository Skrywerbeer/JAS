#ifndef VCA_H
#define VCA_H

#include "jass.h"
#include "source.h"

class VCA : public Source {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(Source *input
		           READ input
		           WRITE setInput
		           NOTIFY inputChanged
		           REQUIRED)
		Q_PROPERTY(Source *cv
		           READ cv
		           WRITE setCV
		           NOTIFY cvChanged
		           REQUIRED)
	public:
		explicit VCA(QObject *parent = nullptr);

		Source *input() const;
		void setInput(Source *input);
		Source *cv() const;
		void setCV(Source *cv);

		float newSample() override;
		void reset() override;

	signals:
		void inputChanged();
		void cvChanged();

	private:
		Source *_input = nullptr;
		Source *_cv = nullptr;
};

#endif // VCA_H
