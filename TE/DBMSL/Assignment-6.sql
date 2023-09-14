-- Cursor for merging old and new customer tables

mysql> select* from cust_old;
+------+---------+-----------+
| id   | name    | location  |
+------+---------+-----------+
|    1 | Aarti   | NYC       |
|    3 | Saniya  | Texas     |
|    4 | Anushka | Rome      |
|    6 | Shlok   | Seoul     |
|    9 | Joel    | Vancouver |
+------+---------+-----------+
5 rows in set (0.22 sec)


mysql> select* from cust_new;
+------+---------+-----------+
| id   | name    | location  |
+------+---------+-----------+
|    1 | Aarti   | NYC       |
|    2 | Shivraj | Pune      |
|    5 | Emily   | Paris     |
|    7 | Elsa    | Beijing   |
|    8 | Marco   | Sydney    |
|    9 | Joel    | Vancouver |
+------+---------+-----------+
6 rows in set (0.00 sec)


mysql> desc cust_old;
+----------+-------------+------+-----+---------+-------+
| Field    | Type        | Null | Key | Default | Extra |
+----------+-------------+------+-----+---------+-------+
| id       | int(11)     | NO   | PRI | NULL    |       |
| name     | varchar(30) | YES  |     | NULL    |       |
| location | varchar(50) | YES  |     | NULL    |       |
+----------+-------------+------+-----+---------+-------+
3 rows in set (0.01 sec)


mysql> desc cust_new;
+----------+-------------+------+-----+---------+-------+
| Field    | Type        | Null | Key | Default | Extra |
+----------+-------------+------+-----+---------+-------+
| id       | int(11)     | NO   | PRI | NULL    |       |
| name     | varchar(30) | YES  |     | NULL    |       |
| location | varchar(50) | YES  |     | NULL    |       |
+----------+-------------+------+-----+---------+-------+
3 rows in set (0.00 sec)


mysql> select* from cust_old;
+----+---------+-----------+
| id | name    | location  |
+----+---------+-----------+
|  1 | Aarti   | NYC       |
|  3 | Saniya  | Texas     |
|  4 | Anushka | Rome      |
|  6 | Shlok   | Seoul     |
|  9 | Joel    | Vancouver |
+----+---------+-----------+
5 rows in set (0.00 sec)


mysql> select* from cust_new;
+----+-------+-----------+
| id | name  | location  |
+----+-------+-----------+
|  1 | Aarti | NYC       |
|  2 | Kyle  | Pune      |
|  5 | Emily | Paris     |
|  7 | Elsa  | Beijing   |
|  8 | Marco | Sydney    |
|  9 | Joel  | Vancouver |
+----+-------+-----------+
6 rows in set (0.00 sec)


mysql> delimiter //
mysql> create procedure merge()
    -> begin
    -> declare done int default false;
    -> declare old_id int;
    -> declare old_name varchar(50);
    -> -- declare cursor
    -> declare mergeCursor cursor for 
    -> select id, name from cust_old;
    -> -- declare exception handler 
    -> declare continue handler for not found set done = true;
    -> open mergeCursor;
    -> read_loop: loop
    -> fetch mergeCursor into old_id, old_name;
    -> if done then
    -> leave read_loop;
    -> end if;
    -> -- check if row already exists in cust_new
    -> if not exists (select 1 from cust_new where id=old_id and name=old_name) then
    -> insert into cust_new (id, name) values (old_id, old_name);
    -> end if;
    -> end loop;
    -> close mergeCursor;
    -> end;
    -> //
Query OK, 0 rows affected (0.00 sec)


mysql> delimiter ;
mysql> call merge();
Query OK, 0 rows affected, 1 warning (0.03 sec)


mysql> select * from cust_new;
+----+---------+-----------+
| id | name    | location  |
+----+---------+-----------+
|  1 | Aarti   | NYC       |
|  2 | Kyle    | Pune      |
|  3 | Saniya  | NULL      |
|  4 | Anushka | NULL      |
|  5 | Emily   | Paris     |
|  6 | Shlok   | NULL      |
|  7 | Elsa    | Beijing   |
|  8 | Marco   | Sydney    |
|  9 | Joel    | Vancouver |
+----+---------+-----------+
9 rows in set (0.00 sec)
