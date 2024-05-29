//
//  lab2.cpp
//  CRYPTO_LAB
//
//  Created by Georgy Petriv on 13.05.2024.
//

#include "lab2.hpp"

PublicKey::PublicKey(){
    e = -1;
    n = -1;
}

PublicKey::PublicKey(int128 _e, int128 _n){
    e = _e;
    n = _n;
}

Message::Message(){
    PbKey = PublicKey();
    size = 0;
    m = nullptr;
}

Message::Message(PublicKey _PbKey, int128 * _m, int _size){
    PbKey = _PbKey;
    size = _size;
    m = new int128[size];
    for(int i=0; i < _size; ++i){
        m[i]= _m[i];
    }
}

Message & Message::operator =(const Message &_m){
    PbKey = _m.PbKey;
    size = _m.size;
    m = new int128[size];
    for(int i=0; i < size; ++i){
        m[i]= _m.m[i];
    }
    return *this;
}

Message::~Message(){
    delete [] m;
}

bool generate_pq(int128 & p, int128 & q, int order){
    if(order == 0){
        p = q = 1;
        return false;
    }
    p = generate_prime(order);
    do{
        q = generate_prime(order);
    }while(p == q);
    return true;
}

int128 BaseEncode(int128 m, PublicKey Pbkey){
    return fast_pow(m, Pbkey.e, Pbkey.n);
}

int128 BaseDecode(int128 c, int128 d, int128 n){
    return fast_pow(c, d, n);
}

Message Encode(string m, PublicKey Pbkey){
    int _size = m.size();
    int128 * p = str_to_message(m);
    Message res(Pbkey, p, _size);
    for(int i = 0; i < _size; ++i){
        res.m[i]= BaseEncode(p[i], Pbkey);
    }
    delete [] p;
    return res;
}

string Decode(Message &m, int128 d, int128 p, int128 q){
    string res;
    for(int i=0; i<m.size; ++i){
        char c = CRT(m.m[i], d, p, q);
        res.push_back(c);
    }
    return res;
}
