#ifndef Vector_h
#    define Vector_h

//Temporary type until class is made template able
#    define VTYPE int

class Vector {
 private:
	VTYPE * V;
	int m_len;
 public:
	 Vector();
	~Vector();
};

#endif				//Vector_h
