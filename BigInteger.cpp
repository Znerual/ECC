//BigInteger module
#include "BigInteger.hpp"

//Contructors
template<int N>
BigInteger<N>::BigInteger(const long long value) : negative(false), data(std::make_unique<unsigned int[]>(N)) {
	negative = value < 0 ? true : false;
	if (value <= UINT_MAX && value >= UINT_MAX) {
		data[0] = std::abs(value);
		filled = value == 0 ? 0 : 1;
		return;
	}
	unsigned long long rest = std::abs(value);
	int i = 0;
	while (rest != 0 && i < N) {
		data[i++] = rest%UINT_MAX;
		rest /= UINT_MAX;
	}
	filled = i;
}

//conversion
template<int N>
BigInteger<N>::operator bool() const {
	for (int i =0 ; i < N;i++) {
		if (data[i] != 0) return true;
	}
	return false;
}

//operators

template<int N>
BigInteger<N> BigInteger<N>::operator+(const BigInteger& other) {
	//check for negative values
	if (this->negative && !other.negative) {
		BigInteger<N> signFlipped = BigInteger<N>(*this);
		signFlipped.negative = !signFlipped.negative;
		return (other - signFlipped);
	} 
	if (!this->negative && other.negative) {
		BigInteger<N> signFlipped = BigInteger<N>(other);
		signFlipped.negative = !signFlipped.negative;
		return (*this - signFlipped);
	}
	BigInteger<N> result = BigInteger<N>();
	if (this->negative && other.negative) result.negative = true;
	
	int maxFill = std::max(filled, other.filled);
	result.filled = maxFill;
	int carry = 0; //a = data, b = other.data
	for (int i = 0; i < maxFill+1; i++) { //evt. ein int filled einbauen und i < filled machen
		if ((UINT_MAX - other.data[i] < carry) || (UINT_MAX - data[i] < carry + other.data[i])) { //overflow
			result.set(i,carry + data[i] - (UINT_MAX + 1 - other.data[i])); //+1 because basis = UINT_MAX + 1
			carry = 1;
			result.filled = result.filled == i+1 ? result.filled + 1 : result.filled; 
		} else {
			result.set(i,other.get(i) + data[i] + carry);
			carry = 0;
		}
	}
	
	if (carry != 0) throw "Overflow!";
	return result;
}

template<int N>
BigInteger<N> BigInteger<N>::operator-(const BigInteger& other) { //calculates *this - other
	//check for negative values
	if (this->negative && !other.negative) {
		BigInteger<N> signFlipped = BigInteger<N>(*this);
		signFlipped.negative = !signFlipped.negative;
		return (other + *this);	
	}
	if (!this->negative && other.negative) {
		BigInteger<N> signFlipped = BigInteger<N>(other);
		signFlipped.negative = !signFlipped.negative;
		return (*this + other);
	} 
	BigInteger<N> result = BigInteger<N>();
	if (this->negative && other.negative) result.negative = true;

	const BigInteger<N>* ll;
	const BigInteger<N>* rr;
	//check for subtractions that would get negative
	if (*this < other) {
		rr = this;
		ll = &other;
		result.negative = !result.negative;
	} else {
		ll = this;
		rr = &other;
	}
	int maxFill = std::max(filled, other.filled);
	result.filled = 0;
	int carry = 0;
	for (int i = 0; i < maxFill; i++) { 
		if (rr->get(i) + carry > ll->data[i]) { 
			result.set(i,ll->data[i] + (UINT_MAX + 1 - rr->get(i) - carry)); //+1 because basis = UINT_MAX + 1
			carry = 1;
		} else {
			result.set(i,ll->data[i] - rr->get(i) - carry);
			carry = 0;
		}
		result.filled = result[i] == 0 ? result.filled : i + 1;
	}
	if (carry == 1) throw "Underflow!";
	return result;
}

