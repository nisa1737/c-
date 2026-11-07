# CENG241 – Labwork 4

Write a C++ program for the inventory and weapon customization subsystem of an RPG game.
To achieve this task, firstly, implement the following class:

```
+------------------------------------------------------------------+
|                         EnchantedWeapon                          |
+------------------------------------------------------------------+
| - weaponID: int                                                  |
| - weaponName: char*                                              |
| - baseDamage: double                                             |
| - durability: double                                             |
| - loreScroll: char*                                              |
+------------------------------------------------------------------+
| + EnchantedWeapon(int, const char*, double, double, const char*) |
| + upgradeDamage(double): EnchantedWeapon&                        |
| + repairWeapon(double): EnchantedWeapon&                         |
| + infuseElement(const char*): EnchantedWeapon&                   |
| + sharpenEdge(double): EnchantedWeapon&                          |
| + displayStats(): void                                           |
| + inspectWeaponLore(const EnchantedWeapon&): void   <-- friend   |
+------------------------------------------------------------------+
```

Parameterized constructor will be used to properly initialize variables and allocate dynamic
memory for both the weapon name and lore scroll (the parameter names must be the same as
the class member variables), the destructor will release all dynamically allocated memory upon
destruction, and multiple operational methods. The upgradeDamage() function will return a
reference to the current object to enable method chaining. repairWeapon(), sharpenEdge(), and
infuseElement() functions will also utilize the this pointer to update stats, apply magical
infusions (also print with which element the weapon is enchanted), and support continuous
method chaining. Furthermore, an internal scope resolution operator will be used within the
upgradeDamage() and sharpenEdge() functions to access a global game balance constant
(named MAX_GLOBAL_DAMAGE and set to the value 200, if weapon's damage exceeds
this value while upgrading the damage or sharpening the edge display the message: "This
weapon is pretty overpowered!", and set the damage to 200). The displayStats() method will
output the weapon's current operational status while omitting the lore text, and a friend function
named inspectWeaponLore() is declared to directly access and display the private loreScroll
member to see the secret text of the weapon.

After implementing the class, in the main function, take necessary inputs from the user
(demonstrated at the sample runs) and create an EnchantedWeapon instance, then display its
initial status, then again ask for necessary inputs to perform function chaining on the object.
Finally, display the latest information of the EnchantedWeapon and its loreScroll text on the
screen.

**Sample Run 1:**

```
--- RPG Weapon Customization System ---
Enter Weapon ID: 707
Enter Weapon Name: Wuuthrad
Enter Initial Base Damage: 150
Enter Initial Durability (0-100): 78
Enter Weapon Lore Description: By Ysmir created at Sky Forge
Enter Elemental Infusion Type (e.g., Fire, Ice): Ice

--- Initial Weapon Status ---
Weapon ID: 707 | Name: Wuuthrad | Damage: 150 | Durability: 78%

Enter Damage Upgrade Amount: 15
Enter Repair Amount: 12
Enter Sharpening Bonus Amount: 7.75

Executing Method Chaining..
Weapon Wuuthrad successfully infused with Ice magic!

--- Updated Weapon Status After Chaining ---
Weapon ID: 707 | Name: Wuuthrad | Damage: 172.75 | Durability: 90%

--- Weapon Lore ---
Lore Scroll Content: By Ysmir created at Sky Forge

[Destructor Executed] Weapon ID 707 dynamic memory freed.
```

**Sample Run 2:**

```
--- RPG Weapon Customization System ---
Enter Weapon ID: 606
Enter Weapon Name: Excalibur
Enter Initial Base Damage: 175
Enter Initial Durability (0-100): 97
Enter Weapon Lore Description: Found at middle of nowhere
Enter Elemental Infusion Type (e.g., Fire, Ice): Fire

--- Initial Weapon Status ---
Weapon ID: 606 | Name: Excalibur | Damage: 175 | Durability: 97%

Enter Damage Upgrade Amount: 30
Enter Repair Amount: 5
Enter Sharpening Bonus Amount: 35

Executing Method Chaining..
"This weapon is pretty overpowered!"
"This weapon is pretty overpowered!"
Weapon Excalibur successfully infused with Fire magic!

--- Updated Weapon Status After Chaining ---
Weapon ID: 606 | Name: Excalibur | Damage: 200 | Durability: 100%

--- Weapon Lore ---
Lore Scroll Content: Found at middle of nowhere

[Destructor Executed] Weapon ID 606 dynamic memory freed.
```
