
#pragma once
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;
using std::shared_ptr;

/* LIST OF STUFF:
- BEHAVIOUR CLASS GENERAL
    VIRTUAL DISTRUCTOR V
    ALL INHERITED FUNCTIONS ARE VIRTUAL V

- RISKTAKING
    NO PROBLEMATIC ASSIGNMENTS V
    ALL FUNCTIONS DEFINED AS IN BASE CLASS v
    NOT TRYING TO ACCESS PRIVATE MEMBERS v

- RESPONSIBLE
    NO PROBLEMATIC ASSIGNMENTS V
    ALL FUNCTIONS DEFINED AS IN BASE CLASS v
    NOT TRYING TO ACCESS PRIVATE MEMBERS v


- PLAYER CLASS GENERAL
    VIRTUAL DISTRUCTOR V
    ALL INHERITING FUNCTIONS ARE VIRTUAL

- WARRIOR
    INITIALIZATION IN CONSTRUCTOR
    NO PROBLEMATIC ASSIGNMENTS
    ALL FUNCTIONS DEFINED AS IN BASE CLASS
    NOT TRYING TO ACCESS PRIVATE MEMBERS

- SORCERER
    INITIALIZATION IN CONSTRUCTOR
    NO PROBLEMATIC ASSIGNMENTS
    NOT TRYING TO ACCESS PRIVATE MEMBERS
    ALL FUNCTIONS DEFINED AS IN BASE CLASS

*/





/////////////////////////////////////EXCEPTIONS AND ENUMS/////////////////////////////////////////

/*
* Exceptions used by player:
*/

class PlayerException {
    public:
    virtual ~PlayerException() = default;
};

class IllegalName : public PlayerException{};

class AboveMaxLevel : public PlayerException{};

class NegativeValue : public PlayerException{};


/////////////////////////////////////BEHAVIOUR/////////////////////////////////////////

//forward declaration
class Player;


class Behaviour {

    public:

        virtual ~Behaviour() = default;

        virtual unique_ptr<Behaviour> clone() const = 0;

        /*
        * buyPotions:
        * Applies changes to the player when a PotionsMerchant card is played.
        * What it does depends on the behaviour type.   
        */
        virtual void buyPotions(Player& player) const = 0;
        
        /*
        * returns a string with the behaviour type.
        */
        virtual const string getBehaviour() const = 0;

    
    };

class RiskTaking : public Behaviour {

    public:
    /*
    * buyPotions:
    * If the player's healthpoints are less than 50, one potion is brought.
    * A potion costs 5 coins and adds 10 health points.
    * If the player doesn't have enough money nothing is done.
    * 
    * @param Player 
    *    the player that took the PotionsMerchant card.
    */
    void buyPotions(Player& player) const override;
    
    unique_ptr<Behaviour> clone() const override;

    /*
    * returns "RiskTaking"
    */
    const string getBehaviour() const override;


};


class Responsible : public Behaviour {

    public:
    /*
    * buyPotions:
    * As many potions are brought as the player can afford, until there is no money left or HP = 100.
    * A potion costs 5 coins and adds 10 health points.
    * If the player doesn't have enough money nothing is done.
    *  @param Player 
    *    the player that took the PotionsMerchant card.
    */
    void buyPotions(Player& player) const override;
    
    unique_ptr<Behaviour> clone() const override;

    /*
    * returns "Resposible"
    */
    const string getBehaviour() const override;
};

    


/////////////////////////////////////PLAYER/////////////////////////////////////////



class Player {
public:

  

    /**
     * Gets the name of the player
     * 
     * @return - name of the player
    */
    string getName() const;

    /**
     * Gets the current level of the player
     * 
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the force of the player
     *             
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     * 
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     * 
     * @return - coins of the player
    */
    int getCoins() const;

    /**
    * Gets the behaviour of the player.
    * 
    * @return - the player's behaviour type 
    */
    const string getBehaviour() const; /***************************************************/


    /**
    * Gets the attack strength. The default is calculated as force + level.
    * @return - the player's attack strength
    */
    virtual int getAttackStrength() const;

    /**
    * Gets the player type.
    * @return - the type of the player. 
    */
    virtual const string getType() const = 0;

