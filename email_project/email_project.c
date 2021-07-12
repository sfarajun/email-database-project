#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "email_project.h"






int main(int argc, char *argv[]) {
    //open files
    FILE *file;
    if (argc != 2) {
        fprintf(stderr, "ERROR: wrong number of arguments. Usage: pr2 <database file>\n");
        return -1;
    }
    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Invalid database file nofile\n");
        return -1;
    }




    //declare email data types
    int num_of_emails = 0;
    email email_info[1001];
    char line[MAX_LINE];




    //parse email database file for information
    parse_database(file, email_info, line, &num_of_emails);

    //change the sender address to just the email (without From: <>)
    int i;
    for ( i = 1; i < num_of_emails + 1; i++) {
        get_email_address(email_info[i].email_address);
        get_email_subject(email_info[i].email_subject, email_info[i].email_raw_subject);
        get_email_date(email_info[i].email_date);
    }





    //when input invalid, repeats asking for input
    int choice = prompt_and_check(4, 1);
    while (choice != 4) {
        if (choice == 1) {
            //print entire email and summary
            print_summary_lines(email_info, &num_of_emails);
        }
        else if (choice == 2) {
            //print email message
            print_email_message(file, email_info, line, &num_of_emails);
        }
        else if (choice == 3) {
            //search key word
            search_a_word(file, email_info, line, &num_of_emails);
        }
        //prompt for the next option
        choice = prompt_and_check(4, 1);
    }



    //if 4 chosen then exits the while loop and program
    return 0;
}










