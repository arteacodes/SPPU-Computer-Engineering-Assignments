mysql> select* from employee;
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+
| emp_id | dept_id | emp_fname | emp_lname | emp_position  | emp_salary | emp_birthdate | emp_joindate |
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+
|   4001 |     113 | Johnny    | Doe       | Manager       |   82500.00 | 1982-03-04    | 2022-01-15   |
|   4002 |     112 | Peyton    | Smith     | Engineer      |   60000.00 | 1985-08-19    | 2021-09-10   |
|   4004 |     114 | Sarah     | Wilson    | Administrator |   48000.00 | 1988-01-07    | 2021-11-05   |
|   4005 |     112 | Emily     | Brown     | Programmer    |   55000.00 | 1989-10-30    | 2023-03-20   |
|   4006 |     110 | Robert    | Rodriguez | Salesperson   |   46200.00 | 1983-06-12    | 2022-12-09   |
|   4007 |     114 | David     | Garcia    | Coordinator   |   52000.00 | 1990-12-20    | 2023-01-02   |
|   4009 |     113 | Laura     | Martinez  | Technician    |   56100.00 | 1984-04-29    | 2022-06-18   |
|   4010 |     110 | James     | Lee       | Salesperson   |   55000.00 | 1986-05-14    | 2023-03-20   |
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+
8 rows in set (0.00 sec)

mysql> select* from department;
+---------+-----------------+---------------+
| dept_id | dept_name       | dept_location |
+---------+-----------------+---------------+
|     110 | Sales           | Pune          |
|     112 | Computer        | Bangalore     |
|     113 | IT              | Chennai       |
|     114 | Human Resources | Delhi         |
+---------+-----------------+---------------+
4 rows in set (0.00 sec)

mysql> select* from project;
+---------+---------+------------------+---------------+-----------+-----------+
| proj_id | dept_id | proj_name        | proj_location | proj_cost | proj_year |
+---------+---------+------------------+---------------+-----------+-----------+
|     501 |     110 | ProductX Launch  | Pune          | 250000.00 |      2006 |
|     503 |     112 | App Development  | Bangalore     | 500000.00 |      2005 |
|     504 |     113 | Website Redesign | Chennai       | 350000.00 |      2007 |
|     505 |     112 | Software Upgrade | Bangalore     | 220000.00 |      2008 |
|     506 |     110 | Brand Event      | Pune          | 180000.00 |      2005 |
|     507 |     114 | Employee Welfare | Delhi         | 400000.00 |      2007 |
+---------+---------+------------------+---------------+-----------+-----------+
6 rows in set (0.00 sec)

mysql> select* from employee natural join department;
+---------+--------+-----------+-----------+---------------+------------+---------------+--------------+-----------------+---------------+
| dept_id | emp_id | emp_fname | emp_lname | emp_position  | emp_salary | emp_birthdate | emp_joindate | dept_name       | dept_location |
+---------+--------+-----------+-----------+---------------+------------+---------------+--------------+-----------------+---------------+
|     113 |   4001 | Johnny    | Doe       | Manager       |   82500.00 | 1982-03-04    | 2022-01-15   | IT              | Chennai       |
|     112 |   4002 | Peyton    | Smith     | Engineer      |   60000.00 | 1985-08-19    | 2021-09-10   | Computer        | Bangalore     |
|     114 |   4004 | Sarah     | Wilson    | Administrator |   48000.00 | 1988-01-07    | 2021-11-05   | Human Resources | Delhi         |
|     112 |   4005 | Emily     | Brown     | Programmer    |   55000.00 | 1989-10-30    | 2023-03-20   | Computer        | Bangalore     |
|     110 |   4006 | Robert    | Rodriguez | Salesperson   |   46200.00 | 1983-06-12    | 2022-12-09   | Sales           | Pune          |
|     114 |   4007 | David     | Garcia    | Coordinator   |   52000.00 | 1990-12-20    | 2023-01-02   | Human Resources | Delhi         |
|     113 |   4009 | Laura     | Martinez  | Technician    |   56100.00 | 1984-04-29    | 2022-06-18   | IT              | Chennai       |
|     110 |   4010 | James     | Lee       | Salesperson   |   55000.00 | 1986-05-14    | 2023-03-20   | Sales           | Pune          |
+---------+--------+-----------+-----------+---------------+------------+---------------+--------------+-----------------+---------------+
8 rows in set (0.01 sec)


