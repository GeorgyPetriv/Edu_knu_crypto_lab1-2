//
//  tests.cpp
//  CRYPTO_LAB
//
//  Created by Georgy Petriv on 13.05.2024.
//

#include "tests.hpp"
#include "lab1.hpp"

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
