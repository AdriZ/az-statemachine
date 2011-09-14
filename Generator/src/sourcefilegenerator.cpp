#include "sourcefilegenerator.h"

// Constructor
SourceFileGenerator::SourceFileGenerator( QIODevice *device, SMDescription fsmDesc )
{
	m_fsmDesc = fsmDesc;

	m_out.setDevice(device);
	m_out.setCodec("UTF-8");	
}

// Public functions

void SourceFileGenerator::generateC()
{
	beginCFile();
	addBanner("Static Function Prototypes");
	addAllStateFctPrototypes();
	addAllTransitionFctPrototypes();
//	addAllEntryFctPrototypes();
//	addAllDuringFctPrototypes();
//	addAllConditionFctPrototypes();
//	addAllActionFctPrototypes();
	addBanner("Static Variables");
	addStateList();
	addTransitionMatrix();
	addBanner("Global Variables");
	addFsmDescription();
	addBanner("Static Functions Implementation");
	addAllStateFunctions();
	addAllTransitionFunctions();
//	addAllEntryFunctions();
//	addAllDuringFunctions();
//	addAllConditionFunctions();
//	addAllActionFunctions();
	endCFile();
}

void SourceFileGenerator::generateH()
{
	beginHFile();
	addBanner("Types");
	addStateEnum();
	addBanner("Global Variables");
	addGlobalVarDefinitions();
	endHFile();
}

// Private functions

QString SourceFileGenerator::formatStateName(QString name)
{
	return STATE_NAME;
}

QString SourceFileGenerator::to1stUpper(QString str)
{
	QString retStr = str;

	retStr[0] = retStr[0].toUpper();

	return retStr;
}

void SourceFileGenerator::addBanner( QString text )
{
	m_out	<< "/*---------------------------------------------------------------------------*/"<<endl
			<< "/* "<<text.leftJustified(73, ' ', true)<<" */"<<endl
			<< "/*---------------------------------------------------------------------------*/"<<endl
			<< endl;
}

// To generate Header File

void SourceFileGenerator::beginHFile()
{
	m_out	<< "/**"<<endl
			<< " * @file"<<endl
			<< " * \t\t"<<"Header file for the \""<<m_fsmDesc.title<<"\" state machine."<<endl
			<< " * \t\t"<<"Declare the state list and the global variable which describe all state machine with its:"<<endl
			<< " * \t\t"<<" - state list with correspondant \"entry\" and \"during\" functions"<<endl
			<< " * \t\t"<<" - transition matrix with correspondant \"conditions\" and \"actions\" functions."<<endl
			<< " * \t\t"<<"This global variable describing the finite state machine is design to work"<<endl
			<< " * \t\t"<<"with the Finite State Machine Engine functions (see finite_state_machine_engine.h file)."<<endl
			<< " * \t\t"<<endl
			<< " * \t\t"<<"This file is partially generated from a state machine description XML file,"<<endl
			<< " * \t\t"<<"thanks to AZStateMachineGenerator."<<endl
			<< " * \t\t"<<"Any modification impacting the state list or the transition matrix"<<endl
			<< " * \t\t"<<"should be made in the XML description file before to re-generate this file."<<endl
			<< " */"<<endl
			<< endl;

	m_out	<< "#ifndef _"<<m_fsmDesc.formatedTitle.toUpper()<<"_H"<<endl
			<< "#define _"<<m_fsmDesc.formatedTitle.toUpper()<<"_H"<<endl
			<< endl
			<< "#ifdef __cplusplus"<<endl
			<< "extern \"C\" {"<<endl
			<< "#endif /* __cplusplus */"<<endl
			<< endl
			<< "#include \"finite_state_machine_engine.h\""<<endl
			<< endl;
}

void SourceFileGenerator::addStateEnum()
{
	QString name;

	m_out	<< "/** Possible states of \""<<m_fsmDesc.title<<"\" */"<<endl
			<< "typedef enum"<<endl
			<< "{"<<endl;
	for( int _i=0; _i < m_fsmDesc.stateList.size(); _i++)
	{
		name = formatStateName( m_fsmDesc.stateList.at(_i).name );

		m_out	<< "    "<<name<<","<<endl;
	}
	m_out	<< "    "<<NB_OF_STATES_NAME<<endl
			<< "} "<<STATE_ENUM_TYPE<<";"<<endl
			<< endl;
}

