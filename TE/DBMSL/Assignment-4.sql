-- AREA OF A CIRCLE

mysql> delimiter //
mysql> create procedure circle (r int)
    -> begin
    -> declare msg1 varchar(30);
    -> declare msg2 varchar(30);
    -> declare ar decimal(7,2);
    -> set msg1 = "area = ";
    -> set msg2 = "radius out of range";
    -> if r>=5 and r<=9 then
    -> set ar = 3.14*r*r;
    -> insert into areas values (r, ar);
    -> select concat(msg1, ar) as result;
    -> else
    -> select msg2;
    -> end if;
    -> end;
    -> //
Query OK, 0 rows affected (0.00 sec)


mysql> delimiter ;


mysql> call circle(4);
+---------------------+
| msg2                |
+---------------------+
| radius out of range |
+---------------------+
1 row in set (0.00 sec)
Query OK, 0 rows affected (0.00 sec)


mysql> call circle(6);
+---------------+
| result        |
+---------------+
| area = 113.04 |
+---------------+
1 row in set (0.03 sec)
Query OK, 0 rows affected (0.03 sec)


mysql> call circle(9);
+---------------+
| result        |
+---------------+
| area = 254.34 |
+---------------+
1 row in set (0.01 sec)
Query OK, 0 rows affected (0.01 sec)

mysql> select* from areas;
+--------+--------+
| radius | area   |
+--------+--------+
|      9 | 254.34 |
+--------+--------+
1 row in set (0.01 sec)


mysql> call circle(3);
+---------------------+
| msg2                |
+---------------------+
| radius out of range |
+---------------------+
1 row in set (0.00 sec)
Query OK, 0 rows affected (0.01 sec)


mysql> select* from areas;
+--------+--------+
| radius | area   |
+--------+--------+
|      9 | 254.34 |
+--------+--------+
1 row in set (0.00 sec)

----------------------------------------------------------------------------------------------------------------

--LIBRARY FINE CALCULATION

mysql> delimiter //
mysql> create procedure calculate(in roll int)
    -> begin
    -> declare ndays int;
    -> declare idate date;
    -> declare finetopay decimal(7,2);
    -> select issuedate into idate from borrower where rollno=roll;
    -> set ndays = datediff(curdate(), idate);
    -> if (ndays>=15 and ndays<=30) then
    -> set finetopay = ndays*5;
    -> insert into fine values (roll, curdate(), finetopay);
    -> update borrower set status='R' where rollno=roll;
    -> elseif (ndays>30) then
    -> set finetopay = (ndays-30)*50;
    -> insert into fine values (roll, curdate(), finetopay+150);
    -> update borrower set status='R' where rollno=roll;
    -> else
    -> select 'no fine to pay!' as message;
    -> end if;
    -> select * from fine;
    -> select * from borrower;
    -> end;
    -> //
Query OK, 0 rows affected (0.00 sec)

mysql> delimiter ;
mysql> call calculate(101);
+--------+------------+--------+
| rollno | date       | amount |
+--------+------------+--------+
|    101 | 2023-08-22 | 105.00 |
+--------+------------+--------+
1 row in set (0.03 sec)

+--------+---------+------------+----------------------+--------+
| rollno | name    | issuedate  | bookname             | status |
+--------+---------+------------+----------------------+--------+
|    101 | John    | 2023-08-01 | Intro to SQL         | R      |
|    102 | Jane    | 2023-08-05 | Data Analysis        | I      |
|    103 | Michael | 2023-07-25 | Programming In Java  | R      |
|    104 | Emily   | 2023-08-10 | Python For Beginners | I      |
|    105 | Daniel  | 2023-07-15 | Database Design      | R      |
|    106 | Sophia  | 2023-08-02 | Web Dev Basics       | I      |
|    107 | William | 2023-08-08 | Computer Networks    | I      |
|    108 | Olivia  | 2023-08-12 | Machine Learning     | R      |
|    109 | Rachel  | 2023-07-20 | Statistics & Numbers | I      |
|    110 | Emma    | 2023-08-06 | Cloud Computing      | R      |
+--------+---------+------------+----------------------+--------+
10 rows in set (0.03 sec)

Query OK, 0 rows affected (0.03 sec)

mysql> call calculate(105);
+--------+------------+--------+
| rollno | date       | amount |
+--------+------------+--------+
|    101 | 2023-08-22 | 105.00 |
|    105 | 2023-08-22 | 550.00 |
+--------+------------+--------+
2 rows in set (0.02 sec)

+--------+---------+------------+----------------------+--------+
| rollno | name    | issuedate  | bookname             | status |
+--------+---------+------------+----------------------+--------+
|    101 | John    | 2023-08-01 | Intro to SQL         | R      |
|    102 | Jane    | 2023-08-05 | Data Analysis        | I      |
|    103 | Michael | 2023-07-25 | Programming In Java  | R      |
|    104 | Emily   | 2023-08-10 | Python For Beginners | I      |
|    105 | Daniel  | 2023-07-15 | Database Design      | R      |
|    106 | Sophia  | 2023-08-02 | Web Dev Basics       | I      |
|    107 | William | 2023-08-08 | Computer Networks    | I      |
|    108 | Olivia  | 2023-08-12 | Machine Learning     | R      |
|    109 | Rachel  | 2023-07-20 | Statistics & Numbers | I      |
|    110 | Emma    | 2023-08-06 | Cloud Computing      | R      |
+--------+---------+------------+----------------------+--------+
10 rows in set (0.02 sec)

Query OK, 0 rows affected (0.02 sec)

mysql> call calculate(108);
+-----------------+
| message         |
+-----------------+
| no fine to pay! |
+-----------------+
1 row in set (0.00 sec)

+--------+------------+--------+
| rollno | date       | amount |
+--------+------------+--------+
|    101 | 2023-08-22 | 105.00 |
|    105 | 2023-08-22 | 550.00 |
+--------+------------+--------+
2 rows in set (0.00 sec)

+--------+---------+------------+----------------------+--------+
| rollno | name    | issuedate  | bookname             | status |
+--------+---------+------------+----------------------+--------+
|    101 | John    | 2023-08-01 | Intro to SQL         | R      |
|    102 | Jane    | 2023-08-05 | Data Analysis        | I      |
|    103 | Michael | 2023-07-25 | Programming In Java  | R      |
|    104 | Emily   | 2023-08-10 | Python For Beginners | I      |
|    105 | Daniel  | 2023-07-15 | Database Design      | R      |
|    106 | Sophia  | 2023-08-02 | Web Dev Basics       | I      |
|    107 | William | 2023-08-08 | Computer Networks    | I      |
|    108 | Olivia  | 2023-08-12 | Machine Learning     | R      |
|    109 | Rachel  | 2023-07-20 | Statistics & Numbers | I      |
|    110 | Emma    | 2023-08-06 | Cloud Computing      | R      |
+--------+---------+------------+----------------------+--------+
10 rows in set (0.00 sec)

Query OK, 0 rows affected (0.00 sec)
