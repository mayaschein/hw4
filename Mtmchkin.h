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
* - FIND SOLUTION TO FREEING IN THE CARD DECK
*
*/


/**
 * Custom exception class for file opening failures.
 */
class FileOpeningFailed {};

/**
 * Mtmchkin class represents the game engine
 */
class Mtmchkin {
private:
    int m_turnIndex;

public:
    std::vector<Player> players;
    std::queue<Card*> deck;

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
};

#endif // MTMCHKIN_H