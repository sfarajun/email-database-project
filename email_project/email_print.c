#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "email_project.h"



//prompt for a choice

int prompt_and_check(int max_number, int scenario) {

    int repeat = perform_check(max_number, scenario);
    while(repeat == 0) {
        if(scenario == 1){
            printf("Invalid command. Try again.\n");
        }
        else if(scenario == 2){
            printf("ERROR: invalid email ID. Try again.\n");
        }
        repeat = perform_check(max_number, scenario);
    }

    return repeat;
}


int perform_check(int max_number, int scenario) {
    //if scenario 1 where choosing command option
    if(scenario == 1){
        printf("Choose an option:\n1.  Print summary lines\n2.  Print email message\n3.  Search key word\n4.  Exit\nEnter option:  ");
    }
        //if scenario 2 where choosing valid ID
    else if(scenario == 2){
        printf("Enter email ID:  ");
    }


    //multiple checks for input
    int repeat = 0;
    char nums[5] = {'\0', '\0', '\0', '\0'};
    char c;
    int all_g = 1;
    int sum = 0;


    //stores the first digits in array nums
    scanf("%c", &c);
    while(c != '\n'){
        //if first 5 digits
        if(repeat < 5){
            nums[repeat] = c;
            repeat++;
        }

        //scans until end or stdin
        scanf("%c", &c);
    }


    //check if inputted more than 4 digits
    if(repeat == 5){
        return 0;
    }
        //checks if nothing inputted
    else if(nums[0] == '\0'){
        return 0;
    }
    else{
        //checks if all values inputed were numbers
        int i;
        for( i = 0; i < repeat; i ++){
            if(isdigit(nums[i]) == 0){
                all_g = 0;
                return  0;
            }
        }
        //if all tests above passed
        if(all_g == 1){
            int tens_exp = 1;
            int p;
            for( i = 0; i < repeat; i ++){
                //stores 10^i into tens_exp
                for(p = 0; p < i; p ++){
                    tens_exp = tens_exp * 10;
                }
                //computes the sum of the values stored in the array
                sum = sum + ( (nums[repeat - i - 1] - '0') * tens_exp);
                tens_exp = 1;
            }

            //if sum is within range return sum
            if((sum <= max_number) && (sum > 0)){
                return sum;
            }
                //if out of range ask for new input
            else{
                return 0;
            }

        }
    }


}



//act on choice and print appropriately

void print_summary_lines(email *email_info, int *num_of_emails){
    int i;
    for( i = 1; i < *num_of_emails + 1; i++){
        printf("%d.  %s %s [%d] %s\n", i, email_info[i].email_date, email_info[i].email_address, (email_info[i].end_email_body - email_info[i].start_email_body), email_info[i].email_subject);
    }
}


void print_email_message(FILE *file, email *email_info, char *line, int *num_of_emails){
    int ask = prompt_and_check(*num_of_emails, 2);


    //change subject to correct format to add two spaces after subject
    int i;
    for ( i = strlen(email_info[ask].email_raw_subject); i > 7; i--){
        email_info[ask].email_raw_subject[i+1] = email_info[ask].email_raw_subject[i];
    }
    email_info[ask].email_raw_subject[8] = ' ';



    printf("\nFrom:  %s\n%sDate:  %s\nMessage:\n", email_info[ask].email_address, email_info[ask].email_raw_subject, email_info[ask].email_date);


    //gets to the start of the line
    rewind(file);
    for ( i = 0; i < email_info[ask].start_email_body; i++) {
        fgets(line, MAX_LINE, file);
    }
    for ( i = email_info[ask].start_email_body; i < email_info[ask].end_email_body; i++) {
        fgets(line, MAX_LINE, file);
        printf("%s", line);
    }
}


void search_a_word(FILE *file, email *email_info, char *line, int *num_of_emails){

    //if 3 entered
    char word_search[MAX_LINE];
    printf("Enter a word:  ");
    scanf("%s", word_search);
    char new_line_dump;
    scanf("%c", &new_line_dump);
    int email_header_printed = 0;


    int line_position = 0;
    int email_hit_already = 0;
    rewind(file);


    int j;
    int i;
    for( j = 1; j < *num_of_emails + 1; j ++){
        //set email_start to  because new email
        email_hit_already = 0;


        //gets to the line where the body starts
        for ( i = line_position; i < email_info[j].start_email_body; i++) {
            fgets(line, MAX_LINE, file);
        }

        //at this point line is at start position
        //the actual body of the email
        for ( i = email_info[j].start_email_body; i < email_info[j].end_email_body; i++) {
            fgets(line, MAX_LINE, file);
            if(strstr(line, word_search) != NULL){

                //if email header not yet printed
                if(email_hit_already == 0){
                    printf("%d.  %s %s [%d] %s\n", j, email_info[j].email_date, email_info[j].email_address, (email_info[j].end_email_body - email_info[j].start_email_body), email_info[j].email_subject);
                }


                //print line where word appears
                printf("%s", line);
                email_hit_already = 1;
            }
        }

        //set line position to where ended
        line_position = email_info[j].end_email_body;
    }
}