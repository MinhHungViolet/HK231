.data
str1: .asciiz "invalid input"

.text
main:
    # Kiểm tra n < 0
    slt $t0, $zero, n
    beq $t0, $zero, check_zero

    # Nếu n < 0, trả về chuỗi "invalid input"
li $v0, 4
la $a0, str1
    syscall
    j end_program

check_n:
    # Kiểm tra n == 0
    beq n, $zero, return_zero

    # Kiểm tra n == 1
    beq n, $t1, return_one

    # Nếu không phải cả hai trường hợp trên, bắt đầu tính toán dãy Fibonacci
    li $t2, 0        # f(0)
    li $t3, 1        # f(1)

    # Vòng lặp tính f(i) cho i = 2 đến n
    li $t4, 2        # i = 2
    loop:
        bge $t4, n, end_loop   # Nếu i >= n, thoát khỏi vòng lặp

        add $t5, $t2, $t3       # f(i) = f(i-1) + f(i-2)
        move $t2, $t3           # f(i-2) = f(i-1)
        move $t3, $t5           # f(i-1) = f(i)

        addi $t4, $t4, 1        # Tăng i lên 1
        j loop

    end_loop:
        move $v0, $t3   # Kết quả là f(n)
        j end_program

return_zero:
    li $v0, 0        # Trả về 0 nếu n == 0
    j end_program

return_one:
    li $v0, 1        # Trả về 1 nếu n == 1
    j end_program

end_program:
li $v0, 10
syscall
