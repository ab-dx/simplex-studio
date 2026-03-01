; test2.asm
; Test error handling
ldc -5
ldc 08ge ; not a number
ldc ; missing operand
ldc 5, 6; extra on end of line
label:
0def: ; bogus label name
add 5 ; unexpected operand
label: ; duplicate label definition
br nonesuch ; no such label
fibble; bogus mnemonic
0def ; bogus mnemonic
