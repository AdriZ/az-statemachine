/**
 * @file
 * 		Finite State Machine Engine.
 * 		See https://github.com/AdriZ/az-statemachine for more informations.
 *
 * @author		Adrien Zancan
 * @version		v1.1
 * @copyright	Simplified BSD License
 */

/*
	The files finite_state_machine_engine.h and finite_state_machine_engine.c are
	provided under the terms of the "Simplified BSD License".

	Copyright (c) 2011, Adrien ZANCAN
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright notice,
	   this list of conditions and the following disclaimer in the documentation
	   and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "finite_state_machine_engine.h"

/*---------------------------------------------------------------------------*/
/* Private functions                                                         */
/*---------------------------------------------------------------------------*/

/**
 *  Detect if a transition is a "null" transition, conrresponding to the end
 *  of a transition matrix.
 *  
 *  @param[in]	transition
 *      Transition to test.
 *  
 *  @return
 *      TRUE if this is a ending transition, FALSE if this is a real transition.
 */
static bool_t IsFsmTransitionEnd( fsm_transition_t transition )
{
	return ( (transition.from_state_id == 0)
		  && (transition.to_state_id   == 0)
		  && (transition.condition_fct == NULL)
		  && (transition.action_fct	== NULL) );
}

/**
 *  Get the current state of a state machine
 *  
 *  @param[out]		current_state
 *  	Current state found.
 *  
 *  @param[in,out]	fsm_desc
 *      State machine.
*/
static void FindCurrentState( fsm_state_t		*current_state,
							  fsm_description_t	*fsm_desc )
{
	int _state_index = 0;

	/* Should never occur */
	/* If current_state_id is higher than number of possible states */
	if ( fsm_desc->current_state_id >= fsm_desc->nb_of_states )
	{
		/* But if it occurs (data corruption for exemple), we return in a known state : the error state */
		fsm_desc->current_state_id = fsm_desc->error_state_id;
	}

	/* Search current state (fsm_desc->current_state_id) */
	for ( _state_index=0; (*fsm_desc->state_list)[_state_index].state_id < (fsm_desc->nb_of_states); _state_index++ )
	{
		/* If the ID is the current state one */
		if ( (*fsm_desc->state_list)[_state_index].state_id == fsm_desc->current_state_id )
		{
			*current_state = (*fsm_desc->state_list)[_state_index];
			break;
		}
	}
}

/**
 *  Search the first transition with a fulfilled condition.
 *  
 *  @param[out]	transition
 *  	Transition found.
 *  
 *  @param[in]	fsm_desc
 *      State machine
 *  
 *  @return
 *      TRUE if a transition with fulfilled condition has been found.
 *  	FALSE if there's no fulfilled condition.
 */
static bool_t FindTransition( fsm_transition_t	 *transition,
							  fsm_description_t *fsm_desc )
{
	bool_t	_transition_is_found = FALSE;
	int		_transition_index = 0;

	/* While we did'nt reach the matrix end */
	while ( ! IsFsmTransitionEnd((*fsm_desc->transition_matrix)[_transition_index]) )
	{
		/* If we found the current_state && the condition is fulfilled */
		if ( ( fsm_desc->current_state_id == (*fsm_desc->transition_matrix)[_transition_index].from_state_id )
		  && ( (*fsm_desc->transition_matrix)[_transition_index].condition_fct() == TRUE ) )
		{
			/* We found a transition, we save it, and return TRUE */
			*transition = (*fsm_desc->transition_matrix)[_transition_index];
			_transition_is_found = TRUE;
			break;
		}
		_transition_index++;
	}

	return _transition_is_found;
}

/**
 *  Execute "during" function (if it exists) of a state
 *  
 *  @param[in]	state
 *      State
*/
static void ExecuteDuringStateFunction( fsm_state_t state )
{
	/* Execute "during" function if it exists */
	if ( state.during_fct != NULL )
	{
		state.during_fct();
	}
}

/**
 *  Execute "entry" function (if it exists) of a state
 *  
 *  @param[in]	state
 *      State
*/
static void ExecuteEntryStateFunction( fsm_state_t state )
{
	/* Execute "entry" function if it exists */
	if ( state.entry_fct != NULL )
	{
		state.entry_fct();
	}
}

/**
 *  Execute "action" function (if it exists) of a transition
 *  
 *  @param[in]	transition
 *      Transition
*/
static void ExecuteTransitionAction( fsm_transition_t transition )
{
	/* Execute "action" function if it exists */
	if ( transition.action_fct != NULL )
	{
		transition.action_fct();
	}
}

/*---------------------------------------------------------------------------*/
/* Public functions                                                          */
/*---------------------------------------------------------------------------*/

/**
 * Intialize the state machine in its "init_state_id" state.
 * Run the entry_fct of this state.
 *
 * @param[in,out]	fsm_desc
 *      State machine to be initialized.
 */
void InitStateMachine( fsm_description_t *fsm_desc )
{
	EntryInState( fsm_desc, fsm_desc->init_state_id );
}


/**
 * One step run of the state machine.
 *
 * @param[in,out]	fsm_desc
 *      State machine to be advanced.
 */
void AdvanceStateMachine( fsm_description_t	*fsm_desc )
{
	fsm_state_t			_current_state		   	= {0};
	fsm_transition_t	_transition	  			= {0};
	bool_t				_transition_is_found	= FALSE;

	/* Search current state */
	FindCurrentState( &_current_state, fsm_desc );

	/* Search a possible transition with a fulfilled condition*/
	_transition_is_found = FindTransition( &_transition, fsm_desc );
	
	/* If no transition found */
	if ( !_transition_is_found )
	{
		/* Execute "during" function */
		ExecuteDuringStateFunction( _current_state );		
	}
	/* If there's a transition with a fulfilled condition */
	else
	{
		/* Execute "action" function */
		ExecuteTransitionAction( _transition );

		/* Save the next state and execute its "entry" function */
		EntryInState( fsm_desc, _transition.to_state_id );
	}
}


/**
 * Force the state machine to jump in a specific state (state_id)
 * and run the entry_fct of this state.
 *
 * @param[in,out]	fsm_desc
 *        State machine to drive.
 *
 * @param[in]		state_id
 *        State to jump to.
 */
void EntryInState( fsm_description_t *fsm_desc, int state_id )
{
	fsm_state_t _current_state = {0};

	/* If state_id is valid */
	if ( state_id < (fsm_desc->nb_of_states) )
	{
		/* We set current state to requested state */
		fsm_desc->current_state_id = state_id;
	}
	else
	{
		/* If not, this is an error, so we force to enter in the error state */
		fsm_desc->current_state_id = fsm_desc->error_state_id;
	}

	/* Search this new state */
	FindCurrentState( &_current_state, fsm_desc );

	/* Execute the "entry" function */
	ExecuteEntryStateFunction( _current_state );
}


/**
 * Return the current state of the state machine.
 * @todo fsm_description_t should be const as it is not modified.
 *
 * @param[in]	fsm_desc
 *        State machine.
 *
 * @return
 *        Current state identifier of the state machine.
 */
int GetCurrentStateId( fsm_description_t *fsm_desc )
{
	return fsm_desc->current_state_id;
}


/**
 * Just return TRUE.
 * Used for always true transitions.
 *
 * @return
 *        Always TRUE
 */
bool_t AlwaysTrue( void )
{
	return TRUE;
}

