SET SERVEROUTPUT ON

DECLARE
    i NUMBER;
    j NUMBER;
    temp NUMBER;

BEGIN
    FOR i IN 2..100 LOOP
        temp := 1;

        FOR j IN 2..TRUNC(i/2) LOOP
            IF MOD(i, j) = 0 THEN
                temp := 0;
                EXIT;     
            END IF;
        END LOOP;

        IF temp = 1 THEN
            dbms_output.put_line(i);
        END IF;
    END LOOP;
END;
/