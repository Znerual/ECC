//ECC Key generation library
#include<cmath>
#include<climits>
#include<iostream>
#include<bitset>
#include "IntegerArithmetic.hpp"


class Point {
	public:
		Point(IntegerArithmetic xx, IntegerArithmetic yy) : pp(pp), xx(xx), yy(yy) {}
		IntegerArithmetic xx;
		IntegerArithmetic yy;
		Point operator==(const Point & aa) {
			return (xx == aa.xx && yy == aa.yy);
		}
		Point operator+(const Point & aa) {
			Point rr;
			if (aa == *this) {
				int ss = 
			} else {
				int ss = IA::divide(pp, IA::subtract(pp, yy, qq.yy), IA::subtract(pp, xx, qq.xx));
				rr.xx = IA::subtract(pp, IA::multiply(pp, ss,ss), IA::add(pp, xx, qq.xx));
				rr.yy = IA::subtract(pp, IA::multiply(pp, ss, IA::subtract(pp, xx, rr.xx)), yy);
			}
			return rr;
		}
	private:
		
};

/*
class EllipticCurve {
	public:
		EllipticCurve(int aa, int bb, int pp) : aa(aa), bb(bb), pp(pp) {}
		Point add(const Point oo,const Point qq) {
			Point rr;
			int ss = IA::divide(pp, IA::subtract(pp, oo.yy, qq.yy), IA::subtract(pp, oo.xx, qq.xx));
			rr.xx = IA::subtract(pp, IA::multiply(pp, ss,ss), IA::add(pp, oo.xx, qq.xx));
			rr.yy = IA::subtract(pp, IA::multiply(pp, ss, IA::subtract(pp, oo.xx, rr.xx)), oo.yy);		
		}
		Point 
		bool isOnCurve(Point point) {
			if (IA::power(pp, point.yy,2) == IA::add(pp, IA::power(pp,point.xx,3), IA::multiply(pp,aa,point.xx), bb)) return true;
			return false;			
		}
	private:
		int aa {}, bb {}, pp{};	
};	
class KeyGenerator {
	public:
		int a;
	private:
		int b;
};
*/

std::ostream &operator<<(std::ostream &os,const IntegerArithmetic &w) { 
     return w.write(os);
}
int main() {
	int a, b, p;
	std::cout << "Gib nacheinander 3 Zahlen ein (a,b,p)" << std::endl;
	std::cin >> a >> b >> p;
	IntegerArithmetic am{p,a}, bm{p,b};
	/*
	//std::cout << "(a+b)%p = " << IntegerArithmetic::add(p, a,b) << std::endl;
	//std::cout << "(a-b)%p = " << IntegerArithmetic::subtract(p, a,b) << std::endl;
	std::cout << "(a*b)%p = " << IntegerArithmetic::multiply(p,a,b) << std::endl;
	std::cout << "(a/b)%p = " << IntegerArithmetic::divide(p,a,b) << std::endl;
	std::cout << "(a^b)%p = " << IntegerArithmetic::power(p, a,b) << std::endl;
	std::cout << "(a^-1)%p = " << IntegerArithmetic::invert(p, a) << std::endl;
	*/
	std::cout << "(a+b)%p = " << am + bm << std::endl;
	std::cout << "(a-b)%p = " << am - bm << std::endl;
	std::cout << "(a*b)%p = " << am * bm << std::endl;
	std::cout << "(a/b)%p = " << am / bm << std::endl;
	std::cout << "(a^b)%p = " << am.pow(bm) << std::endl;
	//std::cout << "(a^-1)%p = " << IntegerArithmetic::invert(p, a) << std::endl;
}