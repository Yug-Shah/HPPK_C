#ifndef hppkEnc_H_
#define hppkEnc_H_

#include "flint/fmpz.h"
#include "flint/fmpz_mod_mpoly.h"
#include "utility/structs.h"

cipherText hppkEncrypt(publicKey key, fmpz_t x);

#endif //hppkEnc_H_