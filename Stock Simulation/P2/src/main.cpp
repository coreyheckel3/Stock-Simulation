/*
    Assume we have 3 stocks: stock A, stock B, stock C, their prices follows the Geometric Brownian Motions.
    In discrete case, to be more specific:

    Daily Return of Stock A: R_A = (S_A_{t+1} - S_A_{t})/S_A_{t} = r + sigma * Z_A_{t}
    Daily Return of Stock B: R_B = (S_B_{t+1} - S_B_{t})/S_B_{t} = r + sigma * Z_B_{t}
    Daily Return of Stock C: R_C = (S_C_{t+1} - S_C_{t})/S_C_{t} = r + sigma * Z_C_{t}

    In the above:
        * S_A_{t+1} is the stock A's price at time t+1, S_A_{t} is the price at time t
        * Initial prices for Stock A,B,C are the same S_A_{0} = S_B_{0} = S_C_{0} = 1.0
        * Z_A_{t} and Z_B_{t} and Z_C_{t} are mutually independent standard Gaussian Random Variables.
        * risk-free rate: r = 0.01 and the volatility of the stock return sigma: = 0.02 are shared by all stocks.

    Based on these settings, please provide solutions for following questions:
        1.(20 points) At t = 5, what is the probability that S_A_{t} > 1.051?
        2.(10 points) If you invest 1/3 dollar in each stock at t = 0, what is the probability that you end up with
            more than 1.051 dollars at t = 5?
        3.(20 points) If you invest 1/3 dollar in each stock at t = 0, what is the daily volatility of your portfolio
        returns?
*/

#include "std_lib_facilities.h"
/**************************************************Your Code********************************************************/
// Define the functions you need
double simulate_stock_price(double r, double sigma, double s0, int t, default_random_engine &engine) {
    normal_distribution<double> dist(0, 1);
    double price = s0;
    for (int i = 0; i < t; i++) {
        double Z = dist(engine);
        price *= (1 + r + sigma * Z);
    }
    return price;
}
/*******************************************************************************************************************/

int main()
{
    /**************************************************Your Code********************************************************/
    random_device seed;
    default_random_engine engine(seed());
    double r = 0.01;
    double sigma = 0.02;
    double s0 = 1.0;
    // number of simulation
    const int N = 1000000;



    // Question 1:
    int count_A = 0;
    for (int i = 0; i < N; i++) {
        double stock_A = simulate_stock_price(r, sigma, s0, 5, engine);
        if (stock_A > 1.051) {
            count_A++;
        }
    }
    double prob_A = static_cast<double>(count_A) / N;
    cout << "Probability that S_A_{t} > 1.051: " << prob_A << endl;

    // Question 2:
    int count_total = 0;
    for (int i = 0; i < N; i++) {
        double stock_A = simulate_stock_price(r, sigma, s0, 5, engine);
        double stock_B = simulate_stock_price(r, sigma, s0, 5, engine);
        double stock_C = simulate_stock_price(r, sigma, s0, 5, engine);
        double total_value = stock_A * (1.0 / 3.0) + stock_B * (1.0 / 3.0) + stock_C * (1.0 / 3.0);
        if (total_value > 1.051) {
            count_total++;
        }
    }
    double prob_total = static_cast<double>(count_total) / N;
    cout << "Probability that I end up with more than 1.051 dollar: " << prob_total << endl;

    // Question 3:
    vector<double> daily_returns(N);
    for (int i = 0; i < N; i++) {
        double stock_A = simulate_stock_price(r, sigma, s0, 1, engine);
        double stock_B = simulate_stock_price(r, sigma, s0, 1, engine);
        double stock_C = simulate_stock_price(r, sigma, s0, 1, engine);
        double portfolio_return = (stock_A - s0) / s0 * (1.0 / 3.0) + (stock_B - s0) / s0 * (1.0 / 3.0) + (stock_C - s0) / s0 * (1.0 / 3.0);
        daily_returns[i] = portfolio_return;
    }

    double mean = accumulate(daily_returns.begin(), daily_returns.end(), 0.0) / N;
    double variance = 0.0;
    for (double ret : daily_returns) {

        variance += (ret - mean) * (ret - mean);
    }
    variance /= N;
    double daily_volatility = sqrt(variance);
    cout << "Daily Volatility of the portfolio returns: " << daily_volatility << endl;

    return 0;


}
