#Chuong trinh lab5_3: Tim min, max
#-----------------------------------
# Data segment
.data
#Cac dinh nghia bien 
array: .float 3.0, 1.5, 4.2, 2.8, 5.6, 7.2, 6.1, 8.9, 10.0, 9.3, 12.5, 11.7, 14.8, 13.2, 15.6, 17.2, 16.4, 19.0, 23.3, 20.0
length: .word 20
#Cac cau nhac nhap du lieu 
printMin: .asciiz " \n min "    
printMax: .asciiz " \n max "
#----------------------------------- 
# Code segment
.text
.globl main
#-----------------------------------
#Chuong trinh chinh
#----------------------------------- 
main:
    # Initialize pointers and counters
    la $a0, array     # Load address of the array
    lw $t1, length     # Load length of the array

    # Initialize min and max values
    lwc1 $f0, 0($a0)      # Set $f0 to the first element of the array
    lwc1 $f2, 0($a0)      # Set $f2 to the first element of the array

    loop:
        # Load the current element into $f4
        lwc1 $f4, 0($a0)

        # Compare with the current min value
        c.lt.s $f4, $f0
        bc1t update_min
        # Compare with the current max value
        c.lt.s $f2, $f4
        bc1t update_max
	j next_iteration
    update_min:
        # Update min value
        mov.s $f0, $f4

    update_max:
        # Update max value
        mov.s $f2, $f4
    next_iteration:
        # Move to the next element
        addi $a0, $a0, 4
        addi $t1, $t1, -1
        bnez $t1, loop

    # Print the results
    addi    $v0, $0, 4
    la      $a0, printMin
    syscall
    li $v0, 2
    mov.s $f12, $f0
    syscall
    addi    $v0, $0, 4
    la      $a0, printMax
    syscall
    li $v0, 2
    mov.s $f12, $f2
    syscall

    # Exit
    li $v0, 10
    syscall