void SourceFileGenerator::addGlobalVarDefinitions()
{
#if 0
	// Not usefull to share these variables
	m_out	<< "/** State list definition of \""<<m_fsmDesc.title<<"\" */"<<endl
			<< "extern "<<STATE_LIST_TYPE<<" "<<STATE_LIST_VAR_NAME<<";"<<endl
			<< endl
			<< "/** Transition matrix definition of \""<<m_fsmDesc.title<<"\" */"<<endl
			<< "extern "<<TRANSITION_MATRIX_TYPE<<" "<<TRANSITION_MATRIX_VAR_NAME<<";"<<endl
			<< endl;
#endif
	m_out	<< "/** Whole description of the finite state machine \""<<m_fsmDesc.title<<"\" */"<<endl
			<< "extern "<<DESCRIPTION_TYPE<<" "<<DESCRIPTION_VAR_NAME<<";"<<endl
			<< endl;
}

void SourceFileGenerator::endHFile()
{
	m_out	<< "#ifdef __cplusplus"<<endl
			<< "} /* extern \"C\" */"<<endl
			<< "#endif /* __cplusplus */"<<endl
			<< endl
			<< "#endif /* _"<<m_fsmDesc.formatedTitle.toUpper()<<"_H */"<<endl;
}


// To generate C Source File

void SourceFileGenerator::beginCFile()
{
	m_out	<< "/**"<<endl
			<< " * @file"<<endl
			<< " * \t\t"<<"Define the \""<<m_fsmDesc.title<<"\" state machine with its:"<<endl
			<< " * \t\t"<<" - state list with correspondant \"entry\" and \"during\" functions"<<endl
			<< " * \t\t"<<" - transition matrix with correspondant \"conditions\" and \"actions\" functions."<<endl
			<< " * \t\t"<<"Implement all the \"entry\", \"during\", \"conditions\" and \"actions\" functions."<<endl
			<< " * \t\t"<<endl
			<< " * \t\t"<<"This file is partially generated from a state machine description XML file,"<<endl
			<< " * \t\t"<<"thanks to AZStateMachineGenerator."<<endl
			<< " * \t\t"<<"Any modification impacting the state list or the transition matrix"<<endl
			<< " * \t\t"<<"should be made in the XML description file before to re-generate this file."<<endl
			<< " */"<<endl
			<< endl;

	m_out	<< "#ifdef __cplusplus"<<endl
			<< "extern \"C\" {"<<endl
			<< "#endif /* __cplusplus */"<<endl
			<< endl
			<< "#include \""<<m_fsmDesc.formatedTitle<<".h\""<<endl
			<< endl;
}

void SourceFileGenerator::addAllStateFctPrototypes()
{
	m_out	<< "/*--- State functions (Entry,During) ---*/"<<endl;

	for( int _i=0; _i < m_fsmDesc.stateList.size(); _i++)
	{
		if( ! m_fsmDesc.stateList.at(_i).entryFct.isEmpty() )
		{
			addVoidFctPrototype( m_fsmDesc.stateList.at(_i).entryFct );
		}
		if( ! m_fsmDesc.stateList.at(_i).duringFct.isEmpty() )
		{
			addVoidFctPrototype( m_fsmDesc.stateList.at(_i).duringFct );
		}
	}
	m_out	<< endl;
}

void SourceFileGenerator::addAllTransitionFctPrototypes()
{
	m_out	<< "/*--- Transition functions (Condition,Action) ---*/"<<endl;

	for( int _i=0; _i < m_fsmDesc.transitionList.size(); _i++)
	{
		if( ! m_fsmDesc.transitionList.at(_i).condition.isEmpty() )
		{
			addConditionFctPrototype( m_fsmDesc.transitionList.at(_i).condition );
		}
		if( ! m_fsmDesc.transitionList.at(_i).action.isEmpty() )
		{
			addVoidFctPrototype( m_fsmDesc.transitionList.at(_i).action );
		}
	}
	m_out	<< endl;
}

void SourceFileGenerator::addVoidFctPrototype(QString name)
{
    m_out	<< "static void "<<name<<"( void );"<<endl;
	//m_out	<< endl;
}

void SourceFileGenerator::addConditionFctPrototype(QString name)
{
    m_out	<< "static "<<BOOLEAN_RETURN_TYPE<<" "<<name<<"( void );"<<endl;
	//m_out	<< endl;
}

