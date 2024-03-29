# az-statemachine

## 1. Introduction

az-statemachine will help you to **easily create finite state machines in C language**.

### az-statemachine generator
*az-statemachine generator* will generate state machine templates.
It takes xml file describing states and transitions and generates :
  - visual state machine graphs
  - C language templates. All the states and transitions exists and the state machine can roll, but states and transitions are empty. Templates show a list of state functions and transition functions ready to be complete by the developper.

### az-statemachine engine
*az-statemachine engine* is composed of a couple of files used to run all the created state machines.

*az-statemachine engine* doesn't require any OS or library and it is really lightweight, so it is especially interested for small embedded system.

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

### 2.3 Linux
*az-statemachine generator* has been compiled for Windows and macOS but, as it uses Qt multi-plateform framework, it should compile on Linux too. Feel free to contribute to this project to test it and even to automate the process.

## 3. Usage
### 3.1 Brief

* Define your finite state machine (FSM) in a XML file (see Examples).
* Open AZ-StateMachine application and open your XML file with the "File > Open" menu.
* Press "Generate files".
* You can verify your FSM graph inside the application. A .png file representing this graph is also copy Generated_doc sub-directory of the XML directory.
* .h et .c files template for your new FSM are generated in a Generated_src sub-directory of the XML directory. Copy these files in your program source and fill its functions.
* Use the finite_state_machine_engine.h functions to deal with your new FSM. Use `InitStateMachine()` to init it and `AdvanceStateMachine()` to run it.

### 3.2 Details

#### 3.2.1 FSM definition (XML file)
The FSM are defined in a XML file (see Examples directory).
##### `<xazfsm>`
This XML file must begin with `<xazfsm>` and end with `</xazfsm>`.

##### `<title>`
Define the FSM title. It will display as this on top of the graph. It will be converted in lowercase with underscores to name your .h .c files and your FSM global variable (with an added "g_" prefix).

Example :

    <title>FSM Parameter Manager</title>
will generate fsm_parameter_manager.h and fsm_parameter_manager.c template files.

Your FSM global variable will be :

    fsm_description_t g_fsm_parameter_manager;

##### `<state>`
Define a new state.
* `name="YOUR_STATE_NAME"` : State name. There's no character verification or replacement (not yet). So be carefull to not use special character (except underscores). This name will be used in a enum (prefixed with "ST_") so it is a good practice to name it in uppercase.
* (optional) `init="true"` : If "true" this state will be the default entry of the state machine (state execute when you call InitStateMachine() ).
* (optional) `error="true"` : The FSM will entry in this state in the improbable case it was in an undefined state. It never happened on my exeperience.
* (optional) `<entryfct>` : Function run when entering in the state. Name it as a C function (no special character except underscores).
* (optional) `<duringfct>` : Function run each time the machine is called as long as it is still in this state. Name it as a C function (no special character except underscores).

##### `<transition>`
Define a transition between two states.
* `from="YOUR_STATE_NAME"` : Departure state name, as named with the `<state>` tag.
* `to="YOUR_STATE_NAME"` : Arrival state name, as named with the `<state>` tag.
* `condition="CONDITION_FUNC"` : Function returning the boolean condition to go from departure state to arrival state. Name it as a C function (no special character except underscores). You can use "AlwaysTrue" if you want a condition that is always true.
* (optional) `action="ACTION_FUNC"` : Function run if CONDITION_FUNC return TRUE and before going in the arrival state. Name it as a C function (no special character except underscores).

#### 3.2.2 FSM Generator
* Open AZ-StateMachine application and open your XML file with the "File > Open" menu.
* Press "Generate files".
* You can verify your FSM graph inside the application. A .png file representing this graph is also copy in Generated_doc sub-directory of the XML directory.

#### 3.2.3 Generated template C files
* .h et .c files template for your new FSM are generated in a Generated_src sub-directory of the XML directory. Copy these files in your program source and fill its functions.

\[TO BE COMPLETED\]

#### 3.2.4 Run the FSM in your program
Make sure you have copy finite_state_machine_engine.h, finite_state_machine_engine.c and your generated .h .c FSM templates.

finite_state_machine_engine.h functions are used to access to your FSM. Most important are `InitStateMachine()` to init the FSM and `AdvanceStateMachine()` to run it.

`InitStateMachine()` initialize the FSM with the "init" states (see "FSM definition (XML File)" chapter) and execute its "entry function".

`AdvanceStateMachine()` do in this order :
  * Search a possible transition with a fulfilled condition
  * If no transition found:
    * Execute the "during function" of the actual state.
  * If there's a transition with a fulfilled condition (just the 1st one found is treated):
    * Execute the "action" function of this transition
    * Enter in the next state and execute its "entry function".

Depending on your application, `AdvanceStateMachine()` can be called in a periodic loop, in the main loop or just when there are specific events.

With `GetCurrentStateId()` you can retrieve the current state.

### 3.3 Example

The Examples directory contains a [baby.azfsm.xml](Examples/baby.azfsm.xml) file.

Open it with AZ-StateMachine application and generate files.

![FSM Baby screenshot](Screenshots/fsm_baby_win10_screenshot.png "FSM Baby screenshot")

The Generaotor will generate [fsm_baby.h](Examples/Generated_src/fsm_baby.h) and [fsm_baby.c](Examples/Generated_src/fsm_baby.c) templates in a Generated_src sub-directory of the Examples directory. Copy them into your project sources.

A .png file representing the FSM graph is also copied in Generated_doc sub-directory of the XML directory. It is usefull in order to include it in a documentation.

In the inatialization phases of your application, add:

    InitStateMachine(&g_fsm_baby);

In a loop or an event, add:

    AdvanceStateMachine(&g_fsm_baby);
    
fsm_baby.c is just a template, functions has not been filled, so this example do nothing except endlessly turn inside the state machine, all conditions being allways true.

## 4. Other
### 4.1 Footprint
The footprint has been tested on a 8 bits MCU: Renesas R8C (R5F21238).
Here are the results (in Bytes) for the Engine v1.1 and a FSM generated by Generator v1.3.0.

|                             |DATA       |ROMDATA        |CODE   |
|:--------------------------- |:---------:|:-------------:|:-----:|
| Engine                      |           |               | 696   |
| 1 empty state machine       | 12        |  24           |       |
| 1 state                     |           |  10           |       |
| 1 entry function            |           |               | 2     |
| 1 during function           |           |               | 2     |
| 1 transition                |           |  12           |       |
| 1 condition in a transition |           |               | 4     |
| 1 action in a transition    |           |               | 2     |

