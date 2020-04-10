# Implementation plan

## Plan overview

The implementation plan of this project is composed of five major parts.
- Room
- World
- Agent
- User interface (UI)
- Main app
    

The **_Room_** is an object which serves as a container for the knowledge that a single room have in the world.
The state of every knowledge is accessable and also modifiable via the accessors provided.

The **_World_** is a bigger container. It builds up the game world from bunch of rooms and a model that
govern the world. In addition it keeps record of information about the main participants of the game
which are the wumpus and the agent.
The bunch of rooms are kept inside a container named grid. The grid keeps rooms with an ID (pair of
row and column number) assigned for each of the rooms. The model is also kept in another container representing
every statment in logical syllogism format. The premis and conclusion of every statement in the model is
accessable. The status of the wumpus and the agent are each stored in separate container. They are accessable
to the user interface and will be used as a source for what will be displayed about the wumpus and the agent on
the user interface.

The **_Agent_** is another object that will build up intelligent game player. The ultimate goal of this intelligent
player is to get the gold containd in the world.
The agent contains the model by which the world is governed. In addition it have it's own version of rooms grid. It
uses its intelligence to fill up this grid and have fully or partialy complete knowledge about what is contained in
the world's grid. Then it can easily avoid pits, get the gold and also kill the wumpus. If it achive the goal, even
before fully completing the grid, the game ends with the agent being the winner.
The Agent also keeps record of the status of itself and the wumpus.
The intelligence of the agent is built from two components and another third component integrates these two parts to
work together. The first component, named "program_evaluator", uses the model and the perception history of the agent
to deduce knowledge about nearby rooms and then the second component, named "rule_match", uses these deduced knowledge
to make decision on the agent's next action. The last component, named "play", is a facilitator for the two components.
It does what needs to be done before and after the execution of each of the two components. Generally it defines
the overall iterative sequence of steps taken by the agent during the game play.

The **_UI_** (user interface) is an object intended to visualize the whole game session. It displays all the knowledge
contained in each of the rooms of the world's grid. In addition it displays the agent's life status, current room,
remaining arrow and the chronologically ordered perception history. It also displays the status of the wumpus and
the information contained in the current room the agent is found in. 
It keeps updating the displayed information every time the agent performs an action. All the information displayed
is obtained from the world and only the signal that indicate the agent has performed an action will be triggered by
the agent and the user interface uses this signal to start updating displayed information.

The **_Main app_** is the place where all the above parts will be initialized and linked together to setup the game
and start the play.


## Detailed plan

Project major parts:

