# FaireCcourses
# Requires to be compile on Linux or WSL


GETTING STARTED ON A FRESH OS

Update apt:
sudo apt-get update
sudo apt-get upgrade

Get compiler:
sudo apt-get install gcc

Get all Needed mysql packages:
sudo apt-get install mysql-client
sudo apt-get install mysql-server
sudo apt-get install libmysqlclient-dev

Get Gtk:

Create & Compile
You can use any text editor, save your file with the .c extension

To compile use this : 
  gcc "file.c" -o "output"

To compile with Mysql :
  gcc "file.c" -o "output" -I/usr/include/mysql -lmysqlclient -L/usr/lib/x86_64-linux-gnu

Authors : Thomas Tresgots / Antoine Thiel
