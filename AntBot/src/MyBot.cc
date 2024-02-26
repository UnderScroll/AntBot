#include "Bot.h"

using namespace std;

#include "Blackboard/Blackboard.h"

/*
    This program will play a single game of Ants while communicating with
    the engine via standard input and output.

    The function "makeMoves()" in Bot.cc is where it makes the moves
    each turn and is probably the best place to start exploring. You are
    allowed to edit any part of any of the files, remove them, or add your
    own, provided you continue conforming to the input and output format
    outlined on the specifications page at:
        http://www.ai-contest.com
*/
int main(int argc, char *argv[])
{

    Job job1{};
    job1.priority = 1;
    job1.id = 0;
    Job job5{};
    job5.priority = 5;
    job5.id = 1;
    Job job2{};
    job2.priority = 2;
    job2.id = 2;
    Job job3{};
    job3.priority = 3;
    job3.id = 3;
    Job job0{};
    job0.priority = 0;
    job0.id = 4;

    
    Blackboard::addJob(job1);
    std::cout << "=====0=====" << std::endl;
    std::cout << Blackboard::getInstance() << std::endl;
    Blackboard::addJob(job5);
    std::cout << "=====1=====" << std::endl;
    std::cout << Blackboard::getInstance() << std::endl;
    Blackboard::addJob(job2);
    std::cout << "=====2=====" << std::endl;
    std::cout << Blackboard::getInstance() << std::endl;
    Blackboard::addJob(job3);
    std::cout << "=====3=====" << std::endl;
    std::cout << Blackboard::getInstance() << std::endl;
    Blackboard::addJob(job0);
    std::cout << "=====4=====" << std::endl;
    std::cout << Blackboard::getInstance() << std::endl;
    std::cout << "=====5=====" << std::endl;
    Blackboard::removeJob(job1);
    std::cout << Blackboard::getInstance() << std::endl;
    std::cout << "=====6=====" << std::endl;
    Blackboard::updateJobPriority(job5, 1);
    std::cout << Blackboard::getInstance() << std::endl;

    /*
    cout.sync_with_stdio(0); //this line makes your bot faster

    Bot bot;
    bot.playGame();
    */
    

    return 0;
}
