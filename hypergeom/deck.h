/*
 * File: deck.h
 * Zachary Muranaka
 * Represents a population that you are sampling from without replacement
 */

#ifndef DECK_H
#define DECK_H

#include <iostream>

class deck
{
private:
    // Member variables
    unsigned long popSize; // The size of the population that is being sampled from
    unsigned long popSuccesses; // The number of successes within the population
    unsigned long sampleSize; // The size of the sample you take from the entire population
    unsigned long desiredSuccesses; // The amount of successes you are looking for from your sample
    unsigned long popFailures; // Calculates the amount of failures throughout the entire population
    double exactChance;
    double orGreaterInclusiveChance;
    double orLessInclusiveChance;

    // Member function prototypes
    const unsigned long long gcd(const unsigned long long givenNumber1, const unsigned long long givenNumber2) const;
    const unsigned long long ncr(unsigned long n, unsigned long r) const;
    const double probability(unsigned long currentDesiredSuccesses) const;
    double orGreater(double exactChance);
    double orLess(double exactChance);

public:
    // Constructor prototype
    deck(const unsigned long popSize, const unsigned long popSuccesses, const unsigned long sampleSize, const unsigned long desiredSuccesses);

    const void print(std::ostream& out) const;
};

#endif
