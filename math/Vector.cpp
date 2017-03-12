#include "Vector.h"
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>

// Default constructor
Vector::Vector()
{
	m_n = 0;
}

// Copy constructor, can be invoked by casting and intermediate values
Vector::Vector(const Vector & v)
{
	if (m_n > 0 && (v.m_n != m_n)) {
		free(m_v);
	}
	m_n = v.m_n;
	m_v = (vtype *) calloc(v.m_n, sizeof(vtype));

	for (int i = 0; i < m_n; i++) {
		m_v[i] = v.m_v[i];
	}
}

// Assignment constructor  - integer array
Vector::Vector(size_t i, vtype a[])
{
	m_n = i;
	m_v = (vtype *) calloc(i, sizeof(vtype));

	for (int j = 0; j < i; j++) {
		m_v[i] = a[i];
	}
}

// Assignment constructor  - Note that the type of the arguments is implicit
// and needs to be the same as the Vector
Vector::Vector(size_t i ...)
{
	va_list ap;

	va_start(ap, i);
	m_n = i;
	m_v = (vtype *) calloc(i, sizeof(vtype));

	for (int j = 0; j < i; j++) {
		m_v[j] = va_arg(ap, int);
	}
	va_end(ap);
}

// Assignment operator  - integer
Vector & Vector::operator =(int i)
{
	if (m_n > 1) {
		free(m_v);
		m_v = (vtype *) calloc(1, sizeof(vtype));
	} else if (m_n == 0) {
		m_v = (vtype *) calloc(1, sizeof(vtype));
	}
	*(int *)m_v = i;
}

// Copy operator (see also copy constructor)
Vector & Vector::operator =(const Vector & v)
{
	if (m_n > 0 && (v.m_n != m_n)) {
		free(m_v);
	}

	m_n = v.m_n;
	m_v = (vtype *) calloc(v.m_n, sizeof(vtype));

	for (int i = 0; i < m_n; i++) {
		m_v[i] = v.m_v[i];
	}
}

// Destructor
Vector::~Vector()
{
	if (m_n > 0 && m_v) {
		free(m_v);
	}
}

