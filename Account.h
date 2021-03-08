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
    int records_in_file {};
    const char *filename{"record.o"};

public:
    void read_data();
    void show_data();
    void write_record();
    void read_record();

    [[maybe_unused]] long long helper_file_size();
    void search_record(int record_num);
    void edit_record(int record_num);
    void delete_record(int record_num);
};
#endif //BANKINGRECORDSYSTEM_ACCOUNT_H
