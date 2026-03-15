; DECLARATION OF AUTHORSHIP
; Abhinav Datta 2401CS30

outer_loop:
    ; pos = 0 
    ldc 0
    ldc pos
    stnl 0

    ; isSorted = 1 
    ldc 1
    ldc isSorted
    stnl 0

inner_loop:
    ; stop if pos == 4
    ldc pos
    ldnl 0
    ldc 4
    sub 
    brz end_inner_loop

    ; temp = arr[pos]
    ldc pos
    ldnl 0
    ldc arr
    add 
    ldnl 0      ; A = arr[pos]

    ldc temp
    stnl 0      ; temp = arr[pos]

    ; A = arr[pos+1] 
    ldc pos
    ldnl 0
    ldc 1
    add
    ldc arr
    add
    ldnl 0      ; A = arr[pos+1]

    ; compare 
    ldc temp
    ldnl 0      ; A = arr[pos], B = arr[pos+1]
    sub         ; A = arr[pos+1] - arr[pos]
    brlz swap
    brz skip_swap

skip_swap:
    ; pos++
    ldc pos
    ldnl 0
    ldc 1
    add         ; A = pos + 1
    ldc pos     
    stnl 0      ; pos = pos + 1

    br inner_loop

swap:
    ; ptr = addr(arr[pos])
    ; arr[pos] = arr[pos+1]
    ldc pos
    ldnl 0
    ldc arr
    add         ; A = addr(arr[pos])
    
    ldc ptr
    stnl 0      ; ptr = addr(arr[pos])

    ; A = arr[pos+1]
    ldc pos
    ldnl 0
    ldc 1
    add
    ldc arr
    add
    ldnl 0      ; A = arr[pos+1]
    
    ; arr[pos] = arr[pos+1]
    ldc ptr
    ldnl 0      ; A = addr(arr[pos]), B = arr[pos+1]
    stnl 0      ; arr[pos] = arr[pos+1]

    ;  arr[pos+1] = temp
    ; ptr = addr(arr[pos+1])
    ldc pos
    ldnl 0
    ldc 1
    add
    ldc arr
    add         ; A = addr(arr[pos+1])
    
    ldc ptr
    stnl 0      ; ptr = addr(arr[pos+1])

    ; A = temp
    ldc temp
    ldnl 0      ; A = original arr[pos]
    
    ; arr[pos+1] = original arr[pos]
    ldc ptr
    ldnl 0      ; A = addr(arr[pos+1]), B = original arr[pos]
    stnl 0      ; arr[pos+1] = original arr[pos]

    ;  isSorted = 0  
    ldc 0
    ldc isSorted
    stnl 0

end_inner_loop:
    ;  check isSorted == 1 ? 
    ldc isSorted
    ldnl 0
    ldc 1
    sub
    brz end_sort ; if isSorted == 1, array is sorted

    ; otherwise, run another pass
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
