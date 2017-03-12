#include "Vector.h"
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <stdexcept>
#include <sstream>

// Default constructor
Vector::Vector()
{
	statmng();
	m_n = 0;
}

// Copy constructor. Run-time invokes when ever an intermediate object is
// needed. Typically part of an expression, i.e. temporary value of
// sub-expression is created using this constructor.
Vector::Vector(const Vector & v)
{
	statmng();
	m_n = v.m_n;
	m_v = (vtype *) calloc(v.m_n, sizeof(vtype));

	for (size_t j = 0; j < m_n; j++) {
		m_v[j] = v.m_v[j];
	}
}

// Assignment constructor  - integer array
Vector::Vector(size_t i, vtype a[])
{
	statmng();
	m_n = i;
	m_v = (vtype *) calloc(i, sizeof(vtype));

	for (size_t j = 0; j < i; j++) {
		m_v[j] = a[j];
	}
}

// Assignment constructor  - Note that the type of the arguments is implicit
// and needs to be the same as the Vector
Vector::Vector(size_t i ...)
{
	statmng();
	va_list ap;

	va_start(ap, i);
	m_n = i;
	m_v = (vtype *) calloc(i, sizeof(vtype));

	for (size_t j = 0; j < i; j++) {
		m_v[j] = va_arg(ap, int);
	}
	va_end(ap);
}

// Assignment operator  - Own element type
Vector & Vector::operator =(const vtype i)
{
	if (m_n > 1) {
		free(m_v);
		m_v = (vtype *) calloc(1, sizeof(vtype));
	} else if (m_n == 0) {
		m_v = (vtype *) calloc(1, sizeof(vtype));
	}
	*(int *)m_v = i;
	return *this;
}

// Copy operator (see also copy constructor)
Vector & Vector::operator =(const Vector & v)
{
	if (m_n > 0 && (v.m_n != m_n)) {
		free(m_v);
	}

	m_n = v.m_n;
	m_v = (vtype *) calloc(v.m_n, sizeof(vtype));

	for (size_t i = 0; i < m_n; i++) {
		m_v[i] = v.m_v[i];
	}
	return *this;
}

// Index operator
vtype & Vector::operator [](size_t i) {
	if (i > (m_n - 1)) {
		std::ostringstream s;
		s << "Index [" << i <<
		    "] is out of range for Vector[" << (m_n - 1) << "]";
		std::string eMsg(s.str());
		throw std::invalid_argument(eMsg);
	}
	return m_v[i];
}

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
const Vector operator *(const Vector lhs, const vtype & m)
{
	for (size_t i = 0; i < lhs.m_n; i++) {
		lhs.m_v[i] *= m;
	}
	return lhs;
}

// Division operator
const Vector operator /(const Vector lhs, const vtype & d)
{
#ifdef NEVER
	if (lhs.is_zero(d)) {
		std::ostringstream s;
		s << "Vector division would be by zero! (avoided)";
		std::string eMsg(s.str());
		throw std::invalid_argument(eMsg);
	}
#endif

	for (size_t i = 0; i < lhs.m_n; i++) {
		lhs.m_v[i] /= d;
	}
	return lhs;
}

// Destructor.
Vector::~Vector()
{
	--instances;
	if (m_n > 0 && m_v) {
		free(m_v);
	}
}

/* Class stats variables */
int Vector::instances = 0;
int Vector::ntotever = 0;

bool Vector::is_zero(const vtype & d)
{
	if (d == 0)
		return true;
	else
		return false;
}
