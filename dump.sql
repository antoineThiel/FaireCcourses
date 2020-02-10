create database project;
use project;

create table customer(
    id int auto_increment primary key, 
    username varchar(40), 
    password varchar(40), 
    total_order int, 
    `status` bool
    );

insert into customer values (NULL, 'toinou', 'toinou', 0, 1);
insert into customer values (NULL, 'thomas', 'thomas', 0, 1);
insert into customer values (NULL, 'client', 'client', 0, 0);


create table store(
    id int auto_increment primary key, 
    name varchar(50)
    );

insert into store values (NULL, 'Auchan');
insert into store values (NULL, 'Lidl');
insert into store values (NULL, 'Super U');
insert into store values (NULL, 'Leclerc');

create table category(
    id int auto_increment primary key, 
    name varchar(50), 
    id_store int
    );

insert into category values ( NULL, 'viande', 1);
insert into category values ( NULL, 'fruits', 1);
insert into category values ( NULL, 'légumes', 1);
insert into category values ( NULL, 'gâteaux', 1);
insert into category values ( NULL, 'bonbons', 1);
insert into category values ( NULL, 'féculents', 1);
insert into category values ( NULL, 'produits de toilettes', 1);
insert into category values ( NULL, 'jardinage', 1);
insert into category values ( NULL, 'habits hommes', 1);
insert into category values ( NULL, 'habits femmes', 1);
insert into category values ( NULL, 'habits enfants', 1);
insert into category values ( NULL, 'congelés', 1);

create table product(
    id int auto_increment primary key, 
    name varchar(50), 
    category varchar(50), 
    price double, 
    id_store int
    );

insert into product values ( NULL, 'bavette', 'viande', 5, 1);
insert into product values ( NULL, 'pomme', 'fruits', 1, 1);
insert into product values ( NULL, 'carottes', 'légumes', 1, 1);
insert into product values ( NULL, 'prince', 'gâteaux', 2, 1);
insert into product values ( NULL, 'crocros', 'bonbons', 3, 1);
insert into product values ( NULL, 'coquillettes', 'féculents', 2 ,1);
insert into product values ( NULL, 'brosse à dents', 'produits de toilettes', 3, 1);
insert into product values ( NULL, 'pelle', 'jardinage', 10, 1);
insert into product values ( NULL, 'slip', 'habits hommes', 5, 1);
insert into product values ( NULL, 'culottes', 'habits femmes', 5, 1);
insert into product values ( NULL, 'sweat', 'habits enfants', 10, 1);
insert into product values ( NULL, 'frites', 'congelés', 7, 1);

create table `order`(
    id int auto_increment primary key, 
    id_customer int, 
    price double, 
    id_store int
    );

create table product_order(
    id_order int, 
    id_product int, 
    quantity int not null
    );

drop table shelf;
create table shelf(
    id int auto_increment primary key, 
    category int, 
    id_store int, 
    shelf_order int
);
    
INSERT INTO shelf VALUES(NULL, 1 , 1 , 1);
INSERT INTO shelf VALUES(NULL, 2 , 1 , 2);
INSERT INTO shelf VALUES(NULL, 3 , 1 , 3);
INSERT INTO shelf VALUES(NULL, 4 , 1 , 4);
INSERT INTO shelf VALUES(NULL, 5 , 1 , 5);
INSERT INTO shelf VALUES(NULL, 6 , 1 , 6);
INSERT INTO shelf VALUES(NULL, 7 , 1 , 7);
INSERT INTO shelf VALUES(NULL, 8 , 1 , 8);
INSERT INTO shelf VALUES(NULL, 9 , 1 , 9);
INSERT INTO shelf VALUES(NULL, 10, 1 , 10);
INSERT INTO shelf VALUES(NULL, 11, 1 , 11);
INSERT INTO shelf VALUES(NULL, 12, 1 , 12);

