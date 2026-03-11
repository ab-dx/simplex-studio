ldc ARR
ldnl 0
stl 0
ldc ARR
ldnl 1
ldl 0
sub
brlz SWAP_01
br CONT_01
SWAP_01:
    ldc ARR
    ldnl 1
    ldc ARR
    stnl 0
    ldl 0
    ldc ARR
    stnl 1
CONT_01:

; COMPARE (1,2)
ldc ARR
ldnl 1
stl 0
ldc ARR
ldnl 2
ldl 0
sub
brlz SWAP_12
br CONT_12
SWAP_12:
    ldc ARR
    ldnl 2
    ldc ARR
    stnl 1
    ldl 0
    ldc ARR
    stnl 2
CONT_12:

; COMPARE (2,3)
ldc ARR
ldnl 2
stl 0
ldc ARR
ldnl 3
ldl 0
sub
brlz SWAP_23
br CONT_23
SWAP_23:
    ldc ARR
    ldnl 3
    ldc ARR
    stnl 2
    ldl 0
    ldc ARR
    stnl 3
CONT_23:

; COMPARE (3,4)
ldc ARR
ldnl 3
stl 0
ldc ARR
ldnl 4
ldl 0
sub
brlz SWAP_34
br CONT_34
SWAP_34:
    ldc ARR
    ldnl 4
    ldc ARR
    stnl 3
    ldl 0
    ldc ARR
    stnl 4
CONT_34:

; --- PASS 2: compare (0,1), (1,2), (2,3) ---
ldc ARR
ldnl 0
stl 0
ldc ARR
ldnl 1
ldl 0
sub
brlz SWAP2_01
br CONT2_01
SWAP2_01:
    ldc ARR
    ldnl 1
    ldc ARR
    stnl 0
    ldl 0
    ldc ARR
    stnl 1
CONT2_01:

ldc ARR
ldnl 1
stl 0
ldc ARR
ldnl 2
ldl 0
sub
brlz SWAP2_12
br CONT2_12
SWAP2_12:
    ldc ARR
    ldnl 2
    ldc ARR
    stnl 1
    ldl 0
    ldc ARR
    stnl 2
CONT2_12:

ldc ARR
ldnl 2
stl 0
ldc ARR
ldnl 3
ldl 0
sub
brlz SWAP2_23
br CONT2_23
SWAP2_23:
    ldc ARR
    ldnl 3
    ldc ARR
    stnl 2
    ldl 0
    ldc ARR
    stnl 3
CONT2_23:

; --- PASS 3: compare (0,1), (1,2) ---
ldc ARR
ldnl 0
stl 0
ldc ARR
ldnl 1
ldl 0
sub
brlz SWAP3_01
br CONT3_01
SWAP3_01:
    ldc ARR
    ldnl 1
    ldc ARR
    stnl 0
    ldl 0
    ldc ARR
    stnl 1
CONT3_01:

ldc ARR
ldnl 1
stl 0
ldc ARR
ldnl 2
ldl 0
sub
brlz SWAP3_12
br CONT3_12
SWAP3_12:
    ldc ARR
    ldnl 2
    ldc ARR
    stnl 1
    ldl 0
    ldc ARR
    stnl 2
CONT3_12:

; --- PASS 4: compare (0,1) ---
ldc ARR
ldnl 0
stl 0
ldc ARR
ldnl 1
ldl 0
sub
brlz SWAP4_01
br CONT4_01
SWAP4_01:
    ldc ARR
    ldnl 1
    ldc ARR
    stnl 0
    ldl 0
    ldc ARR
    stnl 1
CONT4_01:

; done
HALT

; --- data region ---
ARR:
data 5
data 1
data 4
data 2
data 3
