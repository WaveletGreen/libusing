#include <iostream>
using namespace std;
//Ϊ�˼��ݣ����������char*
const int ctrl = 1;//���Կ�������
void Debug(char * outMsg) {
	if(ctrl==1)
	cout <<"\n------����----------------------"<<outMsg <<endl;
}
void Debug(int outMsg) {
	if (ctrl == 1)
	cout << "\n------���Բ�����::" << outMsg << endl;
}
void Debug(string outMsg) {

}