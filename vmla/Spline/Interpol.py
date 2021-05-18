import numpy as np


def _solve_tridiag_matrix(under, up, diag, free, dtype=float):
    N = len(free)
    # Init forward step
    alpha = np.empty(N, dtype)  # alpha i = 1..N-1
    alpha[1] = up[0] / diag[0]
    beta = np.empty(N + 1, dtype)  # beta i = 1..N
    beta[1] = free[0] / diag[0]
    # Iterate
    for i in range(1, N - 1):  # i = 1..N-2
        den = 1 / (diag[i] - under[i] * alpha[i])
        alpha[i + 1] = up[i] * den  # i+1 = 2..N-1
        beta[i + 1] = (free[i] + under[i] * beta[i]) * den
    else:
        beta[N] = (free[N - 1] + under[N - 1] * beta[N - 1]) / (diag[N - 1] - under[N - 1] * alpha[N - 1])
    # Init backward step
    x = np.empty(N, dtype)
    x[N - 1] = (free[N - 1] + under[N - 1] * beta[N - 1]) / (diag[N - 1] - under[N - 1] * alpha[N - 1])
    for i in range(N - 2, -1, -1):  # i = N-2..0
        x[i] = alpha[i + 1] * x[i + 1] + beta[i + 1]
    return x


#np.set_printoptions(precision=5)
up = np.array([1, 1, -2, 4, 0.], float)
und = np.array([0., 3, 5, 6, 5], float)
diag = np.array([2, 8, 12, 18, 10.], float)
f = np.array([-25, 72, -69, -156, 20.], float)
print(_solve_tridiag_matrix(und, up, diag, f))
