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

	cout << endl;
	{
		int a[] = {
			11, 12, 13, 14
		};
		int b[] = {
			21, 22, 23, 24
		};
		int c[] = {
			31, 32, 33, 34
		};
		int d[] = {
			41, 42, 43, 44
		};
		Vector < int >A(4, a);
		Vector < int >B(4, b);
		Vector < int >C(4, c);
		Vector < int >m[] = {
			A, B, C
		};
		Vector < Vector < int > >matrix(3, m);
		cout << matrix << endl;
	}

#ifdef NEVER
	cout << endl;
	{
		int a[] = {
			11, 12, 13, 14
		};
		// ===========================================
		cout << "Constructor and assignments <int>:" << endl;
		// ===========================================
		Vector < int >A(NELEM(a), a);
		Vector < int >B;
		B = A;

		Vector < int >C(4, 21, 22, 23, 24);
		Vector < int >D = C;

		cout << "A:" << A << endl
		    << "B:" << B << endl << "C:" << C << endl << "D:" << D <<
		    endl;

		// ===========================================
		cout << "Index operator <int>:" << endl;
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
		cout << "Test exception<int>s:" << endl;
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
	cout << endl;
	{
		double a[] = {
			11.0, 12.0, 13.0, 14.0
		};
		// ===========================================
		cout << "Constructor and assignments <double>:" << endl;
		// ===========================================
		Vector < double >A(NELEM(a), a);
		Vector < double >B;
		B = A;

		Vector < double >C(4, 21.0, 22.0, 23.0, 24.0);
		Vector < double >D = C;

		cout << "A:" << A << endl
		    << "B:" << B << endl << "C:" << C << endl << "D:" << D <<
		    endl;

		// ===========================================
		cout << "Index operator <double>:" << endl;
		// ===========================================
		for (int i = 0; i < 4; i++) {
			A[i] = 30.3 + i;
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
		cout << "Test exceptions <double>:" << endl;
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
#endif //NEVER

#ifdef NO_LINALGEBRA
	// ===========================================
	cout << "Linear algebra operators (+/-):" << endl;
	// ===========================================
	{
		Vector < int >A(4, 11, 12, 13, 14);
		Vector < int >B(4, 21, 22, 23, 24);
		cout << "A:" << A << endl;
		cout << "B:" << B << endl;
		Vector < int >C = A + B;
		Vector < int >D = B - C;
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
		Vector < int >A(4, 11, 12, 13, 14);
		Vector < int >B(4, 33, 44, 55, 66);
		cout << "A:" << A << endl;
		cout << "B:" << B << endl;
		Vector < int >C = A * 2;
		Vector < int >D = B / 3;
		cout << "C:" << C << endl;
		cout << "D:" << D << endl;
		cout << "Source variables are now NOT tainted" << endl;
		cout << "A:" << A << endl;
		cout << "B:" << B << endl;
	}

#endif				//NO_LINALGEBRA

	cout << Vector < int >::stats(cout);
	cout << endl;
/*
	hash<int> myobject;
	myobject["a"] = 1;
	cout << myobject["a"] << endl;
	cout << myobject << endl;
*/
	return 0;
}
