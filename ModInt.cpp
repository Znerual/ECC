//ModInt module
#ifndef MODINT_HEADER
#include "ModInt.hpp"
#endif
/*
void ModInt::set(const mpz_class& input) {
	if (input < 0) {
		value = input % pp + pp; 
		return;
	} else if (input >= pp) {
		value = input % pp; 
		return;
	}
	value = input;
}
*/
bool ModInt::operator== (const ModInt& aa) const{
	return aa.value == value;
	//return value == aa.value && pp == aa.pp;
}
bool ModInt::operator== (const int& aa) const{
	return value == aa;
	//return value == aa;
}
/* Toni-Shanks algorithm
see https://gmplib.org/list-archives/gmp-devel/2006-May/000633.html
*/
ModInt ModInt::sqrt () const{
	ModInt result = ModInt(pp);
	
    mpz_t w, n_inv, y;
    unsigned int i, s;
 
	
    if(mpz_divisible_p(value.get_mpz_t(), pp.get_mpz_t())) {         /* Is value.get_mpz_t() a multiple of pp.get_mpz_t()?            */
        mpz_set_ui(result.value.get_mpz_t(), 0);               /* Yes, then the square root is 0.  */
        return result;                       /* (special case, not caught        */
    }                                   /* otherwise)                       */
    if(mpz_legendre(value.get_mpz_t(), pp.get_mpz_t()) != 1)         /* Not a quadratic residue?         */
        return result;                       /* No, so return error              */
    if(mpz_tstbit(pp.get_mpz_t(), 1) == 1) {         /* pp.get_mpz_t() = 3 (mod 4) ?                  */
        mpz_set(result.value.get_mpz_t(), pp.get_mpz_t());
        mpz_add_ui(result.value.get_mpz_t(), result.value.get_mpz_t(), 1);
        mpz_fdiv_q_2exp(result.value.get_mpz_t(), result.value.get_mpz_t(), 2);
        mpz_powm(result.value.get_mpz_t(), value.get_mpz_t(), result.value.get_mpz_t(), pp.get_mpz_t());           /* result.get_mpz_t() = value.get_mpz_t() ^ ((pp.get_mpz_t()+1) / 4) (mod pp.get_mpz_t())      */
        return result;
    }
    mpz_init(y);
    mpz_init(w);
    mpz_init(n_inv);
    mpz_set(result.value.get_mpz_t(), pp.get_mpz_t());
    mpz_sub_ui(result.value.get_mpz_t(), result.value.get_mpz_t(), 1);                /* result.get_mpz_t() = pp.get_mpz_t()-1                          */
    s = 0;                              /* Factor out 2^s from result.get_mpz_t()            */
    while(mpz_tstbit(result.value.get_mpz_t(), s) == 0) s++;
    mpz_fdiv_q_2exp(result.value.get_mpz_t(), result.value.get_mpz_t(), s);           /* result.get_mpz_t() = result.get_mpz_t() / 2^s                      */
    mpz_set_ui(w, 2);                   /* Search for a non-residue mod pp.get_mpz_t()   */
    while(mpz_legendre(w, pp.get_mpz_t()) != -1)     /* by picking the first w such that */
        mpz_add_ui(w, w, 1);            /* (w/pp.get_mpz_t()) is -1                      */
    mpz_powm(w, w, result.value.get_mpz_t(), pp.get_mpz_t());               /* w = w^result.get_mpz_t() (mod pp.get_mpz_t())                  */
    mpz_add_ui(result.value.get_mpz_t(), result.value.get_mpz_t(), 1);
    mpz_fdiv_q_2exp(result.value.get_mpz_t(), result.value.get_mpz_t(), 1);           /* result.get_mpz_t() = (result.get_mpz_t()+1) / 2                    */
    mpz_powm(result.value.get_mpz_t(), value.get_mpz_t(), result.value.get_mpz_t(), pp.get_mpz_t());               /* result.get_mpz_t() = value.get_mpz_t()^result.get_mpz_t() (mod pp.get_mpz_t())                  */
    mpz_invert(n_inv, value.get_mpz_t(), pp.get_mpz_t());
    for(;;) {
        mpz_powm_ui(y, result.value.get_mpz_t(), 2, pp.get_mpz_t());        /* y = result.get_mpz_t()^2 (mod pp.get_mpz_t())                  */
        mpz_mul(y, y, n_inv);
        mpz_mod(y, y, pp.get_mpz_t());               /* y = y * value.get_mpz_t()^-1 (mod pp.get_mpz_t())             */
        i = 0;
        while(mpz_cmp_ui(y, 1) != 0) {
            i++;
            mpz_powm_ui(y, y, 2, pp.get_mpz_t());    /*  y = y ^ 2 (mod pp.get_mpz_t())               */
        }
        if(i == 0) {                    /* result.get_mpz_t()^2 * value.get_mpz_t()^-1 = 1 (mod pp.get_mpz_t()), return   */
            return result;
        }
        if(s-i == 1) {                  /* In case the exponent to w is 1,  */
            mpz_mul(result.value.get_mpz_t(), result.value.get_mpz_t(), w);           /* Don't bother exponentiating      */
        } else {
            mpz_powm_ui(y, w, 1 << (s-i-1), pp.get_mpz_t());
            mpz_mul(result.value.get_mpz_t(), result.value.get_mpz_t(), y);
        }
        mpz_mod(result.value.get_mpz_t(), result.value.get_mpz_t(), pp.get_mpz_t());               /* r = r * w^(2^(s-i-1)) (mod pp.get_mpz_t())    */
    }
	return result;
}


