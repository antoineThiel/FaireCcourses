# FaireCcourses
# Requires to be compile on Linux


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
sudo apt-get install libdev-gtk+3 (à vérifier)

Compile using ONLY Gtk3:
gcc `pkg-config --cflags gtk+-3.0` -o "output" "file.c" `pkg-config --libs gtk+-3.0`

Create & Compile
You can use any text editor, save your file with the .c extension

To compile, place yourself in the folder's project and use 
make gcc
