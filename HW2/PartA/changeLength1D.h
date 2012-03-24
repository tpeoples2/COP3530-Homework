#ifndef _CHANGELENGTH1D_
#define _CHANGELENGTH1D_

template<class T>
void changeLength1D(T*& a, int oldLength, int newLength) {
    if (newLength < 0) 
        throw illegalParameterValue("new length must be >= 0");

    T* temp = new T[newLength];
    int number = min(oldLength, newLength);
    copy(a, a + number, temp);
    delete [] a;
    a = temp;
};

#endif
