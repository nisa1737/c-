# CENG241 – Labwork 2

2) Write a C++ program that implements a greenhouse temperature tracking system. To be
able to achieve this task, first implement the following class:

```
+------------------------------------------+
|            GreenhouseMonitor             |
+------------------------------------------+
| - maxTempThreshold: double               |
+------------------------------------------+
| + setThreshold(double): void             |
| + checkThreshold(const double*, int): bool |
+------------------------------------------+
```

setThreshold() function will set the maxTempThreshold() to the value provided as a
parameter by the user and checkThreshold() function will print "[WARNING] At least one
sensor exceeds limit" and return True if any of the read temperature value from greenhouses
exceed the maxTempThreshold, return False otherwise.

After implementing the class, in the main function, create a GreenhouseMonitor instance,
and ask the user the maximum acceptable temperature value, and how many greenhouse
temperature values will be inputted, then dynamically create an array for recording the
related temperature for each greenhouse, then pass this array as a parameter to the
checkThreshold() function. Finally display either "[OK] All greenhouse temperatures are
within optimal range.", if none of the greenhouses' temperatures exceeds the threshold or
"[ALERT] Greenhouse climate regulation required!", if at least one of the greenhouses'
temperatures exceeds the threshold (it will be determined according to the return value of
checkThreshold() function).

Note: Do not forget to free the memory you have dynamically created.

**Sample Run:**

```
Enter the maximum acceptable temperature value: 37.5
Enter number of temperatures: 5
Enter temperature value: 1: 15.25
Enter temperature value: 2: 30.5
Enter temperature value: 3: 32.75
Enter temperature value: 4: 40.00
Enter temperature value: 5: 45.5
[WARNING] At least one sensor exceeds limit 37.5!
[ALERT] Greenhouse climate regulation required!
```
