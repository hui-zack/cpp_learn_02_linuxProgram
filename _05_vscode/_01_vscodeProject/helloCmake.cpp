#include <iostream>
#include <string>

using namespace std;

template<class T>
void mySwap(T &value1, T &value2){
    T temp;
    temp = value1;
    value1 = value2;
    value2 = temp;
}

int main(int argc, char **argv){
    int numA = 10;
    int numB = 20;
    
    mySwap(numA, numB);
    cout  << "hello cmake";
    cout << "numA = " << numA << ", numB = " << numB << endl;
    

    return 0;
}