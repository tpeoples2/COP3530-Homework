// need to compile with "-lrt" options

#include <iostream>
#include <ctime>

using namespace std;

float fibRecursive(int n) {
    if (n <= 1) {
        return 0;
    }
    else if (n == 2) {
        return 1;
    }
    else {
        return fibRecursive(n - 1) + fibRecursive(n - 2);
    }
}

float fibNonRecursive(int n) {
    float a = 0;
    float b = 1;
    
    if (n == 1)
        return a;
    else if (n == 2)
        return b;
    
    while (n > 2) {
        float temp = a;
        a = b;
        b += temp;
        n--;
    }

    return b;
}

int main() {
    time_t start, end;
    
    //time(&start);
    //for (int i = 10; i <= 40; i += 10) {
        //cout << fibRecursive(i) << endl;
        //if (i == 40) {
            //for (i++ ; i <= 50; i++) {
                //cout << fibRecursive(i) << endl;
            //}
        //}
    //}
    //time(&end);

    //cout << "Recursive function time:\t" << difftime(end, start) << endl;
    
    cout << endl;
    
    timespec ts, te;
    clock_gettime(CLOCK_REALTIME, &ts);
    
    time(&start);
    for (int i = 10; i <= 40; i += 10) {
        cout << fibNonRecursive(i) << endl;
        if (i == 40) {
            for (i++ ; i <= 50; i++) {
                cout << fibNonRecursive(i) << endl;
            }
        }
    }
    time(&end);

    clock_gettime(CLOCK_REALTIME, &te);

    cout << "Non-recursive function time in seconds using ctime time():\t\t" << difftime(end, start) << endl;
    cout << "Non-recursive function time in nanoseconds using clock_gettime():\t" << te.tv_nsec - ts.tv_nsec << endl;
    cout << "Non-recursive function time in seconds using clock_gettime():\t\t" << te.tv_sec - ts.tv_sec << endl;
}

// 0    1   1   2   3   5   8   13  21  34 ...


