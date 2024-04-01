#include "Mtmchkin.h"

// Constructor implementation
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

        /*Creating the card deck:*/
        //auxillary variables to help with processing gangs:
        int gangSize = 0;
        int tempGangSize = 0;
        bool isGang = false; 
        Monster tempGang;
        while (cardsFile >> word) //reading by turn each word until the end of the file
        {
            if(gangSize>0) //reading all members of the gang
            {
                if (word=="Dragon")
                {
                    Dragon dragon;
                    tempGang+=dragon;
                }
                else if (word=="Giant")
                {
                    Giant giant;
                    tempGang+=giant;
                }
                else if (word=="Goblin")
                {
                    Goblin goblin;
                    tempGang+=goblin;
                }
                else
                {
                    throw std::runtime_error("Invalid Cards File");
                }
                --gangSize;
            }
            if (gangSize==0 && tempGangSize!=0) //inserting the gang after processing all its members
            {
                deck.push(new Gang(tempGangSize,tempGang));
                tempGang.reset();
                tempGangSize=0;
            }
            if (isGang==true) //Reading the gang size
            {
                gangSize = std::stoi(word);
                if (gangSize<0)
                {
                    throw std::runtime_error("Invalid Cards File");
                }
                tempGangSize = gangSize;
                isGang=false;
            }
            if (word=="Gang") //identifying the current card as a Gang card
            {
                isGang=true;
            }

            if (gangSize==0 && tempGangSize==0 && word!="Gang") //if the current word is not Gang or a card included in the gang
            {
                if (word=="Dragon")
                {
                    deck.push(new Dragon());
                }
                else if (word=="Giant")
                {
                    deck.push(new Giant());
                }
                else if (word=="Goblin")
                {
                    deck.push(new Goblin());
                }
                else if (word=="SolarEclipse")
                {
                    deck.push(new SolarEclipse());
                }
                else if (word=="PotionsMerchant")
                {
                    deck.push(new PotionsMerchant());
                }
                else
                {
                    throw std::runtime_error("Invalid Cards File");
                }
            }
        }

        /*Creating the players array:*/
        int counter = 3;
        std::string name;
        std::string type;
        Responsible responsible;
        RiskTaking risk_taking;
        while(playersFile >> word)
        {
            if (counter==1) //reading the player's behavior and adding it to the players array
            {
                if (type=="Warrior")
                {
                    if (word=="Responsible")
                    {
                       players.push_back(Warrior(name,responsible));
                    }
                    else if (word=="RiskTaking")
                    {
                         players.push_back(Warrior(name,risk_taking));
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
                         players.push_back(Sorcerer(name,responsible));
                    }
                    else if (word=="RiskTaking")
                    {
                         players.push_back(Sorcerer(name,risk_taking));
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

    for(int j=0; j<players.size(); j++) //information on each player

    {

        printStartPlayerEntry(j, players[j]);

    }

    printBarrier();

 

    //Game stage:

 

    bool GameOver=false;

        while(!GameOver)

    {

        printRoundStart(); // starting round announcement

        for (int i = 0; i < players.size(); ++i)

        {

            Card* currentCard = deck.front();

            printTurnDetails(i,players[i],*currentCard);

            currentCard->activate(players[i]); //Activating the card's effects, in accordance with its type and the player's definitions

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

                printWinner(players[i]);

                GameOver=true;

                i = players.size(); //stopping the for loop

            }

            if (players.size()==0) //no players left

            {

                //game over with no victors

                printGameOver();

                printNoWinner();

                GameOver=true;

            }

        }

        if(!GameOver)

        {

        printRoundEnd(); //ending round announcement

        printLeaderBoardMessage();

        std::vector<Player> sortedPlayers = players;

        std::sort(players.begin(), players.end(), [](const Player& a, const Player& b) { //creating a copy of the players vector sorted by levels

            return a.level > b.level;

        });

        for (int i=0; i<sortedPlayers.size()-1; i++) //making adjustments to account for players with equal levels and money

        {

            if(sortedPlayers[i].getLevel()==sortedPlayers[i+1].getLevel())

            {

                if (sortedPlayers[i].getCoins()>sortedPlayers[i+1].getCoins())

                {

                   

                }

            }

        }

        printLeaderBoardEntry(); //Leaderboard

        printBarrier();

        }

 

    }
};