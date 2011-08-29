/**
 * @file
 * 		Header file of the Finite State Machine Engine.
 */

#ifndef _FINITE_STATE_MACHINE_ENGINE_H
#define _FINITE_STATE_MACHINE_ENGINE_H

/* Adapted for Ventec */
#include "../Util.h"

/*---------------------------------------------------------------------------*/
/* Defines                                                                   */
/*---------------------------------------------------------------------------*/

/** Special NULL structure to terminate a transition matrix */
#define END_FSM_TRANSITION_MATRIX	{0,0,NULL,NULL}


/*---------------------------------------------------------------------------*/
/* Types                                                                     */
/*---------------------------------------------------------------------------*/

/** Etat de la machine */
typedef struct
{
  int	state_id;				/**< Identifiant de l'etat */
  void	(*entry_fct)( void );	/**< Fonction executee a l'entree dans l'etat */
  void	(*during_fct)( void );	/**< Fonction executee a chaque appel de la machine, tant qu'on est dans cet etat */
} fsm_state_t;

/** Transition */
typedef struct
{
  int		from_state_id;				/**< Identifiant de l'etat de depart */
  int		to_state_id;				/**< Identifiant de l'etat d'arrivee */
  bool_t	(*condition_fct)( void );	/**< Fonction determinant la condition de transition */
  void		(*action_fct)( void );		/**< Fonction executee si la condition est realisee, et avant de passer a l'etat suivant */
} fsm_transition_t;

/** Liste d'etats */
typedef fsm_state_t fsm_state_list_t[];

/** Liste de transitions (ou matrice de transition) */
typedef fsm_transition_t fsm_transition_matrix_t[];

/** Description complete d'une machine d'etats */
typedef struct
{
	int						current_state_id;	/**< Indentifiant de l'etat courant */
	int						nb_of_states;		/**< Nombre d'etats */
	int						init_state_id;		/**< Identifiant de l'etat d'initialisation */
	int						error_state_id;		/**< Identifiant de l'etat d'erreur */
	fsm_state_list_t		*state_list;		/**< Liste des etats */
	fsm_transition_matrix_t	*transition_matrix;	/**< Matrice de transitions */
} fsm_description_t;


/*---------------------------------------------------------------------------*/
/* Functions                                                                 */
/*---------------------------------------------------------------------------*/

/**
 * Initialise la machine d'etat a son etat d'initialisation "init_state_id".
 * Execute la fonction "entry" de cet etat.
 *
 * @param[in,out]	fsm_desc
 *		Structure de description de la machine d'etat a initialiser.
 */
void InitStateMachine( fsm_description_t *fsm_desc );

/**
 * Fait avancer d'un pas la machine d'etat.
 *
 * @param[in,out]	fsm_desc
 *		Structure de description de la machine d'etat a faire avancer.
 */
void AdvanceStateMachine( fsm_description_t *fsm_desc );

/**
 * Force la machine a entrer dans l'etat "state_id" passe en argument
 * et execute la fonction "entry" de cet etat.
 *
 * @param[in,out]	fsm_desc
 *		Structure de description de la machine d'etat.
 *
 * @param[in]		state_id
 *		Etat dans lequel doit passer la machine d'etat.
 */
void EntryInState( fsm_description_t *fsm_desc, int state_id );

/**
 * Retourne l'etat "state_id" dans lequel est actuellement la machine d'etat.
 *
 * @param[in]		fsm_desc
 *		Structure de description de la machine d'etat.
 *
 * @return
 *		Etat "state_id" dans lequel est la machine d'etat.
 */
int GetCurrentStateId( fsm_description_t fsm_desc );

/**
 * Fonction qui ne fait que retourner TRUE.
 * Utilisee pour les transitions toujours vraies.
 *
 * @return
 *		TRUE
 */
bool_t AlwaysTrue( void );


#endif /* _FINITE_STATE_MACHINE_ENGINE_H */
