SET SERVEROUTPUT ON

ACCEPT l NUMBER PROMPT 'Enter the length:';
ACCEPT b NUMBER PROMPT 'Enter the breadth:';
ACCEPT h NUMBER PROMPT 'Enter the height:';

DECLARE
    l NUMBER;
    b NUMBER;
    h NUMBER;
    v NUMBER;
BEGIN
    l := &l;
    b := &b;
    h := &h;

    v := l * b * h;

    dbms_output.put_line('Volume is ' || v);
END;
/