#ifndef PATCHBOARD_H
#define PATCHBOARD_H

#include "effect.h"

class Patchboard : public Source {
		Q_OBJECT
		QML_ELEMENT
		Q_PROPERTY(QQmlListProperty<Source> sources READ sources)
		Q_CLASSINFO("DefaultProperty", "sources")
		Q_PROPERTY(Source *output
		           READ output
		           WRITE setOutput
		           NOTIFY outputChanged
		           REQUIRED)

	public:
		explicit Patchboard(QObject *parent = nullptr);

		QQmlListProperty<Source> sources();
		void appendSource(Source *source);
		qsizetype sourceCount() const;
		Source *source(qsizetype index) const;
		void clearSources();
		void replaceSource(qsizetype index, Source *source);
		void removeLastSource();

		Source *output() const;
		void setOutput(Source *output);

		float newSample() override;
		void reset() override;

	signals:
		void outputChanged();

	private:
		std::vector<Source *> _sources;
		static void appendSource(QQmlListProperty<Source> *list, Source *source);
		static qsizetype sourceCount(QQmlListProperty<Source> *list);
		static Source *source(QQmlListProperty<Source> *list, qsizetype index);
		static void clearSources(QQmlListProperty<Source> *list);
		static void replaceSource(QQmlListProperty<Source> *list, qsizetype index, Source *source);
		static void removeLastSource(QQmlListProperty<Source> *list);

		Source *_output = nullptr;

};

#endif // PATCHBOARD_H
