SET SERVEROUTPUT ON

DECLARE
    i NUMBER;
    n NUMBER;
    f NUMBER;
BEGIN
    f := 1;
    n := &n;

    IF n = 0 OR n = 1 THEN
        f := 1;
    ELSE
        FOR i IN 1..n LOOP
            f := f * i;
        END LOOP;
    END IF;

    dbms_output.put_line('Factorial is ' || f);
END;
/