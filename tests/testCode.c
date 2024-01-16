#include <stdlib.h>
#include <stdio.h>
#include "flint/fmpz.h"
#include "flint/fmpz_mod_mpoly.h"
#include "flint/mpoly.h"
#include "../HomomorphicOperator/homomorphicOperator.h"
#include "../utilities/functions.h"
#include "../HPPKOperator/KeyGen/hppkKeyGen.h"
#include "../utilities/structs.h"
#include "../HPPKOperator/Encryption/hppkEnc.h"

void init_seed_state(flint_rand_t state){
    //Initialize by seeding a random state
    ulong seed1, seed2;
    seed1 = clock();
    seed2 = time(NULL);
    flint_randseed(state, seed1, seed2);
}

void fullSystemTest(){

    flint_printf("Testing the entire process as a whole based on the toy example provided in the paper:\n");

    //initialize a random state
    flint_rand_t state;
    init_seed_state(state);
    
    //Key Pair Generation
    //Set up parameters
    hppkKeys keys;
    //using 1 variable for now, multiple variables causes a seg fault, haven't found the exact cause yet
    slong nvars = 1;
    const char *mvar[] = {"x","y","z"};
    const char *var[] = {"x"};

    //initialize context for f1(x) and f2(x);
    fmpz_t primeQ;
    fmpz_set_ui(primeQ, 13);
    fmpz_mod_mpoly_ctx_t fctx;
    fmpz_mod_mpoly_ctx_init(fctx, 1, ORD_DEGREVLEX, primeQ);

    //generate the keys
    keys = hppkKeyGen(state);

    //print and test the generated public and private keys
    flint_printf("\nPrivate Keys: \n\n");
    flint_printf("S : ");
    fmpz_print(keys.priv.S);
    flint_printf("\n");
    flint_printf("R1 : ");
    fmpz_print(keys.priv.R1);
    flint_printf("\n");
    flint_printf("R1inv : ");
    fmpz_print(keys.priv.R1inv);
    flint_printf("\n");
    flint_printf("R2 : ");
    fmpz_print(keys.priv.R2);
    flint_printf("\n");
    flint_printf("R2inv : ");
    fmpz_print(keys.priv.R2inv);
    flint_printf("\n");
    flint_printf("f_1(x) : ");
    fmpz_mod_mpoly_print_pretty(keys.priv.uniF_1, var, fctx);
    flint_printf("\n");
    flint_printf("f_2(x) : ");
    fmpz_mod_mpoly_print_pretty(keys.priv.uniF_2, var, fctx);
    flint_printf("\n");
    
    //initialize context for p1 and p2, the cipher public polynomials
    fmpz_mod_mpoly_ctx_t cpctx;
    fmpz_mod_mpoly_ctx_init(cpctx, nvars, ORD_DEGREVLEX, keys.priv.S);

    flint_printf("\nPublic Keys: \n\n");

    flint_printf("CP_1(x) : ");
    fmpz_mod_mpoly_print_pretty(keys.pub.cipherPublic_1, mvar, cpctx);
    flint_printf("\n");

    flint_printf("CP_2(x) : ");
    fmpz_mod_mpoly_print_pretty(keys.pub.cipherPublic_2, mvar, cpctx);
    flint_printf("\n\n");


    //Encryption

    //initialize random input message (plain text)
    //if input message is 0, everything is 0.
    fmpz_t message;
    fmpz_randm(message, state, primeQ);
    if (fmpz_equal_ui(message, 0))
    {
        flint_printf("Input message cannot be 0\n");
    }

    //encrypt the message
    cipherText ct = hppkEncrypt(keys.pub, message, cpctx);

    //print and test the input plain text and generated cipher text
    flint_printf("\nPlainText = ");
    fmpz_print(message);
    flint_printf("\n");
    flint_printf("\nCipherText : ");
    flint_printf("C1 = ");
    fmpz_print(ct.C1);
    flint_printf("\tC2 = ");
    fmpz_print(ct.C2);
    flint_printf("\n\n");

    //Decryption

}

int main(){

    // flint_printf("\nTesting keygen for single pair (R, R_inv) \n");
    // testKeyGenSingle();

    // flint_printf("\nTesting keygen for two pairs (R_1, R_1_inv), (R_2, R_2_inv)\n");
    // testKeyGenDouble();

    // flint_printf("\nTesting Homomorphic Encryption and Decryption:\n");
    // testEncryptDecrypt();

    // flint_printf("\nTesting HPPK Key Generation:\n");
    // testHPPKKeyGen();

    // flint_printf("\nTesting HPPK Encryption:\n");
    // testHPPKEnc();

    // flint_printf("\nTesting HPPK Decryption:\n");
    // testHPPKDec();

    fullSystemTest();

}



