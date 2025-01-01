.data
    str: .asciiz "2211361 - Ho Minh Hung"
.text
    la $t0, str
    move $t1, $t0

    # Calculate the length of the string
    len_loop:
        lb $t2, 0($t1)
        beqz $t2, end_len_loop
        addiu $t1, $t1, 1
        j len_loop
    end_len_loop:

    # Swap the first and last characters
    subu $t1, $t1, 1
    lb $t2, 0($t0)
    lb $t3, 0($t1)
    sb $t2, 0($t1)
    sb $t3, 0($t0)

    la $a0, str
    li $v0, 4
    syscall
