//
// Created by asif1 on 3/7/2021.
//
#include <iostream>
#include <fstream>
#include <vector>
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
 * creates a Account obj after reading user data
 * writes the object to the file stream
 */
void Account::write_record()
{
    std::ofstream out_file;
    try {
        out_file.open(filename, std::ios::binary);
        read_data();
        out_file.write(reinterpret_cast<char *> (this), sizeof(*this));
        out_file.close();
        records_in_file++;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

/**
 * reads the record from a file
 */
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

[[maybe_unused]] long long Account::helper_file_size() {
    std::ifstream file;
    try{
        file.open(filename, std::ios::binary);
        file.seekg(0, std::ios::end); //seeking from the beginning to the end
        long long records = file.tellg()/sizeof(*this); //tellg() returns the current position of the stream
        file.close();
        return records;
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
    return -1;
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

        if(records_in_file > record_num) return; //return to caller since the parameter is out of scope with respect to #records
        file.seekg((record_num-1) * sizeof(*this)); //seeking starting at the end of record_num-1
        file.read(reinterpret_cast<char *> (this), sizeof(*this)); //reading the specific record of size
                                                                         // sizeof(*this) bytes
        show_data(); //print the data
        file.close();

    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

/**
 * The parameter specifies which record to be changed
 * Overrides this record with new data
 * @param record_num
 */
void Account::edit_record(int record_num)
{
    std::fstream file;
    try{

        if(records_in_file > record_num) return; //return to caller since the parameter is out of scope with respect to #records
        file.seekg((record_num-1) * sizeof(*this)); //seeking starting at the end of record_num-1
        file.read(reinterpret_cast<char *> (this), sizeof(*this)); //reading the specific record
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

/**
 * Deletes a record from the file,
 * Creates a temp where all but the unwanted record gets stored, in-order
 * deletes the original file and changes the name of the temp file to
 * the desired name
 * @param record_num the passed parameter specifies which record to remove
 */
void Account::delete_record(int record_num)
{
    std::fstream file;
    try{
        file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
        std::fstream tmp_file;
        tmp_file.open("tmp_file.o", std::ios::out | std::ios::binary);
        try{
            file.seekg(0);
            for(int i = 0; i < records_in_file; i++)
            {
                file.read(reinterpret_cast<char *> (this), sizeof(*this));
                if(i == (record_num-1)) continue;
                tmp_file.write(reinterpret_cast<char *> (this), sizeof(*this));
            }
            tmp_file.close();
        }catch (std::exception &e){
            std::cout << e.what() << std::endl;
        }
        file.close();
        remove(filename);
        rename("tmp_file.o", filename);
        records_in_file--;
    }catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }


}


