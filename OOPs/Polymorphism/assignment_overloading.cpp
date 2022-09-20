#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>

class Account{
public:

  Account()= default;
  Account(int numb): numberOf(numb), deposits(new double[numb]){}

  Account(const Account& other): numberOf(other.numberOf), deposits(new double[other.numberOf]){
    std::copy(other.deposits, other.deposits + other.numberOf, deposits);
  }

  Account& operator = (const Account& other){
    if (this != &other){
        delete[] deposits;
        numberOf = other.numberOf;
        deposits = new double[other.numberOf];
        std::copy(other.deposits, other.deposits + other.numberOf, deposits);
    }
    return *this;
  }

  Account(Account&& other):numberOf(other.numberOf), deposits(other.deposits){
    other.deposits = nullptr;
    other.numberOf = 0;
  }

  Account& operator =(Account&& other){
    numberOf = other.numberOf;
    deposits = other.deposits;
    other.deposits = nullptr;
    other.numberOf = 0;
    return *this;
  }
  ~Account() noexcept {
      delete [] deposits;
  }

private:
  int numberOf;
  double * deposits;
};

int main(){

  std::cout << std::endl;
  std::cout << std::fixed << std::setprecision(10);

  Account account(200000000);
  Account account2(100000000);
  
  auto start = std::chrono::system_clock::now();
  account = account2;
  std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
  std::cout << "Account& operator = (const Account& other): " << dur.count() << " seconds" << std::endl;

  start = std::chrono::system_clock::now();
  account = std::move(account2);
  dur = std::chrono::system_clock::now() - start;
  std::cout << "Account& operator=(Account&& other):" << dur.count() << " seconds" << std::endl;
  
  std::cout << std::endl;
}

// In this example, the assignment operator for the Account class is overloaded for both copy (line 16) and move (line 31) operations.

// If the argument is an lvalue, a copy is performed. A new array on the heap is created, called deposits, and the contents of other's array is copied into it, as seen in lines 20 and 21.

// If the argument is an rvalue, a move is performed. In this case, a new array is not created. This makes the move operation much faster.

// This is evident in the main program.

// The std::move call on line 61 returns an rvalue, hence the assignment operator will move the data from account2 to account.

// This is significantly more efficient than the copy assignment on line 56.