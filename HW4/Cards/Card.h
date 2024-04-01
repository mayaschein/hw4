#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include "Player.h"

/**
 * @brief Abstract base class for all types of cards.
 */
class Card {
public:
    /**
     * @brief Virtual function to get the description of the card.
     */
    virtual std::string getDescription() const = 0;

    /**
     * @brief Virtual function to activate the card's effect on a player.
     * @param player The player on whom the card's effect is activated.
     */
    virtual void activate(Player& player) = 0;
    virtual ~Card() = default;
};

/**
 * @brief Base class for encounter cards.
 */
class Encounter : public Card {
protected:
    int m_CombatPower;
    int m_Loot;
    int m_Damage;

public:
    /**
     * @brief Operator to combine two Encounter objects.
     * @param obj The Encounter object to combine with.
     */
    void operator+=(const Encounter& obj);

    /**
     * @brief Activate the Encounter card's effect on a player.
     * @param player The player on whom the card's effect is activated.
     */
    void activate(Player& player) override;

    /**
     * @brief Getter for the combat power of an Encounter object.
     */
    int getCombatPower() const;

    /**
     * @brief Getter for the loot of an Encounter object.
     */
    int getLoot() const;

    /**
     * @brief Getter for the damage of an Encounter object.
     */
    int getDamage() const;
};

/**
 * @brief Class representing a generic monster encounter.
 */
class Monster : public Encounter {
protected:
    std::string m_Name;

public:
    /**
     * @brief Get the description of the Monster card.
     */
    std::string getDescription() const override;
};

/**
 * @brief Class representing a Dragon monster encounter.
 */
class Dragon : public Monster {
public:
    /**
     * @brief Constructor to initialize a Dragon card.
     */
    Dragon();
};

/**
 * @brief Class representing a Giant monster encounter.
 */
class Giant : public Monster {
public:
    /**
     * @brief Constructor to initialize a Giant card.
     */
    Giant();
};

/**
 * @brief Class representing a Goblin monster encounter.
 */
class Goblin : public Monster {
public:
    /**
     * @brief Constructor to initialize a Goblin card.
     */
    Goblin();
};

/**
 * @brief Class representing a gang encounter card.
 */
class Gang : public Encounter {
private:
    int m_size;

public:
    /**
     * @brief Constructor to initialize a Gang card with a specified size.
     * @param size The size of the gang.
     */
    Gang(int size);

    /**
     * @brief Constructor to initialize a Gang card with a specified size and encounter.
     * @param size The size of the gang.
     * @param encounter The encounter to include in the gang.
     */
    
    /**
     * @brief Get the size of the gang.
     * 
     * @return The size of the gang.
     **/
    int getSize() const;

    /**
     * @brief Copy constructor for the Gang class.
     * 
     * This constructor creates a new Gang object by copying the attributes
     * of an existing Gang object.
     * 
     * @param gang The Gang object to be copied.
     */
    Gang(const Gang& gang);

    /**
     * @brief Get the description of the Gang card.
     */
    std::string getDescription() const override;
};

/**
 * @brief Base class for event cards.
 */
class Event : public Card {
protected:
    std::string m_Name;

public:
    /**
     * @brief Get the description of the Event card.
     */
    std::string getDescription() const override;
};

/**
 * @brief Class representing a Solar Eclipse event card.
 */
class SolarEclipse : public Event {
public:
    /**
     * @brief Constructor to initialize a Solar Eclipse card.
     */
    SolarEclipse();

    /**
     * @brief Activate the Solar Eclipse card's effect on a player.
     * @param player The player on whom the card's effect is activated.
     */
    void activate(Player& player) override;
};

/**
 * @brief Class representing a Potions Merchant event card.
 */
class PotionsMerchant : public Event {
public:
    /**
     * @brief Constructor to initialize a Potions Merchant card.
     */
    PotionsMerchant();

    /**
     * @brief Activate the Potions Merchant card's effect on a player.
     * @param player The player on whom the card's effect is activated.
     */
    void activate(Player& player) override;
};

#endif
