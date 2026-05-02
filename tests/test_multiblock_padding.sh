#!/bin/bash
# Kiểm tra tính năng chia khối và bù bit 0 (Zero Padding)
# Nhập một chuỗi không đủ 64 bit (ví dụ 16 bit)
echo "1
1010101010101010
133457799BBCDFF1" | ./des
