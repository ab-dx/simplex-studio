; DECLARATION OF AUTHORSHIP
; Abhinav Datta 2401CS30

ldc idx
ldnl 0 ; A = idx
ldc arr
add 
ldnl 0; A = arr[idx]

ldc min
stnl 0 ; min = arr[idx]

loop:

; get cur
ldc idx
ldnl 0 ; A = idx
ldc arr
add 
ldnl 0; A = arr[idx]

; compare with min
ldc min
ldnl 0
sub ; A = arr[idx] - min

brlz update
br continue


update:
; update min
ldc idx
ldnl 0 ; A = idx
ldc arr
add 
ldnl 0; A = arr[idx]


ldc min
stnl 0 ; min = arr[idx]

continue:
ldc N
ldc idx
ldnl 0
sub ; A = N - idx
brz exit_loop

ldc idx
ldnl 0
ldc 1
add ; A = idx + 1
ldc idx
stnl 0 ; idx = idx + 1

ldc 0
brz loop

exit_loop:
HALT


; DATA
min:
data 0
idx:
data 0
arr:
data 5
data 4
data 8
data 3
data 1
data 2
N: SET 5
