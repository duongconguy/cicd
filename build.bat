@echo off
g++ -o wallet_system.exe main.cpp UserAccount.cpp UserManager.cpp Wallet.cpp WalletManager.cpp Transaction.cpp TransactionManager.cpp OTPManager.cpp Hash.cpp utils.cpp -static-libstdc++ -static-libgcc
if %errorlevel% equ 0 (
    echo Compilation successful!
    echo Running the program...
    wallet_system.exe
) else (
    echo Compilation failed!
    pause
) 