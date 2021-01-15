//compile with -lgmpxx -lgmp flag

//Header
#ifndef INTEGER_ARITHMETICS_HEADER
#define INTEGER_ARITHMETICS_HEADER

#include<cmath>
#include<climits>
#include<iostream>
#include <gmp.h>
#include <gmpxx.h>
//#include"BigInteger.hpp"


template <int N>
class ModInt {
	public:
		ModInt(const BigInteger<N> pp) : pp(pp), value(BigInteger<N>()) {}
		ModInt(const BigInteger<N> pp, const BigInteger<N> value) : pp(pp), value(value) {}
		ModInt(const ModInt & copy) : pp(copy.pp), value(copy){}
		ModInt(ModInt && move) : pp(copy.pp), value(std::move(copy)) {}
		//int get() const {return value;}
		//int getP() const {return pp;}
		void set(const BigInteger& input);
		ModInt pow (const ModInt& exponent);
		ModInt operator+(const ModInt & aa);
		ModInt operator-(const ModInt & aa);
		ModInt operator* (const ModInt & aa);
		ModInt operator/ (const ModInt& aa);
		ModInt operator= (const ModInt& aa);
		ModInt operator+= (const ModInt& aa);
		ModInt operator*= (const ModInt& aa);
		ModInt operator*= (const int& aa);
		bool operator== (const ModInt& aa);
		bool operator== (const int& aa);
		/*
		int operator& (const ModInt& aa);
		int operator& (const int& aa);
		*/
		ModInt invert();
		std::ostream &write(std::ostream &dest) const { return dest << value;}
	private:
		const BigInteger<N> pp;
		BigInteger<N> value;
};
#endif