.data
    num1: .word 200000
    num2: .word 4000
    num3: .word 700

.text
    la $t0, num1      # Load address of num1 into $t0
    lw $t1, 0($t0)    # Load word from address in $t0 into $t1
    la $t0, num2      # Load address of num2 into $t0
    lw $t2, 0($t0)    # Load word from address in $t0 into $t2
    add $t1, $t1, $t2 # Add $t1 and $t2, store result in $t1

    la $t0, num3      # Load address of num3 into $t0
    lw $t2, 0($t0)    # Load word from address in $t0 into $t2
    sub $s0, $t1, $t2 # Subtract $t2 from $t1, store result in $s0

    li $v0, 1         # system call code for print_int
    move $a0, $s0     # move the result from $s0 to $a0
    syscall           # make the system call