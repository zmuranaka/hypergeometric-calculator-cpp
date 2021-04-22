/*
 * File: main.cpp
 * Zachary Muranaka
 * Solves a hypergeometric distribution
 */

#include <iostream>
#include "deck.h"

const unsigned long validData(const char* prompt);

int main()
{
    // Request the data from the user
    const unsigned long popSize = validData("Population size: ");
    const unsigned long popSuccesses = validData("Population successes: ");
    const unsigned long sampleSize = validData("Sample size: ");
    const unsigned long desiredSuccesses = validData("Desired successes: ");

    // Construct the deck object and print the results
    deck orGreaterDeck(popSize, popSuccesses, sampleSize, desiredSuccesses);
    orGreaterDeck.print(std::cout);

    return 0;
}

// Makes sure the user inputs a valid long for the data being requested
const unsigned long validData(const char* prompt)
{
    unsigned long potentialData = -1;
    std::cout << prompt;
    std::cin >> potentialData;

    // Rerun this function if the user entered something that cannot be stored as a long
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n'); // Take out 1000 characters from the buffer but stop if it encounters a newline
        return validData(prompt);
    }
    return potentialData;
}
