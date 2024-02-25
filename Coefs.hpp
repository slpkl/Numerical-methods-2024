#include <gsl/gsl_linalg.h>

namespace ADAAI {

void Coefs(int N, gsl_vector *c) {
    gsl_matrix *A = gsl_matrix_alloc(N + 1, N + 1);
    gsl_vector *b = gsl_vector_alloc(N + 1);

    gsl_matrix_set_all(A, 0.0l);

    gsl_vector_set_zero(b);
    
    gsl_vector_set(b, N, 1.0l);

    for(int k = 0; k < N; k++) {
        gsl_matrix_set(A, k, k, -1.0l);
        for(int n = k + 1; n < N + 1; n++) {
            if (n % 2 == 0) {
                if (k % 2 != 0) {
                    if (k == 1) {
                        gsl_matrix_set(A, k, n, static_cast<double>(2 * n));
                    }
                    else {
                        gsl_matrix_set(A, k, n, static_cast<double>(2 * n));
                    } 
                }
            }
            else if (n % 2 == 1) {
                    if (k == 0) {
                        gsl_matrix_set(A, k, n, static_cast<double>(n));
                    }
                    else if (k % 2 == 0){
                        gsl_matrix_set(A, k, n, static_cast<double>(2 * n));
                    } 
            }
            gsl_matrix_set(A, k, k, -1.0l);
        }
    }

    //Add Sum_0 ^N c_n * T_n(0) = 1 equality

    for(int n = 0; n < N+1; n++) {
        if(n % 2 == 0) {
            if(n % 4 == 0) {
                gsl_matrix_set(A, N, n, static_cast<double>(1));
            }
            else {
                gsl_matrix_set(A, N, n, static_cast<double>(-1));
            }
        }
    }


    gsl_linalg_HH_solve(A, b, c);

    gsl_matrix_free(A);
    gsl_vector_free(b);

    return;
}

}
