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
        static const Responsible m_responsible; ///////////////////CHANGED TO FIT CONVENTIONS + ADDED STATIC
        static const RiskTaking m_riskTaking;

    public:
        std::vector<std::shared_ptr<Player>> players;
        std::queue<std::unique_ptr<Card>> deck;
        
    /**
     * Handles the creation of gangs and nested gangs from the input file.
     * Recursively builds gangs and adds them to the deck.
     * 
     * @param cardsFile - input file stream containing the gang information
     * 
     * @throws std::runtime_error if the cards file is invalid or contains incorrect data
     * 
     * @return - void
     */
     void handleGangs(std::ifstream& cardsFile);

    /**
     * Constructor to initialize the Mtmchkin game.
     * @param cards Argument vector containing card information.
     * @param playersReceived Argument vector to the file containing player information. ////////////CHANGED
     * @throw FileOpeningFailed if file opening fails or invalid data is encountered.
     */
    Mtmchkin(const std::string& cards, const std::string& playersReceived);

    /**
     * Function to manage the gameplay from start to end.
     */
    void play();
};

#endif // MTMCHKIN_H