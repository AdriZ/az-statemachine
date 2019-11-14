/**
 * @file
 * 		Header file for the "FSM Baby" state machine.
 * 		Declare the state list and the global variable which describe all state machine with its:
 * 		 - state list with correspondant "entry" and "during" functions
 * 		 - transition matrix with correspondant "conditions" and "actions" functions.
 * 		This global variable describing the finite state machine is design to work
 * 		with the Finite State Machine Engine functions (see finite_state_machine_engine.h file).
 * 		
 * 		This file is partially generated from a state machine description XML file,
 * 		thanks to AZStateMachineGenerator.
 * 		Any modification impacting the state list or the transition matrix
 * 		should be made in the XML description file before to re-generate this file.
 */

#ifndef _FSM_BABY_H
#define _FSM_BABY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "finite_state_machine_engine.h"

/*---------------------------------------------------------------------------*/
/* Types                                                                     */
/*---------------------------------------------------------------------------*/

/** Possible states of "FSM Baby" */
typedef enum
{
    ST_CRYING,
    ST_INERT,
    ST_SLEEPING,
    ST_EATING,
    FSM_BABY_NB_OF_STATES
} state_fsm_baby_t;

/*---------------------------------------------------------------------------*/
/* Global Variables                                                          */
/*---------------------------------------------------------------------------*/

/** Whole description of the finite state machine "FSM Baby" */
extern fsm_description_t g_fsm_baby;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* _FSM_BABY_H */
