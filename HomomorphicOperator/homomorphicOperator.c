// HOencryption(h, sk, f):
    
//     sk: (R, S)

//     f: multivariate poly (use flint to init and assign) over F_q

//     for each c_i in f.coefficients():
//         h_i = R*c_i
//         h_i mod S
    
//     h: cipher multivariate poly (use flint to init and assign) over F_q

//     return h;

#include "flint/fmpz.h"
#include "flint/fmpz_mod_mpoly.h"
#include "flint/mpoly.h"
#include "homomorphicOperator.h"
#include "flint/fmpz_mod.h"

void homomorphicKeyGenSingle(fmpz_t R, fmpz_t R_inv, fmpz_t S, flint_bitcnt_t bits, flint_rand_t state){
    //calc the max_value (done to remove the case where S was negative)
    fmpz_t max;
    fmpz_init(max);
    fmpz_set_ui(max, (1 << bits) - 1);

    // initialize a random value for S which is 'bits' bits long
    fmpz_randm(S, state, max);

    fmpz_t gcd;
    fmpz_init(R);
    fmpz_init(R_inv);
    fmpz_init(gcd);

    do
    {
        fmpz_randm(R, state, S);
        fmpz_gcd(gcd, R, S);
    } while (fmpz_cmp_ui(gcd, 1) != 0);

    fmpz_invmod(R_inv, R, S);
    fmpz_clear(gcd);
}

void homomorphicKeyGenDouble(fmpz_t R_1, fmpz_t R_2, fmpz_t R_1_inv, fmpz_t R_2_inv, fmpz_t S,
            flint_bitcnt_t bits, flint_rand_t state)
{
    //calc the max_value (done to remove the case where S was negative)
    fmpz_t max;
    fmpz_init(max);
    fmpz_set_ui(max, (1 << bits) - 1);

    // initialize a random value for S which is 'bits' bits long
    fmpz_randm(S, state, max);

    fmpz_t gcd;
    fmpz_init(R_1);
    fmpz_init(R_2);
    fmpz_init(R_1_inv);
    fmpz_init(R_2_inv);
    fmpz_init(gcd);

    do
    {
        fmpz_randm(R_1, state, S);
        fmpz_gcd(gcd, R_1, S);
    } while (fmpz_cmp_ui(gcd, 1) != 0);

    fmpz_invmod(R_1_inv, R_1, S);

    // reinit gcd to 0 for the value of R_2
    fmpz_init(gcd);

    do
    {
        fmpz_randm(R_2, state, S);
        fmpz_gcd(gcd, R_2, S);
    } while (fmpz_cmp_ui(gcd, 1) != 0);

    fmpz_invmod(R_2_inv, R_2, S);

    fmpz_clear(gcd);
}

void homomorphicEncryptPoly(fmpz_mod_mpoly_t output, const fmpz_mod_mpoly_t input, const fmpz_t R, const fmpz_t S, 
    fmpz_mod_mpoly_ctx_t ctx)
{  
    fmpz_mod_mpoly_init(output, ctx);
    fmpz_mod_mpoly_scalar_mul_fmpz_mod_invertible(output, input, R, ctx);
}

void homomorphicDecryptPoly(fmpz_mod_mpoly_t output, const fmpz_mod_mpoly_t input, const fmpz_t R_inv, const fmpz_t S, 
    fmpz_mod_mpoly_ctx_t ctx)
{
    fmpz_mod_mpoly_init(output, ctx);
    fmpz_mod_mpoly_scalar_mul_fmpz_mod_invertible(output, input, R_inv, ctx);
}

void homomorphicDecryptCipherText(fmpz_t output, const fmpz_t input, const fmpz_t R_inv, fmpz_mod_ctx_t ctx)
{
    fmpz_init(output);
    fmpz_mod_mul(output, input, R_inv, ctx);
}
