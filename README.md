# FaireCcourses
# Requires to be compile on Linux


GETTING STARTED ON A FRESH OS

Update apt:
-   sudo apt-get update
-   sudo apt-get upgrade

Get compiler:
-   sudo apt-get install gcc

Get all Needed mysql packages:
-   sudo apt-get install mysql-client
-   sudo apt-get install mysql-server
-   sudo apt-get install libmysqlclient-dev

in addition, having a BD is necessary. 
-   sudo service mysql start
make sure mysql service is on with :
-   service mysql status ("online" should be written in the last few lines)

you can use our files to create and fill the DB using :
-   mysql < "_path_to_sql_file".sql 



Get Gtk:
-   sudo apt-get install libgtk-3-dev

Create & Compile
You can use any text editor, save your file with the .c extension

To compile, place yourself in the folder's project and use 

make gcc (if wanted , you can also type "make" ,  since gcc is the only target written)

launch program with ./test  (current destination file for compilation)

WE ARE WORKING ON HOW TO COMPILE MULTIPLE FILES IN THE SAME TIME
