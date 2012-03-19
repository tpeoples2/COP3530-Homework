#include "olsm.h"

using namespace std;

int main() {
    olsm<int> test(4, 4);
   
    test.insert(1, 2, 5);
    test.insert(1, 3, 9);
    test.insert(2, 1, 1);
    test.insert(3, 1, 1);
    test.insert(3, 2, 7);

    //test.printSingleRow(1);
    //test.printSingleRow(2);
    //test.printSingleRow(3);
}
