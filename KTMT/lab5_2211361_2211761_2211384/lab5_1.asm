Bài 1:
(a) Để xác định giá trị số thực được chứa trong thanh ghi có nội dung 0xCA202000, 
ta cần phân tích nội dung này thành ba phần: bit dấu, phần mũ và phần định trị. 
Theo chuẩn IEEE 754, số thực dạng đơn (single) được biểu diễn bằng 32 bit, trong đó bit đầu tiên là bit dấu, 
8 bit tiếp theo là phần mũ và 23 bit cuối cùng là phần định trị. Do đó, ta có:

Bit dấu: 1
Phần mũ: 10100010
Phần định trị: 01000000000000000000000
Giá trị số thực được tính theo công thức:
X=(−1)^S×(1+M)×2^(E−127)
Trong đó:

S là bit dấu
M là giá trị thập phân của phần định trị
E là giá trị thập phân của phần mũ

Áp dụng công thức, ta được:
X=(−1)^1×(1+0.25)×2^(162−127)
X=−1.25×235
X≈−4.295×1010

(b) Để xác định nội dung thanh ghi mà giá trị số thực của nó là 36.15625, 
ta cần biểu diễn số này dưới dạng nhị phân và tách ra thành ba phần: 
bit dấu, phần mũ và phần định trị. Theo chuẩn IEEE 754, số thực dạng đơn (single) được biểu diễn bằng 32 bit, 
trong đó bit đầu tiên là bit dấu, 8 bit tiếp theo là phần mũ và 23 bit cuối cùng là phần định trị1. Do đó, ta có:

Bit dấu: 0 (vì số dương)
Phần mũ: 10000100 (vì 36.15625=1.12578125×25 và 5+127=132=10000100)
Phần định trị: 00100000011110101110000 (vì 1.12578125−1=0.12578125=0.0010000001111010111)

Nội dung thanh ghi là:
0 10000100 00100000011110101110000
(c) Không thể biểu diễn chính xác giá trị 20.2 ở dạng IEEE, vì 20.2 là một số thập phân vô hạn trong hệ nhị phân2. 
Nếu biểu diễn 20.2 bằng số thực dạng đơn (single) theo chuẩn IEEE 754, 
ta sẽ bị làm tròn ở bit thứ 23 của phần định trị, dẫn đến sai số. 
Khoảng cách giữa hai số thực liên tiếp (biểu diễn được bằng IEEE 754) không bằng nhau, 
vì nó phụ thuộc vào giá trị của phần mũ3. Càng gần 0, khoảng cách càng nhỏ, và càng xa 0, 
khoảng cách càng lớn. Đây là một đặc điểm của cách biểu diễn dấu phẩy động, cho phép biểu diễn một tầm giá trị rộng hơn so với dấu phẩy tĩnh
