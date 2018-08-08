#ifndef SMDESCRIPTION_H
#define SMDESCRIPTION_H

#include <QString>
#include <QList>

typedef struct
{
	QString name;
	QString entryFct;
	QString duringFct;
	bool    isInit;
	bool    isError;
} t_state;

typedef struct
{
	QString fromState;
	QString toState;
	QString condition;
	QString action;
} t_transition;

typedef QList<t_transition>	t_transition_list;
typedef QList<t_state>		t_state_list;

class SMDescription
{
public:
    SMDescription();

	//void addInitState(QString state, QString action);
	void addState(t_state state);
	void addTitle(QString title);
	void addTransition(t_transition transition);
	void debugTransitionList();
	void clear();

    // TODO: set private and use acessors
	t_state_list stateList;
	t_transition_list transitionList;
	QString title;
	QString formatedTitle; // Title lowercased with '_' instead of whitespaces
	QString initState;
	QString errorState;

private:
	// Format Title in lower case and whit whitespaces replaced by '_'
	void formatTitle();

	void debugTransition(t_transition transition);

};

#endif // SMDESCRIPTION_H
