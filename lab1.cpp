//
//  lab1.cpp
//  CRYPTO_LAB
//
//  Created by Georgy Petriv on 13.05.2024.
//

#include "lab1.hpp"

bool Miller_Rabin(int128 num, int k){
    //base cases
    if(num <= 1){
        return false;
    }
    if(num <= 3){
        return true;
    }
    if(!(num % 2)){
        return false;
    }
    
    //finding d and s
    int128 d = 0, s = 0, q = num - 1;
    while(!(q % 2)){
        s++;
        q >>= 1;
    }
    d = q;
    q = num - 1;
    
    //testing num k times
    random_device seed;
    mt19937 generator(seed());
    uniform_int_distribution<int128> _random(2, num-2);
    for(int _ = 0; _ < k; ++_){
        int128 a = _random(generator);
        int128 x = fast_pow(a, d, num);
        
        if(x == 1 || x == q){
            continue;
        }
        bool prime = false;
        for(int128 j = 1; j < s; ++j){
            
            x = fast_pow(x, 2, num);
            if(x == 1){
                return false;
            }
            if (x == q) {
                prime = true;
                break;
            }
        }
        if(!prime){
            return false;
        }
    }
    return true;
}

bool BPSW(int128 num){
    if(!FLT(num)){
        return false;
    }
    
    return LucasTest(num);
}

int128 generate_prime(int order){
    int128 res=-1, lbound=1;
    for(int i=0; i<order; ++i){
        lbound <<=1;
    }
    int128 rbound = lbound*2 - 1;
    int128 range = rbound-lbound, i=0;
    
    random_device seed;
    mt19937 generator(seed());
    uniform_int_distribution<int128> _random(lbound, rbound);
    while(i++!=range){
        res = _random(generator);
        if(BPSW(res)){
            break;
        }
    }
    return res;
}
