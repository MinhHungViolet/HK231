.data
prompt: .asciiz "Enter the radius of the circle: "
circumferenceMsg: .asciiz "\nThe circumference of the circle is: "
areaMsg: .asciiz "\nThe area of the circle is: "
pi: .float 3.14159

.text
.globl main
main:
    # Print the prompt message
    li $v0, 4
    la $a0, prompt
    syscall

    # Read the radius from the user
    li $v0, 6
    syscall
    mov.s $f12, $f0

    # Check if the radius is negative or zero
    lwc1 $f2, pi
    c.lt.s $f12, $f2
    bc1t negativeOrZero

    # Calculate the circumference (2 * pi * radius)
    mul.s $f4, $f12, $f2
    add.s $f4, $f4, $f4

    # Print the circumference message
    li $v0, 4
    la $a0, circumferenceMsg
    syscall

    # Print the circumference
    mov.s $f12, $f4
    li $v0, 2
    syscall

    # Calculate the area (pi * radius^2)
    mul.s $f12, $f12, $f12
    mul.s $f12, $f12, $f2

    # Print the area message
    li $v0, 4
    la $a0, areaMsg
    syscall

    # Print the area
    li $v0, 2
    syscall

    # Exit the program
    li $v0, 10
    syscall

negativeOrZero:
    # Print an error message and exit the program
    li $v0, 4
    la $a0, errorMsg
    syscall
    li $v0, 10
    syscall