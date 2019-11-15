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
  
  * Go to [Downloads folder](/Downloads/ "Downloads folder") to download the macOS disk image file.
  * Open/mount the DMG.
  * Copy the AZ-State-Machine application in your Application folder or where you prefer.
  * Copy Engine files (finite_state_machine_engine.h and finite_state_machine_engine.c) in your program source.
  * (Optional) Copy Example files where you want.

## 3. Usage
  ### 3.1 Brief
  
  * Define your finite state machine (FSM) in a XML file (see Examples).
  * Open AZ-StateMachine application and open your XML file with the "File > Open" menu.
  * Press "Generate files".
  * .h et .c files are automatically generated in a Generated_src sub-directory of the XML directory. Copy these files in your program source and fill its functions.
  * Use the finite_state_machine_engine.h functions to deal with your new FSM. Use InitStateMachine() to init it and AdvanceStateMachine() to run it.
  
