/*
 * File: deck.h
 * Zachary Muranaka
 * Represents a population that you are sampling from without replacement
 */

#ifndef DECK_H
#define DECK_H

class deck
{
// The following data for deck is all private
private:
    unsigned long popSize; // The size of the population that is being sampled from
    unsigned long popSuccesses; // The number of successes within the population
    unsigned long sampleSize; // The size of the sample you take from the entire population
    unsigned long desiredSuccesses; // The amount of successes you are looking for from your sample
    unsigned long popFailures; // Calculates the amount of failures throughout the entire population
    unsigned long sampleFailures; // Calculates the number of failures in your sample assuming you get exactly the desired number of successes

    /*
     * We need double versions of all of the above variables except for sampleSize
     * These are necessary because there are times when we will need to treat the variables as doubles
     * For example, in the probability() method we treat the variables as doubles
     * However, we do not want to allow the user to enter doubles when creating the object
     */
    double dpopSize;
    double dpopSuccesses;
    double ddesiredSuccesses;
    double dpopFailures;
    double dsampleFailures;

    unsigned long long combination; // The combination of sampleSize and desiredSuccesses (nCr, where n = sampleSize and r = desiredSuccesses)

    const unsigned long long gcd(unsigned long long givenNumber1, unsigned long long givenNumber2) const;

// The following member functions are all public so they can be accessed by the Driver program
public:
    // Function prototypes for the member functions
    deck(unsigned long popSize, unsigned long popSuccesses, unsigned long sampleSize, unsigned long desiredSuccesses);
    deck(const deck& d);
    const double probability(double popSize, double popSuccesses, double desiredSuccesses, double popFailures, double sampleFailures) const;
    const unsigned long long ncr(unsigned long n, unsigned long r) const;
    const unsigned long long factorial(unsigned long sampleSize) const;
    double orGreater(double exactChance);
    double orLess(double exactChance);

    // The following are accessor functions so the Driver program can access the private data
    const double getdpopSize() const { return dpopSize; }
    const double getdpopSuccesses() const { return dpopSuccesses; }
    const double getddesiredSuccesses() const { return ddesiredSuccesses; }
    const double getdpopFailures() const { return dpopFailures; }
    const double getdsampleFailures() const { return dsampleFailures; }
    const unsigned long long getcombination() const { return combination; }
};

#endif
