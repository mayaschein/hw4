#include "Player.h"
using std::string;
using std::unique_ptr;
using std::shared_ptr;

/////////// Helper Functions: ////////////////////

bool nameIsLegal(const string& name){
    if(name.length() > 15){
        return false;
    }
    for(char letter : name){
        if( !((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')) ){ // check that all chars are eng letters
            return false;
        }
    }
    return true;
}

/////////////// constructors and operators: //////////////

 Player::Player(const string &name, const Behaviour& behaviour) :
  m_name(name), m_level(1), m_force(5), m_healthPoints(100), m_coins(10), m_behaviour(behaviour.clone()) {
    if(!nameIsLegal(name)) {
        throw IllegalName();
    }
 }

 Player::Player(const Player& player) : m_name(player.m_name), m_behaviour(player.m_behaviour->clone()) {}

 Warrior::Warrior(const string &name, const Behaviour& behaviour) : Player(name, behaviour){}

 Sorcerer::Sorcerer(const string &name, const Behaviour& behaviour) : Player(name, behaviour){}






 ///////////////// clone functions: //////////////////
 
 unique_ptr<Behaviour> RiskTaking::clone() const{
    unique_ptr<Behaviour> copy(new RiskTaking);
    return copy;
 }

 unique_ptr<Behaviour> Responsible::clone() const{
    unique_ptr<Behaviour> copy(new Responsible);
    return copy;
 }

 shared_ptr<Player> Warrior::clone() const{
    shared_ptr<Player> copy(new Warrior(*this));
    return copy;
 }

 shared_ptr<Player> Sorcerer::clone() const{
    shared_ptr<Player> copy(new Sorcerer(*this));
    return copy;
 }



////////////////////////// getters: ///////////////////////


 string Player::getDescription() const{ 
    //The format is " <Name>, <Job> with <Behavior> behavior (level <Level>, force <Force>) "
    string description(getName());
    description += ", " + getType() + " with " + getBehaviour() + " behaviour (level " + std::to_string(getLevel()) 
    + ", force " +  std::to_string(getForce()) + ")";

    return description;
 }

int Player::getLevel() const{
    return m_level;
}

int Player::getForce() const{
    return m_force;
}

string Player::getName() const{
    return m_name;
}

int Player::getCoins() const{
    return m_coins;
}

int Player::getAttackStrength() const{
    return (m_force + m_level);
}

int Warrior::getAttackStrength() const{
    return (getForce()*2 + getLevel());
}

const string Player::getBehaviour() const{
    return m_behaviour->getBehaviour();
}

int Player::getHealthPoints() const{
    return m_healthPoints;
}

const string Warrior::getType() const{
    string str = "Warrior"; 
    return str;
}

const string Sorcerer::getType() const{
    string str = "Sorcerer";
    return str;
}

const string RiskTaking::getBehaviour() const{
    string str = "RiskTaking";
    return str;
}

const string Responsible::getBehaviour() const{
    string str = "Responsible";
    return str;
}



/////////// functions for changing stats: //////////

void Player::levelUp(){
    if(m_level >= 10){
        throw AboveMaxLevel();
    }
    
    ++m_level;
}

void Player::buff(int boostSize){
    if(boostSize < 0){
        throw NegativeValue();
    }

    m_force += boostSize;
}

void Player::weaken(int amount){
    if(amount < 0){
        throw NegativeValue();
    }

    m_force = (m_force > amount) ? m_force-amount : 0;
}

void Player::heal(int boostSize){
    if(boostSize < 0){
        throw NegativeValue();
    }

    m_healthPoints += boostSize;
}

void Player::damage(int decreaseSize){
    if(decreaseSize < 0){
        throw NegativeValue();
    }

    m_healthPoints = (m_healthPoints > decreaseSize) ? m_healthPoints-decreaseSize : 0;
}

 bool Player::isKnockedOut(){
   
    if(m_healthPoints == 0){
        return true;
    }

    return false;
 }

 void Player::addCoins(int amount){
    
    if(amount < 0){
       throw NegativeValue();
    }

    m_coins += amount;
 }

 bool Player::pay(int amount){
    
    if(amount < 0){
        throw NegativeValue();
    }

    if (m_coins-amount >= 0) {
        m_coins -= amount;
        return true;
    }

    else return false;
}


///////////////EVENTS//////////////

void Warrior::applyEclipse(){
    weaken(1);
}
  
void Sorcerer::applyEclipse(){
    buff(1);
}

void RiskTaking::buyPotions(Player& player) const{
    
    if(player.getHealthPoints() < 50){

        if(player.pay(5)){
            player.heal(10);
        }
    }
}

void Responsible::buyPotions(Player& player) const{
    
    while(player.getHealthPoints() < 100){
        
        if(player.pay(5)){
            player.heal(10);
        }
        
        else {
            break;
        }
    }
}

void Player::buyPotions(){
    m_behaviour->buyPotions(*this);
}
