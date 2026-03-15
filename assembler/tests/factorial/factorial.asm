; DECLARATION OF AUTHORSHIP
; Abhinav Datta 2401CS30

fact_loop:
    ;  end if n == 0 
    ldc n
    ldnl 0
    brz end_fact

    ;  prod = 0
    ldc 0
    ldc prod
    stnl 0

    ;  mul_a = result
    ldc result
    ldnl 0
    ldc mul_a
    stnl 0

    ;  mul_b = n
    ldc n
    ldnl 0
    ldc mul_b
    stnl 0

mul_loop:
    ;  stop if mul_b == 0 
    ldc mul_b
    ldnl 0
    brz end_mul

    ;  prod = prod + mul_a 
    ldc prod
    ldnl 0      ; A = prod
    ldc mul_a
    ldnl 0      ; A = mul_a 
    add         ; A = mul_a + prod
    ldc prod    
    stnl 0      ; prod = B

    ;  mul_b = mul_b - 1 
    ldc mul_b
    ldnl 0      ; A = mul_b
    ldc 1       
    sub         ; A = mul_b - 1
    ldc mul_b   
    stnl 0      ; mul_b = mul_b - 1

    br mul_loop

end_mul:
    ;  result = prod 
    ldc prod
    ldnl 0
    ldc result
    stnl 0

    ;  n = n - 1 
    ldc n
    ldnl 0      
    ldc 1       
    sub         ; A = n - 1
    ldc n       
    stnl 0      ; n = n - 1

    br fact_loop

end_fact:
    HALT

; DATA 
n:
data 5      
result:
data 1      
mul_a:
data 0
mul_b:
data 0
prod:
data 0
