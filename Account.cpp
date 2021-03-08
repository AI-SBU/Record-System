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
void Account::write_record()
{
    std::ofstream out_file;
    try {
        out_file.open(filename, std::ios::binary);
        read_data();
        out_file.write(reinterpret_cast<char *> (this), sizeof(*this));
        out_file.close();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Account::read_record()
{
    std::ifstream in_file;
    try{
        in_file.open(filename, std::ios::binary); //opens a file in read mode(binary)
        while (!in_file.eof())
        {
            if(in_file.read(reinterpret_cast<char *> (this), sizeof(*this))) //if there is content to read
                show_data();    // prints the content
        }
        in_file.close();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

/**
 * -The parameter represents the ith record to search for
 * -First find the size of the file where the record is stored
 * -Dividing it by the size of the current object will return
 *  the number of records in the file
 *
 * @param record_num
 */
void Account::search_record(int record_num)
{
    std::ifstream file;
    try{
        file.open(filename, std::ios::binary);
        file.seekg(0, std::ios::end); //seeking from the beginning to the end
        long long records = file.tellg()/sizeof(*this);  //tellg() returns the current position of the stream
                                                         //this is the number of bytes in the file
        std::cout << "Records in file : " << records << std::endl;
        if(records > record_num) return; //return to caller since the parameter is out of scope with respect to #records
        file.seekg((record_num-1) * sizeof(*this)); //seeking starting at the end of record_num-1
        file.read(reinterpret_cast<char *> (this), sizeof(*this)); //reading the specific record of size
                                                                         // sizeof(*this) bytes
        show_data(); //print the data
        file.close();

    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void Account::edit_record(int record_num)
{
    std::fstream file;
    try{
        file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
        file.seekg(0, std::ios::end); //seeking from the beginning to the end
        long long records = file.tellg()/sizeof(*this); //tellg() returns the current position of the stream
        //this is the number of bytes in the file
        std::cout << "Records in file : " << records << std::endl;
        if(records > record_num) return; //return to caller since the parameter is out of scope with respect to #records
        file.seekg((record_num-1) * sizeof(*this)); //seeking starting at the end of record_num-1
        file.read(reinterpret_cast<char *> (this), sizeof(*this)); //reading the specific record of size
                                                                         // sizeof(*this) bytes
        std::cout << "Record to be removed : " << std::endl;
        show_data();
        file.seekp((record_num-1) * sizeof(*this)); // seeking to where the next input char will be inserted
        std::cout << "Enter new record : \n"  << std::endl;
        read_data();
        file.write(reinterpret_cast<char *> (this), sizeof(*this));
        file.close();

    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void Account::delete_record(int record_num)
{
    std::ifstream file;
    try{
        file.open(filename, std::ios::binary);
        file.seekg(0, std::ios::end);
        long long records = file.tellg()/sizeof(*this); //size of the file
        if(record_num > records) return;

    }catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
}
