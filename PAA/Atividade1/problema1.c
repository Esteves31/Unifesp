#include <stdio.h>
#include <stdint.h>

// Soma todos os bits 1 no intervalo [0, N]
unsigned long long int count_bits_one(unsigned long long int N);

int main() {
    unsigned long long int X, Y;
    scanf("%llu %llu", &X, &Y);

    if (X > Y || Y > 10000000000000000ULL || X < 0) {
        return -1;
    }

    unsigned long long int result = count_bits_one(Y) - count_bits_one(X - 1);
    printf("%llu\n", result);

    return 0;
}

unsigned long long int count_bits_one(unsigned long long int N) {
    unsigned long long int count = 0;
    unsigned long long int power_of_2 = 1;
     
    for (int i = 0; i < 64 && power_of_2 <= N; i++) {
        unsigned long long int total_pairs = (N + 1) / (power_of_2 << 1);
        unsigned long long int count_one_in_position = total_pairs * power_of_2;
        
        unsigned long long int remainder = (N + 1) % (power_of_2 << 1);
        if (remainder > power_of_2) {
            count_one_in_position += remainder - power_of_2;
        }
        
        count += count_one_in_position;
        power_of_2 <<= 1;
    }
    
    return count;
}