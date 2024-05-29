//
//  utils.hpp
//  CRYPTO_LAB
//
//  Created by Georgy Petriv on 13.05.2024.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <stdio.h>
#include <random>
#include <string>
#include <bitset>
#include <iostream>

using namespace std;
typedef __int128 int128;

//basic tools for every method
int128 fast_pow(int128 base, int128 exp, int128 mod);
int128 gcd(int128 num1, int128 num2);
int128 lcm(int128 num1, int128 num2);
int128 coprime(int128 num);

//utils for BPSW test
bool FLT(int128 num);
int Jacobi(int128 num, int128 m);
void LucasSeq(int128& U, int128& V, int128 D, int128 P, int128 Q, int128 num);
bool LucasTest(int128 num);

//output
string int128_to_base2(int128 num);
string int128_to_base10(int128 num);
string int128_to_base64(int128 num);
string int128_to_byteset(int128 num);

//lab2 part
int128 egcd(int128 num1, int128 num2);
int128 CRT(int128 c, int128 d, int128 p, int128 q);
string message_to_str(int128 * m, int size);
int128 * str_to_message(string m);
#endif /* utils_hpp */
