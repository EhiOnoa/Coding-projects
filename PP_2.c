// header files
#include <stdio.h>
#include <math.h>

// global constants
#define TOO_LOW_PREMIUM -1
#define TOO_HIGH_PREMIUM 1
#define RECOMMENDED 0
#define LOWER_THRESHOLD_PREMIUM 0.01
#define UPPER_THRESHOLD_PREMIUM 0.05

// prototypes
double normalCDF(double x);

// main program
int main() {
    // initialize the program
        // declare user input variables
    double currentStockPrice, strikePrice, riskFreeInterestRate, timeToExpire,
           sigma;
        // declare supporting variables
    double ratioStockStrike, growthRate, sumRatioGrowth, overTimeVolatility, 
           expectedStockValue, expectedStrikePrice;
        // declare user output variables
    double d1factor, d2factor, d1NormalDistr, d2NormalDistr, premium;
    
        // show title
            //function: printf
    printf("\nCall Option Price Calculator (Black-Scholes Model)\n");
    printf("==================================================\n\n");
    
    // get the user input
        // print a message explaining the steps
            // functions: printf
    printf("Please provide the data for Call Option Price calculation\n");
    
        // prompt for the current stock price
            // functions: printf
    printf("Inform the current stock price (S):\n");
    
        // read the current stock price from the user input
            // functions: scanf
    scanf("%lf", &currentStockPrice);
    
        // prompt for the strike price
            // functions: printf
    printf("Inform the strike price (X):\n");
    
        // read the strike price from the user input
            // functions: scanf
    scanf("%lf", &strikePrice);
    
        // prompt for the risk-free interest rate
            // functions: printf
    printf("Inform the risk-free interest rate (r - a number between "
           "0.0-1.0):\n");
    
        // read the risk-free interest rate from the user input
            // functions: scanf
    scanf("%lf", &riskFreeInterestRate);
    
        // prompt for the time to expiration in years
            // functions: printf
    printf("Inform the time to expiration in years (T):\n");
    
        // read the time expiration from the user input
            // functions: scanf
    scanf("%lf", &timeToExpire);
    
        // prompt for the volatility
            // functions: printf
    printf("Inform the volatility (sigma - a number between 0.0-1.0):\n");
    
        // read the volatility from the user input
            // functions: scanf
    scanf("%lf", &sigma);
    
    // process the data
        // print a message to inform the user about the processing
    printf("\nCalculating the Call Option Price...\n\n");

    /* PP1 SOLUTION GOES HERE.
    *  YOU WON'T HAVE THIS UNTIL AFTER LATE WORK SUBMISSION DEADLINE
    */

        // calculate the log ratio of the stock price to the strike price
            // functions: log
        ratioStockStrike = log(currentStockPrice / strikePrice);   
    
        // calculate the expected growth rate of the stock over time
    growthRate = riskFreeInterestRate - (sigma * sigma) / 2;  
    
        // calculate the sum of the log ratio and expected growth rate
    sumRatioGrowth = ratioStockStrike + (growthRate * timeToExpire);
    
        // calculate the volatility of the stock over time
            // functions: sqrt
        overTimeVolatility = sigma * sqrt(timeToExpire);
    
        // calculate d1
        d1factor = sumRatioGrowth / overTimeVolatility;
    
        //calculate d2
            // functions: sqrt
            d2factor = d1factor - overTimeVolatility;
    
        // calculate the cummulative distribution estimation for d1
            // functions: normalCDF
    d1NormalDistr = normalCDF(d1factor);
    
        // calculate the cummulative distribution estimation for d2
            // functions: normalCDF
    d2NormalDistr = normalCDF(d2factor);
    
        // calculate the expected value of the stock if option is exercised
    expectedStockValue = currentStockPrice * exp(growthRate * timeToExpire);
    
        // calculate the value of the strike price if the option is exercised
            // functions: exp
    expectedStrikePrice = strikePrice * exp(-riskFreeInterestRate * timeToExpire);

        // calculate the premium (call option price)
    premium = expectedStockValue * d1NormalDistr - expectedStrikePrice * d2NormalDistr;


    /* PP2 BEGINS HERE.
    *  FSPP STEP 1 PROVIDE. FILL WITH STEPS 2-4.
    */

    // TODO 1: Calculate the lower and upper thresholds for interesting premiums
    double lowerThreshold = currentStockPrice * LOWER_THRESHOLD_PREMIUM;
    double upperThreshold = currentStockPrice * UPPER_THRESHOLD_PREMIUM;

    
    // TODO 2: Check the recommendation
    int recommendation;

    if (premium > lowerThreshold && premium < upperThreshold) {
        recommendation = RECOMMENDED;
    } else if (premium <= lowerThreshold) {
        recommendation = TOO_LOW_PREMIUM;
    } else {
        recommendation = TOO_HIGH_PREMIUM;
    }


    // TODO 3: show the results
        // print out the Black-Scholes Call Option Price
            // functions: printf
    printf("Black-Scholes Call Option Price: %.2lf\n\n", premium);
    
    if (recommendation == RECOMMENDED) {
        printf("The call option is potentially interesting.\n");
    } else {
        if (recommendation == TOO_LOW_PREMIUM) {
            printf("The call option is not interesting. The premium is very low, indicating lower expectations for the stock's price movement or lack of demand for the option.\n");
        } else {
            printf("The call option is not interesting. The premium is high, indicating potential risks like high volatility or uncertainty about the stock's future direction.\n");
        }
    }


    // end program
        // print out a message
            // function: printf
    printf("End program.\n\n");

        // return success
    return 0;
}

// supporting functions
/*
Name: normalCDF
Process: calculates the cumulative distribution function (CDF) of the standard
         normal distribution for a given probability.
Function input/parameters: zScore - the z-score value used in the cumulative
         distribution function calculation
Function output/parameters: none
Function output/returned: cummulativeResult - the estimated value of the
                          cummulative distribution
Dependencies: math.h - erf, sqrt
*/
double normalCDF(double zScore) {
    // declare variables
    double cummulativeResult;
    // commulative distribution calculation
        // functions: erf, sqrt
    cummulativeResult = 0.5 * (1 + erf(zScore / sqrt(2)));
    // return the cummulative distribution result
    return cummulativeResult;
}