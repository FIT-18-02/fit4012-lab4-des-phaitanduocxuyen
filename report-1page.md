    # Report 1 page - Lab 4 DES / TripleDES

## Mục tiêu

- Phân tích quy trình hoạt động chi tiết của thuật toán DES thông qua việc sinh khóa vòng và mạng Feistel.

- Hoàn thiện chương trình mã hóa DES để hỗ trợ nhập liệu từ bàn phím, xử lý nhiều khối dữ liệu (multi-block) và thực hiện Zero Padding.

- Xây dựng chức năng giải mã DES và mở rộng hệ thống lên thuật toán TripleDES (3DES) theo quy trình EDE.

- Quản lý dự án chuyên nghiệp thông qua cấu trúc repo chuẩn GitHub, tích hợp CI và hệ thống kiểm thử tự động.

## Cách làm / Method

- Phát triển dựa trên nền tảng: Sử dụng file des.cpp gốc, giữ lại các hàm trợ giúp (XOR, chuyển đổi nhị phân) và các bảng hoán vị chuẩn.

- Bổ sung chức năng nhập liệu (Q2): Chỉnh sửa hàm main để đọc mode, plaintext và key từ stdin thay vì gán cứng, đồng thời thêm logic chia khối 64-bit và thêm số 0 vào cuối khối nếu thiếu (Zero Padding).

- Hoàn thiện giải mã (Q3): Viết hàm giải mã bằng cách tái sử dụng logic mã hóa nhưng đảo ngược thứ tự 16 khóa vòng (từ khóa 16 về khóa 1).

- Xây dựng TripleDES (Q4): Thiết lập quy trình EDE bằng cách gọi liên tiếp: Mã hóa (K1) -> Giải mã (K2) -> Mã hóa (K3).

- Cấu trúc chương trình: Tổ chức theo mô hình hướng đối tượng với các Class KeyGenerator (sinh khóa) và DES (xử lý khối dữ liệu) để đảm bảo tính module hóa.
## Kết quả / Result

- Đúng giao kèo (Submission Contract): Chương trình phản hồi chính xác theo 4 chế độ (1: DES Enc, 2: DES Dec, 3: 3DES Enc, 4: 3DES Dec).

- Xử lý đa khối: Mã hóa thành công các chuỗi nhị phân dài (ví dụ: 128-bit hoặc hơn) bằng cách chia block và ghép kết quả ciphertext cuối cùng.

- Kiểm thử (Tests): Vượt qua các bài test quan trọng như:

    + Round-trip: Mã hóa rồi giải mã khôi phục đúng bản rõ ban đầu.

    + Padding test: Khối cuối không đủ 64-bit vẫn được xử lý chính xác.

    + Negative test: Nhận diện trường hợp sai khóa hoặc dữ liệu bị can thiệp (tamper).

- Minh chứng: Toàn bộ lịch sử chạy test và kết quả đầu ra được lưu trữ đầy đủ trong thư mục logs/.
## Kết luận / Conclusion

- Điều học được: Hiểu sâu về cấu trúc mật mã khối, vai trò của các hộp S-box và tầm quan trọng của việc đảo ngược khóa trong giải mã đối xứng.

- Hạn chế: Thuật toán DES có độ dài khóa thực tế ngắn (56-bit), dễ bị tấn công vét cạn trong môi trường tính toán hiện đại.

- Hướng mở rộng: Đã hoàn thành việc tích hợp TripleDES để tăng cường bảo mật và xử lý multi-block để ứng dụng cho các tập tin dữ liệu lớn thay vì chỉ các khối đơn lẻ.