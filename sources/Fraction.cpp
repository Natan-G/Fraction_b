#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <math.h>

#include "Fraction.hpp"
using namespace std;

namespace ariel{

    Fraction::Fraction(int numerator , int denominator){
        if(denominator == 0){
            throw invalid_argument("denominator can't be 0!");
        }
        this->_numerator = numerator;
        this->_denominator = denominator;
        reduceForm();
    }

    Fraction::Fraction(float frac){
        _numerator = round(frac*1000);
        _denominator = 1000;
        reduceForm();
    }
    
    Fraction Fraction::operator+ (const Fraction& frac){
        if((long)_numerator * frac._denominator + frac._numerator * _denominator >numeric_limits<int>::max()) {
            throw overflow_error("result to big");}

        if((long)_numerator * frac._denominator + frac._numerator * _denominator < numeric_limits<int>::min()){
            throw overflow_error("result to small");}
  
        if((long)_denominator * frac._denominator > numeric_limits<int>::max()){
            throw overflow_error("result of the denominator to big");
        }

        if((long)_numerator * frac._numerator > numeric_limits<int>::max()){
            throw overflow_error("result the numerator to big");
        }
        
        if (_denominator == frac._denominator){
            int nume = _numerator + frac._numerator;
            return Fraction(nume , _denominator);
        }
        else{
            int minimum_divistion = lcm(_denominator , frac._denominator);
            int nume = _numerator*(minimum_divistion/_denominator) + frac._numerator*(minimum_divistion/frac._denominator);
            return Fraction(nume , minimum_divistion);   
        }
    }

    Fraction Fraction::operator- (const Fraction& frac){
        if((long)_numerator * frac._denominator - frac._numerator * _denominator >numeric_limits<int>::max()){
            throw overflow_error("overflow!");
        }
        if((long)_denominator * frac._denominator > numeric_limits<int>::max()){
            throw overflow_error("overflow!");
        }
        
        if (_denominator == frac._denominator){
            int nume = _numerator - frac._numerator;
            return Fraction(nume , _denominator);
        }
        else{
            int minimum_divistion = lcm(_denominator , frac._denominator);
            int nume = _numerator*(minimum_divistion/_denominator) - frac._numerator*(minimum_divistion/frac._denominator);
            return Fraction(nume , minimum_divistion);   
        }
    }

    Fraction Fraction::operator* (const Fraction& frac){
        if((long)_numerator * frac._numerator > numeric_limits<int>::max()){
            throw overflow_error("overflow! the result to big");
        }
        if((long)_denominator * frac._denominator > numeric_limits<int>::max()){
            throw overflow_error("overflow! the result to big");
        }


        int nume = _numerator * frac._numerator;
        int deno = _denominator * frac._denominator;
        return Fraction(nume,deno);
    }

    Fraction Fraction::operator/ (const Fraction& frac){
        if(frac._numerator == 0){
            throw runtime_error("numerator fraction cant be 0 ");
        }
        if((long)_numerator * frac._denominator > numeric_limits<int>::max()){
            throw overflow_error("overflow! the result to big");
        }
        if((long)_denominator * frac._numerator > numeric_limits<int>::max()){
            throw overflow_error("overflow! the result to big");
        }


        int nume = _numerator * frac._denominator;
        int deno = _denominator * frac._numerator;
        return Fraction(nume , deno);

    }

    bool Fraction::operator == (const Fraction &frac) const{
        return (_numerator == frac._numerator && _denominator == frac._denominator);
    }

    bool Fraction::operator != (const Fraction &frac) const{
        return !(*this == frac);
    }
    
    bool Fraction::operator > (const Fraction &frac) const{
        return (_numerator * frac._denominator > frac._numerator * _denominator);
    }        

    bool Fraction::operator >= (const Fraction &frac) const{
        return (_numerator * frac._denominator >= frac._numerator * _denominator);
    }

    bool Fraction::operator < (const Fraction &frac) const{
        return (_numerator * frac._denominator < frac._numerator * _denominator);
    }

    bool Fraction::operator <= (const Fraction &frac) const{
        return (_numerator * frac._denominator <= frac._numerator * _denominator);
    }

    Fraction Fraction::operator ++ (){
        _numerator += _denominator;
        reduceForm();
        return *this;
    }

    Fraction Fraction::operator ++ (int){
        Fraction temp(*this);
        ++(*this);
        return temp;
    }

