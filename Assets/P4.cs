using System;
using System.Linq;
using Extensions;
using static Extensions.ActionExtensions;

namespace NMF4
{
    class Program
    {
        static void Main()
        {
            int b = 5,
                a = 3,
                s = 2,
                m = a,
                i;
            double
                tx0 = 17,
                txb = 850,
                l = 0.5,
                h = 0.1,
                sigma = 1.0 / 6,
                ro = 500,
                lamda = 0.184,
                c = 0.84,
                a_pwr2 = lamda * 1.0 / (c * ro),
                tau = Math.Pow(h, 2) * sigma / a_pwr2,
                gamma = (0.5 * tau) / Math.Pow(h, 2),
                a0 = a_pwr2,
                a1 = 1.0 / tx0;
            double[][] u = new double[a + 1].Select(x => new double[b + 1].ToArray()).ToArray();
             
            double gx(double k) => Math.Pow(k, s + 1);
            for (i = 0; i < (int)(l / h) + 1; i++)
            {
                u[0][i] = (txb - tx0) * gx(h * i) / gx(l) + tx0;
            }

            double[]
                alfa = new double[b],
                beta = new double[b],
                _a = new double[b],
                _b = new double[b],
                _c = new double[b];

            double K(double x) => a0 * (1 - Math.Pow(Math.E, -a1 * x));
            double ABi(double x_prev, double x) => 0.5 * (K(x) + K(x_prev));
            _();
            for (int j = 1; j < b; j++)
            {
                _a[j] = ABi(u[0][j - 1], u[0][j]);
                _b[j] = ABi(u[0][j], u[0][j + 1]);
                _c[j] = _a[j] + _b[j] + 1.0 / gamma;
            }
            for (int it = 1; it <= m; it++)
            {
                u[it][0] = tx0;
                u[it][b] = txb;
                beta[0] = tx0;
                double[] F = new double[b];

                for (i = 1; i < b; i++)
                {
                    var u_i = u[it - 1];
                    F[i - 1] = -(1.0 / gamma) * u_i[i] -
                                _b[i] * (u_i[i + 1] - u_i[i]) +
                                _a[i] * (u_i[i] - u_i[i - 1]);
                    alfa[i] = _b[i] * 1.0 /
                              (_c[i] - alfa[i - 1] * _a[i]);
                    beta[i] = (_a[i] * beta[i - 1] - F[i - 1]) * 1.0 /
                              (_c[i] - alfa[i - 1] * _a[i]);
                }
                _();
                for (int j = b - 1; j > 0; j--)
                {
                    u[it][j] = alfa[j] * u[it][j + 1] + beta[j];
                }
            }

            u.Reverse().Print();
        }
    }
}
