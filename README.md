# az-statemachine

## 1. Introduction

az-statemachine will help you to easily create finite state machines in C/C++ language.

The "az-statemachine generator" will generate state machine templates.
It takes xml file describing states and transitions and generates :
  - visual state machine graphs
  - C language templates. All the states and transitions exists and the state machine can roll, but states and transitions are empty. Templates show a list of state functions and transition functions ready to be complete by the developper.

The "az-statemachine engine" is composed of a couple of files used to run all the created state machines.

## 2. Install
  ### 2.1 Windows
  
  * Go to [Downloads folder](/Downloads/ "Downloads folder") to download the Windows setup file.
  * Run the setup file on your computer and follow instructions.
  It will install Generator, Engine and Examples inside your Program Files folder.
  * Copy "Program Files"/AZ-StateMachine/Engine files (finite_state_machine_engine.h and finite_state_machine_engine.c) in your program source.
  
  ### 2.2 macOS
  
  * Download latest macOS application: [AZ-StateMachine-Generator.app](/Generator/bin/release/macx/AZ-StateMachine-Generator.app/ "AZ-StateMachine-Generator.app"). Put it in your Application folder or where you prefer.
  * Download [Engine](/Engine/ "Engine").
  * Copy Engine files (finite_state_machine_engine.h and finite_state_machine_engine.c) in your program source.
  * (Optional) Download [Examples](/Examples/ "Examples")

