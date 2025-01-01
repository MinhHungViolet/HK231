# Giả sử input được lưu trong thanh ghi $s0, a trong thanh ghi $s1, b trong thanh ghi $s2, c trong thanh ghi $s3


li $s2, 100
li $s3, 2


li $v0, 4       # System call để in chuỗi
la $a0, input_prompt   # Địa chỉ của chuỗi câu hỏi
syscall
li $v0, 5       
syscall
move $s0, $v0   
beq $s0, 1, case_1
beq $s0, 2, case_2
beq $s0, 3, case_3
beq $s0, 4, case_4
j default_case

case_1:
  add $s1, $s2, $s3
  j end_switch

case_2:
  sub $s1, $s2, $s3
  j end_switch

case_3:
  mul $s1, $s2, $s3
  j end_switch

case_4:
  div $s2, $s3
  mflo $s1  # lấy kết quả từ thanh ghi lo
  j end_switch

default_case:
  li $s1, 0

end_switch:
input_prompt: .asciiz "Nhập giá trị (1-4): "