ModInt ModInt::pow (const ModInt& exponent) const {
	ModInt rr(pp);
	mpz_powm(rr.value.get_mpz_t(), value.get_mpz_t(), exponent.value.get_mpz_t(), pp.get_mpz_t());
	return rr;
	/*constexpr unsigned int BITCOUNT = sizeof(pp)*CHAR_BIT;
	ModInt nn = ModInt(pp,value);
	ModInt rr = ModInt(pp,1);
	for (int bit = 0; bit < BITCOUNT; bit++) {
		if (exponent.get() & (1 << bit)) {
			rr =  rr*nn;
		}
		nn = nn*nn;
	}
	return rr;
	*/
}
ModInt ModInt::pow (const mpz_class exponent) const{
	ModInt rr(pp);
	mpz_powm(rr.value.get_mpz_t(), value.get_mpz_t(), exponent.get_mpz_t(), pp.get_mpz_t());
	return rr;
}
ModInt ModInt::pow (const int exponent) const{
	ModInt rr(pp);
	mpz_class mpz_exponent(exponent);
	mpz_powm(rr.value.get_mpz_t(), value.get_mpz_t(), mpz_exponent.get_mpz_t(), pp.get_mpz_t());
	return rr;
}
ModInt ModInt::operator+(const ModInt & aa) const{
	ModInt rr(pp);
	rr.value = value + aa.value;
	if (rr.value >= pp || rr.value < 0) {
		mpz_mod(rr.value.get_mpz_t(), rr.value.get_mpz_t(), pp.get_mpz_t());
	}
	return rr;
}
ModInt ModInt::operator-(const ModInt & aa) const{
	ModInt rr(pp);
	rr.value = value - aa.value;
	if (rr.value < 0 || rr.value >= pp) {
		mpz_mod(rr.value.get_mpz_t(), rr.value.get_mpz_t(), pp.get_mpz_t());
	} 
	return rr;		
}
ModInt ModInt::operator* (const ModInt & aa) const{
	ModInt rr(pp);
	mpz_mul(rr.value.get_mpz_t(), value.get_mpz_t(), aa.value.get_mpz_t());
	mpz_mod(rr.value.get_mpz_t(), rr.value.get_mpz_t(), pp.get_mpz_t());
	return rr;
	/*
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
	*/
}
ModInt ModInt::operator* (const mpz_class aa) const{
	ModInt rr(pp);
	mpz_mul(rr.value.get_mpz_t(), value.get_mpz_t(), aa.get_mpz_t());
	mpz_mod(rr.value.get_mpz_t(), rr.value.get_mpz_t(), pp.get_mpz_t());
	return rr;
}
ModInt ModInt::operator* (const int aa) const{
	ModInt rr(pp);
	mpz_class mpz_aa = mpz_class(aa);
	mpz_mul(rr.value.get_mpz_t(), value.get_mpz_t(), mpz_aa.get_mpz_t());
	mpz_mod(rr.value.get_mpz_t(), rr.value.get_mpz_t(), pp.get_mpz_t());
	return rr;
}
ModInt ModInt::operator/ (const ModInt& aa) const{
	ModInt rr(pp);
	mpz_class tmp = 0;
	mpz_class mpz_inv = mpz_class(aa.value);
	mpz_gcdext(tmp.get_mpz_t(),mpz_inv.get_mpz_t(), tmp.get_mpz_t(), aa.value.get_mpz_t(), pp.get_mpz_t());
	mpz_mul(rr.value.get_mpz_t(), value.get_mpz_t(), mpz_inv.get_mpz_t());
	mpz_mod(rr.value.get_mpz_t(), rr.value.get_mpz_t(), pp.get_mpz_t());
	return rr;
	/*
	ModInt rr = ModInt(aa); 
	return (*this) * rr.invert();
	*/
}
ModInt ModInt::operator/ (const mpz_class aa) const{
	ModInt rr(pp);
	mpz_class tmp = 0;
	mpz_class mpz_inv = mpz_class(aa);
	mpz_gcdext(tmp.get_mpz_t(), mpz_inv.get_mpz_t(),tmp.get_mpz_t(), aa.get_mpz_t(), pp.get_mpz_t());
	mpz_mul(rr.value.get_mpz_t(), value.get_mpz_t(), mpz_inv.get_mpz_t());
	mpz_mod(rr.value.get_mpz_t(), rr.value.get_mpz_t(), pp.get_mpz_t());
	return rr;
}
ModInt ModInt::operator/ (const int aa) const{
	ModInt rr(pp);
	mpz_class mpz_aa = mpz_class(aa);
	mpz_class mpz_inv = mpz_class(aa);
	mpz_class tmp = 0;
	//invert a with gcdextended
	mpz_gcdext(tmp.get_mpz_t(), mpz_inv.get_mpz_t(),tmp.get_mpz_t(), mpz_aa.get_mpz_t(), pp.get_mpz_t());
	mpz_mul(rr.value.get_mpz_t(), value.get_mpz_t(), mpz_inv.get_mpz_t());
	mpz_mod(rr.value.get_mpz_t(), rr.value.get_mpz_t(), pp.get_mpz_t());
	return rr;
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
	if (pp == aa.pp) {
		value = aa.value;
		return *this;
	}
	throw "Invalid assignment for different rooms";
}

//use invert(p,j) with p as prime number and j as the element to be inverted
//ModInt ModInt::invert() {
	/*
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
	*/
//}
/*
int main() {
	std::cout << "TEst" <<std::endl;
	mpz_class prime = mpz_class(29);
	ModInt first = ModInt(prime, 28);
	ModInt second = ModInt(prime, 27);
	
	ModInt result = first * second / first * second + first;
	std::cout<< result << std::endl;
}
*/