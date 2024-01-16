#include "flint/fmpz.h"
#include "flint/fmpz_mod_mpoly.h"
#include "../HomomorphicOperator/homomorphicOperator.h"
#include "../utilities/functions.h"
#include "../utilities/structs.h"
#include "../HPPKOperator/KeyGen/hppkKeyGen.h"
#include "../HPPKOperator/Encryption/hppkEnc.h"

void testHPPKEnc(){
    
    //initialize random state
    flint_rand_t state;
    init_seed_state(state);

    //initialize context for hppkEncrypt() 
    slong nvars = 1;
    fmpz_t primeQ;
    fmpz_set_ui(primeQ, 13);
    fmpz_mod_mpoly_ctx_t ctx;
    fmpz_mod_mpoly_ctx_init(ctx, nvars, ORD_DEGREVLEX, primeQ);
    
    //initialize input message (plain text)
    fmpz_t message;
    fmpz_randm(message, state, primeQ);

    //generate HPPK keys 
    hppkKeys keys = hppkKeyGen(state);

    //encrypt plain text using generated keys
    cipherText ct = hppkEncrypt(keys.pub, message, ctx);
    

    flint_printf("\nPlainText = ");
    fmpz_print(message);
    flint_printf("\n");
    flint_printf("\nCipherText : ");
    flint_printf("C1 = ");
    fmpz_print(ct.C1);
    flint_printf("\tC2 = ");
    fmpz_print(ct.C2);
    flint_printf("\n");
}