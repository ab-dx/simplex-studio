outer_loop:
    ; Initialize pos = 0 
    ldc 0
    ldc pos
    stnl 0

    ; Initialize isSorted = 1 
    ldc 1
    ldc isSorted
    stnl 0

inner_loop:
    ; Stop if pos == 4
    ldc pos
    ldnl 0
    ldc 4
    sub 
    brz end_inner_loop

    ; Load arr[pos] into temp 
    ldc pos
    ldnl 0
    ldc arr
    add 
    ldnl 0      ; A = arr[pos]

    ldc temp
    stnl 0      ; temp = arr[pos]

    ; Load arr[pos+1] 
    ldc pos
    ldnl 0
    ldc 1
    add
    ldc arr
    add
    ldnl 0      ; A = arr[pos+1]

    ;  Compare them 
    ldc temp
    ldnl 0      ; A = arr[pos], B = arr[pos+1]
    sub         ; arr[pos] - arr[pos+1]
    brlz skip_swap
    brz skip_swap

swap:
    ;  Write arr[pos+1] into arr[pos] 
    ; Calculate addr(arr[pos]) and save to ptr
    ldc pos
    ldnl 0
    ldc arr
    add         ; A = addr(arr[pos])
    
    ldc ptr
    stnl 0      ; ptr = addr(arr[pos])

    ; Load arr[pos+1] back into A
    ldc pos
    ldnl 0
    ldc 1
    add
    ldc arr
    add
    ldnl 0      ; A = arr[pos+1]
    
    ; Load our pointer and store!
    ldc ptr
    ldnl 0      ; A = addr(arr[pos]), B = arr[pos+1]
    stnl 0      ; arr[pos] = arr[pos+1]

    ;  Write temp (original arr[pos]) into arr[pos+1] 
    ; Calculate addr(arr[pos+1]) and save to ptr
    ldc pos
    ldnl 0
    ldc 1
    add
    ldc arr
    add         ; A = addr(arr[pos+1])
    
    ldc ptr
    stnl 0      ; ptr = addr(arr[pos+1])

    ; Load temp back into A
    ldc temp
    ldnl 0      ; A = original arr[pos]
    
    ; Load our pointer and store!
    ldc ptr
    ldnl 0      ; A = addr(arr[pos+1]), B = original arr[pos]
    stnl 0      ; arr[pos+1] = original arr[pos]

    ;  Mark isSorted = 0 (False) 
    ldc 0
    ldc isSorted
    stnl 0

skip_swap:
    ;  Increment pos 
    ldc pos
    ldnl 0
    ldc 1
    add         ; A = pos + 1
    ldc pos     
    stnl 0      ; pos = pos + 1

    br inner_loop

end_inner_loop:
    ;  Check if the pass was clean 
    ldc isSorted
    ldnl 0
    ldc 1
    sub
    brz end_sort ; If isSorted == 1, array is sorted!

    ; Otherwise, run another pass
    br outer_loop

end_sort:
    HALT

;  DATA SECTION 
arr:
data 5
data 1
data 3
data 4
data 2

pos:
data 0
isSorted:
data 0
temp:
data 0
ptr:
data 0
