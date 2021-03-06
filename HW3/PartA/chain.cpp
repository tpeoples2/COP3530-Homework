/* @author  Taylor Peoples
 * @UFID    1136-2951
 * @date    2012-03-01
 * @HW      HW3 Part A
 *
 */

// test the class chain
#include<iostream>
#include "linearList.h"
#include "chain.h"

using namespace std;

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
    cout << "\n" << endl;
    cout << "-----------TESTING MEMBER REVERSE METHOD-----------" << endl;
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
    
    cout << "\n" << endl;
    cout << "-----------TESTING NONMEMBER REVERSE METHOD-----------" << endl;
    y = reverse(y);
    cout << "y reversed again is " << y << endl;
    

    cout << "\n" << endl;
    cout << "-----------TESTING MEMBER MELD METHOD-----------" << endl;
    chain<int> a;
    a.insert(0, 1);
    a.insert(1, 3);
    a.insert(2, 5);
    a.insert(3, 7);
    a.insert(4, 8);
    a.insert(5, 9);
    //a.insert(6, 13);
    cout << "a is " << a << endl;

    chain<int> b;
    b.insert(0, 0);
    b.insert(1, 2);
    b.insert(2, 4);
    //b.insert(3, 6);
    //b.insert(4, 8);
    cout << "b is " << b << endl;

    chain<int> c;
    c.insert(0, 15);
    c.insert(1, 17);
    c.insert(2, 18);
    cout << "c is " << c << endl;

    cout << "---AFTER MELD" << endl;
    c.meld(a, b);
    cout << "c is " << c << endl;
    cout << "a is " << a << endl;
    cout << "b is " << b << endl;
    
    cout << "size of c is " << c.size() << endl;
    cout << "size of a is " << a.size() << endl;
    cout << "size of b is " << b.size() << endl;
    
    /* TESTING SPLIT ON EMPTY CHAIN */
    //int cSize = c.size();
    //for (int i = 0; i < cSize; i++) {
        //c.erase(0);
    //}
    //cout << "c is " << c << endl;

    cout << "\n" << endl;

    // put values back into a, b
    a.insert(0, 12);
    a.insert(1, 15);
    b.insert(0, 22);
    b.insert(1, 25);
    cout << "c is " << c << endl;
    cout << "a is " << a << endl;
    cout << "b is " << b << endl;


    cout << "-----------TESTING MEMBER SPLIT METHOD-----------" << endl;

    c.split(a, b);
    cout << "c is " << c << endl;
    cout << "a is " << a << endl;
    cout << "b is " << b << endl;

    cout << "size of c is " << c.size() << endl;
    cout << "size of a is " << a.size() << endl;
    cout << "size of b is " << b.size() << endl;



    

    return 0;

}
