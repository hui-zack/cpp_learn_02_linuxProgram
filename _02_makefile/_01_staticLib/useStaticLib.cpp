/*********************************
* @Author   : Hui
* @Aata     : 2022/12/17$ 0:04$
* @Describe : 
* @Keyword  : 
*********************************/
#include <iostream>
#include <string>

using namespace std;
int add(int num1, int num2);
int sub(int num1, int num2);

int main() {
    cout << "hello linux" << endl;
    int a = 10;
    int b = 5;
    /* 1-2-1 导入库的.h文件直接使用静态库函数 */
    int result = add(a, b);
    cout << result << endl;

    return 0;
}