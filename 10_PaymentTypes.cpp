#pragma once
#include <iostream>
#include "09_Payment.cpp"
using namespace std;

// Inheritance + runtime polymorphism.
class UpiPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "[UPI] Payment of Rs." << amount << " processing...\n";
        cout << "[UPI] Payment successful.\n";
        return true;
    }
    string methodName() const override { return "UPI"; }
};

class CardPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "[CARD] Payment of Rs." << amount << " processing...\n";
        cout << "[CARD] Payment successful.\n";
        return true;
    }
    string methodName() const override { return "Card"; }
};

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "[CASH] Collecting Rs." << amount << "...\n";
        cout << "[CASH] Payment successful.\n";
        return true;
    }
    string methodName() const override { return "Cash"; }
};

// Used only for demonstrating the required failed-payment edge case.
class FailedPayment : public Payment {
public:
    bool pay(double) override {
        cout << "[PAYMENT] Payment failed.\n";
        return false;
    }
    string methodName() const override { return "Failed Test Payment"; }
};