mysql> select emp_fname, emp_position, emp_joindate, dept_location from employee inner join department where employee.dept_id = department.dept_id;
+-----------+---------------+--------------+---------------+
| emp_fname | emp_position  | emp_joindate | dept_location |
+-----------+---------------+--------------+---------------+
| Johnny    | Manager       | 2022-01-15   | Chennai       |
| Peyton    | Engineer      | 2021-09-10   | Bangalore     |
| Sarah     | Administrator | 2021-11-05   | Delhi         |
| Emily     | Programmer    | 2023-03-20   | Bangalore     |
| Robert    | Salesperson   | 2022-12-09   | Pune          |
| David     | Coordinator   | 2023-01-02   | Delhi         |
| Laura     | Technician    | 2022-06-18   | Chennai       |
| James     | Salesperson   | 2023-03-20   | Pune          |
+-----------+---------------+--------------+---------------+
8 rows in set (0.00 sec)


mysql> select employee.*, proj_id, proj_cost from employee inner join project using(dept_id) where proj_location!='Bangalore';
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+---------+-----------+
| emp_id | dept_id | emp_fname | emp_lname | emp_position  | emp_salary | emp_birthdate | emp_joindate | proj_id | proj_cost |
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+---------+-----------+
|   4001 |     113 | Johnny    | Doe       | Manager       |   82500.00 | 1982-03-04    | 2022-01-15   |     504 | 350000.00 |
|   4004 |     114 | Sarah     | Wilson    | Administrator |   48000.00 | 1988-01-07    | 2021-11-05   |     507 | 400000.00 |
|   4006 |     110 | Robert    | Rodriguez | Salesperson   |   46200.00 | 1983-06-12    | 2022-12-09   |     501 | 250000.00 |
|   4006 |     110 | Robert    | Rodriguez | Salesperson   |   46200.00 | 1983-06-12    | 2022-12-09   |     506 | 180000.00 |
|   4007 |     114 | David     | Garcia    | Coordinator   |   52000.00 | 1990-12-20    | 2023-01-02   |     507 | 400000.00 |
|   4009 |     113 | Laura     | Martinez  | Technician    |   56100.00 | 1984-04-29    | 2022-06-18   |     504 | 350000.00 |
|   4010 |     110 | James     | Lee       | Salesperson   |   55000.00 | 1986-05-14    | 2023-03-20   |     501 | 250000.00 |
|   4010 |     110 | James     | Lee       | Salesperson   |   55000.00 | 1986-05-14    | 2023-03-20   |     506 | 180000.00 |
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+---------+-----------+
8 rows in set (0.00 sec)





mysql> select dept_name, emp_fname, emp_lname, emp_position, proj_year from employee, department, project where employee.dept_id = department.dept_id and employee.dept_id = project.dept_id and proj_year='2005';
+-----------+-----------+-----------+--------------+-----------+
| dept_name | emp_fname | emp_lname | emp_position | proj_year |
+-----------+-----------+-----------+--------------+-----------+
| Computer  | Peyton    | Smith     | Engineer     |      2005 |
| Computer  | Emily     | Brown     | Programmer   |      2005 |
| Sales     | Robert    | Rodriguez | Salesperson  |      2005 |
| Sales     | James     | Lee       | Salesperson  |      2005 |
+-----------+-----------+-----------+--------------+-----------+
4 rows in set (0.01 sec)


mysql> select dept_name, emp_fname, emp_lname, emp_position, proj_year from employee 
    -> inner join department using (dept_id) 
    -> inner join project using (dept_id) 
    -> where proj_year='2005';
+-----------+-----------+-----------+--------------+-----------+
| dept_name | emp_fname | emp_lname | emp_position | proj_year |
+-----------+-----------+-----------+--------------+-----------+
| Computer  | Peyton    | Smith     | Engineer     |      2005 |
| Computer  | Emily     | Brown     | Programmer   |      2005 |
| Sales     | Robert    | Rodriguez | Salesperson  |      2005 |
| Sales     | James     | Lee       | Salesperson  |      2005 |
+-----------+-----------+-----------+--------------+-----------+
4 rows in set (0.00 sec)



