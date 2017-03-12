#ifndef Vector_h
#    define Vector_h
#    include <MathExports.h>
#    include <stdlib.h>
#    include<iostream>

using namespace std;

// Number of elements in array
#    define NELEM( A ) \
	( sizeof(A) / sizeof(A[0]) )

//Temporary type until class is made template able
#    define vtype int

MATH_EXPORT class Vector {

 protected:
	//Sub-optimal ways of keeping track of statistics
	static int instances;
	static int ntotever;
	const inline void statmng() {
		instances++;
		m_uid = ntotever;
		ntotever++;
	};

 private:
	vtype * m_v;
	size_t m_n;
	int m_uid;		/* Unique id. Used for debugging DTOR/CTOR order of
				   tmp/stack instances. */

 public:
	MATH_EXPORT Vector();
	MATH_EXPORT Vector(size_t, vtype[]);
	MATH_EXPORT Vector(size_t ...);

	//Copy constructor
	MATH_EXPORT Vector(const Vector & v);

	// Operators
	// Assignment
	MATH_EXPORT virtual Vector & operator =(const vtype i);
	MATH_EXPORT virtual Vector & operator =(const Vector & v);

	MATH_EXPORT friend ostream & operator<<(ostream & out, const Vector & v) {
		size_t i;
		out << "{";
		for (i = 0; i < v.m_n - 1; i++) {
			out << v.m_v[i] << ",";
		};
		out << v.m_v[i] << "}";
		return out;
	}

	MATH_EXPORT ~ Vector();
};

#endif				//Vector_h
