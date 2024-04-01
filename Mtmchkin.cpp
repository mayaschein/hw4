#include "Mtmchkin.h"
#include <algorithm> 
#include <memory>

// Constructor implementation

void Mtmchkin::handleGangs(std::ifstream& cardsFile)
{
    std::string word;
    cardsFile >> word;

    int gangSize;
    gangSize = std::stoi(word); 
    if (gangSize<0) //checking proper input of the gang size
        {
            throw std::runtime_error("Invalid Cards File");
        }

    int tempGangSize = gangSize; ////////////////////WHY DO YOU NEED IT?
    Monster tempGang;
    while (gangSize > 0) { //reading all members of the gang
        cardsFile >> word;

        if (word == "Gang") {
            handleGangs(cardsFile); // Recursive call for nested gangs
        } //builds the gang:
        if (word == "Dragon")
            {
                Dragon dragon;
                tempGang+=dragon;
            }
        else if (word == "Giant")
            {
                Giant giant;
                tempGang+=giant;
            }
        else if (word == "Goblin")
            {
                Goblin goblin;
                tempGang+=goblin;
            }
        else
            {
                throw std::runtime_error("Invalid Cards File");
            }

        gangSize--;
    }

    unique_ptr<Card> gang( new Gang(tempGangSize, tempGang) );

    deck.push(gang); ////////CHANGED BECAUSE MAKE UNIQUE ONLY EXISTS FROM C++14 ONWARDS.
}

 Mtmchkin::Mtmchkin(const std::string& cards, const std::string& playersReceived)
    {
        /*Opening the files and checking the process had been completed successfully:*/
        std::ifstream cardsFile(cards);
        if (!cardsFile.is_open())
        {
            throw FileOpeningFailed();
        }
        std::ifstream playersFile(playersReceived);
        if (!playersFile.is_open())
        {
            cardsFile.close();
            throw FileOpeningFailed();
        }

        std::string word; //helps reading from the files word-by-word
        while (cardsFile >> word)
        {
            if (word!="Gang") //if the current word is not Gang or a card included in the gang
            {
                if (word=="Dragon")
                {
                    unique_ptr<Card> dragon(new Dragon);
                    deck.push(dragon);
                }
                else if (word=="Giant")
                {
                    unique_ptr<Card> giant(new Giant);
                    deck.push(giant);
                }
                else if (word=="Goblin")
                {
                    unique_ptr<Card> goblin(new Goblin);

                    deck.push(goblin);
                }
                else if (word=="SolarEclipse")
                {
                    unique_ptr<Card> solarEclipse(new SolarEclipse);
                    deck.push(solarEclipse);
                }
                else if (word=="PotionsMerchant")
                {
                    unique_ptr<Card> potionsMerchant(new PotionsMerchant);
                    deck.push(potionsMerchant);
                }
                else
                {
                    throw std::runtime_error("Invalid Cards File");
                }
            }
            else
            {
                handleGangs(cardsFile);
            }
        }

        /*Creating the players array:*/
        int counter = 3;
        std::string name;
        std::string type;
        while(playersFile >> word)
        {
            if (counter==1) //reading the player's behavior and adding it to the players array
            {
                if (type=="Warrior")
                {
                    if (word=="Responsible")
                    {
                       players.push_back(shared_ptr<Player>(new Warrior(name , m_responsible)));
                    }
                    else if (word=="RiskTaking")
                    {
                         players.push_back(shared_ptr<Player>(new Warrior(name , m_riskTaking)));
                    }
                    else
                    {
                        throw std::runtime_error("Invalid Players File");
                    }
                }
                else if (type=="Sorcerer")
                {
                     if (word=="Responsible")
                    {
                         players.push_back(shared_ptr<Player>(new Sorcerer(name , m_responsible)));
                    }
                    else if (word=="RiskTaking")
                    {
                         players.push_back(shared_ptr<Player>(new Sorcerer(name , m_riskTaking)));
                    }
                    else
                    {
                        throw std::runtime_error("Invalid Players File");
                    }
                }
                else
                {
                    throw std::runtime_error("Invalid Players File");
                }
                counter=0;
            }
            if (counter==2) //saving the player's type
            {
                type=word;
                counter--;
            }
            if (counter==3) //saving the player's name
            {
                name=word;
                counter--;
            }
            if (counter==0) //moving on to the next line
            {
                counter=3;
            }
        }
        if (players.size() < 2 || players.size() > 6) //checking that there is a valid number of players
        {
            throw std::runtime_error("Invalid Players File");
        }
        /*closing the files:*/
        cardsFile.close();
        playersFile.close();
    }

// Function to manage gameplay
void Mtmchkin::play() {
  //Initial printings:
    void printStartMessage(); //announcement of game beginning
    for(long unsigned int j=0; j < players.size(); j++) //information on each player
    {
        printStartPlayerEntry(j, *players[j]);
    }
    printBarrier();

    //Game stage:

    bool GameOver=false;
        while(!GameOver)
    {
        printRoundStart(); // starting round announcement
        for (long unsigned int i = 0; i < players.size(); ++i) 
        {
           std::unique_ptr<Card>& currentCard = deck.front(); 
            printTurnDetails(i, *players[i], *currentCard);
            currentCard->activate(*players[i]); //Activating the card's effects, in accordance with its type and the player's definitions
            deck.pop();
            deck.push(currentCard); //taking out the used card and pushing it to the end of the deck
            //checking the effects of the round:
            if(players[i].getHealthPoints()==0) //removing a player with no health points
            {
                players.erase(players.begin()+i); 
            }
            if(players[i].getLevel()==10)
            {
                //victory
                printGameOver();
                printWinner(*players[i]);
                GameOver=true;
                break;
            }
            if (players.size()==0) //no players left
            {
                //game over with no victors
                printGameOver();
                printNoWinners();
                GameOver=true;
                break;
            }
        }
        if(!GameOver)
        {
        printRoundEnd(); //ending round announcement
        printLeaderBoardMessage();
        std::vector<Player> sortedPlayers = players;
        // Sort players by level, coins, and name (if necessary)
            std::sort(sortedPlayers.begin(), sortedPlayers.end(), [](const Player& a, const Player& b) {
                if (a.getLevel() != b.getLevel()) {
                    return a.getLevel() > b.getLevel(); // Sort by level in descending order
                } else if (a.getCoins() != b.getCoins()) {
                    return a.getCoins() > b.getCoins(); // If levels are equal, sort by coins in descending order
                } else {
                    return a.getName() < b.getName(); // If levels and coins are equal, sort by name in lexicographical order
                }
            }); 
        //printing the leaderboard:
        for (long unsigned int i=0; i<sortedPlayers.size(); i++)
        {
            printLeaderBoardEntry(i, sortedPlayers[i]);
        }
        printBarrier();
        }

    }
};