    /**
     * Gets the description of the player
     * 
     * @return - description of the player
    */
    string getDescription() const; //********************************************************

    /*
     * Boosts level of player by 1.
     *
     * @exception
     *       if current level is 10, AboveMaxLevel is thrown.
    */
    void levelUp();

    /*
     * Boosts force by specified amount.
     * @param boostSize - The boost amount.
     * @exception
     *      If boostSize < 0 NegativeValue is thrown.
    */
    void buff(int boostSize);

    /*
     * Decreases force by specified amount.
     * If amount > force, force is set to 0.
     * @param boostSize - The decrease amount.
     * @exception
     *      If boostSize < 0 NegativeValue is thrown.
    */
    void weaken(int amount);

    /*
     * Boosts the player's HP by specified amount.
     * @param boostSize - The boost amount. 
     * @exception 
     *      - If boostSize < 0 NegativeValue is thrown.
     *      - If boostSize + current HP > 100, HP is set to 100.
    */
    void heal(int boostSize);

    /*
     * Decreases the player's HP by specified amount.
     * @param decreaseSize - The decreasing amount. 
     * @exception 
     *      - If decreaseSize is greater than the current HP, HP is set to 0.
     *      - If boostSize < 0 NegativeValue is thrown.
    */
    void damage(int decreaseSize);

    /*
    * Checks whether player's HP is 0.
    * @return - true: If HP = 0
    * @return - false: If HP > 0
    */
    bool isKnockedOut();


    /*
     * Increases player's coin number by specified amount.
     * @param amount - The amount of coins to add.
     * @exception
     *       - If amount < 0 NegativeValue is thrown.
    */
    void addCoins(int amount);


    /*
     * Decreases player's coin number by specified amount.
     * @param amount - The amount of coins to take.
     * @return
     *       - true: If the payment suceeded.
     *       - false: If the payment failed.
     * @exception 
     *      - If player doesn't have enough coins, the payment fails and no change is made.
     *      - If amount < 0 NegativeValue is thrown.
    */
    bool pay(int amount);



    /*
    * Applies the relevant changes to the player if a "solar eclipce" card is drawn. 
    */
    virtual void applyEclipse() = 0;

    /*
    * Applies the relevant changes to the player if a "poitions merchant" card is drawn.
    */
    void buyPotions(); /*************************************************/


    /*
    * default c'tor
    */
    Player() = default;

    /*
    * c'tor:
    * @param: 
    *   name - string of max english letters only (upper- and lowercase allowed), without spaces.
    *   behaviour - pointer to a behaviour class. (Warrior or Sorcerer)
    * @default  
    *   level - 1
    *   force - 5
    *   HealthPoints - 100
    *   coins - 10
    */
    Player(const string &name, const Behaviour& behaviour);
    virtual ~Player() = default;
    Player(const Player& player);
    Player& operator=(const Player& other) = delete;
    virtual shared_ptr<Player> clone() const = 0;


private:
    const string m_name; //const because the name isn't changed during the game.
    int m_level;
    int m_force;
    int m_healthPoints;
    int m_coins;
    const unique_ptr<const Behaviour> m_behaviour; //const because the player isn't supposed to change behaviour during the game

};


class Warrior : public Player {

public:

    /*
     * Gets the player's attack strength.
     * The warrior's attack strength is calculated as such: 𝐹𝑜𝑟𝑐𝑒 ∗ 2 + 𝐿𝑒𝑣𝑒l 
     * @return 
     *      The player's attack strength
    */
    int getAttackStrength() const override;

    const string getType() const override;

    /*
    * Reduces the player's HP by 1.
    */
    void applyEclipse() override;

    Warrior() : Player() {}
    Warrior(const string &name, const Behaviour& behaviour);
    shared_ptr<Player> clone() const override;
    Warrior& operator=(const Warrior& other) = delete;
};


class Sorcerer : public Player {

    public:

    const string getType() const override;


    /*
    * increases the player's HP by 1.
    * if the player's HP is 100, nothing is done.
    */
    void applyEclipse() override;

    Sorcerer() : Player() {}
    Sorcerer(const string &name, const Behaviour& behaviour);
    shared_ptr<Player> clone() const override;
    Sorcerer& operator=(const Sorcerer& other) = delete;
};





