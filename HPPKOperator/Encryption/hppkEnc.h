#ifndef hppkEnc_H_
#define hppkEnc_H_

#include "flint/fmpz.h"
#include "flint/fmpz_mod_mpoly.h"
#include "../../utilities/structs.h"

cipherText hppkEncrypt(publicKey key, fmpz_t x, fmpz_mod_mpoly_ctx_t ctx);

#endif //hppkEnc_H_