template<int N>
BigInteger<N> BigInteger<N>::operator*(const BigInteger<N>& other) {
	constexpr int firstBitValue = 1;
	BigInteger<N> result = BigInteger<N>();
	if (filled == 0 || other.filled == 0) return result;
	
	
	
	BigInteger<N> rr, ll;
	
	//lefthand side operand defindes number of shifts
	if (*this < other) {  //this left
		rr = BigInteger<N>(other);
		ll = BigInteger<N>(*this);
		rr.negative = false;
		ll.negative = false;
	} else { //other left
		ll = BigInteger<N>(other);
		rr = BigInteger<N>(*this);
		rr.negative = false;
		ll.negative = false;
	}
	//std::cout << ll << " left (filled:" << ll.filled << ") and " << rr << " right (filled:" << rr.filled << ")" << std::endl;
	//std::cout << " sizeof int " << sizeof(int) << " char_bit " << CHAR_BIT << std::endl;
	while (ll > 1) { //-1 because no shift for the last one	
		if (ll & firstBitValue) { //uneven 
			result = result + rr;
		}
		rr = rr << 1;
		ll = ll >> 1;
		//std::cout << result << " as result with " << ll << " left and " << rr << " right" << std::endl;		
	}
	if (ll & firstBitValue) { //last iteration dont need shift uneven 
		result = result + rr;
	}
	//check for negative values
	if (this->negative && !other.negative) result.negative = true;
	if (!this->negative && other.negative) result.negative = true;
	return result;
}

//Helper for the division
template<int N>
void BigInteger<N>::shiftLeft(const int& amount) {
	if (filled == N) throw "Overflow!";
	for (int i = filled - 1; i >= 0; i--) {
		data[i+1] = data[i];
	}
	filled += 1;
}
template<int N>
void BigInteger<N>::shiftRight(const int& amount) {
	for (int i = 0; i < filled; i++) {
		data[i] = data[i+1];
	}
	filled = filled > 0 ? filled - 1: 0;
}
		
		
template<int N>
BigInteger::div_bigt BigInteger<N>::div(const BigInteger& other) {
	div_bigt result;
	result.quot = BigInteger();
	result.rem = BigInteger();
	
	
}

template<int N>
BigInteger<N>& BigInteger<N>::operator=(const BigInteger& other) {
	negative = other.negative;
	filled = other.filled;
	data = nullptr;
	data = std::make_unique<unsigned int[]>(N);
	for (int i = 0; i < N; i++) {
		data[i] = other.get(i);
	}
	return *this;
}

template<int N>
BigInteger<N> BigInteger<N>::operator&(const BigInteger<N>& other) const {
	BigInteger<N> result = BigInteger<N>();
	for (int i = 0; i < N; i++) {
		result.data[i] = data[i] & other.get(i);
		//std::cout << "data at i " << data[i] << " other at i " << other.get(i) << " result of & " << (data[i] & other.get(i)) << std::endl;
	}
	return result;
}

template<int N>
BigInteger<N> BigInteger<N>::operator&(const int other) const {
	return data[0] & other;
}
//shift
template<int N>
BigInteger<N> BigInteger<N>::operator<<(const int& amount) {
	constexpr int lastBitValue = 1 << sizeof(int) * CHAR_BIT - 1; //actualy the value of lastBit - 1
	BigInteger<N> result = BigInteger<N>(*this);
	int carry = 0;
	for (int a = 0; a< amount; a++) {
		carry = 0;
		int i;
		int tmp_fill = result.filled;
		for (i = 0; i < result.filled + 1; i++){
			int tmp_carry = result.data[i] & lastBitValue ? 1 : 0;
			result.data[i] = result.data[i] << 1;
			result.data[i] += carry;
			carry = tmp_carry;
			if (i == tmp_fill - 1 && carry != 0) result.filled += 1;
			//std::cout << "(<< Function): a: " << a << " at i " << i << " carry " << carry << " data " << result.data[i] << " filled " << result.filled << std::endl; 
		}
		
		if (i == N - 1 && carry != 0) throw "Overflow!";
	}
	return result;
}
template<int N>
BigInteger<N> BigInteger<N>::operator>>(const int& amount) {
	constexpr int firstBitValue = 1;
	constexpr int lastBitValue = 1 << (sizeof(int) * CHAR_BIT - 1);
	BigInteger<N> result = BigInteger<N>(*this);
	int carry;
	for (int a = 0; a<amount; a++) {
		carry = 0;
		for (int i = filled-1; i >= 0; i--) { //replace N-1 with filled
			int tmp_carry = result.data[i] & firstBitValue ? lastBitValue : 0; //checks if first bit is 1 and sets the carry if it is 
			if (result.data[i] == 1) result.filled -= 1;
			result.data[i] = result.data[i] >> 1;
			result.data[i] += carry;
			carry = tmp_carry;
		}
	}
	return result;
}

