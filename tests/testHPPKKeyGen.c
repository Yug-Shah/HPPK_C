#include "flint/fmpz.h"
#include "flint/fmpz_mod_mpoly.h"
#include "../HomomorphicOperator/homomorphicOperator.h"
#include "../utilities/functions.h"
#include "../utilities/structs.h"
#include "../HPPKOperator/KeyGen/hppkKeyGen.h"

void testHPPKKeyGen(){
    // flint_bitcnt_t bits = 10;
    //initialize random state
    flint_rand_t state;
    init_seed_state(state);
    
    //initialize context
    slong nvars = 1;
    const ordering_t ord = ORD_DEGREVLEX;
    fmpz_t primeQ;
    fmpz_set_ui(primeQ, 13);
    fmpz_mod_mpoly_ctx_t uniFctx;
    fmpz_mod_mpoly_ctx_init(uniFctx, nvars, ord, primeQ); 

    //used for testing output
    const char *var = "x"; 
    hppkKeys keys;

   
    //generate HPPK keys
    keys = hppkKeyGen(state);

    //initialize context for testing keygen 
    fmpz_mod_mpoly_ctx_t homoEncctx;
    fmpz_mod_mpoly_ctx_init(homoEncctx, nvars, ord, keys.priv.S);

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
    fmpz_mod_mpoly_print_pretty(keys.priv.uniF_1, &var, uniFctx);
    flint_printf("\n");

    flint_printf("f_2(x) : ");
    fmpz_mod_mpoly_print_pretty(keys.priv.uniF_2, &var, uniFctx);
    flint_printf("\n");

    flint_printf("\nPublic Keys: \n\n");

    flint_printf("Plain public keys only shown for testing homomorphic decryption\n");
    flint_printf("PP_1(x) : ");
    fmpz_mod_mpoly_print_pretty(keys.pub.plainPublic_1, &var, uniFctx);
    flint_printf("\n");

    flint_printf("PP_2(x) : ");
    fmpz_mod_mpoly_print_pretty(keys.pub.plainPublic_2, &var, uniFctx);
    flint_printf("\n\n");

    flint_printf("CP_1(x) : ");
    fmpz_mod_mpoly_print_pretty(keys.pub.cipherPublic_1, &var, homoEncctx);
    flint_printf("\n");

    flint_printf("CP_2(x) : ");
    fmpz_mod_mpoly_print_pretty(keys.pub.cipherPublic_2, &var, homoEncctx);
    flint_printf("\n\n");

    fmpz_mod_mpoly_t DCP_1, DCP_2;
    fmpz_mod_mpoly_init(DCP_1, homoEncctx);
    fmpz_mod_mpoly_init(DCP_2, homoEncctx);

    homomorphicDecryptPoly(keys.pub.plainPublic_1, keys.pub.cipherPublic_1, keys.priv.R1inv, keys.priv.S, homoEncctx);
    homomorphicDecryptPoly(keys.pub.plainPublic_2, keys.pub.cipherPublic_2, keys.priv.R2inv, keys.priv.S, homoEncctx);

    flint_printf("Testing whether Decrypted Cipher Public Key(DCP) = Plain Public Key(PP)\n");
    flint_printf("DCP_1(x) : ");
    fmpz_mod_mpoly_print_pretty(keys.pub.plainPublic_1, &var, homoEncctx);
    flint_printf("\n");

    flint_printf("DCP_2(x) : ");
    fmpz_mod_mpoly_print_pretty(keys.pub.plainPublic_2, &var, homoEncctx);
    flint_printf("\n");
}

