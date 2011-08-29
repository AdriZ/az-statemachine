#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QXmlDefaultHandler>
#include "smdescription.h"

#define XML_PARENT_TAG	"xazfsm"

class XmlHandler : public QXmlDefaultHandler
{
public:
	XmlHandler(SMDescription *stateMachineDesc);

	bool startDocument();
	bool startElement(const QString &namespaceURI, const QString &localName,
					  const QString &name, const QXmlAttributes &attrs);
	bool endElement(const QString &namespaceURI, const QString &localName,
					const QString &name);
	bool characters(const QString &str);

	QString errorString() const;

private:
	void clearState();
	void clearTransition();

	QString m_errorStr;
	t_state m_state;
	t_transition m_transition;

	SMDescription *m_stateMachine;

	bool m_insideXazfsm;
	bool m_insideTitle;
	bool m_insideState;
//	bool m_insideName;
	bool m_insideEntryfct;
	bool m_insideDuringfct;
	bool m_insideTransition;
//	bool m_insideFrom;
//	bool m_insideTo;
	bool m_insideCondition;
	bool m_insideAction;
};

#endif // XMLHANDLER_H
