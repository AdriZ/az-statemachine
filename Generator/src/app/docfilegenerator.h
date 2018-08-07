#ifndef DOCFILEGENERATOR_H
#define DOCFILEGENERATOR_H

#include <QTextStream>
#include "smdescription.h"

class DocFileGenerator
{
public:
	DocFileGenerator(QIODevice *device);

	void generate(SMDescription fsmDesc);

private:
	QTextStream m_out;

	void addAllEntryFunctions(t_state_list stateList);
	void addAllDuringFunctions(t_state_list stateList);
	void addAllConditionFunctions(t_transition_list transitionList);
	void addAllActionFunctions(t_transition_list transitionList);
	void addVoidFunction(QString name);
	void addConditionFunction(QString name);
};

#endif // DOCFILEGENERATOR_H
