#include "dotfilegenerator.h"

DotFileGenerator::DotFileGenerator(QIODevice *device)
{
	out.setDevice(device);
	out.setCodec("UTF-8");
}

void DotFileGenerator::generate(SMDescription smDesc)
{
	newGraph(smDesc.title);

	for( int i=0; i < smDesc.stateList.size(); i++)
	{
		addState(smDesc.stateList.at(i));
	}
	out << endl;

	for( int i=0; i < smDesc.transitionList.size(); i++)
	{
		addTransition(smDesc.transitionList.at(i));
	}

	endGraph();
}

void DotFileGenerator::newGraph(QString title)
{
	out << "digraph \"" << title << "\" \{" << endl
		<<"\t"<< "dpi=100;" << endl
		<<"\t"<< "overlap=false;" << endl
		<<"\t"<< "labelloc=\"t\";   // Text on top" << endl
		<<"\t"<< "labeljust=\"l\";  // Text on left" << endl
		<<"\t"<< "label=\"\\G\\n\\n\"; // Display the graph title" << endl
		<<"\t"<< endl
		<<"\t"<< "node [ shape=record, style=\"rounded,bold,filled\", labelloc=\"t\", fillcolor=\""<<NODE_BG_COLOR<<"\", fontname=\"Courier New\", width=2.3];" << endl
		<<"\t"<< "edge [ fontname=\"Courier New\", color=\"#0000FF\", fontcolor=\"#00008B\" ];" << endl
		<<"\t"<< endl;
}

void DotFileGenerator::endGraph()
{
	out << "}" << endl;
}

void DotFileGenerator::addInit(QString initStateName)
{
	out <<"\t"<< "__ENTER__ [shape=point, fillcolor=black, height=0.1, width=0.1];" << endl;
	out << "\t" << "__ENTER__"
		<< " -> " << initStateName
		<< ";" << endl
		<< endl;
}

void DotFileGenerator::addState(t_state state)
{
	QString _topBgColor = TOP_NODE_BG_COLOR;

	if( state.isInit )
	{
		addInit( state.name );
	}

	if( state.isError )
	{
		_topBgColor = ERROR_TOP_NODE_BG_COLOR; // Brown
	}

	out << "\t" << state.name
		<< " [ label =<<table border=\"0\" cellborder=\"0\" bgcolor=\""<<NODE_BG_COLOR<<"\">"
		<< "<tr><td bgcolor=\""<<_topBgColor<<"\" align=\"center\"><font color=\""<<NODE_BG_COLOR<<"\">"
		<< " \\N ";	// Display the node title (i.e.: state.name)
	out << "</font></td></tr>"
		<< "<tr><td align=\"left\" port=\"f0\">";
	if( state.entryFct != "" )
		out	<< "entry:  "<<state.entryFct<<"()";
	else
		out << " "; // To keep the same height
	out	<< "</td></tr>"
		<< "<tr><td align=\"left\" port=\"f1\">";
	if( state.duringFct != "" )
		out	<< "during: "<<state.duringFct<<"()";
	else
		out << " "; // To keep the same height
	out << "</td></tr>"
		<< "</table>> ];" << endl
		<< endl;
}

void DotFileGenerator::addTransition(t_transition transition)
{
	// Exemple:
	// 	STATE1 -> STATE2 [ label = "ConditionFunction()\l / ActionFunction()" ];
	out << "\t" << transition.fromState
		<< " -> " << transition.toState;
	out	<< " [ label = \""; // Begin label
	if( transition.condition.isEmpty() )
	{
		// No condition in transition, i.e. transition is always TRUE
		if( ! transition.action.isEmpty() )
			out	<< "TRUE  \\l/ " << transition.action << "()  ";
		// Nothing is displayed on the transition if there's no condition and no action
	}
	else // There's a transition condition
	{
		out << transition.condition <<"()  ";
		if( ! transition.action.isEmpty() )
			out	<< "\\l / " << transition.action << "()  ";
	}
	out	<< "\" ];" << endl; // End label
}

