## Wumpus world
The project is organized using the following classes:

1. **room** : an object that will have set of truth values telling the knowledge about the room.

2. **world** : an object representing the whole grid and contents in the grid.

    *Variables*:

        grid // 4X4 grid of room objects
        model
        wumpus_life_status
        agent_status // holds health, remaining arrow and current room informations.
    
    *Methods*:

        get_model() // return the model, and will be used by both the UI and the agent
        get_room(room_id) // return the room at the given id and will be accesible only for the UI
        kill_at(room_id) // attempts to kill wumpus at the given room id if it exists. Used by the agent
        get_grid() // return the grid with all the informations. Only used by UI
        get_wumpus_status() // return wumpus life status. Only used by UI
        get_agent_status() // return agent related informations. Only used by UI
        grid_init() // initialize the grid according to the specifications.

3. **Agent** : an object to represent the intlegent player

    *Variables*:
    
        perception_history
        agent_status // life, remaining arrow and current room
        grid // to depict and fill own version of the world grid
        model // to hold copy of the model in the world
        ok_rooms // for holding stack of safe rooms but unvisited rooms.

    *Methods*:
    
        get_agent_status()
        program_evaluator(premises, conclusion)
        get_perception()
        shoot(room_id)
        go_to(room_id)
        rule_match()
        play()

4. **UI**: user interface

    *descriptions can be found in the header files*
5. **Main**: the app.cpp file that brings all the parts in to the simulated world.

    Initialize ```World```

    Initialize ```Agent```

    Initialize ```UI``` using the ```world``` and ```agent`` as parameters for the constructor so that the user interface can get all the neccessary information needed to display.

Note: most of the implementation plans are on paper and will be soon included into the README file and will be drafted in the header files as done for ```room``` and ```UI```