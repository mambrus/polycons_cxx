#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <simple/SimpleFunctions.h>
#include <advanced/AdvancedFunctions.h>
#include <Vector.h>

#include<iostream>
#include<map>
/*
using namespace std;

template < class T > class hash {
 private:
	map < string, T > _map;
 public:
	T & operator[](string x);
	friend ostream & operator<<(ostream & out, const hash < T > &rhs) {
		return out << "test";
	}
};

template < class T > T & hash < T >::operator[](string x) {
	return _map[x];
}
*/
int main(int argc, char *argv[])
{

	int a[] = {
		11, 12, 13, 14
	};

	Vector A(NELEM(a), a);
	Vector B;
	B = A;

	Vector C(4, 21, 22, 23, 24);
	Vector D = C;

	cout << "A:" << A << endl
	    << "B:" << B << endl << "C:" << C << endl << "D:" << D << endl;

/*
	hash<int> myobject;
	myobject["a"] = 1;
	cout << myobject["a"] << endl;
	cout << myobject << endl;
*/
	return 0;
}
