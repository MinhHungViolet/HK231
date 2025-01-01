.data
cArray: .asciiz "Computer Architecture 2022"
cArray_size: .word 26

.text
.globl main
main:
    la $a0, cArray        # Load address of cArray into $a0
    lw $a1, cArray_size   # Load cArray_size into $a1
    jal reverse           # Call reverse function

    # Print the reversed string
    move $a0, $t0         # Move the address of the reversed string to $a0
    li $v0, 4             # Load syscall service number for print_string
    syscall               # Call syscall

    # Exit the program
    li $v0, 10            # Load syscall service number for exit
    syscall               # Call syscall

reverse:
    move $t0, $a0         # Copy base address of cArray to $t0
    move $t1, $a1         # Copy cArray_size to $t1
    li $t2, 0             # Initialize $t2 to 0 (for i)

loop:
    srl $t3, $t1, 1       # $t3 = cArray_size / 2
    slt $t4, $t2, $t3     # If $t2 < $t3, set $t4 to 1
    beq $t4, $zero, end   # If $t4 == 0, branch to end

    add $t5, $t0, $t2     # $t5 = base address + i
    lb $t6, 0($t5)        # Load byte at address $t5 into $t6 (temp)

    sub $t7, $t1, $t2     # $t7 = cArray_size - i
    addi $t7, $t7, -1     # $t7 = $t7 - 1
    add $t8, $t0, $t7     # $t8 = base address + (cArray_size - 1 - i)
    lb $t9, 0($t8)        # Load byte at address $t8 into $t9

    sb $t9, 0($t5)        # Store $t9 at address $t5
    sb $t6, 0($t8)        # Store $t6 at address $t8

    addi $t2, $t2, 1      # Increment $t2
    j loop                # Jump to the start of the loop

end:
    jr $ra                # Return from function