mysql> select emp_position, dept_name from employee inner join department using (dept_id) inner join project using (dept_id) where proj_cost > 300000;
+---------------+-----------------+
| emp_position  | dept_name       |
+---------------+-----------------+
| Manager       | IT              |
| Engineer      | Computer        |
| Administrator | Human Resources |
| Programmer    | Computer        |
| Coordinator   | Human Resources |
| Technician    | IT              |
+---------------+-----------------+
6 rows in set (0.00 sec)


 mysql> select dept_name, count(emp_id) as no_of_emp from department d left join employee using (dept_id) group by dept_name order by no_of_emp desc limit 1;
+-----------+-----------+
| dept_name | no_of_emp |
+-----------+-----------+
| Sales     |         4 |
+-----------+-----------+
1 row in set (0.00 sec)


mysql> select count(*) as total from employee where year(emp_joindate) < 2021;
+-------+
| total |
+-------+
|     2 |
+-------+
1 row in set (0.00 sec)


mysql> create or replace view emp_view as select * from employee e inner join department d using(dept_id);
Query OK, 0 rows affected (0.03 sec)


mysql> select* from emp_view;
+---------+--------+-----------+-----------+---------------+------------+---------------+--------------+-----------------+---------------+
| dept_id | emp_id | emp_fname | emp_lname | emp_position  | emp_salary | emp_birthdate | emp_joindate | dept_name       | dept_location |
+---------+--------+-----------+-----------+---------------+------------+---------------+--------------+-----------------+---------------+
|     113 |   4001 | Johnny    | Doe       | Manager       |   82500.00 | 1982-03-04    | 2022-01-15   | IT              | Chennai       |
|     112 |   4002 | Peyton    | Smith     | Engineer      |   60000.00 | 1985-08-19    | 2021-09-10   | Computer        | Bangalore     |
|     114 |   4004 | Sarah     | Wilson    | Administrator |   48000.00 | 1988-01-07    | 2021-11-05   | Human Resources | Delhi         |
|     112 |   4005 | Emily     | Brown     | Programmer    |   55000.00 | 1989-10-30    | 2023-03-20   | Computer        | Bangalore     |
|     110 |   4006 | Robert    | Rodriguez | Salesperson   |   46200.00 | 1983-06-12    | 2022-12-09   | Sales           | Pune          |
|     114 |   4007 | David     | Garcia    | Coordinator   |   52000.00 | 1990-12-20    | 2023-01-02   | Human Resources | Delhi         |
|     113 |   4009 | Laura     | Martinez  | Technician    |   56100.00 | 1984-04-29    | 2022-06-18   | IT              | Chennai       |
|     110 |   4010 | James     | Lee       | Salesperson   |   55000.00 | 1986-05-14    | 2023-03-20   | Sales           | Pune          |
|     110 |   4011 | Kobe      | Bryant    | Supervisor    |       NULL | 1991-03-17    | 2020-01-01   | Sales           | Pune          |
|     110 |   4012 | Isabel    | Valencia  | Accountant    |   41000.00 | 1992-11-04    | 2020-12-28   | Sales           | Pune          |
+---------+--------+-----------+-----------+---------------+------------+---------------+--------------+-----------------+---------------+
10 rows in set (0.00 sec)


mysql> update emp_view 
    -> set emp_position = null 
    -> where emp_id = 4009;
Query OK, 1 row affected (0.02 sec)
Rows matched: 1  Changed: 1  Warnings: 0