1. **Room**: A knowledge container to implement the concept of a single room in a world's grid.

    It will keep record of every knowledge(state) of a room.

    It will be implemented as a c++ class and will have:
   
    - Attributes:
        - knowledge
        - room_id
        - default_tv

    - Attributes description:
        - knowledge:

            Container for the knowledge(states) of a room.

            Knowledge will be represented using knowledge terms given below:
        
            - **_Pit_** => true if there is pit in the room.
            - **_Breeze_** => true if there is breeze in the room.
            - **_Wumpus_** => true if there is wumpus in the room.
            - **_Stench_** => true if the room stenchs.
            - **_Visited_** => true if the room is already visited.
            - **_Glitter_** => true if there is gold in the room.

            Can be implemented using c++ map datastructure. Knowledge terms will be used as key and corresponding
            truth-values will be used as value in the map. Truth-values are the integers -1, 0 and 1, where:
            - **-1** implies undetermined (not yet set) truth-value
            - **0** implies the boolean "false"
            - **1** implies the boolean "true"
            
            > Note: The reason to use integers is because of the need to set default value during room object initialization.
            Setting initial value to "true" or "false" is not advisable because the values make sense.
            e.g.: setting Wumpus to "true" by default will initialize every new room having a wumpus.

        - room_id:

            A pair of ```int``` that inidicate the position of the ```room``` in the grid as ```(x,y)``` where ```x``` is the horizontal 
            distance and ```y``` is the vertical distance. 

            The coordinates start with (1, 1) at the left bottom corner and counting increases verticaly up and horizontaly to
            the right.
        
        - default_tv:

            This attribute represents the default value for initializing ```knowledge_terms``` of a ```room```. 

            Has a value of ```-1```, which represents that the ```knowledge_term``` is yet not assigned to a ```true``` or ```false``` value.

    - Constructor:
        - room()
        - room(room_id)
    
    - Constructor description:
        - room():
            
            Initialize ```default_tv``` to **-1** and all the six knowledge terms to this default value of **-1**.
        
        - room(room_id):

            Initialize the _```room_id```_ attribute to the ```room_id``` input parameter and initialize all the six 
            knowledge terms to a default value of **-1**.

    - Accessors:
        - get_truth_value(knowledge_term)
        - set_truth_value(knowledge_term, tv)
        - get_adjacents()
        - get_room_id()
        - get_knowledge()

    - Accessors description:
        - get_truth_value(knowledge_term):

            Getter that use knowledge_term as key to return the truth value of the knowledge_term from the knowledge attribute.

            It maps truth-value(the integers -1, 0 or 1) of the given knowledge_term to the
            corresponding values then return:
            - **NaN** if -1
            - the boolean **false** if 0
            - the boolean **true** if 1

            > Note: We might use **_-1_**, **_0_**, **_1_** as is with out the need to map them to **_NaN_**, **_False_**, **_True_**.
            
        - set_truth_value(knowledge_term, tv):

            Sets the given ```knowledge_term``` to ```true``` or ```false``` as given by the ```tv``` parameter.

            It maps the boolean ```tv``` to the corresponding int value.
        
        - get_adjacents():
            
            Return list of valid adjacent room ids.

        - get_room_id()

            Return the ```room_id``` attribute.

        - get_knowledge()

            Return the ```knowledge``` attribute.

2. **World**: The actual game world. It will contain the environment and all the components that will build up
   the game world.

    It will be implemented as a c++ class and will have:

    - Attributes:
        - model
        - grid
        - agent_status
        - wumpus_status

    - Attributes description:
        - model:
        
            Holds every statment of the world's model in a logical syllogism format. (how?)
            
            There will be seven statments which are listed above in the governing rules of the world.

            It has to have a way to access premis and conclusion of every statment.

        - grid:

            A 4X4 grid of room objects.
            
            It can be implemented using 2D array of room objects.
            
        - agent_status:

            Holds the agent's  ```living```, ```current_room_id```, ```remaining_arrow``` and ```found_gold``` information.
            
            It can be implemented using c++ map.

            e.g: ```map<string, int, string, bool, string, pair<int>, string, bool>```

        - wumpus_status:

            Holds the wumpus' ```living``` and ```room_id``` information.
            
            It can be implemented using c++ map.

            e.g: ```map<string, bool, string, pair<int>>```

    - Constructor:
        - world()

    - Constructor description:
        - world():

            Initialize the world by setting all the attributes to their corresponding values.

    - Accessors:
        - grid_init()
        - get_model()
        - get_grid()
        - get_room(room_id)
        - get_agent_status()
        - get_wumpus_status()
        - kill_wumpus_at(room_id)

    - Accessors description:
        - grid_init():

            Initialize the ```grid``` with random knowledge set to the rooms.

            It has to place the wumpus, the 3 pits and the gold at randomly selected rooms and the agent at room (1,1). Then it will set states of the other rooms based on the random setup. In addition, rooms at (1,2) and (2,1) will contain neither wumpus nor pit.

        - get_model():

            Returns copy of the ```model``` attribute.

        - get_grid():

            Return copy of the ```grid``` attribute. 
            
            It first checks the type of the object calling this function. It only responds to calls from the user interface object and have to deny calls made from the agent object.

        - get_room(room_id):

            Return copy of the room object at the given ```room_id``` from the ```grid```.
            
            It first cross checks validity of this request before returning value. A request is valid if the room given by the ```room_id``` and ```agent_status.current_room``` are neighbours (i.e.: the agent is making this request after moving to a neighbouring room, which is a valid move.)

            It's assumed that the agent calls this function after it moved to the room with the specified ```room_id```. So, this function will also update the ```agent_status.current_room``` to ```room_id```.
            
        - get_agent_status():

            Return copy of the ```agent_status``` attribute.

            It will be used by the user interface object.

            > Note: the function doesn't need to check the type of the caller since the information disclosed is not sensitive.

        - get_wumpus_status():

            Return copy of the ```wumpus_status``` attribute.

            It will be used by the user interface object.

            > Note: the function doesn't need to check the type of the caller since the information disclosed is not sensitive.

        - kill_wumpus_at(room_id):

            Kills the wumpus if it is found in the given ```room_id``` and update ```wumpus_status``` and ```agent_status```.
            
            Returns **true** if the wumpus is found and killed or **false** if the wumpus is not found in the given room. 

            It will be used by the agent object.

            Killing is done based on this _pseudocode_:
            ```
                wumpus_room = grid.get_room(room_id) // get the room object at room_id
                
                // if there is wumpus in the room and the agent has arrow to use
                if(wumpus_room.get(wumpus) and agent_status.remaining_arrow>0) { 
                    
                    wumpus_room.set(wumpus, 0); // change the truth-value to "false"

                    wumpus_status.living = false; // record that the wumpus is dead
                    
                    agent_status.remaining_arrow--; // decrement the remaining_arrow

                    return true
                }
                
                else { // if there is no wumpus in the room

                    agent_status.remaining_arrow--; // decrement the remaining_arrow
                
                    return false
                }
            ```
 
