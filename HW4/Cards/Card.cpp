#include "Card.h"
#include "utilities.h"


//Encounter implementations
void Encounter::operator+=(const Encounter& obj)
{
    m_CombatPower+=obj.m_CombatPower;
    m_Loot+=obj.m_Loot;
    m_Damage+=obj.m_Damage;
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
std::string Monster::getDescription() const
{
    std::string description = m_Name + " (power " + std::to_string(m_CombatPower) +
                              ", loot " + std::to_string(m_Loot) +
                              ", damage " + std::to_string(m_Damage) + ")";
    return description;
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
    m_CombatPower = 0;
    m_Loot = 0;
    m_Damage = 0;
}

int Gang::getSize() const
{
    return m_size;
} 
Gang::Gang(const Gang& gang){
    m_size = gang.getSize();
    m_CombatPower = gang.getCombatPower();
    m_Loot = gang.getLoot();
    m_Damage = gang.getDamage();
}

std::string Gang::getDescription() const
{
    std::string description = "Gang of " + std::to_string(m_size) + " members" +
                              " (power " + std::to_string(m_CombatPower) +
                              ", loot " + std::to_string(m_Loot) +
                              ", damage " + std::to_string(m_Damage) + ")";
    return description;
}


// Event implementations
std::string Event::getDescription() const
{
    return m_Name;
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
