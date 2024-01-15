#include <flint/flint.h>
#include <time.h>

extern void init_seed_state(flint_rand_t state){
    
    //Initialize by seeding a random state
    ulong seed1, seed2;
    seed1 = clock();
    seed2 = time(NULL);
    flint_randseed(state, seed1, seed2);
}

