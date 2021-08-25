#include <iostream>
#include "Account.h"
int main()
{
    Account account{};
    int choice{};
    while(true)
    {
        std::cout<<"Select one option below ";
        std::cout<<"\n\t1-->Add record to file";
        std::cout<<"\n\t2-->Show record from file";
        std::cout<<"\n\t3-->Search Record from file";
        std::cout<<"\n\t4-->Update Record";
        std::cout<<"\n\t5-->Delete Record";
        std::cout<<"\n\t6-->Quit";
        std::cout<<"\nEnter your choice: ";
        std::cin>>choice;
        switch(choice)
        {
            case 1:
                account.write_record();
                break;
            case 2:
                account.read_record();
                break;
            case 3:
                account.search_record();
                break;
            case 4:
                account.edit_record();
                break;
            case 5:
                account.delete_record();
                break;
            case 6:
                std::cout<<"\nExiting program..." << std::endl;
                exit(0);
                break;
            default:
                std::cout<<"\nEnter correct choice" << std::endl;
        }
    }
}
