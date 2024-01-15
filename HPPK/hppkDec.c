// HPPKdencryption((C_1, C_2), (HO_1, HO_2), (f_1(x), f_2(x))):
// 	HOdecryption(HO_1, C_1) -> CP_1 
// 	HOdecryption(HO_2, C_2) -> CP_2

// 	divide CP_1 by CP_2 to eliminate noise variables and the base poly B(x, x_1, ..., x_m) to get
// 		CP_1 / CP_2 = K = f_1(x)/f_2(x)
	
// 	solve for x knowing K, f_1(x) and f_2(x)
// 	return x;