//ECC Key generation library
#include<cmath>
#include<climits>
#include<iostream>

#ifndef MODINT_HEADER
#include "ModInt.hpp"
#endif
#ifndef ELLIPTICCURVE_HEADER
#include "EllipticCurve.hpp"
#endif

#ifndef POINT_HEADER
#include "Point.hpp"
#endif

#ifndef KEYGENERATOR_HEADER
#include "KeyGenerator.hpp"
#endif

Point Point::operator=(const Point &aa) {
	xx = aa.xx;
	yy = aa.yy;
	infinity = aa.infinity;
	curve = aa.curve;
	return *this;
}
bool Point::operator==(const Point & aa) const {
	return (infinity == aa.infinity && xx == aa.xx && yy == aa.yy);
}
Point Point::operator+(const Point & aa) const {
	Point rr = Point(curve);
	//check if one point is at infinity
	std::cout << *this << " und " << aa << std::endl;
	if (aa.infinity) {
		rr = *this;
		return rr;
	} else if (infinity) {
		rr = aa;
		return rr;
	}
	if (aa == *this) {
		std::cout << "Mit sich selbst addieren" << std::endl;
		ModInt ss = ((aa.xx.pow(2)*3) + curve.aa) / (aa.yy * 2);
		std::cout << "s " << ss << std::endl;
		rr.xx = ss.pow(2) - aa.xx * 2;
		std::cout << "rx " << rr.xx << std::endl;
		rr.yy = ss * (aa.xx - rr.xx) - aa.yy;
		std::cout << "ry " << rr.yy << std::endl;
	} else {
		std::cout << "Mit anderen addieren" << std::endl;
		ModInt ss = (yy - aa.yy) / (xx - aa.xx);
		std::cout << "s " << ss << std::endl;
		rr.xx = ss.pow(2) - xx - aa.xx;
		std::cout << "rx " << rr.xx << std::endl;
		rr.yy = ss*(xx-rr.xx)-yy;
		std::cout << "ry " << rr.yy << std::endl;
	}
	
	return rr;
}
Point Point::operator*(const ModInt kk) const{
	Point rr = Point(curve, true);
	
	Point nn = Point(*this);
	mpz_class tmp_result = 0;
	mpz_class i = mpz_class(0);
	for (i = 0; i < curve.bitlength; i++) {
		mpz_tdiv_r_2exp(tmp_result.get_mpz_t(), kk.value.get_mpz_t(),i.get_ui());
		if (tmp_result == 0) { //if bits match
			rr = rr + nn;//add the points
		}
		nn = nn + nn;
	}
	
	return rr;
}
bool Point::isOnCurve() const{
	//std::cout << "OnCurve y: " << yy << " y^2: " << yy.pow(2) << ", x: " << xx << ", x^3: " << xx.pow(3);
	//std::cout << ", a: " << curve.aa << ", b: " << curve.bb << std::endl;
	return (yy.pow(2) == xx.pow(3) + curve.aa*xx + curve.bb);
}


int main() {
	/*
	int aI, bI, pI ;
	while (true) {
	std::cout << "Gib nacheinander 3 Zahlen ein (a,b,p)" << std::endl;
	std::cin >> aI >> bI >> pI;
	ModInt am{pI,aI}, bm{pI,bI};
	std::cout << "(a*b)%p = " << am*bm << std::endl;
	}
	*/
	/*
	//std::cout << "(a+b)%p = " << ModInt::add(p, a,b) << std::endl;
	//std::cout << "(a-b)%p = " << ModInt::subtract(p, a,b) << std::endl;
	std::cout << "(a*b)%p = " << ModInt::multiply(p,a,b) << std::endl;
	std::cout << "(a/b)%p = " << ModInt::divide(p,a,b) << std::endl;
	std::cout << "(a^b)%p = " << ModInt::power(p, a,b) << std::endl;
	std::cout << "(a^-1)%p = " << ModInt::invert(p, a) << std::endl;
	
	std::cout << "(a+b)%p = " << am + bm << std::endl;
	std::cout << "(a-b)%p = " << am - bm << std::endl;
	std::cout << "(a*b)%p = " << am * bm << std::endl;
	std::cout << "(a/b)%p = " << am / bm << std::endl;
	std::cout << "(a^b)%p = " << am.pow(bm) << std::endl;
	//std::cout << "(a^-1)%p = " << ModInt::invert(p, a) << std::endl;
	*/
	std::cout << "Test" << std::endl;
	mpz_class prime = 37;
	mpz_class bitlength = 8;
	ModInt a = ModInt(prime, 2);
	ModInt b = ModInt(prime, 7);
	ModInt px1 = ModInt(prime, 10);
	ModInt px2 = ModInt(prime, 31);
	ModInt px3 = ModInt(prime, 4);
	EllipticCurve curve = EllipticCurve(a,b,prime, bitlength);
	Point p1 = Point(curve, px1);
	Point p2 = Point(curve, px2);
	Point p3 = Point(curve, px3);
	std::cout << "Punkt " << p1 << " ist auf Kurve? " << (p1.isOnCurve() ? "Ja!" : "Nein!") <<  std::endl;
	std::cout << "Punkt " << p2 << " ist auf Kurve? " << (p2.isOnCurve() ? "Ja!" : "Nein!") <<  std::endl;
	std::cout << "Punkt " << p3 << " ist auf Kurve? " << (p3.isOnCurve() ? "Ja!" : "Nein!") <<  std::endl;
	Point c =  p1+p3;//p*ModInt(prime,2) ;
	//c = c+ c;
	std::cout << "Punkt " << c << " ist auf Kurve? " << (c.isOnCurve() ? "Ja!" : "Nein!") <<  std::endl;
}