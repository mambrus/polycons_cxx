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
	{
		// ===========================================
		cout << "Constructor and assignments:" << endl;
		// ===========================================
		Vector A(NELEM(a), a);
		cout << "1:st assignment constructor (array):" << endl;
		cout << A << endl << endl;
		Vector B;
		B = A;

		Vector C(4, 21, 22, 23, 24);
		cout << "2:nd assignment constructor (va_arg):" << endl;
		cout << C << endl << endl;

		Vector D = C;

		cout << "A:" << A << endl
		    << "B:" << B << endl << "C:" << C << endl << "D:" << D <<
		    endl;

		// ===========================================
		cout << "Index operator:" << endl;
		// ===========================================
		for (int i = 0; i < 4; i++) {
			A[i] = 30 + i;
		}

		// Use debugger in this loop as CTOR/DTOR (tmp) operations may occur.
		for (int i = 0; i < 4; i++) {
			B[i] = A[3 - i];
			C[i] = B[3 - i];
			D[i] = C[i] + 1;
		}

		cout << "A:" << A << endl
		    << "B:" << B << endl << "C:" << C << endl << "D:" << D <<
		    endl;

		// ===========================================
		cout << "Test exceptions:" << endl;
		// ===========================================
		//
		// Index operator: Exceed boundaries deliberately
		for (int i = 0; i < (4 + 1); i++) {
			try {
				D[i] = B[i];
			}
			catch(const std::invalid_argument & e) {
				cout <<
				    "Dang! Exception \"invalid_argument\" at index="
				    << i << " and caught. Further info: " <<
				    e.what() << endl;
			}
		}

		cout << "A:" << A << endl
		    << "B:" << B << endl << "C:" << C << endl << "D:" << D <<
		    endl;
	}

	// ===========================================
	cout << "Linear algebra operators (+/-):" << endl;
	// ===========================================
	{
		Vector A(4, 11, 12, 13, 14);
		Vector B(4, 21, 22, 23, 24);
		cout << "A:" << A << endl;
		cout << "B:" << B << endl;
		Vector C = A + B;
		Vector D = B - C;
		cout << "C:" << C << endl;
		cout << "D:" << D << endl;
		cout << "Source variables are now NOT tainted" << endl;
		cout << "A:" << A << endl;
		cout << "B:" << B << endl;
	}

	// ===========================================
	cout << "Linear algebra operators (mul/div):" << endl;
	// ===========================================
	{
		Vector A(4, 11, 12, 13, 14);
		Vector B(4, 33, 44, 55, 66);
		cout << "A:" << A << endl;
		cout << "B:" << B << endl;
		Vector C = A * 2;
		Vector D = B / 3;
		cout << "C:" << C << endl;
		cout << "D:" << D << endl;
		cout << "Source variables are now NOT tainted" << endl;
		cout << "A:" << A << endl;
		cout << "B:" << B << endl;
	}

	//cout << Vector::stats(cout);
	cout << endl;
/*
	hash<int> myobject;
	myobject["a"] = 1;
	cout << myobject["a"] << endl;
	cout << myobject << endl;
*/
	return 0;
}
