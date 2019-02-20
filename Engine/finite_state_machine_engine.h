/**
 * @file
 * 		Header file of the Finite State Machine Engine.
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

#ifndef FINITE_STATE_MACHINE_ENGINE_H
#define FINITE_STATE_MACHINE_ENGINE_H


/*---------------------------------------------------------------------------*/
/* Defines                                                                   */
/*---------------------------------------------------------------------------*/

/** Special NULL structure to terminate a transition matrix */
#define END_FSM_TRANSITION_MATRIX	{0,0,NULL,NULL}


/*---------------------------------------------------------------------------*/
/* Types                                                                     */
/*---------------------------------------------------------------------------*/

/** Boolean type
 *  you can comment it if your system already has a bool_t type */
typedef enum
{
	FALSE	= 0,
	TRUE	= 1
} bool_t;


/** One state defintion of the state machine */
typedef struct
{
    /** State identifier */
    int	state_id;
    /** Function run when entering in the state */
    void	(*entry_fct)( void );
    /** Function run each time the machine is called,
     *  as long as it is still in this state */
    void	(*during_fct)( void );
} fsm_state_t;

/** Transition */
typedef struct
{
    /** Departure state identifier */
    int		from_state_id;
    /** Arrival state identifier */
    int		to_state_id;
    /** Function returning the condition to go from from_state_id to to_state_id */
    bool_t	(*condition_fct)( void );
    /** Function run if condition_fct return TRUE and before going in the next state */
    void	(*action_fct)( void );
} fsm_transition_t;

/** State list */
typedef fsm_state_t fsm_state_list_t[];

/** Transition list (often called transition matrix) */
typedef fsm_transition_t fsm_transition_matrix_t[];

/** Whole description of a state machine */
typedef struct
{
    /** Current state identifier */
	int						current_state_id;
    /** Number of states */
	int						nb_of_states;       /**< @todo Should be const */
    /** Identifier of the first state in the state machine */
	int						init_state_id;		/**< @todo Should be const */
    /** Identifier of an error state : in the improbable case of a call to an unknown
     *  state identifier, the state machine will jump to this error_state */
	int						error_state_id;		/**< @todo Should be const */
    /** Whole state list */
	fsm_state_list_t		*state_list;		/**< @todo Should be const */
    /** Whole transition list/marix */
	fsm_transition_matrix_t	*transition_matrix;	/**< @todo Should be const */
} fsm_description_t;


/*---------------------------------------------------------------------------*/
/* Functions                                                                 */
/*---------------------------------------------------------------------------*/

/**
 * Intialize the state machine in its "init_state_id" state.
 * Run the entry_fct of this state.
 *
 * @param[in,out]	fsm_desc
 *      State machine to be initialized.
 */
void InitStateMachine( fsm_description_t *fsm_desc );

/**
 * One step run of the state machine.
 *
 * @param[in,out]	fsm_desc
 *      State machine to be advanced.
 */
void AdvanceStateMachine( fsm_description_t *fsm_desc );

/**
 * Force the state machine to jump in a specific state (state_id)
 * and run the entry_fct of this state.
 *
 * @param[in,out]	fsm_desc
 *		State machine to drive.
 *
 * @param[in]		state_id
 *		State to jump to.
 */
void EntryInState( fsm_description_t *fsm_desc, int state_id );

/**
 * Return the current state of the state machine.
 * @todo fsm_description_t should be const as it is not modified.
 *
 * @param[in]		fsm_desc
 *		State machine.
 *
 * @return
 *		Current state identifier of the state machine.
 */
int GetCurrentStateId( fsm_description_t *fsm_desc );

/**
 * Just return TRUE.
 * Used for always true transitions.
 *
 * @return
 *		Always TRUE
 */
bool_t AlwaysTrue( void );


#endif /* FINITE_STATE_MACHINE_ENGINE_H */
