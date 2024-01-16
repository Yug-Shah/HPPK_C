#include "flint/fmpz.h"
#include "flint/fmpz_mod_mpoly.h"
#include "../HomomorphicOperator/homomorphicOperator.h"
#include "../utilities/functions.h"


void testEncryptDecrypt(){

    fmpz_t R, R_inv, S;
    flint_bitcnt_t bits = 10;

    fmpz_init(R);
    fmpz_init(R_inv);
    fmpz_init(S);
    
    //initialize and seed random state
    flint_rand_t state;
    init_seed_state(state);

    //generate set of keys to use for test
    homomorphicKeyGenSingle(R, R_inv, S, bits, state);
    
    fmpz_mod_mpoly_t encOut, encIn, decIn, decOut;

    //define required variables
    slong nvars = 1;
    slong length = 3;
    ulong exp_bound = 8;
    const char *value = "x";
    const char **x = &value;
    fmpz_mod_mpoly_ctx_t ctx;
    const ordering_t ord = ORD_DEGREVLEX;

    flint_printf("\nTesting Encryption:\n");
    
    //initialize the context and the encryption input
    fmpz_mod_mpoly_ctx_init(ctx, nvars, ord, S);
    fmpz_mod_mpoly_init(encIn, ctx);
    
    // generate and print a random poly for testing encryption function
    fmpz_mod_mpoly_randtest_bound(encIn, state, length, exp_bound, ctx);
    flint_printf("Encryption input: ");
    fmpz_mod_mpoly_print_pretty(encIn, x, ctx);
    flint_printf("\n");

    //call the encryption fuction on encIn and get the cipher text in encOut
    //Print the cipher text
    homomorphicEncryptPoly(encOut, encIn, R, S, ctx);
    flint_printf("Encryption output: ");
    fmpz_mod_mpoly_print_pretty(encOut, x, ctx);
    flint_printf("\n\n");

    flint_printf("Testing Decryption:\n");

    //initialize the decryption input
    fmpz_mod_mpoly_init(decIn, ctx);
    
    // assign the output of encryption as the decryption input
    fmpz_mod_mpoly_set(decIn, encOut, ctx);
    flint_printf("Decryption input: ");
    fmpz_mod_mpoly_print_pretty(decIn, x, ctx);
    flint_printf("\n");

    //call the decryption fuction on decIn and get the plain text in decOut
    //Print the plain text
    homomorphicDecryptPoly(decOut, decIn, R_inv, S, ctx);
    flint_printf("Decryption output: ");
    fmpz_mod_mpoly_print_pretty(decOut, x, ctx);
    flint_printf("\n\n");    
}
