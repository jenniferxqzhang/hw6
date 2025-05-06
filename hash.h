#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0,0,0,0,0};

        for(int i = 0; i < k.length(); i++){
          int idx = 4 - (i/6);

          int length = k.length();
          // process from right to left
          char c = k[length - 1 -i];
          int cValue = letterDigitToNumber(c);

          int position = i%6; // to find what power of 36
          unsigned long long power = 1;
          for(int j = 0; j < position; j++){
            power *= 36;
          }

          w[idx] += static_cast<unsigned long long>(power *cValue);
        }

        // compute the final has result
        unsigned long long hash = 0;
        for(int i = 0;i < 5; i++){
          hash += w[i] * rValues[i];
        }

        return hash;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        HASH_INDEX_T idx;
        if(isalpha(letter)){
          // convert letters to a digit 1-25
          idx = tolower(letter) - 'a';
        }
        else if(isdigit(letter)){
          // convert digits to 26-35
          idx = letter - '0' + 26;
        }
        return idx;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