void SourceFileGenerator::addStateList()
{
	QString name;
	QString entry;
	QString during;

	m_out	<< "/** State list definition of \""<<m_fsmDesc.title<<"\" */"<<endl
			<< "static "<<STATE_LIST_TYPE<<" "<<STATE_LIST_VAR_NAME<<" ="<<endl
			<< "{"<<endl
			<< " /* {state_id,   entry_function,   during_function}, */"<<endl;
	for( int _i=0; _i < m_fsmDesc.stateList.size(); _i++)
	{
		name = formatStateName( m_fsmDesc.stateList.at(_i).name );

		if( m_fsmDesc.stateList.at(_i).entryFct.isEmpty() )
		{
			entry = "NULL";
		}
		else
		{
			entry = "&"+m_fsmDesc.stateList.at(_i).entryFct;
		}

		if( m_fsmDesc.stateList.at(_i).duringFct.isEmpty() )
		{
			during = "NULL";
		}
		else
		{
			during = "&"+m_fsmDesc.stateList.at(_i).duringFct;
		}

		m_out	<< "    {"<<name<<",   "<<entry<<",   "<<during<<"},"<<endl;
	}
	m_out	<< "};"<<endl
			<< endl;
}

void SourceFileGenerator::addTransitionMatrix()
{
	QString from;
	QString to;
	QString condition;
	QString action;

	m_out	<< "/** Transition matrix definition of \""<<m_fsmDesc.title<<"\" */"<<endl
			<< "static "<<TRANSITION_MATRIX_TYPE<<" "<<TRANSITION_MATRIX_VAR_NAME<<" ="<<endl
			<< "{"<<endl
			<< " /* {from_state_id,   to_state_id,   condition_function,   action_function}, */"<<endl;
	for( int _i=0; _i < m_fsmDesc.transitionList.size(); _i++)
	{
		from = formatStateName( m_fsmDesc.transitionList.at(_i).fromState );
		to = formatStateName( m_fsmDesc.transitionList.at(_i).toState );

		if( m_fsmDesc.transitionList.at(_i).condition.isEmpty() )
		{
			condition = "&AlwaysTrue";
		}
		else
		{
			condition = "&"+m_fsmDesc.transitionList.at(_i).condition;
		}

		if( m_fsmDesc.transitionList.at(_i).action.isEmpty() )
		{
			action = "NULL";
		}
		else
		{
			action = "&"+m_fsmDesc.transitionList.at(_i).action;
		}

		m_out	<< "    {"<<from<<",   "<<to<<",   "<<condition<<",   "<<action<<"},"<<endl;
	}
	m_out	<< "    "<<TRANSITION_MATRIX_END<<endl
			<< "};"<<endl
			<< endl;
}

void SourceFileGenerator::addFsmDescription()
{
	m_out	<< "/** Whole description of the Finite State Machine \""<<m_fsmDesc.title<<"\" */"<<endl
			<< DESCRIPTION_TYPE<<" "<<DESCRIPTION_VAR_NAME<<" ="<<endl
			<< "{"<<endl
			<< "\t"<<"/* current_state_id */"<<endl
			<< "\t"<<formatStateName(m_fsmDesc.initState)<<","<<endl
			<< "\t"<<endl
			<< "\t"<<"/* nb_of_states */"<<endl
			<< "\t"<<NB_OF_STATES_NAME<<","<<endl
			<< "\t"<<endl
			<< "\t"<<"/* init_state_id */"<<endl
			<< "\t"<<formatStateName(m_fsmDesc.initState)<<","<<endl
			<< "\t"<<endl
			<< "\t"<<"/* error_state_id */"<<endl
			<< "\t"<<formatStateName(m_fsmDesc.errorState)<<","<<endl
			<< "\t"<<endl
			<< "\t"<<"/* state_list */"<<endl
			<< "\t"<<"("<<STATE_LIST_TYPE<<"*)&"<<STATE_LIST_VAR_NAME<<","<<endl
			<< "\t"<<endl
			<< "\t"<<"/* transition_matrix */"<<endl
			<< "\t"<<"("<<TRANSITION_MATRIX_TYPE<<"*)&"<<TRANSITION_MATRIX_VAR_NAME<<endl
			<< "};"<<endl
			<< endl;
}

