//
// Created by asif1 on 3/7/2021.
//

#ifndef BANKINGRECORDSYSTEM_ACCOUNT_H
#define BANKINGRECORDSYSTEM_ACCOUNT_H


class Account{

private:
    char account_number[20]{};
    char first_name[20]{};
    char last_name[20]{};
    double balance{};
    const char *filename{"record.o"};

public:
    void read_data();
    void show_data();
    void write_record();
    void read_record();
    void search_record();
    void edit_record();
    void delete_record();
};
#endif //BANKINGRECORDSYSTEM_ACCOUNT_H
