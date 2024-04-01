#include "Card.h"
#include "utilities.h"


//Encounter implementations
void Encounter::operator+=(const Encounter& obj)
{
    m_CombatPower+=obj.m_CombatPower;
    m_Loot+=obj.m_Loot;
    m_Damage+=obj.m_Damage;
}

void Encounter::reset()
{
    m_CombatPower = 0;
    m_Loot = 0;
    m_Damage = 0;
}

void Encounter::activate(Player& player)
{
    if(player.getAttackStrength()>m_CombatPower) //the player is stronger than the monster/Gang
    {
        //The player wins - gets a level up and the loot
        player.levelUp();
        player.addCoins(m_Loot);
        printTurnOutcome(getEncounterWonMessage(player,m_Loot));
    }
    else
    {
        //The player loses - gets a damage to its health points
        player.damage(m_Damage);
        printTurnOutcome(getEncounterLostMessage(player,m_Damage));
    }
}

int Encounter::getCombatPower() const{
    return m_CombatPower;
}


int Encounter::getLoot() const{
    return m_Loot;
}


int Encounter::getDamage() const{
    return m_Damage;
}

// Monster implementations
void Monster::getDescription()
{
    std::cout << m_Name << " (power " << m_CombatPower << ", Loot " << m_Loot << ", Damage " << m_Damage << ")" << std::endl;
}



Dragon::Dragon() {
    m_CombatPower = 17;
    m_Loot = 100;
    m_Damage = 9001;
    m_Name = "Dragon";
} 

Giant::Giant() {
    m_CombatPower = 12;
    m_Loot = 5;
    m_Damage = 25;
    m_Name = "Giant";
}

Goblin::Goblin() {
    m_CombatPower = 5;
    m_Loot = 2;
    m_Damage = 10;
    m_Name = "Goblin";
}

// Gang implementation
Gang::Gang(int size){
    m_size = size;
}

Gang::Gang(int size, const Monster& monster){
    m_size = size;
    m_CombatPower = monster.getCombatPower();
    m_Loot = monster.getLoot();
    m_Damage = monster.getDamage();
}

void Gang::getDescription()
{
    std::cout << "Gang of " << m_size << " members " << " (power " << m_CombatPower << ", Loot " << m_Loot << ", Damage " << m_Damage << ")" << std::endl;
}

// Event implementations
void Event::getDescription()
{
    std::cout << m_Name << std::endl;
}

SolarEclipse::SolarEclipse(){
    m_Name = "SolarEclipse";
}

void SolarEclipse::activate(Player& player) 
{
    player.applyEclipse(); //activates SolarEclipse's effects in accordance with the player's type
}

PotionsMerchant::PotionsMerchant(){
    m_Name = "PotionsMerchant"; 
}

void PotionsMerchant::activate(Player& player)
{
    player.buyPotions(); //activates PotionsMerchant's effects in accordance with the player's type
}
