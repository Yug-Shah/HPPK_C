// HPPKkeyGen():
// 	Private Key Generation: 
// 		HOkeygen -> HO_1 = (R_1, S)
// 		HOkeygen -> HO_2 = (R_2, S) s.t. (R_1 != R_2)
// 		f_1(x): univariate poly with random coeff from F_q (use flint to init and assign) with order < 5
// 		f_2(x): univariate poly with random coeff from F_q (use flint to init and assign) with order < 5
// 		B(x, x_1, ..., x_m): base multivariate poly used once and never stored for generation of plain public keys p_1 and p_2 (use flint to init and assign and clear from memory)

// 	Public Key Generation:
	
// 		p_1(x, x_1, ..., x_m): multivariate poly constructed by poly mul of B(x, x_1, ..., x_m) and f_1(x) (use flint to mul the two values)
// 		p_2(x, x_1, ..., x_m): multivariate poly constructed by poly mul of B(x, x_1, ..., x_m) and f_2(x) (use flint to mul the two values)

// 		HOencryption(HO_1, p_1) -> cp_1
// 		HOencryption(HO_2, p_2) -> cp_2

// 		return (cp_1, cp_2)