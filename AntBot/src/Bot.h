#ifndef BOT_H_
#define BOT_H_

#include "Blackboard/Strategy.h"
#include <vector>
#include "State.h"

/*
    This struct represents your bot in the game of Ants
*/
struct Bot
{
    State state;

    std::vector<Strategy> strategies;

    Bot();

    void playGame();    //plays a single game of Ants

    void setupStrategies();
    void addExploreAnthillStrategy(const size_t& antHillIndex);
    void addAttackAnthillStrategy(const size_t& antHillIndex);
    void addAttackRegionStrategy(const size_t& regionIndex);
    void addOccupyRegionStrategy(const size_t& regionIndex);
    void makeMoves();   //makes moves for a single turn
    void endTurn();     //indicates to the engine that it has made its moves
};

#endif //BOT_H_
