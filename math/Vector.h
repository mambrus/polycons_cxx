#ifndef Vector_h
#    define Vector_h
#    include <stdlib.h>
#    include<iostream>

using namespace std;

// Number of elements in array
#    define NELEM( A ) \
	( sizeof(A) / sizeof(A[0]) )

//Temporary type until class is made template able
#    define vtype int

class Vector {

 private:
	vtype * m_v;
	int m_n;

 public:
	 Vector();
	 Vector(size_t, vtype[]);
	 Vector(size_t ...);

	//Copy constructor
	 Vector(const Vector & v);

	// Operators
	// Assignment
	virtual Vector & operator =(int i);
	virtual Vector & operator =(const Vector & v);

	friend ostream & operator<<(ostream & out, const Vector & v) {
		out << "{";
		for (int i = 0; i < v.m_n; i++) {
			out << v.m_v[i];
		};
		out << "}\n";
		return out;
	}

	~Vector();
};

#endif				//Vector_h
