//Header BigInteger
#include<memory>
#include<climits>
#include<iostream>
#include<string>
#include<cmath>

template<int N>
class BigInteger {
	public:
		constexpr int size() {return N*sizeof(int);}
		
		//Constructors
		BigInteger() : negative(false), filled(0), data(std::make_unique<unsigned int[]>(N)) {for (int i=0;i<N;i++) data[i]=0; }
		BigInteger(const BigInteger& other) : negative(other.negative), filled(other.filled) {
			data = std::make_unique<unsigned int[]>(N);
			for (int i = 0; i < N; i++) {
				data[i] = other.get(i);
			}
		}
		BigInteger(BigInteger&& other) : negative(other.negative), filled(other.filled), data(std::move(other.data)) {};
		BigInteger(const long long value);
		//conversions
		operator bool() const;
		
		//Member Functions
		//operators
		BigInteger operator+(const BigInteger& other);
		BigInteger operator-(const BigInteger& other);
		BigInteger operator*(const BigInteger& other);
		BigInteger operator%(const BigInteger& other); //*this % other //missing wirklich nötig?
		BigInteger operator<<(const int& amount);
		BigInteger operator>>(const int& amount);
		BigInteger operator&(const BigInteger& other) const;
		BigInteger operator&(const int other) const;
		const unsigned int& operator[](const int index) const {return data[index];}
		BigInteger& operator=(const BigInteger& other);
		//BigInteger& operator+=(const BigInteger& other);
		//BigInteger& operator*=(const BigInteger& other);
		bool operator<(const BigInteger& other) const; 
		bool operator<=(const BigInteger& other) const; 
		bool operator>(const BigInteger& other) const; 
		bool operator>=(const BigInteger& other) const; 
		bool operator==(const BigInteger& other) const;
		bool operator<(const int& other) const; 
		bool operator<=(const int& other) const; 
		bool operator>(const int& other) const; 
		bool operator>=(const int& other) const; 
		bool operator==(const int& other) const;
		//interface
		std::ostream& write(std::ostream& os) const;
		bool getNegative() const {return negative;}
		int getFilled() const {return filled;} //filled == 0 means empty
	private:
		bool negative;
		int filled;
		std::unique_ptr<unsigned int[]> data;
		unsigned int get(int pos) const {return data[pos];}
		void set(int pos, unsigned int value) {data[pos] = value;}
};
template <int N>
std::ostream& operator<<(std::ostream& os, const BigInteger<N>& bi){ return bi.write(os);}
