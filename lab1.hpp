//
//  lab1.hpp
//  CRYPTO_LAB
//
//  Created by Georgy Petriv on 13.05.2024.
//

#ifndef lab1_hpp
#define lab1_hpp

#include <stdio.h>

#include "utils.hpp"

//tests
bool Miller_Rabin(int128 num, int k);
bool BPSW(int128 num);

//prime number generator
int128 generate_prime(int order);

#endif /* lab1_hpp */
