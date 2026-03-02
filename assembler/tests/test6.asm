        adj 7

        ; n = 5
        ldc 5
        stl 0          ; local[0] = n

        ; base = &arr
        ldc arr
        stl 3          ; local[3] = base

        ; i = 0
        ldc 0
        stl 1          ; local[1] = i

outer:
        ; if i >= n-1 → done

        ldl 0          ; A = n
        ldc 1
        sub            ; A = n - 1
        ldl 1
        sub            ; A = (n-1) - i
        brlz done
        brz  done

        ; j = 0
        ldc 0
        stl 2          ; local[2] = j

inner:
        ; if j >= n-1-i → next_outer

        ldl 0
        ldc 1
        sub            ; A = n - 1
        ldl 1
        sub            ; A = n - 1 - i
        ldl 2
        sub            ; A = (n-1-i) - j
        brlz next_outer
        brz  next_outer

        ; load a = arr[j]

        ldl 3
        ldl 2
        add
        ldnl 0
        stl 5          ; local[5] = a

        ; load b = arr[j+1]

        ldl 3
        ldl 2
        ldc 1
        add
        add
        ldnl 0
        stl 6          ; local[6] = b

        ; if a <= b → skip swap

        ldl 5
        ldl 6
        sub            ; a - b
        brlz no_swap
        brz  no_swap

        ; arr[j] = b

        ldl 3
        ldl 2
        add
        ldl 6
        stnl 0

        ; arr[j+1] = a

        ldl 3
        ldl 2
        ldc 1
        add
        add
        ldl 5
        stnl 0

no_swap:
        ; j++

        ldl 2
        ldc 1
        add
        stl 2
        br inner

next_outer:
        ; i++

        ldl 1
        ldc 1
        add
        stl 1
        br outer

done:
        HALT
        br done        ; safety trap


; -------- data --------

arr:    data 4
        data 1
        data 5
        data 2
        data 3
