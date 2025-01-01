.data
array: .word 1, 1, 0, 4, 1, 7, 0, 1, 0, 4

.text
main:
    la $t0, array      # Load base address of array into $t0

    lw $t1, 16($t0)    # Load 4th element into $t1
    lw $t2, 24($t0)    # Load 6th element into $t2

    sub $t3, $t1, $t2  # Subtract 6th element from 4th element

    move $a0, $t3      # Move result to $a0 for printing
    li $v0, 1          # Load syscall number for print_int
    syscall             # Call the system to print

    li $v0, 10         # Load syscall number for exit
    syscall             # Call the system to exit