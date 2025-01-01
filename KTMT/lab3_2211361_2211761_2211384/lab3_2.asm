# Giả sử a, b, c được lưu trong thanh ghi $s0, $s1, $s2 tương ứng
# và kết quả được lưu trong thanh ghi $s0

# So sánh a với -3
slt $t0, $s0, -3
bne $t0, $zero, greater_than_minus_3
# So sánh a với 7
slt $t1, $s0, 7
bge $t1, $zero, greater_than_minus_3
move $t2, $s1
move $t3, $s2
mul $s0, $t2, $t3
j end_if_else

greater_than_minus_3:
move $t2, $s1
move $t3, $s2
add $s0, $t2, $t3

end_if_else:
# Kết thúc
