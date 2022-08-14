# Graphics In Matadaan
Graphics was one of the major part in our project without which there would have been a certain lack of interactive property. We implemented the graphics in "Matadaan" by using [Gtkmm](http://www.gtkmm.org/en/) library.

The graphics part of our project consists of a initial login screen. and based on the type of user logging in, there are two seperate screens that can be accessed after [login screen](#login-screen) given as: 



   1. [Voting Screen](#voting-screen)   
        1.1 Components    
        1.2 Functions
   2. [Superuser Screen](#superuser-screen)    
        2.2 Components    
        2.2 Functions


## Login Screen
The login page is the very first screen that is showed after the ececution of our program. This page allows both the admin and user to login and proceed to the next page. There are two textfields that prompt the user to enter their crediantials . Also there can be seen a button which...  The user after entering his/her login credetials can access the voting screen while the admin in the other hand can access the superuser screen. The voting screen and superscreen are individually described below:

### Voting Screen
User lands in this page after they enter their registeres citizenship number and password in the previous login screen.
```cpp
#include<iostream>
```






