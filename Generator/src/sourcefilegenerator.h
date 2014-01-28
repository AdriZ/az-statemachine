#ifndef SOURCEFILEGENERATOR_H
#define SOURCEFILEGENERATOR_H

#include <QTextStream>
#include "smdescription.h"

#define STATE_NAME				"ST_"+name

#define BOOLEAN_RETURN_TYPE			"bool_t"
#define STATE_ENUM_TYPE				"state_"<<m_fsmDesc.formatedTitle<<"_t"
#define STATE_LIST_TYPE				"fsm_state_list_t"
#define TRANSITION_MATRIX_TYPE		"fsm_transition_matrix_t"
#define DESCRIPTION_TYPE			"fsm_description_t"

#define STATE_LIST_VAR_NAME			"s_"<<m_fsmDesc.formatedTitle<<"_state_list"
#define TRANSITION_MATRIX_VAR_NAME	"s_"<<m_fsmDesc.formatedTitle<<"_transition_matrix"
#define DESCRIPTION_VAR_NAME		"g_"<<m_fsmDesc.formatedTitle
#define NB_OF_STATES_NAME			m_fsmDesc.formatedTitle.toUpper()<<"_NB_OF_STATES"

// Examples to adapt to users coding conventions
//#define STATE_LIST_VAR_NAME			m_fsmDesc.formatedTitle<<"_state_list"
//#define TRANSITION_MATRIX_VAR_NAME	m_fsmDesc.formatedTitle<<"_transition_matrix"
//#define DESCRIPTION_VAR_NAME		to1stUpper(m_fsmDesc.formatedTitle)
//#define DESCRIPTION_VAR_NAME		to1stUpper(m_fsmDesc.formatedTitle)<<"_description"

#define TRANSITION_MATRIX_END	"END_FSM_TRANSITION_MATRIX"


class SourceFileGenerator
{
public:
	SourceFileGenerator( QIODevice *device, SMDescription fsmDesc );

	void generateC();
	void generateH();

private:
	QString formatStateName( QString name );
	QString to1stUpper( QString str );
	void addBanner( QString text );

	// To generate Header File
	void beginHFile();
	void addStateEnum();
	void addGlobalVarDefinitions();
	void endHFile();

	// To generate C Source File
	void beginCFile();
	void addAllStateFctPrototypes();
	void addAllTransitionFctPrototypes();
	void addVoidFctPrototype(QString name);
	void addConditionFctPrototype(QString name);
	void addStateList();
	void addTransitionMatrix();
	void addFsmDescription();
	void addAllStateFunctions();
	void addAllTransitionFunctions();
	bool addEntryFunction( t_state state );
	bool addDuringFunction( t_state state );
	bool addConditionFunction( t_transition transition );
	bool addActionFunction( t_transition transition );
	void addVoidFunction(QString name);
	void addBooleanFunction(QString name);
	void endCFile();

	/* Currently not used but can be used */
	void addAllEntryFctPrototypes();
	void addAllDuringFctPrototypes();
	void addAllConditionFctPrototypes();
	void addAllActionFctPrototypes();
	void addAllEntryFunctions();
	void addAllDuringFunctions();
	void addAllConditionFunctions();
	void addAllActionFunctions();


	QTextStream		m_out;
	SMDescription	m_fsmDesc;
};

#endif // SOURCEFILEGENERATOR_H
