//
//  lab2.hpp
//  CRYPTO_LAB
//
//  Created by Georgy Petriv on 13.05.2024.
//

#ifndef lab2_hpp
#define lab2_hpp

#include <stdio.h>
#include <chrono>
#include "lab1.hpp"

using namespace std;

class PublicKey{
public:
    int128 e;
    int128 n;
    PublicKey();
    PublicKey(int128 _e, int128 _n);
};

class Message{
public:
    PublicKey PbKey;
    int128 * m;
    int size;
    Message();
    Message(PublicKey _PbKey, int128 * _m, int _size);
    Message & operator =(const Message &_m);
    ~Message();
};

//utils
bool generate_pq(int128 & p, int128 & q, int order);

//encoding & decoding
int128 BaseEncode(int128 m, PublicKey Pbkey);
int128 BaseDecode(int128 c, int128 d, int128 n); //private key is required
Message Encode(string m, PublicKey Pbkey);

int128 Decode(int128 c, PublicKey Pbkey, int128 d);
string Decode(Message &m, int128 d, int128 p, int128 q); //decoding is only possible with d, CRT decoding also requires p and q, which are available to Alice

#endif /* lab2_hpp */
