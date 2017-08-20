#include <iostream>
using namespace std;
//为了兼容，输入参数是char*
const int ctrl = 1;//测试控制中心
void Debug(char * outMsg) {
	if(ctrl==1)
	cout <<"\n------测试----------------------"<<outMsg <<endl;
}
void Debug(int outMsg) {
	if (ctrl == 1)
	cout << "\n------测试参数是::" << outMsg << endl;
}
void Debug(string outMsg) {

}