3. **Agent**: The intelligent player that move around in the world.

    Its aim is to get the gold while escaping from being eaten by the wumpus and if possible kill it. In addition it will 
    also make decision to avoid falling into a pit. It will continiously move around in the world then deduce and fill in all 
    the knowledge contained in the grid of the world in to it's own version of the grid until it finds the gold.

    It will be implemented as a c++ class and will have:

    - Attributes:
        - model
        - grid
        - agent_status
        - wumpus_status
        - perception_history
        - ok_rooms

    - Attributes description:
        - model:

            copy of the world's model attribute.

        - grid:
        
            A 4X4 grid of room objects. Can be implemented using 2D array of room objects. It'll be filled in using the 
            decisions the agent make. The aim is to fill it up with same knowledge as the grid of the world.
            
        - agent_status:
        
            Holds the agent's ```remaining_arrow```, ```living```, ```current_room_id```, ```facing_toward``` and ```found_gold``` information.

            It can be implemented using c++ map.

            e.g: ```map<string, int, string, bool, string, pair<int>, string, string, string, bool>```

        - wumpus_status:
          
            Holds the wumpus' living and room_id. 
            
            It can be implemented using c++ map.
            
            e.g: ```map<string, bool, string, pair<int>>```

        - perception_history:
          
            Holds all the percived information by the agent in a sequential order. (i.e.: it's list of visited rooms)

            It can be implemented using stack.

        - ok_rooms:
          
            Queue of safe rooms to go to.

            It can be implemented using c++ queue. It is initially filled with rooms of id (1,2) and (2,1) since they are the 
            first possible and known safe rooms to go to in the next step.

    - Constructor:
        - agent(world wumpusArena)

    - Constructor description:
        - agent(world wumpusArena):

            Initialize the agent by setting all the attributes to their coresponding values.

    - Accessors:
        - get_perception_history()

    - Accessors description:
        - get_perception_history():
          
            Returns copy of the perception_history attribute.
        
    - Sensors:
        - does_stench(room_id)
        - does_glitter(room_id)
        - has_breeze(room_id)
        - does_bump(room_id)
        - heared_scream()

    - Sensors description:
        - does_stench(room_id):
          
            Returns the truth-value of the ```stench``` knowledge term of the room at ```room_id``` in the ```grid```.

        - does_glitter(room_id):
          
            Returns the truth-value of the ```Glitter``` knowledge term of the room at ```room_id``` in the ```grid```.

        - has_breeze(room_id):
          
            Returns the truth-value of the ```Breeze``` knowledge term of the room at ```room_id``` in the ```grid```.

        - does_bump(room_id):
          
            Returns ```true``` if ```room_id``` is not a valid room id
            
            i.e:
            ```
            let room_id = (x,y) 
                room_id is valid if 0 < x < 5 and 0 < y < 5
                room_id is invalid if x < 1 or x > 4 or y < 1 or y > 4)
            ```

        - heared_scream():
           
            Returns ```true``` if wumpus is dead by checking the record in the ```wumpus_status``` attribute.

    - Actuators:
        - go_to(room_id)
        - grab(room_id)
        - move_forward()
        - shoot(room_id)
        - turn_left()
        - turn_right()
        - signal_to_UI()

    > NOTE: ```grab(room_id)```, ```move_forward()```, ```turn_left()```, ```turn_right()``` might be redundant with ```go_to(room_id)```

    - Actuators description:
        - go_to(room_id):
            
            Determine and execute sequence of actions inorder to go to the given room and then update states accordingly.

            It will update:
            - Truth-values of the rooms visited and their neighbours during execution
                of the actions sequence.
            - ```agent_status``` and ```wumpus_status```.

            e.g.: ```[turn_left(), move_forward()]```

            > Alternatively, assuming ```grab(room_id)```, ```move_forward()```, ```turn_left()```, ```turn_right()``` are redundant and replaced by ```go_to(room_id)```. The following approach can be used.

            ```go_to(room_id)``` moves the agnet to the given room. But, first it checks if the move is valid (i.e.: the 
            agent can move from current room to the room given by ```room_id```) and then if it's valid, move to the room and 
            update agent's current room, else it keeps the agent in the current room.

        - grab(room_id):
          
            Use ```go_to(room_id)``` to go to the room and then grab gold if there is one in the room. Then update states 
            accordingly.
            
            It will update:
            - Truth-values of the room the gold is found in (i.e.: set ```Glitter``` to ```false``` since its already grabed).
            - ```agent_status```.

        - move_forward():
            
            Move too the next room in the direction the agent is facing toward.
        
        - shoot(room_id):
            
            Calls the ```world.kill_wumpus_at(room_id)``` function and update states accordingly.

            It will update:
            - Truth-values of the room the wumpus was in and the neighbouring rooms.
            - ```agent_status``` and ```wumpus_status```.

        - turn_left():
          
            Change the ```facing_toward``` value of the ```agent_status``` one step in counter clockwise direction.

        - turn_right():
          
            Change the ```facing_toward``` value of the ```agent_status``` one step in clockwise direction.

        - signal_to_UI():
          
            Send out signal to the user interface.

            This is requiered because we plan to run the ```user interface``` and the ```agent``` in separate threads and we 
            need to let ```user interface``` update the graphics whenever the ```agent``` performs an action. So the UI knows 
            that the agent has performed an action when it receives this signal.

    - Deduction components:
        - rule_match()        
        - program_evaluator()
        - play()

    - Deduction components:
        - rule_match():
          
            Determine and execute action commands based on the current knowledge of the agent.
            
            Implemented based on the _pseudocode_ below:

            ```
                for (each adjacent room) {
                    if (wumpus is in the room) {
                        shoot(room_id)
                    }

                    if (room glitters) {
                        grab(room_id)
                    }

                    if (room is safe) {
                        ok_rooms.push(room)
                    }

                    go_to(ok_rooms.pop())
                }
            ```

        - program_evaluator():
            
            Make deduction about unvisited neighbouring rooms of the current room the agent is in.

            It will use the ```perception history```, ```model``` and the ```current room``` of the agent. Finally it       
            updates the knowledge in every unvisited neighbouring rooms accordingly.
            
            The purpose of deduction is to determine truth-value for an undetermined state of a room. It will be done by 
            iterating over every undetermined state of every unvisited neighbouring room.

            Deduction inputs(recipies) at every iteration:
            - Premis: perception_history
            - Conclusion to prove: Undetermined state of a room

        - play():
          
            Defines the steps that the agent will follow in playing the game.

            It performs the following steps iteratively as in the given below sequence:
            - **PERCIVE**.
            - **DEDUCE** knowledge(truth-values) about the states of unvisited neighbouring rooms.
            - **UPDATE** the states of unvisited neighbouring rooms based on the deduction.
            - **DETERMINE** and **EXECUTE** rule based actions.

            _pseudocode_:
            ```
                while (not(agent.found_gold)) { // until the agent finds the gold

                    // percive all the knowledge in the current room and add the room to perception history
                    perception_history.push(world.get_room(agent.current_room_id))

                    // make deduction on knowledge of unvisited neighbouring rooms to agent.current_room_id
                    // and update truth-values of the unvisited neighbouring rooms.
                    program_evaluator()

                    // Determine and execute action based on the knowledge the agent have currently
                    rule_match()
                    
                    //send signal to the user interface
                    signal_to_UI()
                }
            ```

4. **UI**: Terminal based user interface that display the simulated wumpus world game.

    The display includes:
    - grid of the rooms at top-center
    - Agent perception history at right side
    - Current room info at left side
    - wumpus life status and agent status (life and remaining arrow) bottom-center

    It will be implemented as a c++ class and will have:

    - Constructor:
        - UI(world wumpusArena, agent AIplayer)
    
    - Constructor description:
        - UI(world wumpusArena, agent AIplayer): 
         
            Initializ UI with basic informations obtained from the input parameters using their corresponding accessors to 
            acess all the informations to be displayed.

    - Method:
        - start_UI()

    - Method description:
        - start_UI():
            
            Initialize and update the user interface contents. Then trigger the agent to start playing by calling  
            ```AIplayer.play()```.

            The UI is Initialized in a separate thread so that the UI will be updated every time the agent performs an action 
            using the signal sent by the agent after every action.

5. **Main app**: executable file. 

    All the above four components will be integrated and run from the main function of this source code file.
    
    Steps:
    - Initialize a world instance.

    e.g.: ```world wumpusArena = world()```

    - Initialize an agent instance.

    e.g.: ```agent AIplayer = agent()```

    - Initialize a UI instance using the world and agent instances initialized.
    
    e.g.: ```UI gameInterface = UI(wumpusArena, AIplayer)```

    - start the game by starting the UI.
    
    e.g.: ````gameInterface.start_UI()````

## Major parts relationship:

 1. **World** and **Agent**:

    The ```wrold``` contains basic status information (life status, current room and remaining arrow) about the agent. These 
    information are initially set to default and known values. But then will be updated when the ```agent``` makes call to ```world```'s functions.
        
    ```World``` functoins accessable to ```agent``` and information obtained(exchanged) during function call:

    - get_model():

        ```Agent``` obtains:
            
        - copy of the model in the world.
    
    - get_room(room_id):

        ```Agent``` obtains:
            
        * copy of the room object at the given room_id.
        
        ```World``` obtains:
        
        * the current room where the agent is in.
    
    - kill_wumpus_at(room_id):
        
        ```Agent``` obtains:
        
        * know if kill was successfull
        
        ```World``` obtains:
        
        * knows that the agent has used one arrow and will decrement agent's remaining_arrow.

 2. **World** and **UI**:
 
    ```World``` functions accessable to ```UI``` and information obtained(exchanged) during function call:
    
    - get_grid():

        ```UI``` obtains:
        
        * copy of the grid of rooms in the world.
    
    - get_room(room_id):
        
        ```UI``` obtains:
        
        * copy of the room object at the given room_id.
    
    - get_agent_status():
        
        ```UI``` obtains:
        
        * agent's life, current room and remaining arrow information.

    - get_wumpus_status():
        
        ```UI``` obtains:
        
        * wumpus' life status.

 3. **Agent** and **UI**:

    ```Agent``` functoins accessable to ```UI``` and information obtained(exchanged) during function call:
    - play():

        ```UI``` obtains:
    
        * access to make the agent start playing.
    
    - get_perception_history():
    
        ```UI``` obtains:
    
        * copy of agent's perception history.
    
    - signal_to_UI():
    
        ```UI``` obtains:
    
        * signal to start updating the displayed information on the user interface.
        
## TODO

- Plan ```program_evaluator()``` implementation in detail.