mysql> select* from emp_view;
+---------+--------+-----------+-----------+---------------+------------+---------------+--------------+-----------------+---------------+
| dept_id | emp_id | emp_fname | emp_lname | emp_position  | emp_salary | emp_birthdate | emp_joindate | dept_name       | dept_location |
+---------+--------+-----------+-----------+---------------+------------+---------------+--------------+-----------------+---------------+
|     113 |   4001 | Johnny    | Doe       | Manager       |   82500.00 | 1982-03-04    | 2022-01-15   | IT              | Chennai       |
|     112 |   4002 | Peyton    | Smith     | Engineer      |   60000.00 | 1985-08-19    | 2021-09-10   | Computer        | Bangalore     |
|     114 |   4004 | Sarah     | Wilson    | Administrator |   48000.00 | 1988-01-07    | 2021-11-05   | Human Resources | Delhi         |
|     112 |   4005 | Emily     | Brown     | Programmer    |   55000.00 | 1989-10-30    | 2023-03-20   | Computer        | Bangalore     |
|     110 |   4006 | Robert    | Rodriguez | Salesperson   |   46200.00 | 1983-06-12    | 2022-12-09   | Sales           | Pune          |
|     114 |   4007 | David     | Garcia    | Coordinator   |   52000.00 | 1990-12-20    | 2023-01-02   | Human Resources | Delhi         |
|     113 |   4009 | Laura     | Martinez  | NULL          |   56100.00 | 1984-04-29    | 2022-06-18   | IT              | Chennai       |
|     110 |   4010 | James     | Lee       | Salesperson   |   55000.00 | 1986-05-14    | 2023-03-20   | Sales           | Pune          |
|     110 |   4011 | Kobe      | Bryant    | Supervisor    |       NULL | 1991-03-17    | 2020-01-01   | Sales           | Pune          |
|     110 |   4012 | Isabel    | Valencia  | Accountant    |   41000.00 | 1992-11-04    | 2020-12-28   | Sales           | Pune          |
+---------+--------+-----------+-----------+---------------+------------+---------------+--------------+-----------------+---------------+
10 rows in set (0.00 sec)


mysql> delete from emp_view where emp_id = 4012;
ERROR 1395 (HY000): Can not delete from join view 'te31301db.emp_view'
mysql> drop view emp_view;
Query OK, 0 rows affected (0.00 sec)


Q1. SQL Query to fetch records that are present in one table but not in another table.
mysql> select * from department where dept_id not in (select dept_id from project);
+---------+-----------+---------------+
| dept_id | dept_name | dept_location |
+---------+-----------+---------------+
|     115 | Marketing | Kolkata       |
+---------+-----------+---------------+
1 row in set (0.00 sec)


Q2. SQL query to fetch all the employees who are not working on any project.



Q3. SQL query to fetch all the Employees from EmployeeDetails who joined in the Year 2020.
mysql> select * from employee where year(emp_joindate)=2020;
+--------+---------+-----------+-----------+--------------+------------+---------------+--------------+
| emp_id | dept_id | emp_fname | emp_lname | emp_position | emp_salary | emp_birthdate | emp_joindate |
+--------+---------+-----------+-----------+--------------+------------+---------------+--------------+
|   4011 |     110 | Kobe      | Bryant    | Supervisor   |       NULL | 1991-03-17    | 2020-01-01   |
|   4012 |     110 | Isabel    | Valencia  | Accountant   |   41000.00 | 1992-11-04    | 2020-12-28   |
+--------+---------+-----------+-----------+--------------+------------+---------------+--------------+
2 rows in set (0.01 sec)


Q4. Fetch all employees from EmployeeDetails who have a salary record in EmployeeSalary.
mysql> select * from employee where emp_salary is not null;
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+
| emp_id | dept_id | emp_fname | emp_lname | emp_position  | emp_salary | emp_birthdate | emp_joindate |
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+
|   4001 |     113 | Johnny    | Doe       | Manager       |   82500.00 | 1982-03-04    | 2022-01-15   |
|   4002 |     112 | Peyton    | Smith     | Engineer      |   60000.00 | 1985-08-19    | 2021-09-10   |
|   4004 |     114 | Sarah     | Wilson    | Administrator |   48000.00 | 1988-01-07    | 2021-11-05   |
|   4005 |     112 | Emily     | Brown     | Programmer    |   55000.00 | 1989-10-30    | 2023-03-20   |
|   4006 |     110 | Robert    | Rodriguez | Salesperson   |   46200.00 | 1983-06-12    | 2022-12-09   |
|   4007 |     114 | David     | Garcia    | Coordinator   |   52000.00 | 1990-12-20    | 2023-01-02   |
|   4009 |     113 | Laura     | Martinez  | NULL          |   56100.00 | 1984-04-29    | 2022-06-18   |
|   4010 |     110 | James     | Lee       | Salesperson   |   55000.00 | 1986-05-14    | 2023-03-20   |
|   4012 |     110 | Isabel    | Valencia  | Accountant    |   41000.00 | 1992-11-04    | 2020-12-28   |
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+
9 rows in set (0.00 sec)

