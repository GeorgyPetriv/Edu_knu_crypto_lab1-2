//
//  tests.cpp
//  CRYPTO_LAB
//
//  Created by Georgy Petriv on 13.05.2024.
//
#include "tests.hpp"

void test_prime_lab1(int128 num, int k){
    cout << "Testing a number: " << endl;
    cout << "base2: " << int128_to_base2(num) << endl;
    cout << "base10: " << int128_to_base10(num) << endl;
    cout << "base64: " << int128_to_base64(num) << endl;
    cout << "byte[]: " << int128_to_byteset(num) << endl;
    cout << "Miller-Rabin test gives: " << (Miller_Rabin(num, k)? "prime" : "composite") << endl;
    cout << "BPSW test gives: " <<(BPSW(num)? "prime" : "composite") << endl;
}

void test_generator_lab1(int order){
    cout << "Generating and testing a prime number with bit length " << order << "..." << endl;
    int128 p = generate_prime(order);
    cout << "------------------------------------------------------------------" << endl;
    test_prime_lab1(p, order);
    cout << "------------------------------------------------------------------" << endl;
}

void test_base_lab2(){
    int128 p=7, q=13, e=5, d, n, l, m=30, c;
    cout << "A simple test with a single number encoding and decoding: " << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "Alice:" << endl;
    cout << "Takes 2 random primes: p=" << int128_to_base10(p) << "      q=" << int128_to_base10(q) << endl;
    cout<< "and a random number:   e=" << int128_to_base10(e) << endl;
    
    n = p * q;
    l = lcm(p-1, q-1);
    cout<< "Calculates n=" << int128_to_base10(n) << endl;
    cout<< "Calculates Carmichael function for n: l=" << int128_to_base10(l) << endl;
    
    d = egcd(e, l);
    cout<< "And computes d=" << int128_to_base10(d) << endl;
    cout << "Private key is (e, n): (" << int128_to_base10(e) << ", " << int128_to_base10(n) << ')' << endl << endl;
    
    cout << "Bob:" << endl;
    cout << "Takes random num: m=" << int128_to_base10(m) << endl;
    
    c = BaseEncode(m, PublicKey(e, n));
    cout<< "Calculates c=" << int128_to_base10(c) << endl;
    cout<< "And sends it to Alice" << endl << endl;
    
    cout << "Alice:" << endl;
    m = BaseDecode(c, d, n);
    cout<< "Calculates m back: m=" << int128_to_base10(m) << endl;
    cout << "------------------------------------------------------------------" << endl;
}

void test_message_lab2(){
    int128 p, q, e, d, n, l;
    string m = "Hi Alice!!!";
    cout << "A simple test with a message encoding and decoding: " << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "Alice:" << endl;
    generate_pq(p, q, 30);
    cout << "Takes 2 random primes: p=" << int128_to_base10(p) << "      q=" << int128_to_base10(q) << endl;
    n = p * q;
    l = lcm(p-1, q-1);
    cout<< "Calculates n=" << int128_to_base10(n) << endl;
    cout<< "Calculates Carmichael function for n: l=" << int128_to_base10(l) << endl;
    
    e = coprime(l);
    cout<< "and a random number:   e=" << int128_to_base10(e) << endl;
    
    d = egcd(e, l);
    cout<< "And computes d=" << int128_to_base10(d) << endl;
    cout << "Private key is (e, n): (" << int128_to_base10(e) << ", " << int128_to_base10(n) << ')' << endl << endl;
    
    cout << "Bob:" << endl;
    cout << "Takes message m: " << m << endl;
    
    Message enc = Encode(m, PublicKey(e, n));
    cout<< "Encodes it:" << endl;
    for(int i=0; i< enc.size; ++i){
        cout << int128_to_base10(enc.m[i]) << "   ";
    }
    cout << endl;
    cout<< "And sends it to Alice" << endl << endl;
    
    cout << "Alice:" << endl;
    m = Decode(enc, d, p, q);
    cout<< "Calculates m back: " << m << endl;
    cout << "------------------------------------------------------------------" << endl;
}
