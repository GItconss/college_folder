
SET SERVEROUTPUT ON;

DECLARE
    TYPE NamesArray IS VARRAY(5) OF VARCHAR2(10);
    TYPE MarksArray IS VARRAY(5) OF NUMBER;

    Names NamesArray;
    Marks MarksArray;
    i    NUMBER;
    len  NUMBER;
BEGIN
    Names := NamesArray('SUMI', 'NAVYA', 'RAHUL', 'YADHU', 'MANU');
    Marks := MarksArray(56, 76, 55, 67, 98);

    len := Names.COUNT;

    dbms_output.put_line('Total students = ' || len);

    FOR i IN 1..len LOOP
        dbms_output.put_line('Student name = ' || Names(i) || '  Marks = ' || Marks(i));
    END LOOP;
END;
/