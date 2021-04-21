/*
 * File: main.cpp
 * Zachary Muranaka
 * Solves a hypergeometric distribution
 */

#include <iostream>
#include "deck.h"

// Function prototypes
unsigned long validPopSize();
unsigned long validPopSuccesses();
unsigned long validSampleSize();
unsigned long validDesiredSuccesses();

int main()
{
    unsigned long popSize;
    unsigned long popSuccesses;
    unsigned long sampleSize;
    unsigned long desiredSuccesses;

    popSize = validPopSize();
    popSuccesses = validPopSuccesses();
    sampleSize = validSampleSize();
    desiredSuccesses = validDesiredSuccesses();

    // Creates a new deck object which will be used to calculate the exact probability or greater
    deck* orGreaterDeck = new deck(popSize, popSuccesses, sampleSize, desiredSuccesses);
    // Copies the orGreaterDeck object to the orLessDeck object, which will be used to calculate the exact probability or less
    deck* orLessDeck = new deck(*orGreaterDeck);

    // The next six statements calculate probabilities for the decks
    double orGreaterExactChance = orGreaterDeck->probability(orGreaterDeck->getdpopSize(), orGreaterDeck->getdpopSuccesses(), orGreaterDeck->getddesiredSuccesses(), orGreaterDeck->getdpopFailures(), orGreaterDeck->getdsampleFailures());
    double orLessExactChance = orLessDeck->probability(orLessDeck->getdpopSize(), orLessDeck->getdpopSuccesses(), orLessDeck->getddesiredSuccesses(), orLessDeck->getdpopFailures(), orLessDeck->getdsampleFailures());
    orGreaterExactChance *= orGreaterDeck->getcombination(); // Chance of getting exactly desired successes
    double orGreaterInclusiveChance = orGreaterDeck->orGreater(orGreaterExactChance); // Chance of getting desired successes or greater
    orLessExactChance *= orLessDeck->getcombination(); // Chance of getting exactly desired successes
    double orLessInclusiveChance = orLessDeck->orLess(orLessExactChance); // Chance of getting desired successes or less

    // The next five statements print out the probabilities
    std::cout << "Chance of exactly desired successes: " << orGreaterExactChance << std::endl; // orGreaterExactChance and orLessExactChance should be equal so this could also be orLessExactChance
    std::cout << "Chance of less than desired successes: " << orLessInclusiveChance - orLessExactChance << std::endl;
    std::cout << "Chance of desired successes or less: " << orLessInclusiveChance << std::endl;
    std::cout << "Chance of greater than desired successes: " << orGreaterInclusiveChance - orGreaterExactChance << std::endl;
    std::cout << "Chance of desired successes or greater: " << orGreaterInclusiveChance << std::endl;
    
    // Destroy the objects that were created
    delete orGreaterDeck;
    delete orLessDeck;

    return 0;
}

// Function definitions

// Makes sure the user inputs a valid long for the pop size
unsigned long validPopSize()
{
    unsigned long potentialPopSize = -1;
    std::cout << "Population size: ";
    std::cin >> potentialPopSize;

    // Rerun this function if the user entered something that cannot be stored as a long
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000,'\n'); // Take out 1000 characters from the buffer but stop if it encounters a newline
        return validPopSize();
    }
    return potentialPopSize;
}

// Makes sure the user inputs a valid long for the pop successes
unsigned long validPopSuccesses()
{
    unsigned long potentialPopSuccesses = -1;
    std::cout << "Population successes: ";
    std::cin >> potentialPopSuccesses;

    // Rerun this function if the user entered something that cannot be stored as a long
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000,'\n'); // Take out 1000 characters from the buffer but stop if it encounters a newline
        return validPopSuccesses();
    }
    return potentialPopSuccesses;
}

// Makes sure the user inputs a valid long for the sample size
unsigned long validSampleSize()
{
    unsigned long potentialSampleSize = -1;
    std::cout << "Sample size: ";
    std::cin >> potentialSampleSize;
    
    // Rerun this function if the user entered something that cannot be stored as a long
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000,'\n'); // Take out 1000 characters from the buffer but stop if it encounters a newline
        return validSampleSize();
    }
    return potentialSampleSize;
}

// Makes sure the user inputs a valid long for the desired successes
unsigned long validDesiredSuccesses()
{
    unsigned long potentialDesiredSuccesses = -1;
    std::cout << "Desired successes: ";
    std::cin >> potentialDesiredSuccesses;

    // Rerun this function if the user entered something that cannot be stored as a long
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000,'\n'); // Take out 1000 characters from the buffer but stop if it encounters a newline
        return validDesiredSuccesses();
    }
    return potentialDesiredSuccesses;
}
