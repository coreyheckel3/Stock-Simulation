#include "std_lib_facilities.h"
#include <iostream>
#include <random>
#include <cmath>
using namespace std;

// Parameters
const double S0 = 100; // initial stock price
const double K1 = 95; // first strike price
const double K2 = 100; // second strike price
const double K3 = 105; // third strike price
const double r = 0.02; // risk-free interest rate
const double sigma = 0.05; // volatility of the stock price
const double T = 20; // time to maturity in years
const int num_paths = 100000; // number of simulation paths
const int num_steps = 1000; // number of time steps in the simulation

// Function to simulate stock prices using path-dependent simulation
double path_dependent_simulation() {
    // Initialize variables
    double St = S0;
    double K = K1;
    double sum_payoff = 0;
    mt19937 rng; // Mersenne Twister random number generator
    rng.seed(random_device()());
    normal_distribution<double> normal(0,1); // Normal distribution with mean 0 and standard deviation 1

    // Simulate stock prices and calculate payoff at each time step
    for (int i = 0; i < num_steps; i++) {
        double t = i * T / num_steps;
        double dt = T / num_steps;
        double dWt = sqrt(dt) * normal(rng);

        St *= exp((r - 0.5 * sigma * sigma) * dt + sigma * dWt);

        if (St < K) {
            sum_payoff += K - St;
        } else {
            K = (K == K1) ? K2 : K3;
        }
    }

    // Calculate average payoff and discount to present value
    double payoff = sum_payoff / num_steps;
    double discount_factor = exp(-r * T);
    return payoff * discount_factor;
}

// Function to simulate stock prices using path-independent simulation
double path_independent_simulation() {
    // Initialize variables
    double sum_payoff = 0;
    mt19937 rng; // Mersenne Twister random number generator
    rng.seed(random_device()());
    normal_distribution<double> normal(0,1); // Normal distribution with mean 0 and standard deviation 1

    // Simulate stock prices and calculate payoff at maturity
    for (int i = 0; i < num_paths; i++) {
        double St = S0;
        double K = K1;

        for (int j = 0; j < num_steps; j++) {
            double t = j * T / num_steps;
            double dt = T / num_steps;
            double dWt = sqrt(dt) * normal(rng);

            St *= exp((r - 0.5 * sigma * sigma) * dt + sigma * dWt);
        }

        if (St < K1) {
            sum_payoff += K2 - K1;
        } else if (St < K2) {
            sum_payoff += St - K1;
        } else if (St < K3) {
            sum_payoff += K3 - St;
        } else {
            sum_payoff += 0;
        }
    }

    // Calculate average payoff and discount to present value
    double payoff = sum_payoff / num_paths;
    double discount_factor = exp(-r * T);
    return payoff * discount_factor;
}

int main() {
    double fair_price_path_dependent = path_dependent_simulation();
    double fair_price_path_independent = path_independent_simulation();

    cout << "Fair price using path-dependent simulation: " << fair_price_path_dependent << endl;
    cout << "Fair price using path-independent simulation: " << fair_price_path_independent << endl;

    return 0;
}