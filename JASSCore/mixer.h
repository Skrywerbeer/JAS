#ifndef MIXER_H
#define MIXER_H

#include <QQmlListProperty>
#include <vector>

#include "jass.h"
#include "source.h"

struct MixerInput {
		MixerInput(Source *source, bool feedback) :
		source(source), feedbackInput(feedback) {

		}
		Source *source = nullptr;
		bool feedbackInput = false;
};

class Mixer : public Source {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(QQmlListProperty<Source> inputs READ inputs)
		Q_CLASSINFO("DefaultProperty", "inputs")

	public:
		explicit Mixer(QObject *parent = nullptr);

		QQmlListProperty<Source> inputs();
		void appendInput(Source *input);
		qsizetype inputCount() const;
		Source *input(qsizetype index) const;
		void clearInputs();
		void replaceInput(qsizetype index, Source *input);
		void removeLastInput();

		float newSample() override;
		void reset() override;
		bool isDependency(const Source *source) const override;

	signals:

	private:
//		QList<Source *> _inputs;
//		std::vector<Source *> _inputs;
		std::vector<MixerInput> _inputs;
		static void appendInput(QQmlListProperty<Source> *list, Source *input);
		static qsizetype inputCount(QQmlListProperty<Source> *list);
		static Source *input(QQmlListProperty<Source> *list, qsizetype index);
		static void clearInputs(QQmlListProperty<Source> *list);
		static void replaceInput(QQmlListProperty<Source> *list, qsizetype index, Source *input);
		static void removeLastInput(QQmlListProperty<Source> *list);
};

#endif // MIXER_H
