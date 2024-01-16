#ifndef structs_H_
#define structs_H_

#include "flint/fmpz.h"
#include "flint/fmpz_mod_mpoly.h"

typedef struct 
{
    fmpz_mod_mpoly_t cipherPublic_1;
    fmpz_mod_mpoly_t cipherPublic_2;
    fmpz_mod_mpoly_t plainPublic_1;
    fmpz_mod_mpoly_t plainPublic_2;

} publicKey;

typedef struct
{
    fmpz_t S;
    fmpz_t R1;
    fmpz_t R2;
    fmpz_t R1inv;
    fmpz_t R2inv;
    fmpz_mod_mpoly_t uniF_1;
    fmpz_mod_mpoly_t uniF_2;

} privateKey;

typedef struct 
{
    publicKey pub;
    privateKey priv;

} hppkKeys;

typedef struct
{
    fmpz_t C1;
    fmpz_t C2;
} cipherText;


#endif //structs_H_