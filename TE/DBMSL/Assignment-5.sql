-- Student Classification Based on Marks

mysql> create table stud_marks (name varchar(20), marks int);
Query OK, 0 rows affected (0.05 sec)

mysql> desc stud_marks;
+-------+-------------+------+-----+---------+-------+
| Field | Type        | Null | Key | Default | Extra |
+-------+-------------+------+-----+---------+-------+
| name  | varchar(20) | YES  |     | NULL    |       |
| marks | int(11)     | YES  |     | NULL    |       |
+-------+-------------+------+-----+---------+-------+
2 rows in set (0.00 sec)

mysql> create table result (roll int, name varchar(20), class varchar(20));
Query OK, 0 rows affected (0.04 sec)

mysql> desc result;
+-------+-------------+------+-----+---------+-------+
| Field | Type        | Null | Key | Default | Extra |
+-------+-------------+------+-----+---------+-------+
| roll  | int(11)     | YES  |     | NULL    |       |
| name  | varchar(20) | YES  |     | NULL    |       |
| class | varchar(20) | YES  |     | NULL    |       |
+-------+-------------+------+-----+---------+-------+
3 rows in set (0.00 sec)

mysql> insert into stud_marks values ('John', 820);
Query OK, 1 row affected (0.01 sec)

mysql> insert into stud_marks values ('Alice', 860);
Query OK, 1 row affected (0.12 sec)

mysql> insert into stud_marks values ('Tia', 999);
Query OK, 1 row affected (0.14 sec)

mysql> insert into stud_marks values ('Kyle', 1340);
Query OK, 1 row affected (0.01 sec)

mysql> insert into stud_marks values ('Diana', 1100);
Query OK, 1 row affected (0.02 sec)

mysql> insert into stud_marks values ('Steve', 950);
Query OK, 1 row affected (0.01 sec)

mysql> insert into stud_marks values ('Olive', 917);
Query OK, 1 row affected (0.01 sec)

mysql> insert into stud_marks values ('Aiden', 1490);
Query OK, 1 row affected (0.14 sec)

mysql> select* from stud_marks;
+-------+-------+
| name  | marks |
+-------+-------+
| John  |   820 |
| Alice |   860 |
| Tia   |   999 |
| Kyle  |  1340 |
| Diana |  1100 |
| Steve |   950 |
| Olive |   917 |
| Aiden |  1490 |
+-------+-------+
8 rows in set (0.01 sec)


mysql> delimiter //
mysql> create procedure classify(in vroll int, in vname varchar(20), in vmarks int)
    -> begin
    -> declare vclass varchar(20);
    -> declare sigstate condition for sqlstate '45000';
    -> if vmarks>=990 and vmarks<=1500 then
    -> set vclass = 'Distinction';
    -> elseif vmarks>=900 and vmarks<=989 then
    -> set vclass = 'First Class';
    -> elseif vmarks>=825 and vmarks<=899 then
    -> set vclass = 'Second Class';
    -> elseif vmarks>=0 and vmarks<=824 then
    -> set vclass = '-';
    -> else 
    -> signal sigstate
    -> set message_text = 'INVALID MARKS!';
    -> end if;
    -> insert into result values (vroll, vname, vclass);
    -> select* from result where roll=vroll;
    -> end;
    -> //
Query OK, 0 rows affected (0.00 sec)


mysql> delimiter ;


mysql> select* from result;
Empty set (0.00 sec)


mysql> call classify(1, 'John', 820);
+------+------+-------+
| roll | name | class |
+------+------+-------+
|    1 | John | -     |
+------+------+-------+
1 row in set (0.02 sec)

Query OK, 0 rows affected (0.02 sec)


mysql> call classify(2, 'Alice', 860);
+------+-------+--------------+
| roll | name  | class        |
+------+-------+--------------+
|    2 | Alice | Second Class |
+------+-------+--------------+
1 row in set (0.01 sec)

Query OK, 0 rows affected (0.01 sec)


mysql> call classify(3, 'Steve', 950);
+------+-------+-------------+
| roll | name  | class       |
+------+-------+-------------+
|    3 | Steve | First Class |
+------+-------+-------------+
1 row in set (0.02 sec)

Query OK, 0 rows affected (0.02 sec)


mysql> call classify(4, 'Kyle', 1340);
+------+------+-------------+
| roll | name | class       |
+------+------+-------------+
|    4 | Kyle | Distinction |
+------+------+-------------+
1 row in set (0.02 sec)

Query OK, 0 rows affected (0.02 sec)


mysql> select * from result;
+------+-------+--------------+
| roll | name  | class        |
+------+-------+--------------+
|    1 | John  | -            |
|    2 | Alice | Second Class |
|    3 | Steve | First Class  |
|    4 | Kyle  | Distinction  |
+------+-------+--------------+
4 rows in set (0.00 sec)


-- Error Handling
mysql> call classify (10, 'hello', -40);
ERROR 1644 (45000): INVALID MARKS!
