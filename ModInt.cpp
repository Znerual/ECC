//ModInt module
#include "ModInt.hpp"

template <int N>
void ModInt<N>::set(const BigInteger<N>& input) {
	if (input < 0) {
		value = input % pp + pp; 
		return;
	} else if (input >= pp) {
		value = input % pp; 
		return;
	}
	value = input;
}

bool ModInt::operator== (const ModInt& aa) {
	return value == aa.get() && pp == aa.getP();
}
bool ModInt::operator== (const int& aa) {
	return value == aa;
}
ModInt ModInt::pow (const ModInt& exponent) {
	constexpr unsigned int BITCOUNT = sizeof(pp)*CHAR_BIT;
	ModInt nn = ModInt(pp,value);
	ModInt rr = ModInt(pp,1);
	for (int bit = 0; bit < BITCOUNT; bit++) {
		if (exponent.get() & (1 << bit)) {
			rr =  rr*nn;
		}
		nn = nn*nn;
	}
	return rr;
}
ModInt ModInt::operator+(const ModInt & aa) {
	ModInt rr(pp);
	if (value + aa.get() >= pp) {
		rr.set(value + aa.get() - pp);
	} else {
		rr.set(value + aa.get());
	}
	return rr;
}
ModInt ModInt::operator-(const ModInt & aa) {
	ModInt rr(pp);
	if (value - aa.get() < 0) {
		rr.set(value - aa.get() + pp);
	} else {
		rr.set(value - aa.get());
	}
	return rr;		
}
ModInt ModInt::operator* (const ModInt & aa) {
	constexpr unsigned int BITCOUNT = sizeof(pp)*CHAR_BIT;
	ModInt rr = ModInt(pp);
	ModInt nn = ModInt(*this);
	for (unsigned int bit = 0; bit < BITCOUNT; bit++) {
		if (aa.get() & (1 << bit)) {
			rr += nn;
		}
		nn *= 2;
	}
	return rr;
}
ModInt ModInt::operator/ (const ModInt& aa) {
	ModInt rr = ModInt(aa); 
	return (*this) * rr.invert();
}
/*
int ModInt::operator& (const ModInt& aa) {
	return (value & aa.get());
}
int ModInt::operator& (const int& aa) {
	return (value & aa);
}
*/
ModInt ModInt::operator= (const ModInt& aa){
	if (pp == aa.getP()) {
		value = aa.get();
		return *this;
	}
	throw "Invalid assignment for different rooms";
}
ModInt ModInt::operator+= (const ModInt& aa) {
	if (pp == aa.getP()) {
		this->set(value + aa.get());
		return *this;
	}
	throw "Invalid assignment for different rooms";
}
ModInt ModInt::operator*= (const ModInt& aa) {
	if (pp == aa.getP()) {
		this->set(value * aa.get());
		return *this;
	}
	throw "Invalid assignment for different rooms";
}
ModInt ModInt::operator*= (const int& aa) {
	this->set(value * aa);
	return *this;
}
//use invert(p,j) with p as prime number and j as the element to be inverted
ModInt ModInt::invert() {
	//extended euclidian algorithm
	ModInt rr = ModInt(pp);
	int s {1}, t {0}, u {0}, v{1}, ii {pp}, jj{value} ;
	while (jj != 0) {
		int q = ii / jj;
		int r = ii % jj;
		int unew = s;
		int vnew = t;
		s = u - (q * s);
		t = v - (q * t);
		ii = jj;
		jj = r;
		u = unew;
		v = vnew;
	}
	rr.set(u);
	return rr;
}