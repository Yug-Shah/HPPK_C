// HPPKencryption(x, (cp_1, cp_2)):
// 	plain text message = x mod q
// 	random assign x_1, ..., x_m as noise mod q
// 	precalculate and store the values for x_11 = x_1*x, x_12 = x_1*x^2 ... x_mm = x_m * x^m 
// 		since each value corresponds to the coefficient of the corresponding term in the public key (cp_1, cp_2)

// 	use flint to evaluate cp_1 and cp_2 on these values of x, x_1, ..., x_m
// 		C_1 = cp_1(x, x_1, ..., x_m)
// 		C_2 = cp_2(x, x_1, ..., x_m)
	
// 		return (C_1, C_2)
#include "flint/fmpz_vec.h"
#include "flint/fmpz_mod_mpoly.h"
#include "../KeyGen/hppkKeyGen.h"
#include "../../HomomorphicOperator/homomorphicOperator.h"
#include "../../utilities/structs.h"

cipherText hppkEncrypt(publicKey key, fmpz_t x, fmpz_mod_mpoly_ctx_t ctx){

    cipherText cipherText;

    //Can be extended to an array of size m, and initializing the other values variables to random
    const fmpz_t *vals[] = {x};

    fmpz_mod_mpoly_evaluate_all_fmpz(cipherText.C1 , key.cipherPublic_1, vals, ctx);

    fmpz_mod_mpoly_evaluate_all_fmpz(cipherText.C2 , key.cipherPublic_2, vals, ctx);

    return cipherText;
}
