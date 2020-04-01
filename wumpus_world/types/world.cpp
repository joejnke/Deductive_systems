#include "world.hpp"


using namespace std;

World::World()
{
	grid_init();
	pair<int, int> wumpus_room = this->wumpus_room;
	pair<int, int> agent_room = make_pair(1, 1);
	this->wumpus_status[wumpus_room] = 1; // set wumpus room and wumpus living in that room to true
	vector<int> v;
	v.push_back(1);
	v.push_back(1);
	v.push_back(0);
	this->agent_status[agent_room] = v;  
	
}

void World::grid_init(){
	srand((int)time(0));
    int random_number ;
	vector<pair<int, int>> store;
    pair<int, int> agent_room_id;      // to hold the agent room_id
    pair<int, int> restricted_position; //to hold the restricted position adjcent to the agent
	pair<int, int> restrictedPosition2; //to hold the restricted position adjcent to the agent
    agent_room_id = make_pair(1, 1);
    restricted_position = make_pair(1, 2);
    restrictedPosition2 = make_pair(2, 1);

	room agent_initial_room(agent_room_id);
	room restricted_room (restricted_position);
	room restricted_room2 (restricted_position2);

	this->grid.push_back(agent_initial_room);
	this->grid.push_back(restricted_room);
	this->grid.push_back(restricted_room2);

    while (store.size() < 8)
    {
        int x, y;

        random_number = rand() % size;
        x = random_number + 1;
        random_number = rand() % size;
        y = random_number + 1;
        pair<int, int> newpair = make_pair(x, y);
        if (newpair != restricted_position && newpair != resticted_position2 && newpair != agent_room_id)
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

	pair< int, int> new_room_pair;
	for(pair<int, int> i : store){
		new_room_pair = make_pair(i.first, i.second);
		if (new_room_pair == pit1 || new_room_pair == pit2 || new_room_pair == pit3 || new_room_pair == wumpus || new_room_pair == gold){
			continue;
		}
		room new_room(new_room_pair);
		this->grid.push_back(new_room);
	}
    put_wumpus(wumpus);

    put_pit(pit1);

    put_pit(pit2);

    put_pit(pit3);

    put_gold(gold);
}

map<pair<int, int>, vector<int> > World::get_agent_status(){
	return this->agent_status;
}
map<pair<int, int>, int> World::get_wumpus_status(){
	return this->wumpus_status;
}
pair<int, int> World::get_wumpus_room(){
	return this->wumpus_room;
}
pair<int, int> World::get_agent_room(){
	return this->agent_room;
}
pair<int, int> World::get_gold_room(){
	return this->gold_room;
}
pair<int, int> World::get_pit_room(){
	return this->pit_room;
}

void put_pit(pair<int, int> pit){
	room pit_room(pit);
	pit_room.set_truth_value("pit", 1);
	this->grid.push_back(pit_room);
}
void put_gold(pair<int, int> gold){
	room gold_room(gold);
	gold_room.set_truth_value("glitter", 1);
	this->grid.push_back(gold_room);
}
void put_wumpus(pair<int, int> wumpus){
	room wumpus_room(wumpus);
	wumpus_room.set_truth_value("wumpus", 1);
	this->wumpus_room = wumpus;
	this->grid.push_back(wumpus_room);
}

void kill_wumpus_at(pair<int, int> room_id){
	this->wumpus_status[room_id] = 0;
}
