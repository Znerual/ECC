//compile with -lgmpxx -lgmp flag

//Header
#ifndef MODINT_HEADER
#define MODINT_HEADER

#include<cmath>
#include<climits>
#include<iostream>
#include <gmp.h>

#include <gmpxx.h>
//#include"BigInteger.hpp"

//Print everything that has .print
template<class T>
auto operator<<(std::ostream& os, T const & t) -> decltype(t.print(os), os) 
{ 
    t.print(os); 
    return os; 
} 

class ModInt {
	public:
		//ModInt() : pp(0), value(0) {}
		ModInt(const mpz_class pp) : pp(pp) {mpz_class(value);}
		ModInt(const mpz_class pp, mpz_class value) : pp(pp), value(value) {}
		ModInt(const ModInt pp, mpz_class value) : pp(pp.value), value(value) {}
		ModInt(const ModInt & copy) : pp(copy.pp), value(copy.value){/*std::cout << "Copied!" << std::endl;*/}
		ModInt(ModInt && mint) : pp(std::move(mint.pp)), value(std::move(mint.value)) {/*std::cout << "Moved!" << std::endl;*/}
		//int get() const {return value;}
		//int getP() const {return pp;}
		//void set(const mpz_class& input);
		ModInt pow (const ModInt& exponent) const;
		ModInt pow (const mpz_class exponent) const;
		ModInt pow (const int exponent) const;
		ModInt sqrt() const;
		ModInt operator+(const ModInt & aa) const;
		ModInt operator-(const ModInt & aa) const;
		ModInt operator* (const ModInt & aa) const;
		ModInt operator* (const mpz_class aa) const;
		ModInt operator* (const int aa) const;
		ModInt operator/ (const ModInt& aa) const;
		ModInt operator/ (const mpz_class aa) const;
		ModInt operator/ (const int aa) const;
		ModInt operator= (const ModInt& aa);
		bool operator== (const ModInt& aa) const;
		bool operator== (const int& aa) const;
		/*
		int operator& (const ModInt& aa);
		int operator& (const int& aa);
		*/
		//ModInt invert();
		std::ostream &print(std::ostream &dest) const { return dest << value;}
		const mpz_class pp;
		mpz_class value;
	private:
		
};

#endif