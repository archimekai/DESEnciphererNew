#pragma once
#define BLOCK_SIZE 64 // 一块密文的长度
#define BLOCK_HALF_SIZE (BLOCK_SIZE/2)
#define BLOCK_elemType 8
#define E_SIZE 48 // 经过选择拓展之后的位数
#define ROUND_N 16 // 加密的轮数
#define KEY_LEN 64 // 密钥长度
#define KEY_LEN_AFTER_P1 56  // 经过置换选择之后的密钥长度
#define KEY_HALF_LEN_AFTER_P1 (KEY_LEN_AFTER_P1/2)
#define SUB_KEY_LEN 48
#define ELEM_TYPE_BIT_SIZE 8
#define DEBUG // 输出中间结果
//#define DEBUG_ROUND
typedef unsigned char elemType;
//typedef unsigned char textType; //文本的类型

#include<string>


using namespace std;

namespace DESUtility {
	class Encipherer {
	public:
		unsigned char * encipher(string text);
		void setKey(unsigned char key[KEY_LEN / 8]);
		int ciphertextSize; // 密文长度
		elemType* decipher(elemType* compactBlock, int len); // blocks为压缩过的密文
		void encipherBlock(elemType block[BLOCK_SIZE]);
		void decipherBlock(elemType block[BLOCK_SIZE], elemType text[8]);
		Encipherer() { ; }
		Encipherer(unsigned char key[KEY_LEN / 8]) {
			this->setKey(key);
		}
	private:  // TODO private 的函数也放在.h里面吗？
		elemType key[KEY_LEN]; // 秘钥
		elemType subkeys[KEY_LEN_AFTER_P1 * ROUND_N]; //子密钥

													  // 通用函数，应该被提取到另一个头文件中重构比较好
		int char2block(unsigned char* ch, elemType block[BLOCK_SIZE], int len);
		int block2hex(elemType block[BLOCK_SIZE], elemType converted[BLOCK_SIZE / ELEM_TYPE_BIT_SIZE]);
		void printConvertedBlock(elemType converted[BLOCK_SIZE / ELEM_TYPE_BIT_SIZE]);
		void printSparseBlock(elemType block[BLOCK_SIZE]);

		void initialPermutation(elemType* block, elemType* temp64);
		void initialPermutation(elemType block[BLOCK_SIZE]);
		void reversePermutation(elemType* block, elemType* temp64);
		void reversePermutation(elemType block[BLOCK_SIZE]);
		//void encipherBlock(elemType block[BLOCK_SIZE]);

		void genSubKey();

		void round(elemType block[BLOCK_SIZE], int iterCount);
		void extend(elemType block[BLOCK_HALF_SIZE], elemType tempE[E_SIZE]);
		void shiftLeft(elemType* block, int len, int shiftCount);
		void shiftLeftOneBit(elemType* block, int len);
		void replaceSelection2(elemType CD[KEY_LEN_AFTER_P1], elemType target[SUB_KEY_LEN]);
		void xorWithKey(elemType blockE[E_SIZE], int iterCount);
		void xorWithLAndSwapLR(elemType block[BLOCK_SIZE]);
		void selectCompression(elemType blockE[E_SIZE], elemType target[BLOCK_HALF_SIZE]);
		void permutation(elemType input[BLOCK_HALF_SIZE], elemType target[BLOCK_HALF_SIZE]);
		void swapLR(elemType block[BLOCK_SIZE]);

		//void decipherBlock(elemType block[BLOCK_SIZE], elemType text[8]);
		//void num2bits();
	};
}