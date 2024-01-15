#include <stdlib.h>
#include <stdio.h>
#include "flint/fmpz.h"
#include "flint/fmpz_mod_mpoly.h"
#include "flint/mpoly.h"
#include "../homomorphicOperator.h"
#include "../utility/utilityFunctions.h"


void testKeyGenSingle(){
    fmpz_t R, R_inv, S;
    flint_bitcnt_t bits = 10; // can change based on the number of bits required.

    fmpz_init(R);
    fmpz_init(R_inv);
    fmpz_init(S);

    flint_rand_t state;
    init_seed_state(state);

    keyGenSingle(R, R_inv, S, bits, state); // call the main function

    flint_printf("S : ");
    fmpz_print(S);
    flint_printf("\n");
    flint_printf("R : ");
    fmpz_print(R);
    flint_printf("\n");
    flint_printf("R_inv : ");
    fmpz_print(R_inv);
    flint_printf("\n");


    fmpz_clear(R);
    fmpz_clear(R_inv);
    
}

void testKeyGenDouble(){
    fmpz_t R_1, R_2, R_1_inv, R_2_inv, S;
    flint_bitcnt_t bits = 10; // can change based on the number of bits required.

    fmpz_init(R_1);
    fmpz_init(R_2);
    fmpz_init(R_1_inv);
    fmpz_init(R_2_inv);
    fmpz_init(S);

    flint_rand_t state;
    init_seed_state(state);

    keyGenDouble(R_1, R_2, R_1_inv, R_2_inv, S, bits, state); // call the main function

    flint_printf("S : ");
    fmpz_print(S);
    flint_printf("\n");
    flint_printf("R_1 : ");
    fmpz_print(R_1);
    flint_printf("\n");
    flint_printf("R_1_inv : ");
    fmpz_print(R_1_inv);
    flint_printf("\n");
    flint_printf("R_2 : ");
    fmpz_print(R_2);
    flint_printf("\n");
    flint_printf("R_2_inv : ");
    fmpz_print(R_2_inv);
    flint_printf("\n");


    fmpz_clear(R_1);
    fmpz_clear(R_2);
    fmpz_clear(R_1_inv);
    fmpz_clear(R_2_inv);
}

int main(){
    flint_printf("\nTesting keygen for single pair (R, R_inv) \n");
    testKeyGenSingle();
    flint_printf("\nTesting keygen for two pairs (R_1, R_1_inv), (R_2, R_2_inv)\n");
    testKeyGenDouble();
    flint_printf("\n");
}