void SourceFileGenerator::addAllStateFunctions()
{
	m_out	<< "/*--------------------------------*/"<<endl
			<< "/* State functions (Entry,During) */"<<endl
			<< "/*--------------------------------*/"<<endl
			<< endl;

	for( int _i=0; _i < m_fsmDesc.stateList.size(); _i++)
	{
		m_out	<< "/*--- "<<m_fsmDesc.stateList.at(_i).name<<" state ---*/"<<endl
				<< endl;
		addEntryFunction( m_fsmDesc.stateList.at(_i) );
		addDuringFunction( m_fsmDesc.stateList.at(_i) );
	}
}

void SourceFileGenerator::addAllTransitionFunctions()
{
	m_out	<< "/*-----------------------------------------*/"<<endl
			<< "/* Transition functions (Condition,Action) */"<<endl
			<< "/*-----------------------------------------*/"<<endl
			<< endl;

	for( int _i=0; _i < m_fsmDesc.transitionList.size(); _i++)
	{
		m_out	<< "/*--- From "<<m_fsmDesc.transitionList.at(_i).fromState<<" to "<<m_fsmDesc.transitionList.at(_i).toState<<" state ---*/"<<endl
				<< endl;
		addConditionFunction( m_fsmDesc.transitionList.at(_i) );
		addActionFunction( m_fsmDesc.transitionList.at(_i) );
	}
}

bool SourceFileGenerator::addEntryFunction( t_state state )
{
	bool _fctExists = false;

	if( ! state.entryFct.isEmpty() )
	{
		_fctExists = true;

		m_out	<< "/**"<<endl
				<< " * Function executed entering in the "<< state.name<<" state."<<endl
				<< " */"<<endl;
		addVoidFunction( state.entryFct );
	}

	return _fctExists;
}

bool SourceFileGenerator::addDuringFunction( t_state state )
{
	bool _fctExists = false;

	if( ! state.duringFct.isEmpty() )
	{
		_fctExists = true;

		m_out	<< "/**"<<endl
				<< " * Function executed during the "<< state.name<<" state."<<endl
				<< " */"<<endl;
		addVoidFunction( state.duringFct );
	}

	return _fctExists;
}

bool SourceFileGenerator::addConditionFunction( t_transition transition )
{
	bool _fctExists = false;

	if( ! transition.condition.isEmpty() )
	{
		_fctExists = true;

		m_out	<< "/**"<<endl
				<< " * Condition to pass"<<endl
				<< " * from "<<transition.fromState<<" to "<<transition.toState<<" state."<<endl
				<< " * "<<endl
				<< " * @return"<<endl
				<< " * \t\t"<<"TRUE if the condition is satisfied, FALSE otherwise."<<endl
				<< " */"<<endl;
		addBooleanFunction( transition.condition );
	}

	return _fctExists;
}

bool SourceFileGenerator::addActionFunction( t_transition transition )
{
	bool _fctExists = false;

	if( ! transition.action.isEmpty() )
	{
		_fctExists = true;

		m_out	<< "/**"<<endl
				<< " * Action executed during the transition"<<endl
				<< " * from "<<transition.fromState<<" to "<<transition.toState<<" state."<<endl
				<< " */"<<endl;
		addVoidFunction( transition.action );
	}

	return _fctExists;
}

void SourceFileGenerator::addVoidFunction(QString name)
{
    m_out	<< "static void "<<name<<"( void )"<<endl
			<< "{"<<endl
			<< "}"<<endl
			<< endl;
}

void SourceFileGenerator::addBooleanFunction(QString name)
{
    m_out	<< "static "<<BOOLEAN_RETURN_TYPE<<" "<<name<<"( void )"<<endl
			<< "{"<<endl
            << "\t"<<"return ( TRUE );"<<endl
			<< "}"<<endl
			<< endl;
}

void SourceFileGenerator::endCFile()
{
	m_out	<< "#ifdef __cplusplus"<<endl
			<< "} /* extern \"C\" */"<<endl
			<< "#endif /* __cplusplus */"<<endl;
}

/* Currently not used but can be used */

