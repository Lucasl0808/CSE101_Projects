/* Lucas Lee
 * luclee
 * pa6
 * CSE101-02 Spring 2022
 */

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include"BigInteger.h"

using namespace std;

int main(void){
	BigInteger A = BigInteger("+35579758422123123");
	BigInteger B = BigInteger("+35579758422123123");
	BigInteger C = BigInteger("+12345034001");
	cout << "A < B is  " << A.compare(B) << endl;
	cout << B.sign() << endl;
	cout << A << endl;
	cout << B << endl;
	cout << C << endl;
	List L;
	List S;
	L.insertBefore(35);
	L.insertBefore(57);
	L.insertBefore(97);
	S.insertBefore(14);
	S.insertBefore(90);
	S.insertBefore(82);
	cout << L << endl;
	cout << S << endl;
	BigInteger Q = A+B;
	cout << Q << endl;
	BigInteger M = A-B;
	cout << "here " << M << endl;
	
	cout << L << endl;
	BigInteger N = BigInteger("123");
	BigInteger D = BigInteger("456");
	BigInteger G = N*D;
	cout << G << endl;

	BigInteger T("+999");
	BigInteger TT("+999");
	cout << T << endl;
	List PO;
	PO.insertBefore(81);
	PO.insertBefore(81);
	PO.insertBefore(81);
	BigInteger TTT = T*TT;
	cout << TTT << endl;
	BigInteger LL = A*B;
	cout << LL << endl;
	
	BigInteger in1("-0041085449");
	BigInteger in2("7402779357");
	
	cout << in1 << endl;
	cout << in2 << endl;
	BigInteger testadd = in1 + in2;
	cout << testadd << endl;



	BigInteger a("+13378008135");
	A.negate();
	cout << A.sign() << endl;
	A.negate();
	cout << A.sign() << endl;
	BigInteger b = BigInteger();
	b.negate();
	cout << b.sign() << endl;

	BigInteger c("+111122223333");
	BigInteger d("+222211110000");
	BigInteger e("+333333333333");
	BigInteger f = c + d;
	cout << f << endl;
	cout << e << endl;

	BigInteger l("-111122223333");
	BigInteger lc = l + c;
	cout << lc.sign() << endl;

	BigInteger g("-110122223333");
	BigInteger h("1000000000");
	BigInteger i = g + h;
	cout << i.sign() << endl;
	cout << i << endl;
	cout << h << endl;

}
