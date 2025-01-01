a. $a2 = 0+1+2+...+99 = 4950
b.
begin : 3 Instructions
loop :	a1 = 0 : 4
	a1 = 1 : 4
	...
	a1 = 100 : 1
=> IC = 3 + 4*100+1 = 404
=> Clock cycles = 404
c.
addi $a0, $zero, 100 	  	Ox10080000
addi $a1, $zero, 0 		Ox10080004
add $a2, $zero, $zero 		Ox10080008
loop:
beq $a0, $a1, exit		Ox1008000C
add $a2, $a2, $a1			Ox10080010
addi $a1, $a1, 1			Ox10080014
j loop				Ox10080018
exit:

0x1008000 :
	0001 0000 0000 1000 0000 0000 0000
JumpAddr : 0x1008000C
	0001/ 0000 0000 1000 0000 0000 0000 11/00
Mã máy của lệnh j loop :
	000010 0000 0000 1000 0000 0000 0000 11 
= Ox08020003
