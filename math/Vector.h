#ifndef Vector_h
#    define Vector_h
#    include <MathExports.h>
#    include <stdlib.h>
#    include <iostream>
#    include <sstream>

using namespace std;

// Number of elements in array
#    define NELEM( A ) \
	( sizeof(A) / sizeof(A[0]) )

MATH_EXPORT template < class VTYPE > class Vector {

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
	VTYPE ** m_v;
	size_t m_n;
	int m_uid;		/* Unique id. Used for debugging DTOR/CTOR order of
				   tmp/stack instances. */
#    ifdef NEVER
	virtual bool is_zero(const VTYPE &);
#	endif

	void free_array();

 public:
	MATH_EXPORT Vector();
	MATH_EXPORT Vector(size_t, VTYPE[]);
#    ifdef NEVER
	MATH_EXPORT Vector(size_t ...);
#	endif

	//Copy constructor
	MATH_EXPORT Vector(const Vector & v);

	// Operators
	// Assignment
	MATH_EXPORT virtual Vector & operator =(const VTYPE i);
	MATH_EXPORT virtual Vector & operator =(const Vector & v);

	// Index operator
	MATH_EXPORT virtual VTYPE & operator[] (size_t i);

#    ifdef NO_LINALGEBRA
	//Linear algebra operators
	MATH_EXPORT const friend Vector operator +(const Vector lhs,
						   const Vector & v);
	MATH_EXPORT const friend Vector operator -(const Vector lhs,
						   const Vector & v);
	MATH_EXPORT const friend Vector operator *(const Vector lhs,
						   const VTYPE & m);
	MATH_EXPORT const friend Vector operator /(const Vector lhs,
						   const VTYPE & d);
#    endif			//NO_LINALGEBRA

	MATH_EXPORT friend ostream & operator<<(ostream & out, const Vector & v) {
		size_t i;
		out << "{";
		for (i = 0; i < v.m_n - 1; i++) {
			out << *(v.m_v[i]) << ",";
		};
		out << *(v.m_v[i]) << "}";
		return out;
	}

	MATH_EXPORT static ostream & stats(ostream & out) {
		out << "{i=";
		out << instances;
		out << ",";
		out << "t=";
		out << ntotever;
		out << "}" << endl;
		return out;
	}

	MATH_EXPORT ~ Vector();
};

#    include "Vector.tpp"

#endif				//Vector_h