Q5. Write an SQL query to fetch a project-wise count of employees.
mysql> select proj_id, count(emp_id) as proj_count from project inner join employee using (dept_id) group by proj_id;
+---------+------------+
| proj_id | proj_count |
+---------+------------+
|     501 |          4 |
|     503 |          2 |
|     504 |          2 |
|     505 |          2 |
|     506 |          4 |
|     507 |          2 |
+---------+------------+
6 rows in set (0.01 sec)


Q6. Fetch employee names and salaries even if the salary value is not present for the employee.
mysql> select emp_fname, emp_salary from employee;
+-----------+------------+
| emp_fname | emp_salary |
+-----------+------------+
| Johnny    |   82500.00 |
| Peyton    |   60000.00 |
| Sarah     |   48000.00 |
| Emily     |   55000.00 |
| Robert    |   46200.00 |
| David     |   52000.00 |
| Laura     |   56100.00 |
| James     |   55000.00 |
| Kobe      |       NULL |
| Isabel    |   41000.00 |
+-----------+------------+
10 rows in set (0.00 sec)


Q7. Write an SQL query to fetch all the Employees who are also managers.
mysql> select * from employee where emp_position = 'Manager';
+--------+---------+-----------+-----------+--------------+------------+---------------+--------------+
| emp_id | dept_id | emp_fname | emp_lname | emp_position | emp_salary | emp_birthdate | emp_joindate |
+--------+---------+-----------+-----------+--------------+------------+---------------+--------------+
|   4001 |     113 | Johnny    | Doe       | Manager      |   82500.00 | 1982-03-04    | 2022-01-15   |
+--------+---------+-----------+-----------+--------------+------------+---------------+--------------+
1 row in set (0.00 sec)


Q8. Write an SQL query to fetch duplicate records from EmployeeDetails.
mysql> select emp_fname, emp_lname, emp_position, emp_salary from employee group by emp_position having count(emp_position)>1;
+-----------+-----------+--------------+------------+
| emp_fname | emp_lname | emp_position | emp_salary |
+-----------+-----------+--------------+------------+
| Robert    | Rodriguez | Salesperson  |   46200.00 |
+-----------+-----------+--------------+------------+
1 row in set (0.00 sec)


Q9. Write an SQL query to fetch only odd rows from the table.
mysql> select * from employee where mod(emp_id, 2)=1;
+--------+---------+-----------+-----------+--------------+------------+---------------+--------------+
| emp_id | dept_id | emp_fname | emp_lname | emp_position | emp_salary | emp_birthdate | emp_joindate |
+--------+---------+-----------+-----------+--------------+------------+---------------+--------------+
|   4001 |     113 | Johnny    | Doe       | Manager      |   82500.00 | 1982-03-04    | 2022-01-15   |
|   4005 |     112 | Emily     | Brown     | Programmer   |   55000.00 | 1989-10-30    | 2023-03-20   |
|   4007 |     114 | David     | Garcia    | Coordinator  |   52000.00 | 1990-12-20    | 2023-01-02   |
|   4009 |     113 | Laura     | Martinez  | NULL         |   56100.00 | 1984-04-29    | 2022-06-18   |
|   4011 |     110 | Kobe      | Bryant    | Supervisor   |       NULL | 1991-03-17    | 2020-01-01   |
+--------+---------+-----------+-----------+--------------+------------+---------------+--------------+
5 rows in set (0.00 sec)


Q10. Write a query to find the 3rd highest salary from a table without top or limit keyword.
mysql> select emp_fname, emp_salary from employee order by emp_salary desc limit 1 offset 2;
+-----------+------------+
| emp_fname | emp_salary |
+-----------+------------+
| Laura     |   56100.00 |
+-----------+------------+
1 row in set (0.00 sec)