    Fraction Fraction::operator -- (){
        _numerator -= _denominator;
        reduceForm();
        return *this;
    }

    Fraction Fraction::operator -- (int){
        Fraction temp(*this);
        --(*this);
        return temp;
    }

    //friends operators
    Fraction operator + (float frac1 , Fraction frac2){
        Fraction temp(frac1);
        if (temp._denominator == frac2._denominator){
            int nume = temp._numerator + frac2._numerator;
            return Fraction(nume , temp._denominator);
        }
        else{
            int minimum_divistion = Fraction::lcm(temp._denominator , frac2._denominator);
            int nume = temp._numerator*(minimum_divistion/temp._denominator) + frac2._numerator*(minimum_divistion/frac2._denominator);
            return Fraction(nume , minimum_divistion);   
        }
    }

    Fraction operator - (float frac1 , Fraction frac2){
        Fraction temp(frac1);
        if (temp._denominator == frac2._denominator){
            int nume = temp._numerator - frac2._numerator;
            return Fraction(nume , temp._denominator);
        }
        else{
            int minimum_divistion = Fraction::lcm(temp._denominator , frac2._denominator);
            int nume = temp._numerator*(minimum_divistion/temp._denominator) - frac2._numerator*(minimum_divistion/frac2._denominator);
            return Fraction(nume , minimum_divistion);   
        }
    }

    Fraction operator * (float frac1 , Fraction frac2){
        Fraction temp(frac1);
        int nume = temp._numerator * frac2._numerator;
        int deno = temp._denominator * frac2._denominator;
        return Fraction(nume , deno);
    }

    Fraction operator / (float frac1 , Fraction frac2){
        Fraction temp(frac1);
        if(frac2._numerator == 0){
            throw runtime_error("numerator fraction cant be 0 ");
        }
        int nume = temp._numerator * frac2._denominator;
        int deno = temp._denominator * frac2._numerator;
        return Fraction(nume , deno);
    }

    bool operator == (float frac1 , Fraction frac2){
        Fraction temp(frac1);
        return (temp._numerator == frac2._numerator && temp._denominator == frac2._denominator);
    }

    bool operator != (float frac1 , Fraction frac2){
        Fraction temp(frac1);
        return !(temp == frac2);
    }
    
    bool operator > (float frac1 , Fraction frac2){
        Fraction temp(frac1);
        return (temp._numerator * frac2._denominator > frac2._numerator * temp._denominator);
    }        

    bool operator >= (float frac1 , Fraction frac2){
        Fraction temp(frac1);
        return (temp._numerator * frac2._denominator >= frac2._numerator * temp._denominator);
    }

    bool operator < (float frac1 , Fraction frac2){
        Fraction temp(frac1);
        return (temp._numerator * frac2._denominator < frac2._numerator * temp._denominator);
    }

    bool operator <= (float frac1 , Fraction frac2){
        Fraction temp(frac1);
        return (temp._numerator * frac2._denominator <= frac2._numerator * temp._denominator);
    }

    ostream& operator << (ostream& output, const Fraction& frac){
        output << frac._numerator << "/" << frac._denominator;
        return output;
    }

    istream& operator >> (istream& input , Fraction& frac){
        int nume , deno;
        if(!(input >> nume >> deno)){
            throw runtime_error("invalid input");
        }
        if(deno == 0){
            throw runtime_error("cant divide by 0!");
        }
        
        frac = Fraction(nume , deno);
        return input;
    }

    void Fraction::reduceForm(){
        if(_numerator == 0){
            _denominator = 1;
            return;
        }      
        int sign = 1;

        if(_numerator < 0){
            sign *= -1;
            _numerator *= -1;
        }
        if(_denominator < 0 ){
            sign *= -1;
            _denominator *= -1;
        }

        int g = gcd(_numerator , _denominator);
        _numerator = _numerator/g * sign;
        _denominator = _denominator/g;


    }

    //taken from geeksforgeeks
    int Fraction::gcd(int numerator , int denominator){
        if(denominator == 0){
            return numerator;
        }
        return gcd(denominator, numerator % denominator);
    }
    int Fraction::lcm(int deno1 , int deno2){
        return ((deno1 * deno2) / gcd(deno1 , deno2));
    }

    int Fraction::getNumerator() const{
        return this->_numerator;
    }

    int Fraction::getDenominator() const{
        return this->_denominator;
    }

}

