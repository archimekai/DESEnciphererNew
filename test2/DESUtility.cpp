#include "DESUtility.h"
#include <iostream>
using namespace std;
namespace DESUtility {
#pragma region constant parameters

	//初始置换表IP   
	int IP_Table[64] = { 57,49,41,33,25,17,9,1,
		59,51,43,35,27,19,11,3,
		61,53,45,37,29,21,13,5,
		63,55,47,39,31,23,15,7,
		56,48,40,32,24,16,8,0,
		58,50,42,34,26,18,10,2,
		60,52,44,36,28,20,12,4,
		62,54,46,38,30,22,14,6 };

	//逆初始置换表IP^-1   
	int IP_1_Table[64] = { 39,7,47,15,55,23,63,31,
		38,6,46,14,54,22,62,30,
		37,5,45,13,53,21,61,29,
		36,4,44,12,52,20,60,28,
		35,3,43,11,51,19,59,27,
		34,2,42,10,50,18,58,26,
		33,1,41,9,49,17,57,25,
		32,0,40,8,48,16,56,24 };

	//扩充置换表E   
	int E_Table[E_SIZE] = { 31, 0, 1, 2, 3, 4,
		3,  4, 5, 6, 7, 8,
		7,  8,9,10,11,12,
		11,12,13,14,15,16,
		15,16,17,18,19,20,
		19,20,21,22,23,24,
		23,24,25,26,27,28,
		27,28,29,30,31, 0 };

	//置换函数P   
	int P_Table[BLOCK_HALF_SIZE] = { 15,6,19,20,28,11,27,16,
		0,14,22,25,4,17,30,9,
		1,7,23,13,31,26,2,8,
		18,12,29,5,21,10,3,24 };

