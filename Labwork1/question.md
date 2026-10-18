# CENG241 – Labwork 1

1) Write a C++ program which implements the below class inside a namespace called Math:

```
+------------------------------------+
|             Calculator             |
+------------------------------------+
| +add(int, int): int                |
| +add(double, double): double       |
| +subtract(int, int): int           |
| +subtract(double, double): double  |
| +multiply(int, int): int           |
| +multiply(double, double): double  |
| +divide (int, int): int            |
| +divide(double, double): double    |
+------------------------------------+
```

This class will let the user perform four basic arithmetic operations. Notice that each function
has two types (meaning you will perform function overloading). You also have to consider the
condition where the second parameter is 0; if that is the case, you should display an error
message "Division by zero error!" and terminate the program.

After implementing the class, create an object of type Calculator, then ask for four numeric
inputs (two integers and two doubles) and two character inputs (representing operators). Finally,
perform the desired operations on the numbers and display the results on the screen.

**Sample Run:**

```
Enter two integer numbers: 2 9
Enter two double numbers: 3.2 0.0
Enter the desired operation to perform on integer numbers: -
Enter the desired operation to perform on double numbers: /
Results of the operations:
Subtraction of 2 from 9 is: -7
Division by zero error!
```
