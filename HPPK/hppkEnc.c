// HPPKencryption(x, (cp_1, cp_2)):
// 	plain text message = x mod q
// 	random assign x_1, ..., x_m as noise mod q
// 	precalculate and store the values for x_11 = x_1*x, x_12 = x_1*x^2 ... x_mm = x_m * x^m 
// 		since each value corresponds to the coefficient of the corresponding term in the public key (cp_1, cp_2)

// 	use flint to evaluate cp_1 and cp_2 on these values of x, x_1, ..., x_m
// 		C_1 = cp_1(x, x_1, ..., x_m)
// 		C_2 = cp_2(x, x_1, ..., x_m)
	
// 		return (C_1, C_2)