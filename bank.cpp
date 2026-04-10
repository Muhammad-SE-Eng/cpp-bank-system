#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Account{
    string name;
    string pin;
    int accountNumber;
    double balance;
    int transactionCount;
};

void saveAccount(Account acc){
    ofstream file(to_string(acc.accountNumber)+".txt");
    file<<acc.name<<"\n"<<acc.accountNumber<<"\n"<<acc.balance<<"\n"<<acc.pin<<"\n"<<acc.transactionCount;
    file.close();
}

bool accountExists(int accountNumber){
    ifstream file(to_string(accountNumber)+".txt");
    return file.is_open();
}

Account loadAccount(int accountNumber){
    Account acc;
    ifstream file(to_string(accountNumber)+".txt");
    if(file.is_open()){
        file>>acc.name>>acc.accountNumber>>acc.balance>>acc.pin>>acc.transactionCount;
        file.close();
    }
    return acc;
}

void logTransaction(int accountNumber,string type,double amount,double balance,int count){
    ofstream log(to_string(accountNumber)+"_transactions.txt",ios::app);
    log<<"#"<<count<<" | "<<type<<" | Amount: "<<amount<<" | Balance: "<<balance<<"\n";
    log.close();
}

void createAccount(){
    Account acc;
    cout<<"Enter your name: ";
    cin>>acc.name;
    cout<<"Enter account number: ";
    cin>>acc.accountNumber;
    if(accountExists(acc.accountNumber)){
        cout<<"Account number already exists."<<endl;
        return;
    }
    cout<<"Set a 4-digit PIN: ";
    cin>>acc.pin;
    acc.balance=0.0;
    acc.transactionCount=0;
    saveAccount(acc);
    cout<<"Account created successfully!"<<endl;
}

bool login(Account &acc){
    int accountNumber;
    string pin;
    cout<<"Enter account number: ";
    cin>>accountNumber;
    if(!accountExists(accountNumber)){
        cout<<"Account not found."<<endl;
        return false;
    }
    acc=loadAccount(accountNumber);
    int tries=3;
    while(tries>0){
        cout<<"Enter PIN: ";
        cin>>pin;
        if(pin==acc.pin){
            cout<<"Login successful! Welcome "<<acc.name<<endl;
            return true;
        }
        tries--;
        cout<<"Wrong PIN. "<<tries<<" attempts left."<<endl;
    }
    cout<<"Account locked. Too many wrong attempts."<<endl;
    return false;
}

void deposit(Account &acc){
    double amount;
    cout<<"Enter amount to deposit: ";
    cin>>amount;
    if(amount<=0){
        cout<<"Invalid amount."<<endl;
        return;
    }
    acc.balance+=amount;
    acc.transactionCount++;
    saveAccount(acc);
    logTransaction(acc.accountNumber,"DEPOSIT",amount,acc.balance,acc.transactionCount);
    cout<<"Deposited "<<amount<<" successfully."<<endl;
}

void withdraw(Account &acc){
    double amount;
    cout<<"Enter amount to withdraw: ";
    cin>>amount;
    if(amount<=0){
        cout<<"Invalid amount."<<endl;
        return;
    }
    if(amount>acc.balance){
        cout<<"Insufficient balance."<<endl;
        return;
    }
    acc.balance-=amount;
    acc.transactionCount++;
    saveAccount(acc);
    logTransaction(acc.accountNumber,"WITHDRAW",amount,acc.balance,acc.transactionCount);
    cout<<"Withdrawn "<<amount<<" successfully."<<endl;
}

