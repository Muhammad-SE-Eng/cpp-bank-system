# Bank Account System in C++

A console-based multi-user bank account system written in pure C++. Each user has their own account with PIN login, and all data is saved to local files permanently.

## Features

- Multi-user support (unlimited accounts)
- Create account with name, account number and PIN
- PIN login system with 3 attempts before lockout
- Deposit and withdraw with validation
- Transfer money between accounts (updates both accounts)
- Check balance anytime
- View full transaction history per account
- Change PIN
- Delete account
- Logout and switch between users
- Each account saved in its own file

## Files Generated

Each account generates its own files:
- `accountNumber.txt` stores account details (e.g. `12345.txt`)
- `accountNumber_transactions.txt` stores transaction history (e.g. `12345_transactions.txt`)

## How to Compile and Run

**Compile:**
```bash
g++ bank.cpp -o bank
```

**Run:**
```bash
./bank
```

## Example
--- Bank Account System ---

Create Account
Login
Exit
Choose: 1
Enter your name: Ahmad
Enter account number: 12345
Set a 4-digit PIN: 1234
Account created successfully!

--- Bank Account System ---

Create Account
Login
Exit
Choose: 2
Enter account number: 12345
Enter PIN: 1234
Login successful! Welcome Ahmad

--- Welcome Ahmad ---

View Account
Deposit
Withdraw
Transfer
Check Balance
Transaction History
Change PIN
Delete Account
Logout
Choose: 2
Enter amount to deposit: 5000
Deposited 5000 successfully.

Choose: 4
Enter recipient account number: 67890
Enter amount to transfer: 1000
Transferred 1000 to Ali successfully.

## Transaction History Example
#1 | DEPOSIT | Amount: 5000 | Balance: 5000
#2 | TRANSFER to 67890 | Amount: 1000 | Balance: 4000
#3 | WITHDRAW | Amount: 500 | Balance: 3500

## File Structure
bank-account-system/
├── bank.cpp
└── README.md

Note: .txt files are generated automatically at runtime and should be added to .gitignore.

## .gitignore

Create a `.gitignore` file to avoid pushing account data to GitHub:
*.txt

## License

This project is open source and free to use.
