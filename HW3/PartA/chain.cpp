// test the class chain
#include<iostream>
#include "linearList.h"
#include "chain.h"

using namespace std;
/* WORKING VERSION, NOT OPTIMIZED
 * Runs in O(n^3) time, terrible
 * Try using iterators
 */
template <class T>
chain<T>& nonMemberReverse(chain<T>& oldChain) {
    if (oldChain.empty())
        return oldChain;

    int size = oldChain.size();

    chain<T> c(size);
    for (int i = 0; i < size; i++) {
        c.insert(i, oldChain.get(size - i - 1));
    }

    for (int i = 0; i < size; i++) {
        oldChain.erase(i);
        oldChain.insert(i, c.get(i));
    }

    return oldChain;
}

int main()
{
   // test constructor
   //linearList<double> *x = new chain<double>;
   chain<int> y, z;
    
    /*
   // test size
   cout << "Initial size of x, y, and z = "
        << x->size() << ", "
        << y.size() << ", "
        << z.size() << endl;

   // test empty
   if (x->empty()) cout << "x is empty" << endl;
   else cout << "x is not empty" << endl;
   if (y.empty()) cout << "y is empty" << endl;
   else cout << "y is not empty" << endl;

   // test insert
   y.insert(0, 2);
   y.insert(1, 6);
   y.insert(0, 1);
   y.insert(2, 4);
   y.insert(3, 5);
   y.insert(2, 3);
   cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
   cout << "Size of y = " << y.size() << endl;
   if (y.empty()) cout << "y is empty" << endl;
   else cout << "y is not empty" << endl;
   y.output(cout);
   cout << endl << "Testing overloaded <<" << endl;
   cout << y << endl;

   // test indexOf
   int index = y.indexOf(4);
   if (index < 0) cout << "4 not found" << endl;
   else cout << "The index of 4 is " << index << endl;

   index = y.indexOf(7);
   if (index < 0) cout << "7 not found" << endl;
   else cout << "The index of 7 is " << index << endl;

   // test get
   cout << "Element with index 0 is " << y.get(0) << endl;
   cout << "Element with index 3 is " << y.get(3) << endl;

   // test erase
   y.erase(1);
   cout << "Element 1 erased" << endl;
   cout << "The list is "  << y << endl;
   y.erase(2);
   cout << "Element 2 erased" << endl;
   cout << "The list is "  << y << endl;
   y.erase(0);
   cout << "Element 0 erased" << endl;
   cout << "The list is "  << y << endl;

   cout << "Size of y = " << y.size() << endl;
   if (y.empty()) cout << "y is empty" << endl;
   else cout << "y is not empty" << endl;

   try {y.insert(-3, 0);}
   catch (illegalIndex e)
   {
      cout << "Illegal index exception" << endl;
      cout << "Insert index must be between 0 and list size" << endl;
      e.outputMessage();
   }

   // test copy constructor
   chain<int> w(y);
   y.erase(0);
   y.erase(0);
   cout << "w should be old y, new y has first 2 elements removed" << endl;
   cout << "w is " << w << endl;
   cout << "y is " << y << endl;
   
   */

   // a few more inserts, just for fun
   y.insert(0,4);
   y.insert(1,5);
   y.insert(2,6);
   y.insert(3,7);
   cout << "y is " << y << endl;
   
    // test reverse method
    y.reverse();
    cout << "y reversed is " << y << endl;
    
    for (int i = 0; i < 250; i++) {
        z.insert(i, 10*i + i/3);
    }
    //cout << "z is " << z << endl;
    z.reverse();
    //cout << "z reversed is " << z << endl;
    
    y = nonMemberReverse(y);
    cout << "y reversed again is " << y << endl;
    
    chain<int> a;
    a.insert(0, 1);
    a.insert(1, 2);
    a.insert(2, 3);
    a.insert(3, 4);
    a.insert(4, 5);
    a.insert(5, 6);
    a.insert(6, 7);
    cout << "a is " << a << endl;

    chain<int> b;
    b.insert(0, 10);
    b.insert(1, 20);
    b.insert(2, 30);
    b.insert(3, 40);
    b.insert(4, 50);
    cout << "b is " << b << endl;

    chain<int> c;
    c.meld(a, b);
    cout << "c is " << c << endl;
    cout << "a is " << a << endl;
    cout << "b is " << b << endl;
    
    return 0;

}
