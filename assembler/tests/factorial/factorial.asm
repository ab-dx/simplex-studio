; DECLARATION OF AUTHORSHIP
; Abhinav Datta 2401CS30

fact_loop:
    ;  Stop if n == 0 
    ldc n
    ldnl 0
    brz end_fact

    ;  Setup Multiplication (prod = 0) 
    ldc 0
    ldc prod
    stnl 0

    ;  Setup Multiplication (mul_a = result) 
    ldc result
    ldnl 0
    ldc mul_a
    stnl 0

    ;  Setup Multiplication (mul_b = n) 
    ldc n
    ldnl 0
    ldc mul_b
    stnl 0

mul_loop:
    ;  Stop adding if mul_b == 0 
    ldc mul_b
    ldnl 0
    brz end_mul

    ;  prod = prod + mul_a 
    ldc prod
    ldnl 0      ; A = prod
    ldc mul_a
    ldnl 0      ; A = mul_a, B = prod
    add         ; A = mul_a + prod
    ldc prod    ; A = addr(prod), B = mul_a + prod
    stnl 0      ; prod = B

    ;  mul_b = mul_b - 1 
    ldc mul_b
    ldnl 0      ; A = mul_b
    ldc 1       ; A = 1, B = mul_b
    sub         ; A = B - A (mul_b - 1)
    ldc mul_b   ; A = addr(mul_b), B = mul_b - 1
    stnl 0      ; mul_b = B

    br mul_loop

end_mul:
    ;  result = prod 
    ldc prod
    ldnl 0
    ldc result
    stnl 0

    ;  n = n - 1 
    ldc n
    ldnl 0      ; A = n
    ldc 1       ; A = 1, B = n
    sub         ; A = B - A (n - 1)
    ldc n       ; A = addr(n), B = n - 1
    stnl 0      ; n = B

    br fact_loop

end_fact:
    HALT

;  DATA SECTION 
n:
data 5      ; Number to calculate factorial for
result:
data 1      ; Running product (starts at 1)

; Variables for multiplication
mul_a:
data 0
mul_b:
data 0
prod:
data 0
