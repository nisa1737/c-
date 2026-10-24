# CENG241 – Labwork 2

1) Write a C++ program to design a financial asset tracking module for a wealth management
application. To be able to achieve this task, first implement the following class:

```
+-----------------------------------+
|             Portfolio             |
+-----------------------------------+
| - capacity: int                   |
| - assetPrices: double*            |
+-----------------------------------+
| + initialize(int): void           |
| + cleanup(): void                 |
| + calculateTotalValue(): double   |
| + exceedsRiskLimit(double): bool  |
| + displayPortfolio(): void        |
+-----------------------------------+
```

initialize() function will dynamically allocate memory for x assets (x will be provided as a
parameter by the user) and let the user x many asset values into the assetPrices dynamic
array, cleanup() function will free the memory located by the initialize() function at the end
of the program, calculateTotalValue() function will return the total of the assetPrices,
exceedsRiskLimit() will return True if the value provided by the user (drawdown value) as
a parameter is greater than the globally declared GLOBAL_MARKET_RISK_THRESHOLD value
(set it to 0.05), False otherwise, and displayPortfolio() function will display the portfolio
information.

After implementing the class, in the main function, ask the user how many assetPrices
would like to be entered, then create a Portfolio class instance and initialize it with the
number of assetPrices, then ask the user their observed drawdown percentage and compare
it with the GLOBAL_MARKET_RISK_THRESHOLD value by calling exceedsRiskLimit() function,
then according to the return value if it is True, print that the observed drawdown is greater
than GLOBAL_MARKET_RISK_THRESHOLD value (to do this you have to use unary scope
resolution operator), if it is False, print "Portfolio risk is within acceptable parameters.".
Finally call the displayPortfolio() function to display the assets. (Do not forget to call the
cleanup() function at the end of the program).

**Sample Run:**

```
Enter how many assets you would like to enter: 4
Enter Asset Price 1: 1250.50
Enter Asset Price 2: 430.25
Enter Asset Price 3: 2100.00
Enter Asset Price 4: 850.75
Enter the drawdown you have observed so far: 0.065
[WARNING] Portfolio drawdown exceeds global risk limit (5%)!
Assets Tracked: 4/4
Prices: $1250.50 $430.25 $2100.00 $850.75
Total Portfolio Value: $4631.50
[INFO] Released portfolio dynamic memory.
```
