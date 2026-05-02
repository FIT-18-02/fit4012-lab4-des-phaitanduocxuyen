#!/bin/bash
# Negative Test: Thay đổi dữ liệu bản mã (Tamper)
# Giải mã một chuỗi bit ngẫu nhiên, kết quả phải ra bản rõ sai
echo "2
1111111111111111111111111111111111111111111111111111111111111111
133457799BBCDFF1" | ./des
