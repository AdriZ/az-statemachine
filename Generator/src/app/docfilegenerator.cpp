#include "docfilegenerator.h"

DocFileGenerator::DocFileGenerator(QIODevice *device)
{
	m_out.setDevice(device);
	m_out.setCodec("UTF-8");
}

void DocFileGenerator::generate(SMDescription fsmDesc)
{
	addAllEntryFunctions( fsmDesc.stateList );
	addAllDuringFunctions( fsmDesc.stateList );
	addAllConditionFunctions( fsmDesc.transitionList );
	addAllActionFunctions( fsmDesc.transitionList );
}

void DocFileGenerator::addAllEntryFunctions(t_state_list stateList)
{
	m_out	<< "// Entry functions :"<<endl
			<< endl;

	for( int _i=0; _i < stateList.size(); _i++)
	{
		if( ! stateList.at(_i).entryFct.isEmpty() )
		{
			addVoidFunction( stateList.at(_i).entryFct );
		}
	}
}

void DocFileGenerator::addAllDuringFunctions(t_state_list stateList)
{
	m_out	<< "// During functions :"<<endl
			<< endl;

	for( int _i=0; _i < stateList.size(); _i++)
	{
		if( ! stateList.at(_i).duringFct.isEmpty() )
		{
			addVoidFunction( stateList.at(_i).duringFct );
		}
	}
}

void DocFileGenerator::addAllConditionFunctions(t_transition_list transitionList)
{
	m_out	<< "// Condition functions :"<<endl
			<< endl;

	for( int _i=0; _i < transitionList.size(); _i++)
	{
		if( ! transitionList.at(_i).condition.isEmpty() )
		{
			addConditionFunction( transitionList.at(_i).condition );
		}
	}
}

void DocFileGenerator::addAllActionFunctions(t_transition_list transitionList)
{
	m_out	<< "// Action functions :"<<endl
			<< endl;

	for( int _i=0; _i < transitionList.size(); _i++)
	{
		if( ! transitionList.at(_i).action.isEmpty() )
		{
			addVoidFunction( transitionList.at(_i).action );
		}
	}
}

void DocFileGenerator::addVoidFunction(QString name)
{
	m_out	<< name<<"()"<<endl
			<< "{"<<endl
			<< "}"<<endl
			<<endl;
}

void DocFileGenerator::addConditionFunction(QString name)
{
	m_out	<< name<<"()"<<endl
			<< "{"<<endl
			<< "    "<<"return( TRUE );"<<endl
			<< "}"<<endl
			<<endl;
}

