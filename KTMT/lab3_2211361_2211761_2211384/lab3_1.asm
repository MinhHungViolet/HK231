.data
    str1:    .asciiz "Computer Science and Engineering, HCMUT"
    str2:    .asciiz "Computer Architecture 2022"
.text
    # Giả sử thanh ghi $a chứa giá trị của 'a'

    # Kiểm tra a % 2 = 0
    div $a, $zero      # Chia $a cho 2
    mfhi $t0           # Lấy phần dư (phần dư trong $t0)
    
    # So sánh phần dư với 0
    beq $t0, $zero, even  # Nếu phần dư là 0, nhảy tới nhãn 'even'
    j odd              # Nếu phần dư không phải là 0, nhảy tới nhãn 'odd'

even:
    # In chuỗi cho trường hợp a là số chẵn
li $v0, 4
la $a0, str1
syscall
j end

odd:
    # In chuỗi cho trường hợp a là số lẻ
li $v0, 4
la $a0, str2
Syscall

end:
