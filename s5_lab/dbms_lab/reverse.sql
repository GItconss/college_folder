SET SERVEROUTPUT ON

DECLARE
    str  VARCHAR2(30) := '&str';
    str1 VARCHAR2(30);   
    len  NUMBER;
    i    NUMBER;
BEGIN
    len := LENGTH(str);
    str1 := '';

    FOR i IN REVERSE 1..len LOOP
        str1 := str1 || SUBSTR(str, i, 1);
    END LOOP;

    dbms_output.put_line('Reverse is: ' || str1);
END;
/
