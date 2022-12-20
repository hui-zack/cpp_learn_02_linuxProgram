#include <iostream>
#include <string>
#include "config.h"
#include "myMathStatic.h"
#include "myMathShared.h"
using namespace std;


int main(int argc, char **argv){

    int result1 = add(19, 6);
    int result2 = mul(3, 7);
    
    cout << "hello cmake" << endl;

    cout << "the result1 = " << result1 << endl; 
    cout << "the result2 = " << result2 << endl; 

    

    /* 在代码中使用配置内容 */
    #ifdef TEST_CONFIG
        cout << "TEST_CONFIG = " << TEST_CONFIG << endl;
    #endif
    return 0;
}