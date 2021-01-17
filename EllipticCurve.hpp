//Elliptic Curve Header
#ifndef ELLIPTICCURVE_HEADER
#define ELLIPTICCURVE_HEADER

#include <gmp.h>
#include <gmpxx.h>

#ifndef MODINT_HEADER
#include "ModInt.hpp"
#endif
//#include "Point.hpp"
class EllipticCurve {
	public:
		EllipticCurve(ModInt aa, ModInt bb, mpz_class pp, mpz_class bitlength) : aa(aa), bb(bb), pp(pp), bitlength(bitlength) { if (aa.pow(3)*4 + bb.pow(2)*27 == 0) throw "Invalid parameters!";}
		EllipticCurve(const EllipticCurve& curve) : aa(curve.aa), bb(curve.bb), pp(curve.pp), bitlength(curve.bitlength) {}
		EllipticCurve operator=(const EllipticCurve& curve) {aa = curve.aa; bb = curve.bb; pp = curve.pp; bitlength = curve.bitlength;return *this;}
	private:
		ModInt aa;
		ModInt bb;
		mpz_class pp;
		mpz_class bitlength;
		friend class Point;
};	
#endif