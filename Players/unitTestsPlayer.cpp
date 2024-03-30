#include "Player.h"
#include <string>
#include <memory>
#include <iostream>
#include <vector>
using std::string;
using std::unique_ptr;
using std::vector;


void testConstruction(){
    std::cout << "Testing Construction:\n";
    Responsible responsible;
    RiskTaking risktaking;

    string name = "Mushi";
    unique_ptr<Warrior> mushiRes(new Warrior(name , responsible));
    std::cout << mushiRes->getDescription() << "\n";
    unique_ptr<Warrior> mushiRis(new Warrior(name , risktaking));
    std::cout << mushiRis->getDescription() << "\n";

    name = "Falafel";
    unique_ptr<Sorcerer> falafelRes(new Sorcerer(name , responsible));
    std::cout << falafelRes->getDescription() << "\n";
    unique_ptr<Sorcerer> falafelRis(new Sorcerer(name , risktaking));
    std::cout << falafelRis->getDescription() << "\n";
}

void testVector(){
    std::cout << "testing Vector:\n";

    vector<shared_ptr<Player>> players;

    string tempName = "Mushi";
    Responsible responsible;

    shared_ptr<Warrior> mushi( new Warrior(tempName, responsible) );
    players.push_back(mushi);

    tempName = "Falafel";
    shared_ptr<Sorcerer> falafel( new Sorcerer(tempName, responsible));
    players.push_back(falafel);

    shared_ptr<Player> mushon = mushi->clone();
    players.push_back(mushon);

    std::cout << "The players are:\n";

    int i=1;
    for(shared_ptr<Player> player : players){
        std::cout << i << ": " << player->getDescription() << "\n";
        i++;
    }

    std::cout << "taking second mushi out for a walk\n";
    players.pop_back();

    std::cout << "The players are:\n";

    for(shared_ptr<Player> player : players){
        std::cout << i << ": " << player->getDescription() << "\n";
    }
    
}

void testSolar(shared_ptr<Player> player){
   
    std::cout << "testing solar ecplipse:\n";

    std::cout << "current stats: " << player -> getDescription() << "\n";

    player -> applyEclipse();

    std::cout << "after eclipse: " << player -> getDescription() << "\n";

}

void testPotions(shared_ptr<Player> player){
    std::cout << "testing potions:\n";

    std::cout << "current stats: " << player -> getDescription() << "\n";

    player -> buyPotions();

    std::cout << "after potions: " << player -> getDescription() << "\n";
}

/*void testNameIsLegal(){
    std::cout << "NameIsLegal test:\n";
    string string1 = "mkljknjldhnfjhgfjhgfjhfjhgfjhgfjhgfjhgfjhfjhgf";
    if (nameIsLegal(string1)) {
        std::cout << "length check failed\n";
    }

    string string2 = "j klp2";
    string string3 = "kGhjk";
    if(nameIsLegal(string2) || !nameIsLegal(string3)) {
        std::cout << "letter check failed\n";
    }
}*/

int main(){

    string tempName = "Mushi";
    RiskTaking risktaking;
    Responsible responsible;

    shared_ptr<Warrior> mushiResponsible( new Warrior(tempName, responsible) );
    shared_ptr<Warrior> mushiRisk( new Warrior(tempName, risktaking) );

    tempName = "Falafel";
    shared_ptr<Sorcerer> falafelResponsible( new Sorcerer(tempName, responsible) );
    shared_ptr<Sorcerer> falafelRisk( new Sorcerer(tempName, risktaking) );


    testConstruction();
    std::cout << "\n\n-----------------------------";

    testVector();
    std::cout << "\n\n-----------------------------";

    testSolar(mushiRisk);
    std::cout << "\n\n-----------------------------";

    testSolar(falafelRisk);
    std::cout << "\n\n-----------------------------";

    testPotions(mushiRisk);
    std::cout << "\n\n-----------------------------";

    testPotions(falafelResponsible);
    std::cout << "\n\n-----------------------------";


    //testNameIsLegal();
    return 0;
}