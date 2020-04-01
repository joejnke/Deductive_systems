#include "world.hpp"


using namespace std;

World::World()
{
	pair<int, int> wumpus_room = get_wumpus_room();
	auto wumpus_initial_status = make_pari(1, wumpus_room);
	this->wumpus_status.insert(make_pair());
	grid_init();
}

void World::grid_init(){
	srand((int)time(0));
    int iter = 3;
    vector<pair<int, int>> store;      // a set of position for storing wumpus, pit , gold
    pair<int, int> agent_room_id;      // to hold the agent room_id
    pair<int, int> restricted_position; //to hold the restricted position adjcent to the agent
    agent_room_id = make_pair(1, 1);
    store.push_back(agent_room_id);
    restricted_position = make_pair(1, 2);
    store.push_back(restricted_position);
    pair<int, int> restrictedPosition2 = make_pair(2, 1);
    store.push_back(restricted_position2);
    int j = 0;
    while (store.size() < 5)
    {
        int x, y;

        for (int i = 0; i < iter; ++i)
        {

            x = rand() % size;
            rand() % 15;
            y = rand() % size;
        }
        pair<int, int> newpair = make_pair(x, y);
        if (newpair != restricted_position && newpair != agent_room_id && newpair != restricted_position2)
        {
            store.push_back(newpair);
            sort(store.begin(), store.end());
            store.erase(unique(store.begin(), store.end()), store.end());
        }
    }
    

    vector<pair<int, int>>::iterator it = store.end();
    --it;
    pair<int, int> pit3 = *it; //random position for pit
    --it;
    pair<int, int> wumpus = *it; //random position for wumpus
    --it;
    pair<int, int> pit2 = *it; //random position for pit
    --it;

    pair<int, int> gold = *it; //random position for gold
    --it;
    pair<int, int> pit1 = *it; //random position for pit

    put_wumpus(wumpus);

    put_pit(pit1);

    put_pit(pit2);

    put_pit(pit3);

    put_gold(gold);
}

map<pair<int, int>, int, int, int> World::get_agent_status(){
	return this->agent_status;
}
map<pair<int, int>, int> World::get_wumpus_status(){
	return this->wumpus_status;
}

