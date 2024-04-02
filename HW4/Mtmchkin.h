#ifndef MTMCHKIN_H
#define MTMCHKIN_H
#include "utilities.h" 
#include <queue>
#include <fstream>
#include <string>
#include <stdexcept>
#include <memory>
#include <vector>


/**
 * Custom exception class for file opening failures.
 */
class FileOpeningFailed {};

/**
 * Mtmchkin class represents the game engine
 */
class Mtmchkin {
private:
    const Responsible responsible;
    const RiskTaking risk_taking;
    int m_turn = 0;
    bool GameOver=false;
    int roundCounter=0;

public:
    std::vector<shared_ptr<Player>> players;
    std::queue<shared_ptr<Card>> deck;
/**
 * Handles the creation of gangs and nested gangs from the input file.
 * Recursively builds gangs and returns it
 * 
 * @param cardsFile - input file stream containing the gang information
 * 
 * @throws std::runtime_error if the cards file is invalid or contains incorrect data
 * 
 * @return - Gang
 */
    Gang handleGangs(std::ifstream& cardsFile);

    /**
     * Constructor to initialize the Mtmchkin game.
     * @param cards Path to the file containing card information.
     * @param playersReceived Path to the file containing player information.
     * @throw FileOpeningFailed if file opening fails or invalid data is encountered.
     */
    Mtmchkin(const std::string& cards, const std::string& playersReceived);

    /**
     * Function to manage the gameplay from start to end.
     */
    void play();

    ~Mtmchkin();
    bool isGameOver();
    int getNumberOfRounds();
};

#endif // MTMCHKIN_H