#include "Vector.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>
#include <stdexcept>
#include <sstream>

// Default constructor
template < class VTYPE >
Vector < VTYPE >::Vector()
{
	statmng();
	m_n = 0;
}

// Copy constructor. Run-time invokes when ever an intermediate object is
// needed. Typically part of an expression, i.e. temporary value of
// sub-expression is created using this constructor.
template < class VTYPE >
Vector < VTYPE >::Vector(const Vector & v)
{
	statmng();
	m_n = v.m_n;
	m_v = (VTYPE *) calloc(v.m_n, sizeof(VTYPE));

	for (size_t j = 0; j < m_n; j++) {
		m_v[j] = v.m_v[j];
	}
}

/* Shallow copy */
template < class VTYPE >
static void assign(VTYPE & lhs, const VTYPE & rhs){
	memcpy(&lhs, &rhs, sizeof(VTYPE));
}

// Assignment constructor  - integer array
template < class VTYPE >
Vector < VTYPE >::Vector(size_t i, VTYPE a[])
{
	statmng();
	m_n = i;
	m_v = (VTYPE *) calloc(i, sizeof(VTYPE));

	for (size_t j = 0; j < i; j++) {
		//m_v[j] = a[j];
		assign(m_v[j],a[j]);
	}
}

#ifdef NEVER
// Assignment constructor  - Note that the type of the arguments is implicit
// and needs to be the same as the Vector
template < class VTYPE >
Vector < VTYPE >::Vector(size_t i ...)
{
	statmng();
	va_list ap;
	VTYPE t;

	va_start(ap, i);
	m_n = i;
	m_v = (VTYPE *) calloc(i, sizeof(VTYPE));

	for (size_t j = 0; j < i; j++) {
		t = va_arg(ap, VTYPE);
		assign(m_v[j],t);
	}
	va_end(ap);
}
#endif //NEVER

// Assignment operator  - Own element type
template < class VTYPE >
Vector< VTYPE > & Vector < VTYPE >::operator =(const VTYPE i)
{
	if (m_n > 1) {
		free(m_v);
		m_v = (VTYPE *) calloc(1, sizeof(VTYPE));
	} else if (m_n == 0) {
		m_v = (VTYPE *) calloc(1, sizeof(VTYPE));
	}
	*m_v = i;
	return *this;
}

// Copy operator (see also copy constructor)
template < class VTYPE >
Vector< VTYPE > & Vector < VTYPE >::operator =(const Vector & v)
{
	if (m_n > 0 && (v.m_n != m_n)) {
		free(m_v);
	}

	m_n = v.m_n;
	m_v = (VTYPE *) calloc(v.m_n, sizeof(VTYPE));

	for (size_t i = 0; i < m_n; i++) {
		m_v[i] = v.m_v[i];
	}
	return *this;
}

// Index operator
template < class VTYPE >
VTYPE & Vector < VTYPE >::operator [](size_t i) {
	if (i > (m_n - 1)) {
		std::ostringstream s;
		s << "Index [" << i <<
		    "] is out of range for Vector[" << (m_n - 1) << "]";
		std::string eMsg(s.str());
		throw std::invalid_argument(eMsg);
	}
	return m_v[i];
}

#ifdef NO_LINALGEBRA
// Add operator
const Vector operator +(const Vector lhs, const Vector & v)
{
	if (lhs.m_n != v.m_n) {
		std::ostringstream s;
		s << "Vectors must have the same dimension to be added. [" <<
		    (lhs.m_n - 1) << "] != [" << (v.m_n - 1) << "]";
		std::string eMsg(s.str());
		throw std::invalid_argument(eMsg);
	}

	for (size_t i = 0; i < lhs.m_n; i++) {
		lhs.m_v[i] += v.m_v[i];
	}
	return lhs;
}

// Subtract operator
const Vector operator -(const Vector lhs, const Vector & v)
{
	if (lhs.m_n != v.m_n) {
		std::ostringstream s;
		s << "Vectors must have the same dimension to be added. [" <<
		    (lhs.m_n - 1) << "] != [" << (v.m_n - 1) << "]";
		std::string eMsg(s.str());
		throw std::invalid_argument(eMsg);
	}

	for (size_t i = 0; i < lhs.m_n; i++) {
		lhs.m_v[i] -= v.m_v[i];
	}
	return lhs;
}

// Multiply operator
const Vector operator *(const Vector lhs, const VTYPE & m)
{
	for (size_t i = 0; i < lhs.m_n; i++) {
		lhs.m_v[i] *= m;
	}
	return lhs;
}

// Division operator
const Vector operator /(const Vector lhs, const VTYPE & d)
{
#    ifdef NEVER
	if (lhs.is_zero(d)) {
		std::ostringstream s;
		s << "Vector division would be by zero! (avoided)";
		std::string eMsg(s.str());
		throw std::invalid_argument(eMsg);
	}
#    endif

	for (size_t i = 0; i < lhs.m_n; i++) {
		lhs.m_v[i] /= d;
	}
	return lhs;
}
#endif				//NO_LINALGEBRA

// Destructor.
template < class VTYPE >
Vector < VTYPE >::~Vector()
{
	--instances;
	if (m_n > 0 && m_v) {
		free(m_v);
	}
}

/* Class stats variables */
// Below is probably not such a good idea...
template < class VTYPE >
int Vector < VTYPE >::instances = 0;

template < class VTYPE >
int Vector < VTYPE >::ntotever = 0;

#    ifdef NEVER
template < class VTYPE >
bool Vector < VTYPE >::is_zero(const VTYPE & d)
{
	if (d == 0)
		return true;
	else
		return false;
}
#    endif
