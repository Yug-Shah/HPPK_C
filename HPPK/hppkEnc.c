// HPPKencryption(x, (cp_1, cp_2)):
// 	plain text message = x mod q
// 	random assign x_1, ..., x_m as noise mod q
// 	precalculate and store the values for x_11 = x_1*x, x_12 = x_1*x^2 ... x_mm = x_m * x^m 
// 		since each value corresponds to the coefficient of the corresponding term in the public key (cp_1, cp_2)

// 	use flint to evaluate cp_1 and cp_2 on these values of x, x_1, ..., x_m
// 		C_1 = cp_1(x, x_1, ..., x_m)
// 		C_2 = cp_2(x, x_1, ..., x_m)
	
// 		return (C_1, C_2)
#include <stdlib.h>
#include "utility/structs.h"
#include "flint/fmpz_vec.h"
#include "hppkKeyGen.h"
#include "../HomomorphicOperator/homomorphicOperator.h"

cipherText hppkEncrypt(publicKey key, fmpz_t x){

    cipherText cipherText;
    slong nvars = 1;
    const ordering_t ord = ORD_DEGREVLEX;
    fmpz_t primeQ;
    fmpz_set_ui(primeQ, 13);
    fmpz_mod_mpoly_ctx_t uniFctx;
    fmpz_mod_mpoly_ctx_init(uniFctx, nvars, ord, primeQ);
    fmpz_t *vals[1]; // Array of pointers
    vals[0] = &x;    // Set the first element to point to x


    fmpz_mod_mpoly_evaluate_all_fmpz(cipherText.C1 , key.cipherPublic_1, vals, uniFctx);

    fmpz_mod_mpoly_evaluate_all_fmpz(cipherText.C2 , key.cipherPublic_2, vals, uniFctx);

    return cipherText;

}

void hppkDecrypt(hppkKeys keys, cipherText cipherText){
    
    slong nvars = 1;
    const ordering_t ord = ORD_DEGREVLEX;
    
    fmpz_mod_ctx_t homoDecctx;
    fmpz_mod_ctx_init(homoDecctx, keys.priv.S);

    fmpz_t primeQ;
    fmpz_set_ui(primeQ, 13);

    fmpz_mod_ctx_t HPPKctx;
    fmpz_mod_ctx_init(HPPKctx, primeQ);

    fmpz_t p1, p2, K;
    fmpz_init(p1);
    fmpz_init(p2);
    fmpz_init(K);

    homomorphicDecryptCipherText(p1, cipherText.C1, keys.priv.R1inv, homoDecctx);
    homomorphicDecryptCipherText(p2, cipherText.C2, keys.priv.R2inv, homoDecctx);

    flint_printf("Before mod q:\n");
    flint_printf("\nP1 : ");
    fmpz_print(p1);
    flint_printf("\n");
    flint_printf("\nP2 : ");
    fmpz_print(p2);
    flint_printf("\n\n");

    fmpz_mod_set_fmpz(p1, p1, HPPKctx);
    fmpz_mod_set_fmpz(p2, p2, HPPKctx);

    flint_printf("After mod q:\n");
    flint_printf("\nP1 : ");
    fmpz_print(p1);
    flint_printf("\n");
    flint_printf("\nP2 : ");
    fmpz_print(p2);
    flint_printf("\n\n");

    //K holds the value of the ratio of f_1(x) and f_2(x) which can then be used to solve for x
    fmpz_mod_divides(K, p1, p2, HPPKctx);

    flint_printf("Ratio K : ");
    fmpz_print(K);
    flint_printf("\n\n");


}

int main(){
    // hppkEncrypt();
    flint_printf("Testing\n");
    flint_rand_t state;
    init_seed_state(state);
    fmpz_t message;
    fmpz_set_ui(message, 8);
    hppkKeys keys = hppkKeyGen(state);
    cipherText ct = hppkEncrypt(keys.pub, message);
    flint_printf("CipherText generated\n");
    flint_printf("\nC1 : ");
    fmpz_print(ct.C1);
    flint_printf("\n");
    flint_printf("\nC2 : ");
    fmpz_print(ct.C2);
    flint_printf("\n");
    hppkDecrypt(keys, ct);
}