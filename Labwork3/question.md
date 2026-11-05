# CENG241 – Labwork 3

Write a C++ program to develop a compact configuration module for a hardware diagnostic
tool. To achieve this task, firstly implement the following class:

```
+------------------------------------------------+
|                 DeviceMonitor                  |
+------------------------------------------------+
| - deviceID: int                                |
| - operationalStatus: int                       |
| - deviceName[]: char                           |
+------------------------------------------------+
| + DeviceMonitor(int, int, const char*)         |
| + setOperationalStatus(int): DeviceMonitor&    |
| + setDeviceName(const char*): DeviceMonitor&   |
| + displayInfo(): void                          |
+------------------------------------------------+
```

deviceName[] is a character array with a fixed size of 30, DeviceMonitor(int, int, const char*)
is the overloaded constructor to set the respective fields of the DeviceMonitor instance (you
have to set each parameter name the same as the member variable of the class, so you have to
use **this pointer** to set each parameter to the related variable) it also calls a global function
called registerDevice(DeviceMonitor*), which displays the memory address of the provided
variable with the format provided in the sample run, setOperationalStatus(int), and
setDeviceName(const char*) functions should be written in a way that they can be called with
an instance via chaining.

After implementing the class, in the main function, ask the user to input two deviceIDs,
operationalStatus, and deviceNames. Then create two DeviceMonitor instances with these
parameters, after creating the instances, display them. Finally, ask the user to input new
operationalStatus and deviceName to change both the operationalStatus and deviceName of
one instance via function chaining and display the last form of that instance after the operation.

**Sample Run:**

```
Enter first deviceID: 501
Enter second deviceID: 502
Enter first deviceName: Alpha-Node
Enter second deviceName: Beta-Node
Enter first deviceStatus: 80
Enter second deviceStatus: 45

[Registry System] Device pointer registered at address: 0x5ffe20
[Registry System] Device pointer registered at address: 0x5ffdf0

--- Initial States ---
Device ID : 501
Name      : Alpha-Node
Status    : 80

Device ID : 502
Name      : Beta-Node
Status    : 45

Enter new deviceName for first instance: Alpha-Node-Master
Enter new deviceStatus for first instance: 99

--- State After Method Chaining ---
Device ID : 501
Name      : Alpha-Node-Master
Status    : 99
```
