 # Welcome to Rugby Rerformance Metric Ltd.

 ## Manual.
 1.In order to start using this application ,admin has to create a login file in the directory  as a main.c file.
 2.If a login file not created the app will terminate
 3.If a login file being created but not filled with user's details use 'rootme' as an user name  and 'rootme' as a password
 4.After the user were being verified,the user can use a menu and pick an option 
 5.The first time use of the app requires admin to fill up the database table with the data
 6.If there are some data it will be loaded into a player struct
 7.The outputs are printed to the screen in form of a table like a database table so make sure  your screen is wide enough to accomodate the width of the table
 8.Make sure you enter player position with hyphen
 9.All user inputs are validated

 ## Report.
This appliction has been created by using a single link list as a data structure.
All outputs on the screen and the report to a file are being structured as database table.
The most challenging part was to create list of the players in order of their height
For that i used sort method to get the players sorted by the height but because the origanal data
were being unsorted by IRFU number i used reverse sort to sort back to the original state once the user 
leaves the menu of that option. 