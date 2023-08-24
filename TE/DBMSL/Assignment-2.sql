mysql> create table department (dept_id int(5) primary key, dept_name varchar(20), dept_location varchar(20));
Query OK, 0 rows affected (0.04 sec)

    
mysql> desc department;
+---------------+-------------+------+-----+---------+-------+
| Field         | Type        | Null | Key | Default | Extra |
+---------------+-------------+------+-----+---------+-------+
| dept_id       | int(5)      | NO   | PRI | NULL    |       |
| dept_name     | varchar(20) | YES  |     | NULL    |       |
| dept_location | varchar(20) | YES  |     | NULL    |       |
+---------------+-------------+------+-----+---------+-------+
3 rows in set (0.01 sec)

    
mysql> insert into department values (110, "Sales", "Pune");
Query OK, 1 row affected (0.04 sec)

mysql> insert into department values (111, "Marketing", "Mumbai");
Query OK, 1 row affected (0.02 sec)

mysql> insert into department values (112, "Computer", "Bangalore");
Query OK, 1 row affected (0.01 sec)

mysql> insert into department values (113, "IT", "Chennai");
Query OK, 1 row affected (0.01 sec)

mysql> insert into department values (114, "Human Resources", "Delhi");
Query OK, 1 row affected (0.02 sec)

    
mysql> select* from department;
+---------+-----------------+---------------+
| dept_id | dept_name       | dept_location |
+---------+-----------------+---------------+
|     110 | Sales           | Pune          |
|     111 | Marketing         | Mumbai        |
|     112 | Computer      | Bangalore     |
|     113 | IT      | Chennai       |
|     114 | Human Resources | Delhi         |
+---------+-----------------+---------------+
5 rows in set (0.00 sec)

    
mysql> create table employee (emp_id int(5) primary key, dept_id int(5), emp_fname varchar(20), emp_lname varchar(20), emp_position varchar(20), emp_salary decimal(10,2), emp_joindate date, foreign key (dept_id) references department(dept_id));
Query OK, 0 rows affected (0.04 sec)

    
mysql> desc employee;
+--------------+---------------+------+-----+---------+-------+
| Field        | Type          | Null | Key | Default | Extra |
+--------------+---------------+------+-----+---------+-------+
| emp_id       | int(5)        | NO   | PRI | NULL    |       |
| dept_id      | int(5)        | YES  | MUL | NULL    |       |
| emp_fname    | varchar(20)   | YES  |     | NULL    |       |
| emp_lname    | varchar(20)   | YES  |     | NULL    |       |
| emp_position | varchar(20)   | YES  |     | NULL    |       |
| emp_salary   | decimal(10,2) | YES  |     | NULL    |       |
| emp_joindate | date          | YES  |     | NULL    |       |
+--------------+---------------+------+-----+---------+-------+
7 rows in set (0.00 sec)

    
mysql> insert into employee values (4001, 113, "John", "Doe", "Manager", 75000, "2022-01-15");
Query OK, 1 row affected (0.02 sec)

mysql> insert into employee values (4002, 112, "Peyton", "Smith", "Engineer", 60000, "2021-09-10");
Query OK, 1 row affected (0.02 sec)

