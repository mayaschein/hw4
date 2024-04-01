#include "Card.h"
#include "utilities.h"


//Encounter implementations
void Encounter::operator+=(const Encounter& object)
{
    m_combatPower+=object.m_combatPower;
    m_loot+=object.m_loot;
    m_damage+=object.m_damage;
}

void Encounter::reset()
{
    m_combatPower = 0;
    m_loot = 0;
    m_damage = 0;
}

void Encounter::activate(Player& player)
{
    if(player.getAttackStrength()>m_combatPower) //the player is stronger than the monster/Gang
    {
        //The player wins - gets a level up and the loot
        player.levelUp();
        player.addCoins(m_loot);
        printTurnOutcome(getEncounterWonMessage(player, m_loot));
    }
    else
    {
        //The player loses - gets a damage to its health points
        player.damage(m_damage);
        printTurnOutcome(getEncounterLostMessage(player, m_damage));
    }
}

int Encounter::getCombatPower() const{
    return m_combatPower;
}


int Encounter::getLoot() const{
    return m_loot;
}


int Encounter::getDamage() const{
    return m_damage;
}


// Monster implementations
void Monster::getDescription() 
{
    std::cout << m_name << " (power " << m_combatPower << ", Loot " << m_loot << ", Damage " << m_damage << ")" << std::endl;
}



Dragon::Dragon() {
    m_combatPower = 17;
    m_loot = 100;
    m_damage = 9001;
    m_name = "Dragon";
} 

Giant::Giant() {
    m_combatPower = 12;
    m_loot = 5;
    m_damage = 25;
    m_name = "Giant";
}

Goblin::Goblin() {
    m_combatPower = 5;
    m_loot = 2;
    m_damage = 10;
    m_name = "Goblin";
}

// Gang implementation
Gang::Gang(int size){
    m_size = size;
}

Gang::Gang(int size, const Encounter& monster){
    m_size = size;
    m_combatPower = monster.getCombatPower();
    m_loot = monster.getLoot();
    m_damage = monster.getDamage();
}

void Gang::getDescription()
{
    std::cout << "Gang of " << m_size << " members " << " (power " << m_combatPower << ", Loot " << m_loot << ", Damage " << m_damage << ")" << std::endl;
}

// Event implementations
void Event::getDescription()
{
    std::cout << m_name << std::endl;
}

SolarEclipse::SolarEclipse(){
    m_name = "SolarEclipse";
}

void SolarEclipse::activate(Player& player) 
{
    player.applyEclipse(); //activates SolarEclipse's effects in accordance with the player's type
}

PotionsMerchant::PotionsMerchant(){
    m_name = "PotionsMerchant"; 
}

void PotionsMerchant::activate(Player& player)
{
    player.buyPotions(); //activates PotionsMerchant's effects in accordance with the player's type
}
