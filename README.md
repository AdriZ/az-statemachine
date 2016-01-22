# az-statemachine
az-statemachine will help you to easily create finite state machines in C/C++ language.

The "az-statemachine generator" will generate state machine templates.
It takes xml file describing states and transitions and generates :
  - visual state machine graphs
  - C language templates. All the states and transitions exists and the state machine can roll, but states and transitions are empty. The template shows a list of state functions and transition functions ready to be complete by the developper.

The "az-statemachine engine" is composed of a couple of files used to run all the created state machines.