void transfer(Account &acc){
    int toAccountNumber;
    double amount;
    cout<<"Enter recipient account number: ";
    cin>>toAccountNumber;
    if(!accountExists(toAccountNumber)){
        cout<<"Recipient account not found."<<endl;
        return;
    }
    if(toAccountNumber==acc.accountNumber){
        cout<<"Cannot transfer to your own account."<<endl;
        return;
    }
    cout<<"Enter amount to transfer: ";
    cin>>amount;
    if(amount<=0){
        cout<<"Invalid amount."<<endl;
        return;
    }
    if(amount>acc.balance){
        cout<<"Insufficient balance."<<endl;
        return;
    }
    Account recipient=loadAccount(toAccountNumber);
    acc.balance-=amount;
    acc.transactionCount++;
    recipient.balance+=amount;
    recipient.transactionCount++;
    saveAccount(acc);
    saveAccount(recipient);
    logTransaction(acc.accountNumber,"TRANSFER to "+to_string(toAccountNumber),amount,acc.balance,acc.transactionCount);
    logTransaction(toAccountNumber,"TRANSFER from "+to_string(acc.accountNumber),amount,recipient.balance,recipient.transactionCount);
    cout<<"Transferred "<<amount<<" to "<<recipient.name<<" successfully."<<endl;
}

void checkBalance(Account acc){
    cout<<"Current balance: "<<acc.balance<<endl;
}

void displayAccount(Account acc){
    cout<<"Name: "<<acc.name<<endl;
    cout<<"Account Number: "<<acc.accountNumber<<endl;
    cout<<"Balance: "<<acc.balance<<endl;
    cout<<"Total Transactions: "<<acc.transactionCount<<endl;
}

void viewTransactions(Account acc){
    ifstream file(to_string(acc.accountNumber)+"_transactions.txt");
    if(!file.is_open()){
        cout<<"No transactions found."<<endl;
        return;
    }
    string line;
    cout<<"\n--- Transaction History ---"<<endl;
    while(getline(file,line)){
        cout<<line<<endl;
    }
    file.close();
}

void changePin(Account &acc){
    string oldPin,newPin;
    cout<<"Enter current PIN: ";
    cin>>oldPin;
    if(oldPin!=acc.pin){
        cout<<"Wrong PIN."<<endl;
        return;
    }
    cout<<"Enter new PIN: ";
    cin>>newPin;
    acc.pin=newPin;
    saveAccount(acc);
    cout<<"PIN changed successfully."<<endl;
}

void deleteAccount(Account acc){
    char confirm;
    cout<<"Are you sure you want to delete your account? (y/n): ";
    cin>>confirm;
    if(confirm=='y'||confirm=='Y'){
        remove((to_string(acc.accountNumber)+".txt").c_str());
        remove((to_string(acc.accountNumber)+"_transactions.txt").c_str());
        cout<<"Account deleted successfully."<<endl;
        exit(0);
    }
}

int main(){
    int choice;
    do{
        cout<<"\n--- Bank Account System ---"<<endl;
        cout<<"1. Create Account"<<endl;
        cout<<"2. Login"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Choose: ";
        cin>>choice;
        switch(choice){
            case 1:createAccount();break;
            case 2:{
                Account acc;
                if(login(acc)){
                    int opt;
                    do{
                        cout<<"\n--- Welcome "<<acc.name<<" ---"<<endl;
                        cout<<"1. View Account"<<endl;
                        cout<<"2. Deposit"<<endl;
                        cout<<"3. Withdraw"<<endl;
                        cout<<"4. Transfer"<<endl;
                        cout<<"5. Check Balance"<<endl;
                        cout<<"6. Transaction History"<<endl;
                        cout<<"7. Change PIN"<<endl;
                        cout<<"8. Delete Account"<<endl;
                        cout<<"9. Logout"<<endl;
                        cout<<"Choose: ";
                        cin>>opt;
                        switch(opt){
                            case 1:displayAccount(acc);break;
                            case 2:deposit(acc);break;
                            case 3:withdraw(acc);break;
                            case 4:transfer(acc);break;
                            case 5:checkBalance(acc);break;
                            case 6:viewTransactions(acc);break;
                            case 7:changePin(acc);break;
                            case 8:deleteAccount(acc);break;
                            case 9:cout<<"Logged out."<<endl;break;
                            default:cout<<"Invalid choice."<<endl;
                        }
                    }while(opt!=9&&opt!=8);
                }
                break;
            }
            case 3:cout<<"Goodbye!"<<endl;break;
            default:cout<<"Invalid choice."<<endl;
        }
    }while(choice!=3);
    return 0;
}