# CENG241 – Labwork 1

2) Write a C++ program that implements the following structure, for the purpose of developing
a telemetry logging system:

```
+-----------------------------------+
|            <<struct>>             |
|        TelemetryProcessor         |
+-----------------------------------+
| +calibrationFactor: T             |
+-----------------------------------+
| +testPassByValue(T): void         |
| +testPassByReference(T&): void    |
+-----------------------------------+
```

`testPassByValue()` function will take a T type variable and will multiply the value given as
a parameter with the `calibrationFactor` (recognize pass-by-value behavior),
`testPassByReference()` function will also take a T type variable and perform the same
operation (however, this time as pass-by-reference also recognize this behavior).

In the main function, create a `TelemetryProcessor` instance and ask the user to input a
`calibrationFactor`, after taking the `calibrationFactor` as input, ask the user to input a
`userReading` (will be used to send as parameter to the functions), then send this value to
first `testPassByValue()` function then to `testPassByReference()` function and print the value
of `userReading` after each operation.

**Sample Run:**

```
Enter the calibration factor: 2.7
Enter a raw sensor reading value (e.g., 25.5): 20

Before pass-by-value function, userReading = 20
[Inside testPassByValue] Modified copy inside function: 54
After pass-by-value function, userReading = 20 (Unchanged!)

Before pass-by-reference function, userReading = 20
[Inside testPassByReference] Modified original via reference: 54
After pass-by-reference function, userReading = 54 (Changed & Persisted!)
```
