#ifndef homomorphicOperator_H_
#define homomorphicOperator_H_

#include "flint/fmpz.h"
#include "flint/fmpz_mod_mpoly.h"
#include "flint/mpoly.h"

void keyGenSingle(fmpz_t R, fmpz_t R_inv, fmpz_t S, flint_bitcnt_t bits, flint_rand_t state);

void keyGenDouble(fmpz_t R_1, fmpz_t R_2, fmpz_t R_1_inv, fmpz_t R_2_inv, fmpz_t S, flint_bitcnt_t bits, flint_rand_t state);

void Encrypt(fmpz_mod_mpoly_t output, const fmpz_mod_mpoly_t input, const fmpz_t R, const fmpz_t S, 
    fmpz_mod_mpoly_ctx_t ctx);

void Decrypt(fmpz_mod_mpoly_t output, const fmpz_mod_mpoly_t input, const fmpz_t R_inv, const fmpz_t S, 
    fmpz_mod_mpoly_ctx_t ctx);    

#endif //homomorphicOperator_H_