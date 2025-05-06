# bai-tap-lon-C

# Hệ thống Đăng nhập, Đăng ký và Quản lý Ví Điểm Thưởng

## Mô tả
- Đăng ký, đăng nhập tài khoản với phân quyền (user, admin)
- Quản lý ví điểm thưởng, chuyển điểm giữa các ví
- OTP xác thực các thao tác quan trọng
- Lưu trữ, backup, phục hồi dữ liệu
- Hash mật khẩu bảo mật

## Cấu trúc thư mục
```
login/
├── main.cpp
├── UserAccount.h / UserAccount.cpp
├── UserManager.h / UserManager.cpp
├── Wallet.h / Wallet.cpp
├── WalletManager.h / WalletManager.cpp
├── Transaction.h / Transaction.cpp
├── TransactionManager.h / TransactionManager.cpp
├── OTPManager.h / OTPManager.cpp
├── Hash.h / Hash.cpp
├── utils.h / utils.cpp
├── data/
│   ├── users.dat
│   ├── wallets.dat
│   ├── transactions.dat
│   └── backup/
│       ├── users_backup.dat
│       ├── wallets_backup.dat
│       └── transactions_backup.dat
└── README.md
```

## Build
```sh
g++ -std=c++17 main.cpp UserAccount.cpp UserManager.cpp Wallet.cpp WalletManager.cpp Transaction.cpp TransactionManager.cpp OTPManager.cpp Hash.cpp utils.cpp -o login
```

## Chạy
```sh
./login
```

## Chức năng chính
- Đăng ký, đăng nhập, đổi mật khẩu
- Quản lý ví, chuyển điểm, xem lịch sử giao dịch
- OTP xác thực
- Backup, phục hồi dữ liệu

## Backup & Phục hồi
- Dữ liệu tự động backup trước khi ghi đè
- Có thể phục hồi từ file backup trong thư mục `data/backup/`

## Lưu ý
- Mật khẩu được hash bằng SHA-256
- OTP là mã 6 số, hiệu lực 5 phút
- Không thay đổi username sau khi tạo

## Liên hệ
- Tác giả: [Tên bạn]