	//S盒   
	int S[8][4][16] =//S1   
	{ { { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
	{ 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
	{ 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
	{ 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 } },
		//S2   
	{ { 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
	{ 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
	{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
	{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 } },
		//S3   
	{ { 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
	{ 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
	{ 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
	{ 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 } },
		//S4   
	{ { 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
	{ 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
	{ 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
	{ 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 } },
		//S5   
	{ { 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
	{ 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
	{ 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
	{ 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 } },
		//S6   
	{ { 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
	{ 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
	{ 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
	{ 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 } },
		//S7   
	{ { 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
	{ 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
	{ 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
	{ 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 } },
		//S8   
	{ { 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
	{ 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
	{ 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
	{ 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 } } };
	//置换选择1   
	int PC_1[KEY_LEN_AFTER_P1] = { 56,48,40,32,24,16,8,
		0,57,49,41,33,25,17,
		9,1,58,50,42,34,26,
		18,10,2,59,51,43,35,
		62,54,46,38,30,22,14,
		6,61,53,45,37,29,21,
		13,5,60,52,44,36,28,
		20,12,4,27,19,11,3 };

	//置换选择2   
	int PC_2[SUB_KEY_LEN] = { 13,16,10,23,0,4,2,27,
		14,5,20,9,22,18,11,3,
		25,7,15,6,26,19,12,1,
		40,51,30,36,46,54,29,39,
		50,44,32,46,43,48,38,55,
		33,52,45,41,49,35,28,31 };

	//对左移次数的规定   
	int MOVE_TIMES[ROUND_N] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };
#pragma endregion


	unsigned char * Encipherer::encipher(string text) {
		const int len = text.size();
#ifdef DEBUG
		cout << "Text length: " << len <<"\n";
#endif // DEBUG

		unsigned char temp[8] = { 0 };
		elemType block[BLOCK_SIZE] = { 0 };
		int size = 0;
		if (len % 8 == 0) {
			size = len;
		}
		else {
			size = ((int)(len / 8)) * 8 + 8;
		}
#ifdef DEBUG
		cout << "Enciphered block size(bytes):" << size << "\n";
#endif // DEBUG

		unsigned char * resultBlock = (unsigned char *)malloc(sizeof(unsigned char) * size); // 为结果的紧致表示
		memset(resultBlock, 0, sizeof(unsigned char) * size);
		int i = 0;
		int blockNo = -1;
		for (i = 0; i < len; ++i) {
			temp[i % 8] = text.at(i);
			if ((i + 1) % 8 == 0) {
				blockNo = (i + 1) / 8 - 1;
#ifdef DEBUG
				cout << "\n====Now encipher block no." << blockNo << "====\n";
				cout << "Text to be enciphered: ";
				for (int k = 0; k < 8; ++k) {
					cout << temp[k];
				}
				cout << "\n";
#endif // DEBUG
				char2block(temp, block, 8);
#ifdef DEBUG
				cout << "converted text:\n ";
				printSparseBlock(block);
				cout << "\n";
#endif // DEBUG
				encipherBlock(block);
				block2hex(block, resultBlock + blockNo * 8);
#ifdef DEBUG
				cout << "====Enciphered block no." << blockNo << "====\n";
				cout << "====Enciphered text:====\n";
				printConvertedBlock(resultBlock + blockNo * 8);
				cout << "\n";
#endif // DEBUG
				memset(temp, 0, sizeof(unsigned char) * 8);
				memset(block, 0, sizeof(elemType) * BLOCK_SIZE);
			}
		}
		if (len % 8 != 0) {
			++blockNo;
#ifdef DEBUG
			cout << "\n====Now encipher block no." << blockNo << "====\n";
			cout << "Text to be enciphered: ";
			for (int k = 0; k < 8; ++k) {
				printf("%c", temp[k]);
			}
			cout << "\n";
#endif // DEBUG
			// 再加密一次
			char2block(temp, block, 8);
#ifdef DEBUG
			cout << "converted text:\n ";
			printSparseBlock(block);
			cout << "\n";
#endif // DEBUG
			encipherBlock(block);
			block2hex(block, resultBlock + blockNo * 8);
#ifdef DEBUG
			cout << "====Enciphered block no." << blockNo << "====\n";
			cout << "====Enciphered text:====\n";
			printConvertedBlock(resultBlock + blockNo * 8);
			cout << "\n";
#endif // DEBUG
		}
		ciphertextSize = size;
		return resultBlock; // memory leak

	}

	void Encipherer::setKey(unsigned char key[KEY_LEN / 8]) {
		char2block(key, this->key, KEY_LEN / 8);
		genSubKey();
	}

	// 输入的为经过紧致的密文，需要先转换为稀疏的密文
	// len必须是8的倍数
	elemType * Encipherer::decipher(elemType * compactBlock, int len) {
		int sparseLen = len * ELEM_TYPE_BIT_SIZE;
		elemType * block = (elemType *)malloc(sizeof(elemType) * sparseLen);
		for (int i = 0; i < len; ++i) {
			for (int j = 0; j < ELEM_TYPE_BIT_SIZE; ++j) {
				block[i * ELEM_TYPE_BIT_SIZE + j] = (compactBlock[i] >> j) % 2;
			}
		}
		elemType * result = (elemType *)malloc(sizeof(elemType) * len);
		memset(result, 0, sizeof(elemType) * len); // malloc 一定要记得初始化！！
		for (int i = 0; i < len / 8; ++i) {
			decipherBlock(block + i * BLOCK_SIZE, (elemType *)(result + 8 * i));
		}
		return result;
	}


	// 将C风格字符串序列转化为block，返回成功转化的个数，该值一般为8
	// len: ch 中还有几个字符
	int Encipherer::char2block(unsigned char * ch, elemType block[BLOCK_SIZE], int len) {
		int ncharsToConvert = BLOCK_SIZE / ELEM_TYPE_BIT_SIZE;
		int i;
		for (i = 0; i < ncharsToConvert && i < len; ++i) {
			for (int j = 0; j < 8; ++j) {
				// 一个char一般是8个bit
				block[i * 8 + j] = (ch[i] >> j) % 2;
			}
		}
		return i;
	}

	// converted为block的压缩表示
	int Encipherer::block2hex(elemType block[BLOCK_SIZE], elemType converted[BLOCK_SIZE / ELEM_TYPE_BIT_SIZE]) {
		for (int i = 0; i < BLOCK_SIZE / ELEM_TYPE_BIT_SIZE; ++i) {
			for (int j = 0; j < ELEM_TYPE_BIT_SIZE; ++j) {
				converted[i] += block[i * ELEM_TYPE_BIT_SIZE + j] << j;
			}
		}
		return 0;
	}

	void Encipherer::printConvertedBlock(elemType converted[BLOCK_SIZE / ELEM_TYPE_BIT_SIZE]) {
		for (int i = 0; i < BLOCK_SIZE / ELEM_TYPE_BIT_SIZE; ++i) {
			printf("%02X", converted[i]);
			if ((i + 1) % 2 == 0) printf(" ");
		}
	}

	void Encipherer::printSparseBlock(elemType block[BLOCK_SIZE]){
		elemType compactBlock[BLOCK_SIZE / ELEM_TYPE_BIT_SIZE] = { 0 };
		block2hex(block, compactBlock);
		printConvertedBlock(compactBlock);
	}



	// 初始置换
	void Encipherer::initialPermutation(elemType* block, elemType* temp64) {
		for (int i = 0; i < BLOCK_SIZE; ++i) {
			temp64[i] = block[IP_Table[i]];
		}
	}

	void Encipherer::initialPermutation(elemType block[BLOCK_SIZE]) {
		elemType temp[BLOCK_SIZE] = { 0 };
		for (int i = 0; i < BLOCK_SIZE; ++i) {
			temp[i] = block[IP_Table[i]];
		}
		memcpy(block, temp, sizeof(elemType) * BLOCK_SIZE);
	}

	// 初始置换逆置换
	void Encipherer::reversePermutation(elemType* block, elemType* temp64) {
		for (int i = 0; i < BLOCK_SIZE; ++i) {
			temp64[i] = block[IP_1_Table[i]];
		}
	}

	void Encipherer::reversePermutation(elemType block[BLOCK_SIZE]) {
		elemType temp[BLOCK_SIZE] = { 0 };
		for (int i = 0; i < BLOCK_SIZE; ++i) {
			temp[i] = block[IP_1_Table[i]];
		}
		memcpy(block, temp, sizeof(elemType) * BLOCK_SIZE);
	}

	// 加密一个块
	void Encipherer::encipherBlock(elemType block[BLOCK_SIZE]) {
		initialPermutation(block);
#ifdef DEBUG
		cout << "Enciphered block after initialPermutation:\n";
		printSparseBlock(block);
		cout << "\n";
#endif // DEBUG
		for (int i = 0; i < ROUND_N; ++i) {
			round(block, i);
#ifdef DEBUG
			cout << "Enciphered block after round " << i <<":\n";
			printSparseBlock(block);
			cout << "\n";
#endif // DEBUG
		}
		swapLR(block);
#ifdef DEBUG
		cout << "Enciphered block after left-right-swap:\n";
		printSparseBlock(block);
		cout << "\n";
#endif // DEBUG
		reversePermutation(block);
#ifdef DEBUG
		cout << "Enciphered block after reversePermutation:\n";
		printSparseBlock(block);
		cout << "\n";
#endif // DEBUG
	}

	//产生16个子密钥。每当设置新秘钥时调用
	void Encipherer::genSubKey() {
		elemType temp[KEY_LEN_AFTER_P1] = { 0 };
		// 置换选择 1
		for (int i = 0; i < KEY_LEN_AFTER_P1; ++i) {
			temp[i] = key[PC_1[i]]; // TODO 严格来说这里需要对key的正确性进行验证
		}

		for (int i = 0; i < ROUND_N; ++i) {
			// 循环左移  C
			shiftLeft(temp, KEY_HALF_LEN_AFTER_P1, MOVE_TIMES[i]);
			// 循环左移 D
			shiftLeft(temp + KEY_HALF_LEN_AFTER_P1, KEY_HALF_LEN_AFTER_P1, MOVE_TIMES[i]);
			// 置换选择 2 
			replaceSelection2(temp, subkeys + i * SUB_KEY_LEN);
		}

	}

	// 一轮加密
	void Encipherer::round(elemType block[BLOCK_SIZE], int iterCount) {
		elemType eletemps_R[BLOCK_HALF_SIZE] = { 0 };
		memcpy(eletemps_R, block + BLOCK_HALF_SIZE, sizeof(elemType) * BLOCK_HALF_SIZE); // 应该在每轮开始时就把右32位保存起来
		elemType extended[E_SIZE] = { 0 };
		extend(block + BLOCK_HALF_SIZE, extended);
#ifdef DEBUG_ROUND
		printSparseBlock(block);
		cout << "\n";
#endif //DEBUG_ROUND
		xorWithKey(extended, iterCount);
		selectCompression(extended, block + BLOCK_HALF_SIZE);
#ifdef DEBUG_ROUND
		printSparseBlock(block);
		cout << "\n";
#endif //DEBUG_ROUND
		elemType permutated[BLOCK_HALF_SIZE];
		permutation(block + BLOCK_HALF_SIZE, permutated);
#ifdef DEBUG_ROUND
		printSparseBlock(block);
		cout << "\n";
#endif //DEBUG_ROUND
		memcpy(block + BLOCK_HALF_SIZE, permutated, sizeof(elemType) * BLOCK_HALF_SIZE);
#ifdef DEBUG_ROUND
		printSparseBlock(block);
		cout << "\n";
#endif //DEBUG_ROUND
		xorWithLAndSwapLR(block);
		memcpy(block, eletemps_R, sizeof(elemType) * BLOCK_HALF_SIZE);
#ifdef DEBUG_ROUND
		printSparseBlock(block);
		cout << "\n";
#endif //DEBUG_ROUND
	}

	//选择扩展运算
	// blockE:48个字节的elemType数组
	void Encipherer::extend(elemType blockE[BLOCK_HALF_SIZE], elemType tempE[E_SIZE]) {  // 运行的时候会检查写在[48]的数字
		for (int i = 0; i < E_SIZE; ++i) {
			tempE[i] = blockE[E_Table[i]];
		}
	}

	//循环左移
	// shiftcount 
	void Encipherer::shiftLeft(elemType* block, int len, int shiftCount) {
		for (int i = 0; i < shiftCount; ++i) {
			shiftLeftOneBit(block, len);
		}
	}
	// 循环左移一位
	void Encipherer::shiftLeftOneBit(elemType* block, int len) {
		if (len <= 1) return;
		elemType temp = block[len - 1];
		block[len - 1] = block[0];
		for (int i = 1; i <= len - 2; ++i) {
			block[i - 1] = block[i];
		}
		block[len - 2] = temp;
	}

	// 置换选择2
	void Encipherer::replaceSelection2(elemType CD[KEY_LEN_AFTER_P1], elemType target[SUB_KEY_LEN]) {
		for (int i = 0; i < SUB_KEY_LEN; ++i) {
			target[i] = CD[PC_2[i]];
		}
	}

	// 与 子密钥异或，异或的结果仍然存在block里面
	// iterCount 从1开始
	void Encipherer::xorWithKey(elemType blockE[E_SIZE], int iterCount) {
		for (int i = 0; i < E_SIZE; ++i) {
			blockE[i] = blockE[i] ^ subkeys[(iterCount - 1) * SUB_KEY_LEN + i];
		}
	}

	// 选择压缩运算
	void Encipherer::selectCompression(elemType blockE[E_SIZE], elemType target[BLOCK_HALF_SIZE]) {
		for (int i = 0; i < 6; ++i) {
			//for (int j = 0; j < 8; ++j) {
			int row = blockE[i * 6] * 2 + blockE[i * 6 + 5];
			int col = blockE[i * 6 + 1] * 8 +
				blockE[i * 6 + 2] * 4 +
				blockE[i * 6 + 3] * 2 +
				blockE[i * 6 + 4];
			int out = S[i][row][col];
			for (int k = 0; k < 4; ++k) {
				target[i * 4 + k] = (elemType)((out >> (3 - k)) % 2);
			}
			//}
		}
	}

	// 每轮加密中的置换运算
	void Encipherer::permutation(elemType input[BLOCK_HALF_SIZE], elemType target[BLOCK_HALF_SIZE]) {
		for (int i = 0; i < BLOCK_HALF_SIZE; ++i) {
			target[i] = input[P_Table[i]];
		}
	}

	void Encipherer::swapLR(elemType block[BLOCK_SIZE]) {
		elemType temp;
		for (int i = 0; i < BLOCK_HALF_SIZE; ++i) {
			temp = block[i];
			block[i] = block[i + BLOCK_HALF_SIZE];
			block[i + BLOCK_HALF_SIZE] = temp;
		}
	}

	void Encipherer::decipherBlock(elemType block[BLOCK_SIZE], elemType text[8]) {
#ifdef DEBUG
		cout << "In decipherBlock:\n";
		printSparseBlock(block);
		cout << "\n";
#endif // DEBUG
		// 解密过程与加密过程完全类似
		initialPermutation(block);
#ifdef DEBUG
		cout << "Deciphered block after initialPermutation:\n";
		printSparseBlock(block);
		cout << "\n";
#endif // DEBUG
		// 16轮迭代
		for (int i = ROUND_N - 1; i >= 0; --i) {
			round(block, i);
#ifdef DEBUG
			cout << "Deciphered block after round " << i << ":\n";
			printSparseBlock(block);
			cout << "\n";
#endif // DEBUG
		}
		swapLR(block);
#ifdef DEBUG
		cout << "Deciphered block after left-right-swap:\n";
		printSparseBlock(block);
		cout << "\n";
#endif // DEBUG
		reversePermutation(block);
#ifdef DEBUG
		cout << "Dnciphered block after reversePermutation:\n";
		printSparseBlock(block);
		cout << "\n";
#endif // DEBUG
		block2hex(block, text);
	}

	void Encipherer::xorWithLAndSwapLR(elemType block[BLOCK_SIZE]) {
		for (int i = 0; i < BLOCK_HALF_SIZE; ++i) {
			block[BLOCK_HALF_SIZE + i] = block[BLOCK_HALF_SIZE + i] ^ block[i];
		}

		//for (int i = 0; i < BLOCK_HALF_SIZE; ++i) {
		//	elemType temp = block[i];
		//	block[i] = block[BLOCK_HALF_SIZE + i];
		//	block[BLOCK_HALF_SIZE + i] = temp;
		//}
	}

}