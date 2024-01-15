#include <stdlib.h>
#include <stdio.h>
#include "flint/fmpz.h"
#include "flint/fmpz_mod_mpoly.h"
#include "flint/mpoly.h"
// #include "flint/fq_poly.h"
// #include "flint/fq.h"
#include "HomomorphicOperator/homomorphicOperator.h"
#include "HomomorphicOperator/utility/utilityFunctions.h"
#include "HPPK/hppkKeyGen.h"
#include "HPPK/utility/structs.h"

// int main(){

//     flint_printf("\nTesting keygen for single pair (R, R_inv) \n");
//     testKeyGenSingle();

//     flint_printf("\nTesting keygen for two pairs (R_1, R_1_inv), (R_2, R_2_inv)\n");
//     testKeyGenDouble();

//     flint_printf("\nTesting Homomorphic Encryption and Decryption:\n");
//     testEncryptDecrypt();

//     flint_printf("\nTesting HPPK Key Generation:\n");
//     testHPPKKeyGen();

// }