//comparison

template<int N>
bool BigInteger<N>::operator==(const BigInteger<N>& other) const {
	if (negative != other.negative && data[0] != 0) return false;
	for (int i = 0; i < N; i++) {
		if (data[i] != other.get(i)) return false;
	}
	return true;
}
template<int N>
bool BigInteger<N>::operator==(const int& other) const {
	if (other == 0 && filled == 0) return true;
	if (filled > 1) return false;
	return (data[0] == std::abs(other) && ((negative && other <= 0) || (!negative && other >= 0))) ;
}


template<int N>
bool BigInteger<N>::operator<(const BigInteger<N>& other) const { //*this < other; 
	if (negative && !other.negative && data[0] != 0) return true;
	if (!negative && other.negative && data[0] != 0) return false;
	for (int i = N-1; i >= 0; i--) {
		if (data[i] < other.get(i)) {
			return true;
		} else if (data[i] > other.get(i)) {
			return false;
		}
	}
	return false;
}

template<int N>
bool BigInteger<N>::operator<(const int& other) const { //*this < other; 
	if (filled > 1 && !negative) return false;
	if (filled > 1 && negative) return true;
	if (negative && other > 0) return true;
	if (!negative && other < 0) return false;
	return data[0] < std::abs(other);
}

template<int N>
bool BigInteger<N>::operator>(const BigInteger<N>& other) const { //*this > other; 
	if (negative && !other.negative && data[0] != 0) return false;
	if (!negative && other.negative && data[0] != 0) return true;
	for (int i = N-1; i >= 0; i--) {
		if (data[i] > other.get(i)) {
			return true;
		} else if (data[i] < other.get(i)){
			return false;
		}
	}
	return false;
}

template<int N>
bool BigInteger<N>::operator>(const int& other) const { //*this > other; 
	if (filled > 1 && !negative) return true;
	if (filled > 1 && negative) return false;
	if (negative && other > 0 && data[0] != 0) return false;
	if (!negative && other < 0 && data[0] != 0) return true;
	return data[0] > other;
}

template<int N>
bool BigInteger<N>::operator<=(const BigInteger<N>& other) const { //*this <= other; 
	return !(other > *this);
}

template<int N>
bool BigInteger<N>::operator<=(const int& other) const { //*this <= other; 
	return !(other > *this);
}

template<int N>
bool BigInteger<N>::operator>=(const BigInteger<N>& other) const { //*this >= other; 
	return !(other < *this);
}
template<int N>
bool BigInteger<N>::operator>=(const int& other) const { //*this >= other; 
	return !(other < *this);
}


//output

template<int N>
std::ostream& BigInteger<N>::write(std::ostream& os) const {
	//basis = UINT_MAX + 1 which can't be calculated with integers because of overflow
	const std::string intMaxString = std::to_string(UINT_MAX);
	const int stringLength = intMaxString.length();
	const std::string basis = intMaxString.substr(0, stringLength - 1) + std::to_string(intMaxString[stringLength-1]-'0' +1);
	negative ? os << "-(" :os <<  "(";
	os << data[0];
	if (filled > 2) {
		for (int i = 1; i < filled -1; i++) {
			os << " + " << data[i] << "*" << basis << "^" << i;
		}
	}
	if (filled > 1) {
		os << " + " << data[filled -1] << "*" << basis << "^" << filled -1 << ")";
	} else {
		os << ")";
	}
	
	return os;
}

