#include "flint/fmpz.h"
// #include "flint/mpoly.h"
// #include "flint/fq_poly.h"
// #include "flint/fq.h"
// #include "flint/fmpz_mpoly.h"
#include "flint/fmpz_mod_mpoly.h"
#include "../../HomomorphicOperator/homomorphicOperator.h"
#include "../../HomomorphicOperator/utility/utilityFunctions.h"
#include "../utility/structs.h"
#include "../hppkKeyGen.h"

void testHPPKKeyGen(){
    // flint_bitcnt_t bits = 10;
    flint_rand_t state;
    init_seed_state(state);
    // slong length = 3;
    slong nvars = 1;
    // ulong exp_bound = 8;
    const ordering_t ord = ORD_DEGREVLEX;
    fmpz_t primeQ;
    fmpz_set_ui(primeQ, 13);
    // fmpz_mod_mpoly_t B, p_1, p_2;
    //used for testing output
    const char *var = "x"; 
    // const char *value = "x";
    // const char **x = &value;
    hppkKeys keys;

    fmpz_mod_mpoly_ctx_t uniFctx;
    fmpz_mod_mpoly_ctx_init(uniFctx, nvars, ord, primeQ);    

    keys = hppkKeyGen(state);

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

    flint_printf("DCP_1(x) : ");
    fmpz_mod_mpoly_print_pretty(keys.pub.plainPublic_1, &var, homoEncctx);
    flint_printf("\n");

    flint_printf("DCP_2(x) : ");
    fmpz_mod_mpoly_print_pretty(keys.pub.plainPublic_2, &var, homoEncctx);
    flint_printf("\n");
}

