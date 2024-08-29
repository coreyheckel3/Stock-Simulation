/* 
Problem 2 (30 points)

Given that the stock price S_t follows the Geometric Brownian Motion Defined
in Assigment 1, please anwser the following questions:

1. What is the expected value of the stock price at time T?
2. What is the variance of the stock price at time T?
3. What is the probability that the stock price at time T is between 95 and 105?

Hint: You could use either path-dependent or path-independent simulation to solve this problem.
*/

#include"std_lib_facilities.h"


int main() {

    double S0 = 100;
    double r = 0.05;
    double sigma = 0.2;
    double T = 1;
    int N = 10000;

    double expected_value = S0 * exp((r - 0.5 * sigma * sigma) * T);
    double variance = S0 * S0 * exp(2 * (r - 0.5 * sigma * sigma) * T) * (exp(sigma * sigma * T) - 1);

    cout << "Expected value of S_T: " << expected_value << endl;
    cout << "Variance of S_T: " << variance << endl;





    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dist(0, 1);


    double sum = 0;
    double sum_sq = 0;
    for (int i = 0; i < N; i++) {
        double S_T = S0 * exp((r - 0.5 * sigma * sigma) * T + sigma * sqrt(T) * dist(gen));
        sum += S_T;
        sum_sq += S_T * S_T;
    }


    double mean = sum / N;
    double var = sum_sq / N - mean * mean;

    double z1 = (log(95) - log(S0) - (r - 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double z2 = (log(105) - log(S0) - (r - 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double prob = 0.5 * (erf(z2 / sqrt(2)) - erf(z1 / sqrt(2)));

    cout << "Expected value of S_T: " << mean << endl;
    cout << "Variance of S_T: " << var << endl;
    cout << "Probability that S_T is between 95 and 105: " << prob << endl;


    return 0;
}