int main() {
	BigInteger<4> bi1 = BigInteger<4>(2147483647);
	BigInteger<4> bi2 = BigInteger<4>(256);
	BigInteger<4> bi3 = BigInteger<4>(9223372036854775807L);
	BigInteger<4> bi4 = BigInteger<4>(0);
	BigInteger<4> bi5 = BigInteger<4>(23123809);
	BigInteger<4> bi6 = BigInteger<4>(1);
	BigInteger<4> bi7 = 5;
	
	BigInteger<4> rbi1 = BigInteger<4>();
	BigInteger<4> rbi2 = BigInteger<4>();
	BigInteger<4> rbi3 = BigInteger<4>();
	BigInteger<4> rbi4 = BigInteger<4>();
	BigInteger<4> rbi5 = BigInteger<4>();
	
	//comparison tests
	std::cout  << bi1 << " > " << bi3 << " == " << (bi1 > bi3) << std::endl;
	std::cout  << bi3 << " > " << bi1 << " == " << (bi3 > bi1) << std::endl;
	std::cout  << bi4 << " > " << bi6 << " == " << (bi4 > bi6) << std::endl;
	
	std::cout  << bi5 << " < " << bi1 << " == " << (bi5 < bi1) << std::endl;
	std::cout  << bi4 << " < " << bi6 << " == " << (bi4 < bi6) << std::endl;
	
	
	//operator tests
	rbi1 = bi1 + bi3;
	std::cout << "add " << bi1 << " and " << bi3 << " = " << rbi1 << std::endl;
	rbi1 = bi2 << 30;
	std::cout << "leftshif " << bi2 << " by " << 30 << " = " << rbi1 << std::endl;
	
	rbi2 = bi2 - bi4;
	std::cout << "subtract " << bi4 << " from " << bi2 << " = " << rbi2 << std::endl;
	rbi2 = bi2 >> 2;
	std::cout << "rightshif " << bi2 << " by " << 2 << " = " << rbi2 << std::endl;
	
	//rbi1 = bi2 * bi7;
	//std::cout << "mulitply " << bi2 << " with " << bi7 << " = " << rbi1 << std::endl;
	rbi2 = bi1 * bi4;
	std::cout << "mulitply " << bi1 << " with " << bi4 << " = " << rbi2 << std::endl;
	rbi3 = bi1 * bi6;
	std::cout << "mulitply " << bi1 << " with " << bi6 << " = " << rbi3 << std::endl;
	rbi3 = bi6 << 34;
	rbi4 = rbi3 * rbi3;
	std::cout << "mulitply " << rbi3 << " with " << rbi3 << " = " << rbi4 << std::endl;
	rbi5 = bi3 * bi7;
	std::cout << "mulitply " << bi3 << " with " << bi7 << " = " << rbi5 << std::endl;
	
	rbi2 = bi3 * bi5;
	std::cout << "mulitply " << bi3 << " with " << bi5 << " = " << rbi2 << std::endl;
	rbi3 = bi6 << 34;
	rbi4 = rbi3 * rbi3;
	std::cout << "mulitply " << bi1 << " with " << bi3 << " = " << (bi1*bi3) << std::endl;
	rbi5 = bi3 * bi7;
	std::cout << "mulitply " << rbi3 << " with " << bi3 << " = " << (rbi3*bi3) << std::endl;
	//rbi3 = bi6;
	//rbi3 = rbi3 << 8;
	
	//rbi4 = bi2 & bi1;
	//std::cout << "rbi1 " << rbi1 << " \nrbi2 " << rbi2 <<  " \nrbi3 " << rbi3 << " rbi4 " << rbi4 << std::endl;
	
	//comparions tests
	//std::cout << "rbi3 == bi2 " << (rbi3 == bi2) << ", rbi3 == bi3 " << (rbi3 == bi3) << std::endl;
	BigInteger<4> result = BigInteger<4>();
	while (true) {
		unsigned int aa,bb;
		char selection;
		std::cout << "Gib eine Zahl ein " << std::endl;
		std::cin >> aa;
		std::cin.clear();
		BigInteger<4> bia = aa;
		std::cout << "Und einen Operator (+,-,*)" << std::endl;
		std::cin >> selection;
		std::cout << result << selection << bia; 
		switch (selection) {
			case '+':
				result = bia + result;
				break;
			case '-':
				result = result- bia;
				break;
			case '*':
				result = bia * result;
				break;
		}
		std::cout << " = " << result << std::endl;
	}
}
