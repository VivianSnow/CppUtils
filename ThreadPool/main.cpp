#include <iostream>
#include <unistd.h>
#include "ThreadPool.h"

using namespace std;

int multiply(int a, int b){
    cout << a << ' ' << b << a * b << endl;
    sleep(2);
}


int main() {
    ThreadPool pool(10);
    pool.init();
    for (int i = 0; i < 20; i++) {
        pool.add_task(std::bind(multiply, i, i));
    }
    sleep(10);
    pool.stop();
    return 0;
}