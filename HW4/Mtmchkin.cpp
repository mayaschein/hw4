#include "Mtmchkin.h"
#include <algorithm> 
#include <memory>
#include <sstream>
#include <string>

// Constructor implementation

Gang Mtmchkin::handleGangs(std::ifstream& cardsFile)
{
    std::string word;
    //get the gang
    cardsFile >> word;
    int gangSize;
    try {
        gangSize = std::stoi(word);
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Invalid Cards File");
    } catch (const std::out_of_range& e) {
        throw std::runtime_error("Invalid Cards File");
    }

    if (gangSize < 2) {
        throw std::runtime_error("Invalid Cards File");
    }

    Gang gang(gangSize);
    while (gangSize > 0) {
        try {
            cardsFile >> word;
        } catch(...) {
            throw std::runtime_error("Invalid Cards File");
        }

        if (word == "Gang") {
            gang += handleGangs(cardsFile); // Recursive call for nested gangs
        } else if (word == "Dragon") {
            Dragon dragon;
            gang += dragon;
        } else if (word == "Giant") {
            Giant giant;
            gang += giant;
        } else if (word == "Goblin") {
            Goblin goblin;
            gang += goblin;
        } else {
            throw std::runtime_error("Invalid Cards File");
        }

        gangSize--;
    }
    
    return gang;
     
}
// catch(...){throw std::runtime_error("Invalid Cards File");}

Mtmchkin::Mtmchkin(const std::string& cards, const std::string& playersReceived)
{
    std::ifstream cardsFile(cards);
    if (!cardsFile.is_open()) {
       throw FileOpeningFailed();
       //throw std::runtime_error("Invalid Cards File");
    }

    std::ifstream playersFile(playersReceived);
    if (!playersFile.is_open()) {
        cardsFile.close();
        throw FileOpeningFailed();
    }

    std::string word;
    int numCards = 0;
    try {
        while (cardsFile >> word) {
            if (word != "Gang") {
                if (word == "Dragon") {
                    deck.push(shared_ptr<Card>(new Dragon()));
                } else if (word == "Giant") {
                    deck.push(shared_ptr<Card>(new Giant()));
                } else if (word == "Goblin") {
                    deck.push(shared_ptr<Card>(new Goblin()));
                } else if (word == "SolarEclipse") {
                    deck.push(shared_ptr<Card>(new SolarEclipse()));
                } else if (word == "PotionsMerchant") {
                    deck.push(shared_ptr<Card>(new PotionsMerchant()));
                } else {
                    throw std::runtime_error("Invalid Cards File");
                }
            } else {
                deck.push(shared_ptr<Card>(new Gang(handleGangs(cardsFile))));
            }

            numCards++;
        }
    } catch(...) {
        throw std::runtime_error("Invalid Cards File");
    }

    if (numCards < 2) {
        throw std::runtime_error("Invalid Cards File");
    }

    int counter = 3;
    std::string name;
    std::string type;

    while(playersFile >> word) {
        if(word.empty()) {
            throw std::runtime_error("Invalid Players File");
        }

        if (counter == 1) {
            if (type == "Warrior") {
                if (word == "Responsible") {
                    players.push_back(shared_ptr<Player>(new Warrior(name, responsible)));
                } else if (word == "RiskTaking") {
                    players.push_back(shared_ptr<Player>(new Warrior(name, risk_taking)));
                } else {
                    throw std::runtime_error("Invalid Players File");
                }
            } else if (type == "Sorcerer") {
                if (word == "Responsible") {
                    players.push_back(shared_ptr<Player>(new Sorcerer(name, responsible)));
                } else if (word == "RiskTaking") {
                    players.push_back(shared_ptr<Player>(new Sorcerer(name,risk_taking)));
                } else {
                    throw std::runtime_error("Invalid Players File");
                }
            } else {
                throw std::runtime_error("Invalid Players File");
            }

            counter = 0;
        }

        if (counter == 2) {
            type = word;
            counter--;
        }

        if (counter == 3) {
            name = word;
            if (name.length() < 3 || name.length() > 15) {
                throw std::runtime_error("Invalid Players File");
            }
            counter--;
        }

        if (counter == 0) {
            counter = 3;
        }
    } 

    if (players.size() < 2 || players.size() > 6 || counter != 3) {
        throw std::runtime_error("Invalid Players File");
    }

    cardsFile.close();
    playersFile.close();

    if(deck.empty()) {
        throw std::runtime_error("Invalid Cards File");
    }
}

// Function to manage gameplay
void Mtmchkin::play() {
    printStartMessage();
    for(long unsigned int j = 0; j < players.size(); j++) {
        printStartPlayerEntry(j + 1, *players[j]);
    }
    printBarrier();

    long unsigned int activePlayers = players.size();
    while (!GameOver) {
        printRoundStart();
        roundCounter++;
        for (long unsigned int i = 0; i < players.size(); ++i) {
            if (players[i]->getHealthPoints() > 0) {
                shared_ptr<Card> currentCard = deck.front(); 
                m_turn++;
                if (players[i] != nullptr && currentCard != nullptr) {
                    printTurnDetails(m_turn, *players[i], *currentCard);
                }
                currentCard->activate(*players[i]);
                deck.push(currentCard);
                deck.pop();
                if (players[i]->getHealthPoints() == 0) {
                    activePlayers--;
                }

                if (players[i]->getLevel() == 10) {
                    GameOver = true;
                    break;
                }
                if (activePlayers == 0) {
                    GameOver = true;
                    break;
                }
            }
        }

        printRoundEnd();
        printLeaderBoardMessage();
        std::vector<shared_ptr<Player>> sortedPlayers = players;
        std::sort(sortedPlayers.begin(), sortedPlayers.end(), [](shared_ptr<Player> a, shared_ptr<Player> b) {
            if (a->getLevel() != b->getLevel()) {
                return a->getLevel() > b->getLevel();
            } else if (a->getCoins() != b->getCoins()) {
                return a->getCoins() > b->getCoins();
            } else {
                return a->getName() < b->getName();
            }
        });

        for (long unsigned int i = 0; i < sortedPlayers.size(); i++) {
            printLeaderBoardEntry(i + 1, *sortedPlayers[i]);
        }
        printBarrier();

        if (activePlayers == 0) {
            printGameOver();
            printNoWinners();
        }

        for (long unsigned int i = 0; i < players.size(); i++) {
            if (players[i]->getLevel() == 10) {
                printGameOver();
                printWinner(*players[i]);
            }
        }
    }
}

Mtmchkin::~Mtmchkin() {
    while (!deck.empty()) {
        deck.pop();
    }

    for (shared_ptr<Player> player : players) {
        // No need to delete player;
    }

    players.clear();
}

bool Mtmchkin::isGameOver() {
    return GameOver;
}

int Mtmchkin::getNumberOfRounds() {
    return roundCounter;
}
