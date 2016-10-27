/*
2.	2.	编制一个DES算法，设密钥为SECURITY，明文为NETWORK INFORMATION SECURITY，计算密文，并列出每一轮的中间结果

*/



#include "DESUtility.h"
#include <iostream>
#include <string>


using namespace std;
using namespace DESUtility;

void main() {
	cout << "Hello world!\n";
	Encipherer encipherer = Encipherer();
	char key[8] = { 'S', 'E', 'C', 'U', 'R', 'I', 'T', 'Y' };
	string text = string("NETWORK INFORMATION SECURITY");
	//string text = string("a");
	encipherer.setKey((unsigned char *)key);
	unsigned char * result = encipherer.encipher(text);
	printf("\nEnciphered text:");
	for (int i = 0; i < encipherer.ciphertextSize; ++i) {
		printf("%02X", result[i]);
		if ((i + 1) % 2 == 0) printf(" ");
	}
	printf("\n");
	
	elemType * decipered = encipherer.decipher(result, encipherer.ciphertextSize);
	printf("\nPlain text:");
	for (int i = 0; i < encipherer.ciphertextSize; ++i) {
		printf("%c", decipered[i]);
	}

	system("pause");
}