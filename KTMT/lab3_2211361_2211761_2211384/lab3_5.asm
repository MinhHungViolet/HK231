.data
charArray: .asciiz "Computer Architecture CSE_HCMUT"

.text
.globl main
main:
    la $t1, charArray     # Load address of charArray into $t1
    li $t0, 0             # Initialize $t0 to 0

loop:
    lb $t2, 0($t1)        # Load byte at address $t1 into $t2
    beq $t2, 'r', found   # If $t2 == 'r', branch to found
    beq $t2, '\0', notfound # If $t2 == '\0', branch to notfound
    addi $t0, $t0, 1      # Increment $t0
    addi $t1, $t1, 1      # Increment $t1 to point to the next character
    j loop                # Jump to the start of the loop

found:
    move $a0, $t0         # Move $t0 to $a0 for printing
    li $v0, 1             # Load syscall service number for print_int
    syscall               # Call syscall
    j end                 # Jump to end

notfound:
    li $a0, -1            # Load -1 into $a0 for printing
    li $v0, 1             # Load syscall service number for print_int
    syscall               # Call syscall

end:
    # Exit the program
    li $v0, 10            # Load syscall service number for exit
    syscall               # Call syscall