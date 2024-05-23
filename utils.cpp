//
//  utils.cpp
//  CRYPTO_LAB
//
//  Created by Georgy Petriv on 13.05.2024.
//
#include "utils.hpp"

int128 fast_pow(int128 base, int128 exp, int128 mod){
    int128 res = 1, temp;
    base %= mod;
    
    
    while(exp > 0){
        if(exp & 1){
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    
    return res;
}

int128 gcd(int128 num1, int128 num2){
    return num2 == 0 ? num1 : gcd(num2, num1 % num2);
}

int128 lcm(int128 num1, int128 num2){
    return (num1 / gcd(num1, num2)) * num2;
}

int128 coprime(int128 num){
    random_device seed;
    mt19937 generator(seed());
    uniform_int_distribution<int128> _random(1, num);
    
    int128 x;
    while(true){
        x = _random(generator);
        if(gcd(x,num) == 1){
            return x;
        }
    }
}

bool FLT(int128 num){
    if(num<=1){
        return false;
    }
    if(num == 2){
        return true;
    }
    if(!(num % 2)){
        return false;
    }
    return fast_pow(2, num-1, num) == 1;
}

int Jacobi(int128 num, int128 m) {
    if(m <= 0 || m % 2 == 0){
        throw "Out of range Jacoby symbol call";
    }
    num = num % m;
    int t = 1;
    int128 r;
    while (num != 0) {
        while (num % 2 == 0) {
            num /= 2;
            r = m % 8;
            if (r == 3 || r == 5) {
                t = -t;
            }
        }
        r = m;
        m = num;
        num = r;
        if (num % 4 == 3 && m % 4 == 3) {
            t = -t;
        }
        num = num % m;
    }
    if (m == 1) {
        return t;
    }
    else {
        return 0;
    }
}

void LucasSeq(int128& U, int128& V, int128 D, int128 P, int128 Q, int128 num){
    U=1;
    V=P;
    int128 Qk = Q, temp = num + 1, k = 1;
    int128 U_temp, V_temp;
    int* stack = new int[int(log2(temp)+1)];
    int iter = 0;
    
    while(temp > 1){
        stack[iter++] = temp % 2;
        temp >>= 1;
    }
    --iter;
    
    while(iter != -1){
        int cur = stack[iter--];
        
        U = (U * V) % num;
        V = (V * V - 2 * Qk) % num;
        Qk = fast_pow(Qk, 2, num);
        k *= 2;
        
        if(cur == 1){
            U_temp = U;
            V_temp = V;

            int128 s = P*U_temp + V_temp;
            int128 m = (D*U_temp + P*V_temp);
            
            if (s & 1) {
                s += num;
            }
            if (m & 1) {
                m += num;
            }
            
            U = (s/2)%num;
            V = (m/2)%num;
            k++;
            Qk = (Qk * Q) % num;
        }
    }
    delete [] stack;
}

bool LucasTest(int128 num){
    if(num == 2){
        return true;
    }
    int128 D = 5;
    while(Jacobi(D, num) != -1){
        D = -D + (D > 0 ? -2 : 2);
    }
    
    int128 P = 1, Q = (1 - D) / 4, U, V;
    LucasSeq(U, V, D, P, Q, num);
    
    return U % num == 0;
}

string int128_to_base2(int128 num){
    string res;
    if(num == 0){
        return "0";
    }
    while(num > 1){
        if(num & 1){
            res += '1';
        }
        else{
            res += '0';
        }
        num >>= 1;
    }
    res += '1';
    reverse(res.begin(), res.end());
    return res;
}

string int128_to_base10(int128 num){
    string res;
    do{
        res += char(num % 10 + 48);
        num /= 10;
    }while(num > 0);
    
    reverse(res.begin(), res.end());
    return res;
    
}
string int128_to_base64(int128 num){
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string res;
    if(num == 0){
        return "0";
    }
    while(num > 0){
        res += chars[num % 64];
        num /= 64;
    }
    reverse(res.begin(), res.end());
    return res;
}
string int128_to_byteset(int128 num){
    string res;
    int bytes[sizeof(int128)];
    int i=0;
    while(num > 0){
        bytes[i++]=num % 256;
        num /= 256;
    }
    i--;
    while(i > 0){
        res += to_string(bytes[i--]) + " ";
    }
    res += to_string(bytes[0]);
    return res;
}
