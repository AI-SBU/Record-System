//
// Created by asif1 on 3/7/2021.
//
#include <iostream>
#include <fstream>
#include "Account.h"

/**
 * Reading in the information about an account
 */
void Account::read_data() {
    std::cout << "Enter your account number : "; std::cin >> account_number;
    std::cout << "Enter your first name : "; std::cin >> first_name;
    std::cout << "Enter your last name : "; std::cin >> last_name;
    std::cout << "Enter your balance : "; std::cin >> balance;
}

/**
 * Printing the data to the user
 */
void Account::show_data() {
    std::cout << "Your account number : " << account_number << std::endl;
    std::cout << "Your first name : " << first_name << std::endl;
    std::cout << "Your last name : " << last_name << std::endl;
    std::cout << "Your balance : " << balance << std::endl;
}

/**
 *
 * Reading in user data and  writing it to a file in binary format
 */
void Account::write_record() {
    std::ofstream out_file;
    try {
        out_file.open(filename, std::ios::binary);
        read_data();
        out_file.write(reinterpret_cast<char *> (this), sizeof(*this));
        out_file.close();
    } catch (std::exception &e) {
        std::cout << "The error is " << e.what() << std::endl;
    }
}

void Account::read_record() {
    std::ofstream in_file;
    try{
        in_file.open(filename, std::ios::binary);
    } catch (std::exception &e) {
        std::cout << "Error is " <<  e.what() << std::endl;
    }
}

void Account::search_record() {

}

void Account::edit_record() {

}

void Account::delete_record() {

}
