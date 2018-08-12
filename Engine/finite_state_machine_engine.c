/**
 * @file
 * 		Finite State Machine Engine.
 *      See https://github.com/AdriZ/az-statemachine for more informations.
 *
 * @author		Adrien Zancan
 * @version     v1.1
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

static bool_t IsFsmTransitionEnd( fsm_transition_t transition )
{
	return ( (transition.from_state_id == 0)
		  && (transition.to_state_id   == 0)
		  && (transition.condition_fct == NULL)
		  && (transition.action_fct	== NULL) );
}

static void FindCurrentState( fsm_state_t			*current_state,
							  fsm_description_t	*fsm_desc )
{
	int _state_index = 0;

	/* Ne devrait jamais arriver */
	/* Si le current_state_id est superieur au nombre d'etats */
	if ( fsm_desc->current_state_id >= fsm_desc->nb_of_states )
	{
		/* Mais si ca arrivait, on se debrouille pour revenir dans un etat connu : l'etat d'erreur */
		fsm_desc->current_state_id = fsm_desc->error_state_id;
	}

	/* Recherche de l'etat courant (fsm_desc->current_state_id) */
	for ( _state_index=0; (*fsm_desc->state_list)[_state_index].state_id < (fsm_desc->nb_of_states); _state_index++ )
	{
		/* Si l'id est celui de l'etat courant */
		if ( (*fsm_desc->state_list)[_state_index].state_id == fsm_desc->current_state_id )
		{
			*current_state = (*fsm_desc->state_list)[_state_index];
			break;
		}
	}
}

static bool_t FindTransition( fsm_transition_t	 *transition,
							  fsm_description_t *fsm_desc )
{
	bool_t	_transition_is_found = FALSE;
	int		_transition_index = 0;

	/* Tant qu'on n'est pas a la fin de la matrice */
	while ( ! IsFsmTransitionEnd((*fsm_desc->transition_matrix)[_transition_index]) )
	{
		/* Si on trouve le current_state && que la condition est satisfaite */
		if ( ( fsm_desc->current_state_id == (*fsm_desc->transition_matrix)[_transition_index].from_state_id )
		  && ( (*fsm_desc->transition_matrix)[_transition_index].condition_fct() == TRUE ) )
		{
			/* On a trouve une transition on l'enregistre et on retourne TRUE */
			*transition = (*fsm_desc->transition_matrix)[_transition_index];
			_transition_is_found = TRUE;
			break;
		}
		_transition_index++;
	}

	return _transition_is_found;
}

static void ExecuteDuringStateFunction( fsm_state_t state )
{
	/* Execution de la fonction "during" si elle a ete definie */
	if ( state.during_fct != NULL )
	{
		state.during_fct();
	}
}

static void ExecuteEntryStateFunction( fsm_state_t state )
{
	/* Execution de la fonction "entry" si elle a ete definie */
	if ( state.entry_fct != NULL )
	{
		state.entry_fct();
	}
}

static void ExecuteTransitionAction( fsm_transition_t transition )
{
	/* Execution de la fonction "action" si elle a ete definie */
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
 * @param[in,out]    fsm_desc
 *      State machine to be initialized.
 */
void InitStateMachine( fsm_description_t *fsm_desc )
{
	EntryInState( fsm_desc, fsm_desc->init_state_id );
}


/**
 * One step run of the state machine.
 *
 * @param[in,out]    fsm_desc
 *      State machine to be advanced.
 */
void AdvanceStateMachine( fsm_description_t	*fsm_desc )
{
	fsm_state_t			_current_state		   	= {0};
	fsm_transition_t	_transition	  			= {0};
	bool_t				_transition_is_found	= FALSE;

	/* Recherche de l'etat courant */
	FindCurrentState( &_current_state, fsm_desc );

	/* Recherche de l'eventuelle transition */
	_transition_is_found = FindTransition( &_transition, fsm_desc );
	
	/* S'il n'y a pas de transition trouvee */
	if ( !_transition_is_found )
	{
		/* Execution de la fonction "during" */
		ExecuteDuringStateFunction( _current_state );		
	}
	/* S'il y a une condition de transition valide */
	else
	{
		/* Execute l'action */
		ExecuteTransitionAction( _transition );

		/* Enregistrement de l'etat suivant et execution de sa fonction "entry" */
		EntryInState( fsm_desc, _transition.to_state_id );
	}
}


/**
 * Force the state machine to jump in a specific state (state_id)
 * and run the entry_fct of this state.
 *
 * @param[in,out]    fsm_desc
 *        State machine to drive.
 *
 * @param[in]        state_id
 *        State to jump to.
 */
void EntryInState( fsm_description_t *fsm_desc, int state_id )
{
	fsm_state_t _current_state = {0};

	/* Si le state_id n'est pas en dehors de la plage autorisee */
	if ( state_id < (fsm_desc->nb_of_states) )
	{
		/* On positionne l'etat courant a l'etat demandÈ */
		fsm_desc->current_state_id = state_id;
	}
	else
	{
		/* Sinon, c'est une erreur donc on force l'etat "erreur" */
		fsm_desc->current_state_id = fsm_desc->error_state_id;
	}

	/* Recherche de l'etat */
	FindCurrentState( &_current_state, fsm_desc );

	/* Execution de la fonction "entry" */
	ExecuteEntryStateFunction( _current_state );
}


/**
 * Return the current state of the state machine.
 * @todo fsm_description_t should be const as it is not modified.
 *
 * @param[in]        fsm_desc
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

