#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace ariel{

    class Fraction{

        int _numerator;
        int _denominator;

        public:
            Fraction() : _numerator(0) , _denominator(1){};
            Fraction(int numerator , int denominator);
            Fraction(float frac);

            Fraction operator + (const Fraction& frac);
            Fraction operator - (const Fraction& frac);
            Fraction operator * (const Fraction& frac);
            Fraction operator / (const Fraction& frac);

            bool operator == (const Fraction &frac) const;
            bool operator != (const Fraction &frac) const;
            bool operator > (const Fraction &frac) const;
            bool operator < (const Fraction &frac) const;
            bool operator >= (const Fraction &frac) const;
            bool operator <= (const Fraction &frac) const;

            
            Fraction operator++();
            Fraction operator++(int);
            Fraction operator--();
            Fraction operator--(int);

            //friends
            friend Fraction operator + (float frac1 , Fraction frac2);
            friend Fraction operator - (float frac1 , Fraction frac2);
            friend Fraction operator / (float frac1 , Fraction frac2);
            friend Fraction operator * (float frac1 , Fraction frac2);

            friend bool operator == (float frac1 , Fraction frac2);
            friend bool operator != (float frac1 , Fraction frac2);
            friend bool operator > (float frac1 , Fraction frac2);
            friend bool operator < (float frac1 , Fraction frac2);
            friend bool operator >= (float frac1 , Fraction frac2);
            friend bool operator <= (float frac1 , Fraction frac2);
          

            
            friend ostream& operator << (std::ostream& output, const Fraction& frac);
            friend istream& operator >> (std::istream& input , Fraction& frac);






            void reduceForm();
            static int gcd(int numerator , int denominator);
            static int lcm(int deno1 , int deno2);


            //getters
            int getNumerator() const;
            int getDenominator() const;

    };
}