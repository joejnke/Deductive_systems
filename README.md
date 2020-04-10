# Deductive Systems in Wumpus World Game
This is a c++ implementation of the well known game, wumpus world, and an intelligent agent that play the game by its own to win it.
Description about the game and the implementation plan is provided below.

# Intelligent Agent Description
[_source_](https://github.com//Bemhreth/intelligent-agent/blob/master/README.md#intelligent-agent-desciption)

## Definitions

- __Intelligent Agent__:  an agent that perceives and acts in the environment it lives in.
- __Agent function__: a procedure that maps a perception to an action.
- __Agent program__: actual implementation of the agent function.
- __Perception history__: chronologically ordered list of the history that the agent perceived. 

## Types of Agents:

- __Simple reflex agent__: percept and sends corresponding action. For every perception, it has an action mapped to it.
- __Model-based (knowledge-based) reflex agent__
  - __Model__: the general knowledge of things and rules in an environment (world).
  - __Agent’s internal state__: representation of the current state based on perception history and previous actions.
  - __Deductive system__: the agent function must contain a deductive mechanizable procedure. It is the system that uses the model and the agent’s internal state

- __Learning agent__: an agent that can extract knowledge or model from an environment. It can find a new axiom from the environment.

# Wumpus World Game

According to [this](https://www.javatpoint.com/the-wumpus-world-in-artificial-intelligence) article,
the Wumpus world is a simple world example to illustrate the worth of a knowledge-based agent and to represent knowledge 
representation. It was inspired by a video game **Hunt the Wumpus** by Gregory Yob in 1973.

The Wumpus world is a cave which has 4X4 rooms connected with passageways. So there are total of 16 rooms which are connected 
with each other. We have a knowledge-based agent who will go forward in this world. The cave has a room with a beast which is 
called _**Wumpus**_, who eats anyone who enters the room. The Wumpus can be shot by the agent, but the agent has a single arrow. In 
the Wumpus world, there are 3 _**Pits**_, rooms which are bottomless, and if agent falls in Pits, then he will be stuck there 
forever. The exciting thing with this cave is that in one room there is a possibility of finding a heap of _**gold**_. So the agent 
goal is to find the gold and climb out of the cave without fallen into Pits or eaten by Wumpus. The agent will get a reward 
if he comes out with gold, and he will get a penalty if eaten by Wumpus or falls in to a pit.

The **World** will be governed based on the following _rules_:
- Rooms adjacent to wumpus stench.
- Rooms adjacent to pits breeze.
- Rooms with Gold glitter.
- The agent has one arrow.
- If the agent shoots an arrow into the room the wumpus is in, then the Wumpus dies.
- If wumpus and agent are in the same room wumpus will kill the agent. 
- There is one wumpus, 3 pits and 1 gold kept at randomly choosen rooms. The rooms at grid location of (1, 2) and
(2, 1) are initialy empty and the agent is in the room at grid location (1,1).

[_here_](https://github.com/joejnke/Deductive_systems/blob/master/wumpus_world/components/README.md) _you can find the implemention plan._