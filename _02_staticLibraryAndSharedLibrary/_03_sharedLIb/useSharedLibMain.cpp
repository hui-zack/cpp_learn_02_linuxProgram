/*********************************
* @Author   : Hui
* @Aata     : 2022/12/18 1:51
* @Describe : 
* @Keyword  : 
*********************************/

#include <iostream>
#include <string>

using namespace std;
/* 声明动态C库 */
extern "C" {
    #include "resource/myMath.h"
}


int main() {
    int result = sub(10, 4);
    cout << "[C++] hello shared library, the result = " << result << endl;
    return 0;
}