.data
iArray:     .word 2, 5, 8, 12, 15, 20, 25, 30, 35, 40
iArray_size: .word 10

.text
main:
    la $a0, iArray
    lw $a1, iArray_size
    jal range
    li $v0, 10
    syscall
range:
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    jal max
    move $t0, $v0
    lw $ra, 0($sp)
    addi $sp, $sp, 4

    addi $sp, $sp, -4
    sw $ra, 0($sp)

    jal min
    move $t1, $v0
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    sub $v0, $t0, $t1


    jr $ra

# max function
max:

    lw $a0, 0($a0)  

    lw $a1, 0($a1)  
    lw $t0, 0($a0)
    loop_max:
        addi $a0, $a0, 4  # Move to the next element
        beq $a0, $a1, end_max  # If the end of the array is reached, exit the loop

        lw $t1, 0($a0)  # Load the current element
        bgt $t1, $t0, update_max  
        j loop_max  

    update_max:
        move $t0, $t1  
        j loop_max

    end_max:
        # Return max
        move $v0, $t0
        jr $ra

# min function
min:
    
    lw $a0, 0($a0)  # Assuming the array address is stored in $a0

    lw $a1, 0($a1)  

    lw $t0, 0($a0)

    # Loop through the array to find the minimum value
    loop_min:
        addi $a0, $a0, 4  # Move to the next element
        beq $a0, $a1, end_min  # If the end of the array is reached, exit the loop

        lw $t1, 0($a0)  
        blt $t1, $t0, update_min  # If the current element is less than min, update min

        j loop_min  

    update_min:
        move $t0, $t1  
        j loop_min

    end_min:
        move $v0, $t0
        jr $ra
