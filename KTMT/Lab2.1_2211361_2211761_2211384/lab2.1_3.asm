.data 
a: .word 0
b: .word 0
c: .word 0
d: .word 0
f: .asciiz "f(x) = "
newline: .asciiz "\n"
.text
.globl main
main: 
li $v0, 5
syscall
sw $v0, a
li $v0, 5
syscall
sw $v0, b
li $v0, 5
syscall
sw $v0, c
li $v0, 5
syscall
sw $v0, d
li $v0, 5
syscall
sw $v0, x
lw $t0, a
lw $t1, x
mul $t0, $t0, $t1
lw $t2, b
add $t0, $t0, $t2
mul $t0, $t0, $t1
lw $t2, c
sub $t0, $t0, $t2
mul $t0, $t0, $t1
lw $t2, d
sub $s0, $t0, $t2
li $v0, 4
la $a0, f
syscall
li $v0, 1
move $a0, $s0
syscall
li $v0, 4
la $a0, newline 
syscall
li $v0, 10 
syscall
