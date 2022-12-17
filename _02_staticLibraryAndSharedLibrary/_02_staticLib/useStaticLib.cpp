/*********************************
* @Author   : Hui
* @Aata     : 2022/12/17 0:04
* @Describe : 
* @Keyword  : 
*********************************/

#include <iostream>
#include <string>

///* cpp导入静态C库的头文件 */
extern "C"{
    #include "resource/myMath.h"
}
//#include "resource/myMath.h"

using namespace std;


int main() {

    /* 使用静态C库函数 */
    int result = add(10, 5);

    cout << "[C++] hello static library, the result = " << result << endl;

    return 0;
}