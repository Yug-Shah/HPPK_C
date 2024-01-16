// HPPKkeyGen():
// 	Private Key Generation: 
// 		HOkeygen -> HO_1 = (R_1, S)
// 		HOkeygen -> HO_2 = (R_2, S) s.t. (R_1 != R_2)
// 		f_1(x): univariate poly with random coeff from F_q (use flint to init and assign) with order < 5
// 		f_2(x): univariate poly with random coeff from F_q (use flint to init and assign) with order < 5
// 		B(x, x_1, ..., x_m): base multivariate poly used once and never stored for generation of plain public keys p_1 and p_2 (use flint to init and assign and clear from memory)

// 	Public Key Generation:
	
// 		p_1(x, x_1, ..., x_m): multivariate poly constructed by poly mul of B(x, x_1, ..., x_m) and f_1(x) (use flint to mul the two values)
// 		p_2(x, x_1, ..., x_m): multivariate poly constructed by poly mul of B(x, x_1, ..., x_m) and f_2(x) (use flint to mul the two values)

// 		HOencryption(HO_1, p_1) -> cp_1
// 		HOencryption(HO_2, p_2) -> cp_2

// 		return (cp_1, cp_2)

// #include "flint/fmpz.h"
// #include "flint/mpoly.h"
// #include "flint/fq_poly.h"
// #include "flint/fq.h"
// #include "flint/fmpz_mpoly.h"
// #include "flint/fmpz_mod_mpoly.h"
#include "../../HomomorphicOperator/homomorphicOperator.h"
#include "../../utilities/functions.h"
#include "../../utilities/structs.h"
#include "../../utilities/constants.h"
#include "hppkKeyGen.h"

hppkKeys hppkKeyGen(flint_rand_t state){

    publicKey pub;
    privateKey priv;
    hppkKeys keys;

    //define required constants
    slong length = 3;
    slong nvars = 1;
    const ordering_t ord = ORD_DEGREVLEX;
    fmpz_t primeQ;
    fmpz_set_ui(primeQ, 13);
    ulong exp_bound = 8;
    fmpz_mod_mpoly_t B;
    //used for testing output
    // const char *var = "x"; 
    // const char *value = "x";
    // const char **x = &value;

    //define and initialize contexts for hppk key generation
    fmpz_mod_mpoly_ctx_t uniFctx;
    fmpz_mod_mpoly_ctx_init(uniFctx, nvars, ord, primeQ);

    //inits
    fmpz_init(priv.S);
    fmpz_init(priv.R1);
    fmpz_init(priv.R2);
    fmpz_init(priv.R1inv);
    fmpz_init(priv.R2inv);
    fmpz_mod_mpoly_init(priv.uniF_1, uniFctx);
    fmpz_mod_mpoly_init(priv.uniF_2, uniFctx);
    fmpz_mod_mpoly_init(B, uniFctx);
    fmpz_mod_mpoly_init(pub.cipherPublic_1, uniFctx);
    fmpz_mod_mpoly_init(pub.cipherPublic_2, uniFctx);
    fmpz_mod_mpoly_init(pub.plainPublic_1, uniFctx);
    fmpz_mod_mpoly_init(pub.plainPublic_2, uniFctx);
    

    //generate private keys
    homomorphicKeyGenDouble(priv.R1, priv.R2, priv.R1inv, priv.R2inv, priv.S, bits, state);
        
    //generate univariate polynomials uniF_1 amd uniF_2
    fmpz_mod_mpoly_randtest_bound(priv.uniF_1, state, length, exp_bound, uniFctx);
    fmpz_mod_mpoly_randtest_bound(priv.uniF_2, state, length, exp_bound, uniFctx);
    
    //The following code is for using fq_poly for uniF_1 and uniF_2, however it is difficult since no conversion exists in FLINT
    // //univariate poly from fq with random coeff
    // fmpz_t q;
    // fmpz_set_ui(q, 13);
    // slong d = 1;
    // const char *var = "x";
    // fq_ctx_t fctx;
    // fq_ctx_init(fctx, q, d, var);
    // //test with a random finite field
    // // fq_ctx_randtest(fctx, state);
    // // slong length = 3;
    // fq_poly_t f_1, f_2;
    // fq_poly_init(f_1, fctx);
    // fq_poly_init(f_2, fctx);
    // fq_poly_randtest_not_zero(f_1, state, length, fctx);
    // fq_poly_randtest_not_zero(f_2, state, length, fctx);

    // flint_printf("\nf_1(x) : ");
    // fq_poly_print_pretty(f_1, "x",fctx);
    // flint_printf("\nf_2(x): ");
    // fq_poly_print_pretty(f_2, "x", fctx);
    // flint_printf("\n");

    //generate public keys

    //generate the base polynomial B()
    fmpz_mod_mpoly_randtest_bound(B, state, length, exp_bound, uniFctx); 

    //generate plain public polynomials p_1 and p_2
    fmpz_mod_mpoly_mul(pub.plainPublic_1, B, priv.uniF_1, uniFctx);
    fmpz_mod_mpoly_mul(pub.plainPublic_2, B, priv.uniF_2, uniFctx);

    //clear the base polynomial B()
    fmpz_mod_mpoly_clear(B, uniFctx);

    //define and initialize contexts for passing to homomorphic encrypt
    fmpz_mod_mpoly_ctx_t homoEncctx;
    fmpz_mod_mpoly_ctx_init(homoEncctx, nvars, ord, priv.S);

    //generate the cipher public polynomials cipherPublic_1 and cipherPublic_2
    homomorphicEncryptPoly(pub.cipherPublic_1, pub.plainPublic_1, priv.R1, priv.S, homoEncctx);
    homomorphicEncryptPoly(pub.cipherPublic_2, pub.plainPublic_2, priv.R2, priv.S, homoEncctx);

    keys.pub = pub;
    keys.priv = priv;

    return keys;
}

