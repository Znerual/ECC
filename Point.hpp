// Point header
#ifndef POINT_HEADER
#define POINT_HEADER

#include <gmp.h>
#include <gmpxx.h>

#ifndef MODINT_HEADER
#include "ModInt.hpp"
#endif

#ifndef ELLIPTICCURVE_HEADER
#include "EllipticCurve.hpp"
#endif

class Point {
	public:
		Point(const EllipticCurve& input_curve) : curve(input_curve), xx(ModInt(curve.pp)), yy(ModInt(curve.pp)), infinity(false) {}
		Point(const EllipticCurve& input_curve, bool infinity) : curve(input_curve), xx(ModInt(curve.pp)), yy(ModInt(curve.pp)), infinity(infinity) {}
		Point(const EllipticCurve& i_curve,const ModInt i_xx) : curve(i_curve), xx(i_xx), yy(ModInt(curve.pp)), infinity(false)  {
			yy = ModInt(curve.pp);
			yy = (i_xx.pow(3) + curve.aa * i_xx + curve.bb).sqrt();
		}
		Point(const EllipticCurve& input_curve,const ModInt& xx,const ModInt& yy) :curve(input_curve),  xx(xx), yy(yy), infinity(false) {}
		Point(const Point& aa) : curve(aa.curve), xx(aa.xx), yy(aa.yy), infinity(aa.infinity) {}
		Point(Point && aa) : curve(std::move(curve)), xx(std::move(aa.xx)), yy(std::move(aa.yy)), infinity(aa.infinity) {}
		Point operator=(const Point &aa);
		bool operator==(const Point & aa) const;
		Point operator+(const Point & aa) const;
		Point operator*(const ModInt kk) const;
		bool isOnCurve() const;
		std::ostream &print(std::ostream &dest) const { return dest << "Inf: " << (infinity ? "Yes" : "No") << ", x: " << xx << ", y: " << yy;}
	private:
		EllipticCurve curve;
		ModInt xx;
		ModInt yy;
		bool infinity;
};
/*std::ostream &operator<<(std::ostream &os,const Point &w) { 
     return w.write(os);
}
*/
#endif