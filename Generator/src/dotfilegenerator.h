#ifndef DOTFILEGENERATOR_H
#define DOTFILEGENERATOR_H

#include <QTextStream>
#include "smdescription.h"

#define NODE_BG_COLOR			"#E7E7F0"	// Lightgrey
#define TOP_NODE_BG_COLOR		"black"
#define ERROR_TOP_NODE_BG_COLOR	"#700000"	// Brown

class DotFileGenerator
{
public:
	DotFileGenerator(QIODevice *device);

	void generate(SMDescription smDesc);

private:
	QTextStream out;

	void newGraph(QString title);
	void addState(t_state state);
	void addInit(QString initStateName);
	void addTransition(t_transition transition);
	void endGraph();
};

#endif // DOTFILEGENERATOR_H
