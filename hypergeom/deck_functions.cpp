/*
 * File: deck.h
 * Zachary Muranaka
 * Represents a population that you are sampling from without replacement
 */

#include "deck.h"
#include <exception>
#include <iostream>
#include <cstdlib>

 // Constructor for the deck class
deck::deck(unsigned long popSize, unsigned long popSuccesses, unsigned long sampleSize, unsigned long desiredSuccesses)
{
    // Checks if the numbers they entered allow for a valid Deck
    if (popSize >= popSuccesses && popSize >= sampleSize && popSize >= desiredSuccesses
        && popSuccesses >= desiredSuccesses && sampleSize >= desiredSuccesses
        && popSize >= 0 && popSuccesses >= 0 && sampleSize >= 0 && desiredSuccesses >= 0)
    {
        try
        {
            this->popSize = popSize;
            this->popSuccesses = popSuccesses;
            this->sampleSize = sampleSize;
            this->desiredSuccesses = desiredSuccesses;

            popFailures = popSize - popSuccesses;
            sampleFailures = sampleSize - desiredSuccesses;

            exactChance = probability(this->desiredSuccesses); // Chance of getting exactly desired successes
            orGreaterInclusiveChance = orGreater(exactChance); // Chance of getting desired successes or greater
            orLessInclusiveChance = orLess(exactChance); // Chance of getting desired successes or less
        }
        // It is possible to construct a valid Deck that still results in a divide-by-zero error
        catch (const std::exception& ex)
        {
            std::cerr << ex.what() << std::endl;
            std::cerr << "The numbers you entered cause a divide-by-zero error. Try again." << std::endl;
            exit(1);
        }
    }
    else
    {
        std::cerr << "The numbers you entered are not a valid hypergeometric distribution. Try again." << std::endl;
        exit(1);
    }
}

// Calculates the greatest common denominator between two numbers
const unsigned long long deck::gcd(unsigned long long givenNumber1, unsigned long long givenNumber2) const
{
    unsigned long greatestCommonDenominator = 1; // The minimum GCD of any two numbers is 1

    for (unsigned i = 1; i <= givenNumber1 && i <= givenNumber2; i++)
    {
        if (givenNumber1 % i == 0 && givenNumber2 % i == 0) // Checks if i is factor of both integers using modulus division
            greatestCommonDenominator = i;
    }

    return greatestCommonDenominator;
}

/*
 * Calculates a combination of sampleSize and desiredSuccesses
 * The equation for nCr is (n!) / ((r!) * (n - r)!)
 * This can be simplified to n * (n - 1) * (n - 2) * ... * (n - r + 1) / r!
 * This method calculates nCr using this simplified equation
 * n = sampleSize and r = desiredSuccesses
 */
const unsigned long long deck::ncr(unsigned long n, unsigned long r) const
{
    /*
     * The combination of n and r is equal to the combination of n and (n - r)
     * For example, 17 combination 13 is the same as 17 combination 4
     * Therefore, we can substitute (n - r) for r if we have a larger r value
     * Attempting to prevent overflow, if (n - r) is less than r we use it instead
     */
    if (n - r < r) r = n - r;

    // Tries to calculate the combination of n and r
    try
    {
        unsigned long long top = 1; // top holds the value of n * (n - 1) * (n - 2) ...
        unsigned long long bottom = 1; // bottom holds the value of r * (r - 1) * (r - 2) ...

        if (r)
        {
            /*
             * Because this only loops until r = 0, we only calculate the first r numbers of the factorial
             * This is equivalent to the n * (n - 1) * (n - 2) * ... * (n - r + 1)
             * In other words, it is a reduced factorial of n from n to n - r + 1
             * This is how we calculate nCr with the simplified equation
             * The top is n * (n - 1) * (n - 2) * ... * (n - r + 1) and the bottom is r!
             */
            while (r)
            {
                top *= n;
                bottom *= r;

                unsigned long long greatestCommonDenominator = gcd(top, bottom);

                // Divides the top and bottom of the fraction by their gcd to help prevent overflow
                top /= greatestCommonDenominator;
                bottom /= greatestCommonDenominator;

                n--;
                r--;
            }
        }
        else top = 1; // n combination 0, where n is any number, is always equal to 1

        /*
         * A factorial always simplifies to a whole number
         * Therefore, we can just return the top, because using the gcd division, bottom should simplify to 1
         * In the case where r = 0, we simply store 1 in top because n combination 0 is always 1
         */
        return top;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        std::cerr << "The numbers you entered cause a divide-by-zero error. Try again." << std::endl;
        exit(1);
    }
}

// Calculates the hypergeometric probability
const double deck::probability(unsigned long currentDesiredSuccesses) const
{
    double popSize = this->popSize;
    double popSuccesses = this->popSuccesses;
    double popFailures = this->popFailures;
    double sampleFailures = this->sampleSize - currentDesiredSuccesses;

    double prob = 1;
    unsigned long long combination = ncr(this->sampleSize, currentDesiredSuccesses);

    // Calculate the probability from the successes
    for (currentDesiredSuccesses; currentDesiredSuccesses > 0; currentDesiredSuccesses--)
    {
        prob *= (popSuccesses / popSize);
        popSuccesses--;
        popSize--;
    }

    // Calculate the probability from the failures
    for (sampleFailures; sampleFailures > 0; sampleFailures--)
    {
        prob *= (popFailures / popSize);
        popFailures--;
        popSize--;
    }

    return prob * combination;
}

// Calculates the probability of n or greater successes
double deck::orGreater(double exactChance)
{
    unsigned long tempDesiredSuccesses = this->desiredSuccesses;

    while (tempDesiredSuccesses < sampleSize)
    {
        tempDesiredSuccesses++;
        exactChance += probability(tempDesiredSuccesses);
    }
    return exactChance;
}

// Calculates the probability of n or less successes
double deck::orLess(double exactChance)
{
    unsigned long tempDesiredSuccesses = this->desiredSuccesses;

    while (tempDesiredSuccesses > 0)
    {
        tempDesiredSuccesses--;
        exactChance += probability(tempDesiredSuccesses);
    }
    return exactChance;
}

// Prints out the probabilities to the ostream
const void deck::print(std::ostream& out) const
{
    out << "Chance of exactly desired successes: " << exactChance << std::endl;
    out << "Chance of less than desired successes: " << orLessInclusiveChance - exactChance << std::endl;
    out << "Chance of desired successes or less: " << orLessInclusiveChance << std::endl;
    out << "Chance of greater than desired successes: " << orGreaterInclusiveChance - exactChance << std::endl;
    out << "Chance of desired successes or greater: " << orGreaterInclusiveChance << std::endl;
}
