/**
 * @file
 * 		Define the "FSM Baby" state machine with its:
 * 		 - state list with correspondant "entry" and "during" functions
 * 		 - transition matrix with correspondant "conditions" and "actions" functions.
 * 		Implement all the "entry", "during", "conditions" and "actions" functions.
 * 		
 * 		This file is partially generated from a state machine description XML file,
 * 		thanks to AZStateMachineGenerator.
 * 		Any modification impacting the state list or the transition matrix
 * 		should be made in the XML description file before to re-generate this file.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "fsm_baby.h"

/*---------------------------------------------------------------------------*/
/* Static Function Prototypes                                                */
/*---------------------------------------------------------------------------*/

/*--- State functions (Entry,During) ---*/
static void OpenMouth( void );
static void DoLotOfNoise( void );
static void JustBreath( void );
static void SpinelessPosition( void );
static void JustBreath( void );
static void OpenMouth( void );
static void Suckle( void );

/*--- Transition functions (Condition,Action) ---*/
static bool_t AllIsGood( void );
static bool_t AllIsGood( void );
static bool_t IsHungryOrDirty( void );
static bool_t IsHungryAndTheresABreast( void );
static bool_t IsTired( void );
static bool_t IsHungryOrDirty( void );
static bool_t IsDirty( void );
static bool_t AllIsGood( void );
static void Burp( void );
static bool_t TheresABreast( void );

/*---------------------------------------------------------------------------*/
/* Static Variables                                                          */
/*---------------------------------------------------------------------------*/

/** State list definition of "FSM Baby" */
static const fsm_state_list_t s_fsm_baby_state_list =
{
 /* {state_id,   entry_function,   during_function}, */
    {ST_CRYING,   &OpenMouth,   &DoLotOfNoise},
    {ST_INERT,   NULL,   &JustBreath},
    {ST_SLEEPING,   &SpinelessPosition,   &JustBreath},
    {ST_EATING,   &OpenMouth,   &Suckle},
};

/** Transition matrix definition of "FSM Baby" */
static const fsm_transition_matrix_t s_fsm_baby_transition_matrix =
{
 /* {from_state_id,   to_state_id,   condition_function,   action_function}, */
    {ST_CRYING,   ST_INERT,   &AllIsGood,   NULL},
    {ST_INERT,   ST_SLEEPING,   &AllIsGood,   NULL},
    {ST_INERT,   ST_CRYING,   &IsHungryOrDirty,   NULL},
    {ST_INERT,   ST_EATING,   &IsHungryAndTheresABreast,   NULL},
    {ST_EATING,   ST_SLEEPING,   &IsTired,   NULL},
    {ST_SLEEPING,   ST_CRYING,   &IsHungryOrDirty,   NULL},
    {ST_EATING,   ST_CRYING,   &IsDirty,   NULL},
    {ST_EATING,   ST_INERT,   &AllIsGood,   &Burp},
    {ST_CRYING,   ST_EATING,   &TheresABreast,   NULL},
    END_FSM_TRANSITION_MATRIX
};

/*---------------------------------------------------------------------------*/
/* Global Variables                                                          */
/*---------------------------------------------------------------------------*/

/** Whole description of the Finite State Machine "FSM Baby" */
fsm_description_t g_fsm_baby =
{
	/* current_state_id */
	ST_CRYING,
	
	/* nb_of_states */
	FSM_BABY_NB_OF_STATES,
	
	/* init_state_id */
	ST_CRYING,
	
	/* error_state_id */
	ST_CRYING,
	
	/* state_list */
	(fsm_state_list_t*)&s_fsm_baby_state_list,
	
	/* transition_matrix */
	(fsm_transition_matrix_t*)&s_fsm_baby_transition_matrix
};

/*---------------------------------------------------------------------------*/
/* Static Functions Implementation                                           */
/*---------------------------------------------------------------------------*/

/*--------------------------------*/
/* State functions (Entry,During) */
/*--------------------------------*/

/*--- CRYING state ---*/

/**
 * Function executed entering in the CRYING state.
 */
static void OpenMouth( void )
{
}

/**
 * Function executed during the CRYING state.
 */
static void DoLotOfNoise( void )
{
}

/*--- INERT state ---*/

/**
 * Function executed during the INERT state.
 */
static void JustBreath( void )
{
}

/*--- SLEEPING state ---*/

/**
 * Function executed entering in the SLEEPING state.
 */
static void SpinelessPosition( void )
{
}

/**
 * Function executed during the SLEEPING state.
 */
static void JustBreath( void )
{
}

/*--- EATING state ---*/

/**
 * Function executed entering in the EATING state.
 */
static void OpenMouth( void )
{
}

/**
 * Function executed during the EATING state.
 */
static void Suckle( void )
{
}

/*-----------------------------------------*/
/* Transition functions (Condition,Action) */
/*-----------------------------------------*/

/*--- From CRYING to INERT state ---*/

/**
 * Condition to pass
 * from CRYING to INERT state.
 * 
 * @return
 * 		TRUE if the condition is satisfied, FALSE otherwise.
 */
static bool_t AllIsGood( void )
{
	return ( TRUE );
}

/*--- From INERT to SLEEPING state ---*/

/**
 * Condition to pass
 * from INERT to SLEEPING state.
 * 
 * @return
 * 		TRUE if the condition is satisfied, FALSE otherwise.
 */
static bool_t AllIsGood( void )
{
	return ( TRUE );
}

/*--- From INERT to CRYING state ---*/

/**
 * Condition to pass
 * from INERT to CRYING state.
 * 
 * @return
 * 		TRUE if the condition is satisfied, FALSE otherwise.
 */
static bool_t IsHungryOrDirty( void )
{
	return ( TRUE );
}

/*--- From INERT to EATING state ---*/

/**
 * Condition to pass
 * from INERT to EATING state.
 * 
 * @return
 * 		TRUE if the condition is satisfied, FALSE otherwise.
 */
static bool_t IsHungryAndTheresABreast( void )
{
	return ( TRUE );
}

/*--- From EATING to SLEEPING state ---*/

/**
 * Condition to pass
 * from EATING to SLEEPING state.
 * 
 * @return
 * 		TRUE if the condition is satisfied, FALSE otherwise.
 */
static bool_t IsTired( void )
{
	return ( TRUE );
}

/*--- From SLEEPING to CRYING state ---*/

/**
 * Condition to pass
 * from SLEEPING to CRYING state.
 * 
 * @return
 * 		TRUE if the condition is satisfied, FALSE otherwise.
 */
static bool_t IsHungryOrDirty( void )
{
	return ( TRUE );
}

/*--- From EATING to CRYING state ---*/

/**
 * Condition to pass
 * from EATING to CRYING state.
 * 
 * @return
 * 		TRUE if the condition is satisfied, FALSE otherwise.
 */
static bool_t IsDirty( void )
{
	return ( TRUE );
}

/*--- From EATING to INERT state ---*/

/**
 * Condition to pass
 * from EATING to INERT state.
 * 
 * @return
 * 		TRUE if the condition is satisfied, FALSE otherwise.
 */
static bool_t AllIsGood( void )
{
	return ( TRUE );
}

/**
 * Action executed during the transition
 * from EATING to INERT state.
 */
static void Burp( void )
{
}

/*--- From CRYING to EATING state ---*/

/**
 * Condition to pass
 * from CRYING to EATING state.
 * 
 * @return
 * 		TRUE if the condition is satisfied, FALSE otherwise.
 */
static bool_t TheresABreast( void )
{
	return ( TRUE );
}

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */
