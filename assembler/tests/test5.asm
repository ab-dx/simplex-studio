        adj 4

        ; load base = address of pad (we know pad is after code)
        ldc pad
        stl 0

        ; compute base + 0 and write value 99 there via stnl
        ldl 0
        ldl 0
        add
        ldc 99
        stnl 0

        HALT
pad:    data 0