mysql> insert into employee values (4003, 111, "Michael", "Johnson", "Accountant", 50000,
Query OK, 1 row affected (0.01 sec)

mysql> insert into employee values (4004, 114, "Sarah", "Wilson", "Administrator", 48000, "2021-11-05");
Query OK, 1 row affected (0.03 sec)

mysql> insert into employee values (4005, 112, "Emily", "Brown", "Programmer", 55000, "2023-03-20");
Query OK, 1 row affected (0.01 sec)

mysql> insert into employee values (4006, 110, "Robert", "Rodriguez", "Salesperson", 42000, "2022-12-09");
Query OK, 1 row affected (0.02 sec)

mysql> insert into employee values (4007, 114, "David", "Garcia", "Coordinator", 52000, "2023-01-02");
Query OK, 1 row affected (0.01 sec)

mysql> insert into employee values (4008, 111, "Jennifer", "Thomas", "Analyst", 48000, "2023-06-30");
Query OK, 1 row affected (0.01 sec)

mysql> insert into employee values (4009, 114, "Laura", "Martinez", "Assistant Manager", 51000, "2022-06-18");
Query OK, 1 row affected (0.01 sec)

mysql> insert into employee values (4010, 110, "James", "Lee", "Salesperson
", 55000, “2023-03-20”);
Query OK, 1 row affected (0.01 sec)

    
mysql> select* from employee;
+--------+---------+-----------+-----------+-------------------+------------+--------------+
| emp_id | dept_id | emp_fname | emp_lname | emp_position      | emp_salary | emp_joindate |
+--------+---------+-----------+-----------+-------------------+------------+--------------+
|    4001 |     113 | John      | Doe       | Manager           |   75000.00 | 2022-01-15   |
|    4002 |     112 | Peyton      | Smith     | Engineer          |   60000.00 | 2021-09-10   |
|    4003 |     111 | Michael   | Johnson   | Accountant        |   50000.00 | 2021-02-28   |
|    4004 |     114 | Sarah     | Wilson    | Administrator     |   48000.00 | 2021-11-05   |
|    4005 |     112 | Emily     | Brown     | Programmer        |   55000.00 | 2023-03-20   |
|    4006 |     110 | Robert    | Rodriguez | Salesperson       |   42000.00 | 2022-12-09   |
|    4007 |     114 | David     | Garcia    | Coordinator       |   52000.00 | 2023-01-02   |
|    4008 |     111 | Jennifer  | Thomas    | Analyst           |   48000.00 | 2023-06-30   |
|    4009 |     114 | Laura     | Martinez  | Technician       |   51000.00 | 2022-06-18   |
|    4010 |     110 | James     | Lee       | Salesperson       |   55000.00 | 2023-03-20   |
+--------+---------+-----------+-----------+-------------------+------------+--------------+
10 rows in set (0.01 sec)

    
mysql> create table project (proj_id int(5) primary key, dept_id int(5), proj_name varchar(20), proj_location varchar(20), proj_cost decimal(10,2), proj_year year), foreign key(dept_id) references department(dept_id);
Query OK, 0 rows affected (0.05 sec)

    
mysql> desc project;
+---------------+---------------+------+-----+---------+-------+
| Field         | Type          | Null | Key | Default | Extra |
+---------------+---------------+------+-----+---------+-------+
| proj_id       | int(5)        | NO   | PRI | NULL    |       |
| dept_id       | int(5)        | YES  | MUL | NULL    |       |
| proj_name     | varchar(20)   | YES  |     | NULL    |       |
| proj_location | varchar(20)   | YES  |     | NULL    |       |
| proj_cost     | decimal(10,2) | YES  |     | NULL    |       |
| proj_year     | year(4)       | YES  |     | NULL    |       |
+---------------+---------------+------+-----+---------+-------+
6 rows in set (0.00 sec)

    
mysql> insert into project values (501, 110, "ProductX Launch", "Pune", 250000, 2022); 
Query OK, 1 row affected (0.04 sec)

mysql> insert into project values (502, 111, "Data Analysis", "Mumbai", 100000, 2023);

Query OK, 1 row affected (0.02 sec)

mysql> insert into project values (503, 112, "App Development", "Bangalore", 500000, 2021);
Query OK, 1 row affected (0.01 sec)

mysql> insert into project values (504, 113, "Website Redesign", "Chennai", 350000, 2023);
Query OK, 1 row affected (0.02 sec)

mysql> insert into project values (505, 112, "Software Upgrade", "Bangalore", 220000,
2022);
Query OK, 1 row affected (0.01 sec)

mysql> insert into project values (506, 110, "Brand Event", "Pune", 180000, 2023);
Query OK, 1 row affected (0.01 sec)

mysql> insert into project values (507, 114, "Employee Welfare", "Delhi", 400000, 2022);
Query OK, 1 row affected (0.01 sec)

    
mysql> select* from project;
+---------+---------+------------------+---------------+-----------+-----------+
| proj_id | dept_id | proj_name        | proj_location | proj_cost | proj_year |
+---------+---------+------------------+---------------+-----------+-----------+
|     501 |     110 | ProductX Launch  | Pune          | 250000.00 |      2022 |
|     502 |     111 | Data Analysis    | Mumbai        | 100000.00 |      2023 |
|     503 |     112 | App Development  | Bangalore     | 500000.00 |      2021 |
|     504 |     113 | Website Redesign | Chennai       | 350000.00 |      2023 |
|     505 |     112 | Software Upgrade | Bangalore     | 220000.00 |      2022 |
|     506 |     110 | Brand Event      | Pune          | 180000.00 |      2023 |
|     507 |     114 | Employee Welfare | Delhi         | 400000.00 |      2022 |
+---------+---------+------------------+---------------+-----------+-----------+
7 rows in set (0.00 sec)

    
mysql> select* from department;
+---------+-----------------+---------------+
| dept_id | dept_name       | dept_location |
+---------+-----------------+---------------+
|     110 | Sales           | Pune          |
|     111 | Finance         | Mumbai        |
|     112 | Computer        | Bangalore     |
|     113 | IT              | Chennai       |
|     114 | Human Resources | Delhi         |
+---------+-----------------+---------------+
5 rows in set (0.00 sec)

    
mysql> select* from employee;
+--------+---------+-----------+-----------+---------------+------------+--------------+
| emp_id | dept_id | emp_fname | emp_lname | emp_position  | emp_salary | emp_joindate |
+--------+---------+-----------+-----------+---------------+------------+--------------+
|      1 |     113 | John      | Doe       | Manager       |   75000.00 | 2022-01-15   |
|      2 |     112 | Jane      | Smith     | Engineer      |   60000.00 | 2021-09-10   |
|      3 |     111 | Michael   | Johnson   | Accountant    |   50000.00 | 2021-02-28   |
|      4 |     114 | Sarah     | Wilson    | Administrator |   48000.00 | 2021-11-05   |
|      5 |     112 | Emily     | Brown     | Programmer    |   55000.00 | 2023-03-20   |
|      6 |     110 | Robert    | Rodriguez | Salesperson   |   42000.00 | 2022-12-09   |
|      7 |     114 | David     | Garcia    | Coordinator   |   52000.00 | 2023-01-02   |
|      8 |     111 | Jennifer  | Thomas    | Analyst       |   48000.00 | 2023-06-30   |
|      9 |     113 | Laura     | Martinez  | Technician    |   51000.00 | 2022-06-18   |
|     10 |     110 | James     | Lee       | Salesperson   |   55000.00 | 2023-03-20   |
+--------+---------+-----------+-----------+---------------+------------+--------------+
10 rows in set (0.00 sec)

    
mysql> SELECT e.* 
    -> FROM employee e 
    -> JOIN department d ON e.dept_id = d.dept_id 
    -> WHERE d.dept_name IN ("Computer", "IT") 
    -> AND (e.emp_fname LIKE "P%" OR e.emp_fname LIKE "H%");
+--------+---------+-----------+-----------+--------------+------------+--------------+
| emp_id | dept_id | emp_fname | emp_lname | emp_position | emp_salary | emp_joindate |
+--------+---------+-----------+-----------+--------------+------------+--------------+
|      2 |     112 | Peyton    | Smith     | Engineer     |   60000.00 | 2021-09-10   |
+--------+---------+-----------+-----------+--------------+------------+--------------+
1 row in set (0.00 sec)

    
mysql> SELECT DISTINCT emp_position FROM employee;
+---------------+
| emp_position  |
+---------------+
| Manager       |
| Engineer      |
| Accountant    |
| Administrator |
| Programmer    |
| Salesperson   |
| Coordinator   |
| Analyst       |
| Technician    |
+---------------+
9 rows in set (0.00 sec)

    
mysql> UPDATE employee 
    -> SET emp_salary = emp_salary*1.1 
    -> WHERE YEAR(emp_joindate) < 2022;
Query OK, 3 rows affected (0.01 sec)
Rows matched: 3  Changed: 3  Warnings: 0

    
mysql> select* from employee;
+--------+---------+-----------+-----------+---------------+------------+--------------+
| emp_id | dept_id | emp_fname | emp_lname | emp_position  | emp_salary | emp_joindate |
+--------+---------+-----------+-----------+---------------+------------+--------------+
|      1 |     113 | John      | Doe       | Manager       |   75000.00 | 2022-01-15   |
|      2 |     112 | Peyton    | Smith     | Engineer      |   66000.00 | 2021-09-10   |
|      3 |     111 | Michael   | Johnson   | Accountant    |   55000.00 | 2021-02-28   |
|      4 |     114 | Sarah     | Wilson    | Administrator |   52800.00 | 2021-11-05   |
|      5 |     112 | Emily     | Brown     | Programmer    |   55000.00 | 2023-03-20   |
|      6 |     110 | Robert    | Rodriguez | Salesperson   |   42000.00 | 2022-12-09   |
|      7 |     114 | David     | Garcia    | Coordinator   |   52000.00 | 2023-01-02   |
|      8 |     111 | Hayley    | Thomas    | Analyst       |   48000.00 | 2023-06-30   |
|      9 |     113 | Laura     | Martinez  | Technician    |   51000.00 | 2022-06-18   |
|     10 |     110 | James     | Lee       | Salesperson   |   55000.00 | 2023-03-20   |
+--------+---------+-----------+-----------+---------------+------------+--------------+
10 rows in set (0.00 sec)

    
mysql> alter table employee add foreign key(dept_id) references department(dept_id) on delete cascade on update cascade;
Query OK, 10 rows affected (0.20 sec)
Records: 10  Duplicates: 0  Warnings: 0

    
mysql> alter table project add foreign key(dept_id) references department(dept_id) on delete cascade on update cascade;
Query OK, 7 rows affected (0.08 sec)
Records: 7  Duplicates: 0  Warnings: 0

    
mysql> DELETE FROM department WHERE dept_location="Mumbai";
Query OK, 1 row affected (0.01 sec)

    
mysql> select proj_name from project where proj_location="Pune";
+-----------------+
| proj_name       |
+-----------------+
| ProductX Launch |
| Brand Event     |
+-----------------+
2 rows in set (0.00 sec)

    
mysql> select* from project where proj_cost between 100000 and 500000;
+---------+---------+------------------+---------------+-----------+-----------+
| proj_id | dept_id | proj_name        | proj_location | proj_cost | proj_year |
+---------+---------+------------------+---------------+-----------+-----------+
|     501 |     110 | ProductX Launch  | Pune          | 250000.00 |      2022 |
|     503 |     112 | App Development  | Bangalore     | 500000.00 |      2021 |
|     504 |     113 | Website Redesign | Chennai       | 350000.00 |      2023 |
|     505 |     112 | Software Upgrade | Bangalore     | 220000.00 |      2022 |
|     506 |     110 | Brand Event      | Pune          | 180000.00 |      2023 |
|     507 |     114 | Employee Welfare | Delhi         | 400000.00 |      2022 |
+---------+---------+------------------+---------------+-----------+-----------+
6 rows in set (0.00 sec)

    
mysql> select* from project where proj_cost = (select max(proj_cost) from project);
+---------+---------+-----------------+---------------+-----------+-----------+
| proj_id | dept_id | proj_name       | proj_location | proj_cost | proj_year |
+---------+---------+-----------------+---------------+-----------+-----------+
|     503 |     112 | App Development | Bangalore     | 500000.00 |      2021 |
+---------+---------+-----------------+---------------+-----------+-----------+
1 row in set (0.00 sec)

    
mysql> select avg(proj_cost) as average_cost from project;
+---------------+
| average_cost  |
+---------------+
| 316666.666667 |
+---------------+
1 row in set (0.00 sec)

    
mysql> select emp_id, emp_fname, emp_lname from employee order by emp_lname desc;
+--------+-----------+-----------+
| emp_id | emp_fname | emp_lname |
+--------+-----------+-----------+
|      4 | Sarah     | Wilson    |
|      2 | Peyton    | Smith     |
|      6 | Robert    | Rodriguez |
|      9 | Laura     | Martinez  |
|     10 | James     | Lee       |
|      7 | David     | Garcia    |
|      1 | John      | Doe       |
|      5 | Emily     | Brown     |
+--------+-----------+-----------+
8 rows in set (0.00 sec)

    
mysql> select proj_name, proj_location, proj_cost from project where proj_year in (2021, 2022);
+------------------+---------------+-----------+
| proj_name        | proj_location | proj_cost |
+------------------+---------------+-----------+
| ProductX Launch  | Pune          | 250000.00 |
| App Development  | Bangalore     | 500000.00 |
| Software Upgrade | Bangalore     | 220000.00 |
| Employee Welfare | Delhi         | 400000.00 |
+------------------+---------------+-----------+
4 rows in set (0.00 sec)

    
mysql> commit;
Query OK, 0 rows affected (0.00 sec)

---------------------------------------------------------------------------------------------------------------

mysql> CREATE VIEW emp_view AS
    -> SELECT emp_id, emp_fname, emp_lname, emp_birthdate, e.dept_id, d.dept_name, emp_position, emp_salary
    -> FROM employee e, department d 
    -> WHERE e.dept_id = d.dept_id;
Query OK, 0 rows affected (0.02 sec)

    
mysql> select* from emp_view;
+--------+-----------+-----------+---------------+---------+-----------------+---------------+------------+
| emp_id | emp_fname | emp_lname | emp_birthdate | dept_id | dept_name       | emp_position  | emp_salary |
+--------+-----------+-----------+---------------+---------+-----------------+---------------+------------+
|     4001 | John            | Doe            | 1982-03-04    |     113 | IT              | Manager       |   75000.00 |
|     4002 | Peyton        | Smith         | 1985-08-19    |     112 | Computer        | Engineer      |   60000.00 |
|     4003 | Michael      | Johnson      | 1981-11-21    |     111 | Marketing       | Accountant    |   50000.00 |
|     4004 | Sarah          | Wilson        | 1988-01-07    |     114 | Human Resources | Administrator |   48000.00 |
|     4005 | Emily         | Brown         | 1989-10-30    |     112 | Computer        | Programmer    |   55000.00 |
|     4006 | Robert       | Rodriguez  | 1983-06-12    |     110 | Sales           | Salesperson   |   42000.00 |
|     4007 | David        | Garcia        | 1990-12-20    |     114 | Human Resources | Coordinator   |   52000.00 |
|     4008 | Jennifer     | Thomas      | 1987-09-05    |     111 | Marketing       | Analyst       |   48000.00 |
|     4009 | Laura        | Martinez     | 1984-04-29    |     113 | IT              | Technician    |   51000.00 |
|     4010 | James        | Lee             | 1986-05-14    |     110 | Sales           | Salesperson   |   55000.00 |
+--------+-----------+-----------+---------------+---------+-----------------+---------------+------------+
10 rows in set (0.00 sec)

    
mysql> CREATE UNIQUE INDEX emp_index ON employee(emp_id);
Query OK, 0 rows affected (0.09 sec)
Records: 0  Duplicates: 0  Warnings: 0

    
mysql> CREATE TABLE emps (name varchar(20), id int(5));
Query OK, 0 rows affected (0.06 sec)

    
mysql> DROP TABLE emps;
Query OK, 0 rows affected (0.00 sec)

    
mysql> SHOW TABLES;
+---------------------+
| Tables_in_te31301db |
+---------------------+
| course              |
| department          |
| emp_view            |
| employee            |
| login               |
| project             |
| student             |
| teacher             |
+---------------------+
8 rows in set (0.00 sec)

    
mysql> SELECT* FROM emp_view;
+--------+-----------+-----------+---------------+---------+-----------------+---------------+------------+
| emp_id | emp_fname | emp_lname | emp_birthdate | dept_id | dept_name       | emp_position  | emp_salary |
+--------+-----------+-----------+---------------+---------+-----------------+---------------+------------+
|   4001 | John      | Doe       | 1982-03-04    |     113 | IT              | Manager       |   75000.00 |
|   4002 | Peyton    | Smith     | 1985-08-19    |     112 | Computer        | Engineer      |   60000.00 |
|   4003 | Michael   | Johnson   | 1981-11-21    |     111 | Marketing       | Accountant    |   50000.00 |
|   4004 | Sarah     | Wilson    | 1988-01-07    |     114 | Human Resources | Administrator |   48000.00 |
|   4005 | Emily     | Brown     | 1989-10-30    |     112 | Computer        | Programmer    |   55000.00 |
|   4006 | Robert    | Rodriguez | 1983-06-12    |     110 | Sales           | Salesperson   |   42000.00 |
|   4007 | David     | Garcia    | 1990-12-20    |     114 | Human Resources | Coordinator   |   52000.00 |
|   4008 | Jennifer  | Thomas    | 1987-09-05    |     111 | Marketing       | Analyst       |   48000.00 |
|   4009 | Laura     | Martinez  | 1984-04-29    |     113 | IT              | Technician    |   51000.00 |
|   4010 | James     | Lee       | 1986-05-14    |     110 | Sales           | Salesperson   |   55000.00 |
+--------+-----------+-----------+---------------+---------+-----------------+---------------+------------+
10 rows in set (0.01 sec)

    
mysql> SELECT* FROM emp_view WHERE dept_name IN ('Computer', 'IT') AND emp_fname LIKE "P%" OR "H%";
+--------+-----------+-----------+---------------+---------+-----------+--------------+------------+
| emp_id | emp_fname | emp_lname | emp_birthdate | dept_id | dept_name | emp_position | emp_salary |
+--------+-----------+-----------+---------------+---------+-----------+--------------+------------+
|   4002 | Peyton    | Smith     | 1985-08-19    |     112 | Computer  | Engineer     |   60000.00 |
+--------+-----------+-----------+---------------+---------+-----------+--------------+------------+
1 row in set, 4 warnings (0.00 sec)

    
mysql> SELECT DISTINCT emp_position FROM emp_view;
+---------------+
| emp_position  |
+---------------+
| Manager       |
| Engineer      |
| Accountant    |
| Administrator |
| Programmer    |
| Salesperson   |
| Coordinator   |
| Analyst       |
| Technician    |
+---------------+
9 rows in set (0.00 sec)

    
mysql> update emp_view 
    -> set emp_salary = emp_salary*1.1 
    -> where year(emp_birthdate) < '1985';
Query OK, 4 rows affected (0.01 sec)
Rows matched: 4  Changed: 4  Warnings: 0

    
mysql> select* from emp_view;
+--------+-----------+-----------+---------------+---------+-----------------+---------------+------------+
| emp_id | emp_fname | emp_lname | emp_birthdate | dept_id | dept_name       | emp_position  | emp_salary |
+--------+-----------+-----------+---------------+---------+-----------------+---------------+------------+
|   4001 | John      | Doe       | 1982-03-04    |     113 | IT              | Manager       |   82500.00 |
|   4002 | Peyton    | Smith     | 1985-08-19    |     112 | Computer        | Engineer      |   60000.00 |
|   4003 | Michael   | Johnson   | 1981-11-21    |     111 | Marketing       | Accountant    |   55000.00 |
|   4004 | Sarah     | Wilson    | 1988-01-07    |     114 | Human Resources | Administrator |   48000.00 |
|   4005 | Emily     | Brown     | 1989-10-30    |     112 | Computer        | Programmer    |   55000.00 |
|   4006 | Robert    | Rodriguez | 1983-06-12    |     110 | Sales           | Salesperson   |   46200.00 |
|   4007 | David     | Garcia    | 1990-12-20    |     114 | Human Resources | Coordinator   |   52000.00 |
|   4008 | Jennifer  | Thomas    | 1987-09-05    |     111 | Marketing       | Analyst       |   48000.00 |
|   4009 | Laura     | Martinez  | 1984-04-29    |     113 | IT              | Technician    |   56100.00 |
|   4010 | James     | Lee       | 1986-05-14    |     110 | Sales           | Salesperson   |   55000.00 |
+--------+-----------+-----------+---------------+---------+-----------------+---------------+------------+
10 rows in set (0.00 sec)

    
mysql> alter table project 
    -> add foreign key(dept_id) 
    -> references department(dept_id) 
    -> on delete cascade;
Query OK, 7 rows affected (0.07 sec)
Records: 7  Duplicates: 0  Warnings: 0

    
mysql> alter table employee 
    -> add foreign key(dept_id) 
    -> references department(dept_id) 
    -> on delete cascade;
Query OK, 10 rows affected (0.09 sec)
Records: 10  Duplicates: 0  Warnings: 0

    
mysql> delete from department where dept_location='Mumbai';
Query OK, 1 row affected (0.01 sec)

    
mysql> select* from emp_view;
+--------+-----------+-----------+---------------+---------+-----------------+---------------+------------+
| emp_id | emp_fname | emp_lname | emp_birthdate | dept_id | dept_name       | emp_position  | emp_salary |
+--------+-----------+-----------+---------------+---------+-----------------+---------------+------------+
|   4001 | John      | Doe       | 1982-03-04    |     113 | IT              | Manager       |   82500.00 |
|   4002 | Peyton    | Smith     | 1985-08-19    |     112 | Computer        | Engineer      |   60000.00 |
|   4004 | Sarah     | Wilson    | 1988-01-07    |     114 | Human Resources | Administrator |   48000.00 |
|   4005 | Emily     | Brown     | 1989-10-30    |     112 | Computer        | Programmer    |   55000.00 |
|   4006 | Robert    | Rodriguez | 1983-06-12    |     110 | Sales           | Salesperson   |   46200.00 |
|   4007 | David     | Garcia    | 1990-12-20    |     114 | Human Resources | Coordinator   |   52000.00 |
|   4009 | Laura     | Martinez  | 1984-04-29    |     113 | IT              | Technician    |   56100.00 |
|   4010 | James     | Lee       | 1986-05-14    |     110 | Sales           | Salesperson   |   55000.00 |
+--------+-----------+-----------+---------------+---------+-----------------+---------------+------------+
8 rows in set (0.01 sec)

    
mysql> select proj_name from project where proj_location='Pune';
+-----------------+
| proj_name       |
+-----------------+
| ProductX Launch |
| Brand Event     |
+-----------------+
2 rows in set (0.00 sec)

    
mysql> select proj_name, proj_cost from project where proj_cost between 100000 and 500000;
+------------------+-----------+
| proj_name        | proj_cost |
+------------------+-----------+
| ProductX Launch  | 250000.00 |
| App Development  | 500000.00 |
| Website Redesign | 350000.00 |
| Software Upgrade | 220000.00 |
| Brand Event      | 180000.00 |
| Employee Welfare | 400000.00 |
+------------------+-----------+
6 rows in set (0.00 sec)

    
mysql> select proj_name, proj_cost from project where proj_cost = (select max(proj_cost) from project);
+-----------------+-----------+
| proj_name       | proj_cost |
+-----------------+-----------+
| App Development | 500000.00 |
+-----------------+-----------+
1 row in set (0.00 sec)

    
mysql> select avg(proj_cost) as average_cost from project;
+---------------+
| average_cost  |
+---------------+
| 316666.666667 |
+---------------+
1 row in set (0.00 sec)

    
mysql> select emp_id, emp_fname, emp_lname from employee order by emp_lname desc;
+--------+-----------+-----------+
| emp_id | emp_fname | emp_lname |
+--------+-----------+-----------+
|   4004 | Sarah     | Wilson    |
|   4002 | Peyton    | Smith     |
|   4006 | Robert    | Rodriguez |
|   4009 | Laura     | Martinez  |
|   4010 | James     | Lee       |
|   4007 | David     | Garcia    |
|   4001 | John      | Doe       |
|   4005 | Emily     | Brown     |
+--------+-----------+-----------+
8 rows in set (0.00 sec)

    
mysql> select proj_name, proj_location, proj_cost from project where proj_year in ('2004', '2005', '2007'); 
+------------------+---------------+-----------+
| proj_name        | proj_location | proj_cost |
+------------------+---------------+-----------+
| App Development  | Bangalore     | 500000.00 |
| Website Redesign | Chennai       | 350000.00 |
| Brand Event      | Pune          | 180000.00 |
| Employee Welfare | Delhi         | 400000.00 |
+------------------+---------------+-----------+
4 rows in set (0.00 sec)

    
mysql> drop index emp_index on employee;
Query OK, 0 rows affected (0.07 sec)
Records: 0  Duplicates: 0  Warnings: 0

    
mysql> CREATE INDEX emp_index on employee(emp_fname);
Query OK, 0 rows affected (0.10 sec)
Records: 0  Duplicates: 0  Warnings: 0

    
mysql> drop index emp_index on employee;
Query OK, 0 rows affected (0.06 sec)
Records: 0  Duplicates: 0  Warnings: 0

    
mysql> create index emp_index on employee(emp_fname asc);
Query OK, 0 rows affected (0.07 sec)
Records: 0  Duplicates: 0  Warnings: 0

    
mysql> commit;
Query OK, 0 rows affected (0.00 sec)
