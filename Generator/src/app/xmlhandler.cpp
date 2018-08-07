#include <QtDebug>
#include "xmlhandler.h"


XmlHandler::XmlHandler(SMDescription *stateMachineDesc)
{
	m_stateMachine = stateMachineDesc;
}

bool XmlHandler::startDocument()
{
	m_insideXazfsm = false;
	m_insideTitle = false;
	m_insideState = false;
//	m_insideName = false;
	m_insideEntryfct = false;
	m_insideDuringfct = false;
	m_insideTransition = false;
//	m_insideFrom = false;
//	m_insideTo = false;
	m_insideCondition = false;
	m_insideAction = false;

	return true;
}

bool XmlHandler::startElement(const QString & /* namespaceURI */,
							  const QString & /* localName */,
							  const QString &name,
							  const QXmlAttributes &attrs)
{
	if (!m_insideXazfsm && name != XML_PARENT_TAG)
	{
		m_errorStr = QObject::tr("The file is not an XML AZ Finite State Machine file.\n(i.e. It doesn't start with the <%1> tag)")
								 .arg(XML_PARENT_TAG);
		return false;
	}

	if( name == XML_PARENT_TAG )
		m_insideXazfsm = true;
	else if(name == "title")
		m_insideTitle = true;
	else if(name == "state")
	{
		m_insideState = true;
		clearState();

		for( int i=0; i<attrs.count(); i++ )
		{
			if( attrs.localName( i ) == "name" )
			{
				m_state.name = attrs.value( i );
			}
			else if( attrs.localName( i ) == "init" )
			{
				if( attrs.value( i ) == "true" )
				{
					m_state.isInit = true;
				}
			}
			else if( attrs.localName( i ) == "error" )
			{
				if( attrs.value( i ) == "true" )
				{
					m_state.isError = true;
				}
			}
		}
	}
//	else if(name == "name")
//		m_insideName = true;
	else if(name == "entryfct")
		m_insideEntryfct = true;
	else if(name == "duringfct")
		m_insideDuringfct = true;
	else if(name == "transition")
	{
		m_insideTransition = true;
		clearTransition();

		for( int i=0; i<attrs.count(); i++ )
		{
			if( attrs.localName( i ) == "from" )
			{
				m_transition.fromState = attrs.value( i );
			}
			else if( attrs.localName( i ) == "to" )
			{
				m_transition.toState = attrs.value( i );
			}
		}
	}
//	else if(name == "from")
//		m_insideFrom = true;
//	else if(name == "to")
//		m_insideTo = true;
	else if(name == "condition")
		m_insideCondition = true;
	else if(name == "action")
		m_insideAction = true;

	return true;
}

bool XmlHandler::endElement(const QString & /* namespaceURI */,
							const QString & /* localName */,
							const QString &name)
{
	if( name == XML_PARENT_TAG )
		m_insideXazfsm = false;
	else if(name == "title")
		m_insideTitle = false;
	else if(name == "state")
	{
		m_insideState = false;
		m_stateMachine->addState(m_state);
		if( m_state.isInit )
			m_stateMachine->initState = m_state.name;
		if( m_state.isError )
			m_stateMachine->errorState = m_state.name;
	}
//	else if(name == "name")
//		m_insideName = false;
	else if(name == "entryfct")
		m_insideEntryfct = false;
	else if(name == "duringfct")
		m_insideDuringfct = false;
	else if(name == "transition")
	{
		m_insideTransition = false;
		m_stateMachine->addTransition(m_transition);
	}
//	else if(name == "from")
//		m_insideFrom = false;
//	else if(name == "to")
//		m_insideTo = false;
	else if(name == "condition")
		m_insideCondition = false;
	else if(name == "action")
		m_insideAction = false;

	return true;
}

bool XmlHandler::characters(const QString &str)
{
	if(m_insideTitle)
	{
		m_stateMachine->addTitle(str);
	}
	if(m_insideState)
	{
//		if(m_insideName)
//		{
//			m_state.name = str;
//		}
		if(m_insideEntryfct)
		{
			m_state.entryFct = str;
		}
		if(m_insideDuringfct)
		{
			m_state.duringFct = str;
		}
	}
	if(m_insideTransition)
	{
//		if(m_insideFrom)
//		{
//			//qDebug() << "from" << str <<endl;
//			m_transition.fromState = str;
//		}
//		if(m_insideTo)
//		{
//			//qDebug() << "to" << str <<endl;
//			m_transition.toState = str;
//		}
		if(m_insideCondition)
		{
			m_transition.condition = str;
		}
		if(m_insideAction)
		{
			m_transition.action = str;
		}
	}

	return true;
}

void XmlHandler::clearTransition()
{
	m_transition.fromState    = "";
	m_transition.toState      = "";
	m_transition.condition    = "";
	m_transition.action       = "";
}

void XmlHandler::clearState()
{
	m_state.name        = "";
	m_state.entryFct    = "";
	m_state.duringFct	= "";
	m_state.isError		= false;
	m_state.isInit		= false;
}

QString XmlHandler::errorString() const
{
	return m_errorStr;
}
