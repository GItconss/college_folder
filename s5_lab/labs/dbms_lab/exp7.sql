1.	CREATE TABLE student (
    rollno INT,
    fname VARCHAR(50),
    lname VARCHAR(50),
    mark FLOAT,
    dob DATE,
    Did INT
	);
	INSERT INTO student VALUES
	(101, 'Ajay', 'Kumar', 85.5, '2002-05-14', 1),
	(102, 'Priya', 'Sharma', 78.0, '2001-11-23', 2),
	(103, 'Rahul', 'Verma', 92.3, '2002-03-19', 3),
	(104, 'Sneha', 'Patel', 88.9, '2001-07-07', 4);
	+--------+-------+--------+------+------------+------+
	| rollno | fname | lname  | mark | dob        | Did  |
	+--------+-------+--------+------+------------+------+
	|    101 | Ajay  | Kumar  | 85.5 | 2002-05-14 |    1 |
	|    102 | Priya | Sharma |   78 | 2001-11-23 |    2 |
	|    103 | Rahul | Verma  | 92.3 | 2002-03-19 |    3 |
	|    104 | Sneha | Patel  | 88.9 | 2001-07-07 |    4 |
	+--------+-------+--------+------+------------+------+


2.	CREATE TABLE department (
		Did INT,
		Dname VARCHAR(50)
	);
	ALTER TABLE student
	ADD FOREIGN KEY(Did) REFERENCES department(Did);
	
	INSERT INTO department (Did, Dname) VALUES
	(1, 'Computer Science'),
	(2, 'Mechanical Engineering'),
	(3, 'Electrical Engineering'),
	(4, 'Civil Engineering');
	+-----+------------------------+
	| Did | Dname                  |
	+-----+------------------------+
	|   1 | Computer Science       |
	|   2 | Mechanical Engineering |
	|   3 | Electrical Engineering |
	|   4 | Civil Engineering      |
	+-----+------------------------+
-- Create the view
3	CREATE VIEW student_info AS
	SELECT 
		student.fname,
		YEAR(CURDATE()) - YEAR(student.dob) AS age,
		department.Dname AS department
	FROM 
		student
	JOIN 
    department ON student.Did = department.Did;