void SourceFileGenerator::addAllConditionFctPrototypes()
{
	m_out	<< "/* - Condition functions prototypes - */"<<endl;
	//m_out	<< endl;

	for( int _i=0; _i < m_fsmDesc.transitionList.size(); _i++)
	{
		if( ! m_fsmDesc.transitionList.at(_i).condition.isEmpty() )
		{
//			m_out	<< "/**"<<endl
//					<< " * Condition to pass"<<endl
//					<< " * from "<<m_fsmDesc.transitionList.at(_i).fromState<<" to "<<m_fsmDesc.transitionList.at(_i).toState<<" state."<<endl
//					<< " * "<<endl
//					<< " * @return"<<endl
//					<< " * \t\t"<<"TRUE if the condition is satisfied, FALSE otherwise."<<endl
//					<< " */"<<endl;
			addConditionFctPrototype( m_fsmDesc.transitionList.at(_i).condition );
		}
	}
	m_out	<< endl;
}

void SourceFileGenerator::addAllActionFctPrototypes()
{
	m_out	<< "/* - Action functions prototypes - */"<<endl;
	//m_out	<< endl;

	for( int _i=0; _i < m_fsmDesc.transitionList.size(); _i++)
	{
		if( ! m_fsmDesc.transitionList.at(_i).action.isEmpty() )
		{
//			m_out	<< "/**"<<endl
//					<< " * Action executed during the transition"<<endl
//					<< " * from "<<m_fsmDesc.transitionList.at(_i).fromState<<" to "<<m_fsmDesc.transitionList.at(_i).toState<<" state."<<endl
//					<< " */"<<endl;
			addVoidFctPrototype( m_fsmDesc.transitionList.at(_i).action );
		}
	}
	m_out	<< endl;
}

void SourceFileGenerator::addAllEntryFctPrototypes()
{
	m_out	<< "/* - Entry functions prototypes - */"<<endl;
	//m_out	<< endl;

	for( int _i=0; _i < m_fsmDesc.stateList.size(); _i++)
	{
		if( ! m_fsmDesc.stateList.at(_i).entryFct.isEmpty() )
		{
//			m_out	<< "/**"<<endl
//					<< " * Function executed entering in the "<< m_fsmDesc.stateList.at(_i).name<<" state."<<endl
//					<< " */"<<endl;
			addVoidFctPrototype( m_fsmDesc.stateList.at(_i).entryFct );
		}
	}
	m_out	<< endl;
}

void SourceFileGenerator::addAllDuringFctPrototypes()
{
	m_out	<< "/* - During functions prototypes - */"<<endl;
	//m_out	<< endl;

	for( int _i=0; _i < m_fsmDesc.stateList.size(); _i++)
	{
		if( ! m_fsmDesc.stateList.at(_i).duringFct.isEmpty() )
		{
//			m_out	<< "/**"<<endl
//					<< " * Function executed during the "<< m_fsmDesc.stateList.at(_i).name<<" state."<<endl
//					<< " */"<<endl;
			addVoidFctPrototype( m_fsmDesc.stateList.at(_i).duringFct );
		}
	}
	m_out	<< endl;
}


void SourceFileGenerator::addAllEntryFunctions()
{
	m_out	<< "/* ------------------- */"<<endl
			<< "/* - Entry functions - */"<<endl
			<< "/* ------------------- */"<<endl
			<< endl;

	for( int _i=0; _i < m_fsmDesc.stateList.size(); _i++)
	{
		addEntryFunction( m_fsmDesc.stateList.at(_i) );
	}
}

void SourceFileGenerator::addAllDuringFunctions()
{
	m_out	<< "/* -------------------- */"<<endl
			<< "/* - During functions - */"<<endl
			<< "/* -------------------- */"<<endl
			<< endl;

	for( int _i=0; _i < m_fsmDesc.stateList.size(); _i++)
	{
		if( ! m_fsmDesc.stateList.at(_i).duringFct.isEmpty() )
		{
			addDuringFunction( m_fsmDesc.stateList.at(_i) );
		}
	}
}

void SourceFileGenerator::addAllConditionFunctions()
{
	m_out	<< "/* ----------------------- */"<<endl
			<< "/* - Condition functions - */"<<endl
			<< "/* ----------------------- */"<<endl
			<< endl;

	for( int _i=0; _i < m_fsmDesc.transitionList.size(); _i++)
	{
		addConditionFunction( m_fsmDesc.transitionList.at(_i) );
	}
}

void SourceFileGenerator::addAllActionFunctions()
{
	m_out	<< "/* -------------------- */"<<endl
			<< "/* - Action functions - */"<<endl
			<< "/* -------------------- */"<<endl
			<< endl;

	for( int _i=0; _i < m_fsmDesc.transitionList.size(); _i++)
	{
		addActionFunction( m_fsmDesc.transitionList.at(_i) );
	}
}

