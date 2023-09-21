-- Trigger to keep track of update and delete records on Library tablename and store old records in Library_audit


mysql> create table library (bookid int, bname varchar(50), author varchar(50), price decimal(7,2));
Query OK, 0 rows affected (0.06 sec)


mysql> insert into library values (101, 'The Great Gatsby', 'F.S. Fitzgerald', 12.99);
Query OK, 1 row affected (0.02 sec)


mysql> insert into library values (102, 'To Kill A Mockingbird', 'Harper
Lee'
Query OK, 1 row affected (0.00 sec)


mysql> insert into library values (103, '1984', 'George Orwell', 9.99);
Query OK, 1 row affected (0.02 sec)


mysql> insert into library values (104, 'Pride & Prejudice', 'Jane Austen', 11.
Query OK, 1 row affected (0.02 sec)


mysql> insert into library values (105, 'The Catcher In The Rye', 'J.D. Salinger', 8.75);
Query OK, 1 row affected (0.01 sec)


mysql> insert into library values (106, 'The Hobbit', 'J.R.R. Tolkien', 14.99);
Query OK, 1 row affected (0.01 sec)


mysql> insert into library values (107, 'A Thousand Splendid Suns', 'Khaled Houssini', 15.79);
Query OK, 1 row affected (0.02 sec)


mysql> insert into library values (108, 'Harry Potter', 'J.K. Rowling', 15.99);
Query OK, 1 row affected (0.02 sec)


mysql> alter table library modify column bookid int primary key;
Query OK, 8 rows affected (0.11 sec)
Records: 8  Duplicates: 0  Warnings: 0


mysql> select* from library;
+--------+--------------------------+-----------------+-------+
| bookid | bname                    | author          | price |
+--------+--------------------------+-----------------+-------+
|    101 | The Great Gatsby         | F.S. Fitzgerald | 12.99 |
|    102 | To Kill A Mockingbird    | Harper Lee      | 10.49 |
|    103 | 1984                     | George Orwell   |  9.99 |
|    104 | Pride & Prejudice        | Jane Austen     | 11.25 |
|    105 | The Catcher In The Rye   | J.D. Salinger   |  8.75 |
|    106 | The Hobbit               | J.R.R. Tolkien  | 14.99 |
|    107 | A Thousand Splendid Suns | Khaled Houssini | 13.50 |
|    108 | Harry Potter             | J.K. Rowling    | 15.79 |
+--------+--------------------------+-----------------+-------+
8 rows in set (0.00 sec)


mysql> select* from library_audit;
Empty set (0.00 sec)


mysql> delimiter //
mysql> create trigger lib_update
    -> after update on library
    -> for each row
    -> begin
    -> insert into library_audit values (old.bookid, old.bname, old.author, old.price, 'Update');
    -> end;
    -> //
Query OK, 0 rows affected (0.07 sec)


mysql> delimiter //
mysql> create trigger lib_delete
    -> before delete on library
    -> for each row
    -> begin
    -> insert into library_audit values (old.bookid, old.bname, old.author, old.price, 'Delete');
    -> end;
    -> //
Query OK, 0 rows affected (0.06 sec)


mysql> delimiter ;


mysql> select* from library;
+--------+--------------------------+-----------------+-------+
| bookid | bname                    | author          | price |
+--------+--------------------------+-----------------+-------+
|    101 | The Great Gatsby         | F.S. Fitzgerald | 12.99 |
|    102 | To Kill A Mockingbird    | Harper Lee      | 10.49 |
|    103 | 1984                     | George Orwell   |  9.99 |
|    104 | Pride & Prejudice        | Jane Austen     | 11.25 |
|    105 | The Catcher In The Rye   | J.D. Salinger   |  8.75 |
|    106 | The Hobbit               | J.R.R. Tolkien  | 14.99 |
|    107 | A Thousand Splendid Suns | Khaled Houssini | 13.50 |
|    108 | Harry Potter             | J.K. Rowling    | 15.79 |
+--------+--------------------------+-----------------+-------+
8 rows in set (0.00 sec)


mysql> update library set bname='The Kite Runner' where bookid=107;
Query OK, 1 row affected (0.01 sec)
Rows matched: 1  Changed: 1  Warnings: 0


mysql> select * from library_audit;
+--------+--------------------------+-----------------+-------+--------+
| bookid | bname                    | author          | price | action |
+--------+--------------------------+-----------------+-------+--------+
|    107 | A Thousand Splendid Suns | Khaled Houssini | 13.50 | Update |
+--------+--------------------------+-----------------+-------+--------+
1 row in set (0.00 sec)


mysql> select* from library;
+--------+------------------------+-----------------+-------+
| bookid | bname                  | author          | price |
+--------+------------------------+-----------------+-------+
|    101 | The Great Gatsby       | F.S. Fitzgerald | 12.99 |
|    102 | To Kill A Mockingbird  | Harper Lee      | 10.49 |
|    103 | 1984                   | George Orwell   |  9.99 |
|    104 | Pride & Prejudice      | Jane Austen     | 11.25 |
|    105 | The Catcher In The Rye | J.D. Salinger   |  8.75 |
|    106 | The Hobbit             | J.R.R. Tolkien  | 14.99 |
|    107 | The Kite Runner        | Khaled Houssini | 13.50 |
|    108 | Harry Potter           | J.K. Rowling    | 15.79 |
+--------+------------------------+-----------------+-------+
8 rows in set (0.00 sec)


mysql> delete from library where bookid=108;
Query OK, 1 row affected (0.83 sec)


mysql> select * from library_audit;
+--------+--------------------------+-----------------+-------+--------+
| bookid | bname                    | author          | price | action |
+--------+--------------------------+-----------------+-------+--------+
|    107 | A Thousand Splendid Suns | Khaled Houssini | 13.50 | Update |
|    108 | Harry Potter             | J.K. Rowling    | 15.79 | Delete |
+--------+--------------------------+-----------------+-------+--------+
2 rows in set (0.00 sec)


mysql> select* from library;
+--------+------------------------+-----------------+-------+
| bookid | bname                  | author          | price |
+--------+------------------------+-----------------+-------+
|    101 | The Great Gatsby       | F.S. Fitzgerald | 12.99 |
|    102 | To Kill A Mockingbird  | Harper Lee      | 10.49 |
|    103 | 1984                   | George Orwell   |  9.99 |
|    104 | Pride & Prejudice      | Jane Austen     | 11.25 |
|    105 | The Catcher In The Rye | J.D. Salinger   |  8.75 |
|    106 | The Hobbit             | J.R.R. Tolkien  | 14.99 |
|    107 | The Kite Runner        | Khaled Houssini | 13.50 |
+--------+------------------------+-----------------+-------+
7 rows in set (0.00 sec)
