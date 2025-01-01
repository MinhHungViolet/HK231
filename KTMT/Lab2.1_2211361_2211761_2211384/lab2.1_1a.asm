.data
.text

# nhap gia tri a
li $v0 , 5
syscall
move $s1, $v0

# nhap gia tri b
li $v0 , 5
syscall
move $s2, $v0

# nhap gia tri c
li $v0 , 5
syscall
move $s3, $v0

sub $s0, $s1, $s2
sub $s0, $s0, $s3
