// need to compile with "-lrt" option

#include <iostream>
#include <ctime>

using namespace std;

long long int fibRecursive(int n) {
    if (n < 1) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }
    else {
        return fibRecursive(n - 1) + fibRecursive(n - 2);
    }
}

long long int fibNonRecursive(int n) {
    long long int a = 0;
    long long int b = 1;
    
    if (n == 0)
        return a;
    else if (n == 1)
        return b;

    long long int temp;    
    while (n > 1) {
        temp = a;
        a = b;
        b += temp;
        n--;
    }

    return b;
}

int main() {
    time_t start, end;
    
    //for (int i = 10; i <= 50; i += 10) {
        //time(&start);
        //cout << fibRecursive(i) << endl;
        //time(&end);
        //cout << "Recursive function time:\t" << difftime(end, start) << endl;
        //if (i == 40) {
            //for (i++ ; i <= 50; i++) {
                //time(&start);
                //cout << fibRecursive(i) << endl;
                //time(&end);
                //cout << "Recursive function time in seconds:\t" << i << "\t" << difftime(end, start) << endl;
            //}
        //}
    //}

    
    
    timespec ts, te;
    
    for (int i = 10; i <= 100; i += 10) {
        clock_gettime(CLOCK_REALTIME, &ts);
        cout << fibNonRecursive(i) << endl;
        clock_gettime(CLOCK_REALTIME, &te);
        cout << "Non-recursive function time in nanoseconds:\t" << i << "\t" << te.tv_nsec - ts.tv_nsec << endl;
        //if (i == 40) {
            //for (i++ ; i <= 50; i++) {
                //clock_gettime(CLOCK_REALTIME, &ts);
                //cout << fibNonRecursive(i) << endl;
                //clock_gettime(CLOCK_REALTIME, &te);
                //cout << "Non-recursive function time in nanoseconds:\t" << i << "\t" << te.tv_nsec - ts.tv_nsec << endl;
            //}
        //}
    }
}