Q11. Create a query that prints first and last name data from a sample table into a column called FULL_NAME.
mysql> select concat(emp_fname, " ", emp_lname) as full_name from employee;
+------------------+
| full_name        |
+------------------+
| Johnny Doe       |
| Peyton Smith     |
| Sarah Wilson     |
| Emily Brown      |
| Robert Rodriguez |
| David Garcia     |
| Laura Martinez   |
| James Lee        |
| Kobe Bryant      |
| Isabel Valencia  |
+------------------+
10 rows in set (0.00 sec)



Q12. Write a query that prints the details from a sample table ascending in first name order.
mysql> select * from employee order by emp_fname;
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+
| emp_id | dept_id | emp_fname | emp_lname | emp_position  | emp_salary | emp_birthdate | emp_joindate |
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+
|   4007 |     114 | David     | Garcia    | Coordinator   |   52000.00 | 1990-12-20    | 2023-01-02   |
|   4005 |     112 | Emily     | Brown     | Programmer    |   55000.00 | 1989-10-30    | 2023-03-20   |
|   4012 |     110 | Isabel    | Valencia  | Accountant    |   41000.00 | 1992-11-04    | 2020-12-28   |
|   4010 |     110 | James     | Lee       | Salesperson   |   55000.00 | 1986-05-14    | 2023-03-20   |
|   4001 |     113 | Johnny    | Doe       | Manager       |   82500.00 | 1982-03-04    | 2022-01-15   |
|   4011 |     110 | Kobe      | Bryant    | Supervisor    |       NULL | 1991-03-17    | 2020-01-01   |
|   4009 |     113 | Laura     | Martinez  | NULL          |   56100.00 | 1984-04-29    | 2022-06-18   |
|   4002 |     112 | Peyton    | Smith     | Engineer      |   60000.00 | 1985-08-19    | 2021-09-10   |
|   4006 |     110 | Robert    | Rodriguez | Salesperson   |   46200.00 | 1983-06-12    | 2022-12-09   |
|   4004 |     114 | Sarah     | Wilson    | Administrator |   48000.00 | 1988-01-07    | 2021-11-05   |
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+
10 rows in set (0.00 sec)


Q13. Print the current date using a SQL query.
mysql> select curdate();
+------------+
| curdate()  |
+------------+
| 2023-08-10 |
+------------+
1 row in set (0.00 sec)


Q14. print name of employee/student works for/studies in department/class. "works for/studies in" should be added while displaying result
mysql> select concat(emp_fname, ' ', emp_lname, ' works for ', dept_name) as description from employee inner join department using(dept_id);
+----------------------------------------+
| description                            |
+----------------------------------------+
| Johnny Doe works for IT                |
| Peyton Smith works for Computer        |
| Sarah Wilson works for Human Resources |
| Emily Brown works for Computer         |
| Robert Rodriguez works for Sales       |
| David Garcia works for Human Resources |
| Laura Martinez works for IT            |
| James Lee works for Sales              |
| Kobe Bryant works for Sales            |
| Isabel Valencia works for Sales        |
+----------------------------------------+
10 rows in set (0.01 sec)



Q15. Display any 5 random rows
mysql> select * from employee order by rand() limit 5;
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+
| emp_id | dept_id | emp_fname | emp_lname | emp_position  | emp_salary | emp_birthdate | emp_joindate |
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+
|   4010 |     110 | James     | Lee       | Salesperson   |   55000.00 | 1986-05-14    | 2023-03-20   |
|   4007 |     114 | David     | Garcia    | Coordinator   |   52000.00 | 1990-12-20    | 2023-01-02   |
|   4009 |     113 | Laura     | Martinez  | NULL          |   56100.00 | 1984-04-29    | 2022-06-18   |
|   4011 |     110 | Kobe      | Bryant    | Supervisor    |       NULL | 1991-03-17    | 2020-01-01   |
|   4004 |     114 | Sarah     | Wilson    | Administrator |   48000.00 | 1988-01-07    | 2021-11-05   |
+--------+---------+-----------+-----------+---------------+------------+---------------+--------------+
5 rows in set (0.01 sec)



