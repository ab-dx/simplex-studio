; HEllo World
; SIMPLEX example program
; Computes: result = (5 + 3) and halts

        ldc 5          ; A = 5
        adc 3          ; A = 8

        stl 0          ; store A at local[0]

        ldl 0          ; load local[0]
        adc 0          ; no-op add, keeps A = 8

        brz end        ; not taken
        br next

next:   ldc 1
        add            ; A = 9 (just to exercise add)

        br done

end:    ldc 0          ; dead code

done:   HALT
;
; ; -------- data section --------
result: data 0
