#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "email_project.h"




void parse_database(FILE *file, email *email_info, char *line, int *num_of_emails){
    int which_line = 0;
    int first_email = 1;   //0 means not in body of email, 1 means in body of email


    while (fgets(line, MAX_LINE, file) != NULL) {
        which_line++;

        //finds beginning of new email
        if (line[0] == 0xc) {
            //checks if end of last email and beginning of new email
            if (first_email == 0) {
                email_info[*num_of_emails].end_email_body = which_line - 1;
            } else {
                first_email = 0;
            }

            //finds number of emails
            *num_of_emails = *num_of_emails + 1;

            //add details of emails to array of email info
            fgets(email_info[*num_of_emails].email_address, MAX_LINE, file);
            which_line++;

            fgets(email_info[*num_of_emails].email_raw_subject, MAX_LINE, file);
            which_line++;

            fgets(email_info[*num_of_emails].email_date, MAX_LINE, file);
            which_line++;


            //find line that body starts
            email_info[*num_of_emails].start_email_body = which_line + 1;
        }


    }
    //find end body of last email
    email_info[*num_of_emails].end_email_body = which_line - 1;
    printf("Email database file contains %d emails\n", *num_of_emails);
}


void get_email_address(char *address) {
    //find out where email address begins
    int address_start = 0;
    int address_end = 0;

    //checks to see if < > present and gives location in string
    int i;
    for( i = 0; i < MAX_LINE; i++){
        if((address[i] == '<') && (address_start == 0)){
            address_start = i + 1;
        }
        else if((address[i] == '>') && (address_end == 0) && (address_start != 0)){
            address_end = i;
            break;
        }
    }



    //if has < >
    if((address_start != 0) && (address_end != 0)){
        for( i = 0; i < address_end - address_start ; i ++){
            address[i] = address[address_start + i];
        }
        address[address_end - address_start] = '\0';
    }

        //if doesnt have < >
    else{
        address_start = 6;
        address_end = (strlen(address) - 1);
        for( i = 0; i < address_end - address_start; i ++){
            address[i] = address[address_start + i];
        }
        address[address_end - address_start] = '\0';
    }
}


void get_email_subject(char *subject, char *raw_subject){
    //copy raw_subject into subject
    int i;
    for( i = 0; i  < MAX_LINE; i ++){
        subject[i] = raw_subject[i];
    }

    int subject_start = 9;
    int subject_end = (strlen(subject) - 1);
    if((subject_end - subject_start) > 25){
        subject_end = 25 + subject_start;
    }
    for( i = 0; i < subject_end - subject_start; i ++){
        subject[i] = subject[subject_start + i];
    }
    subject[subject_end - subject_start] = '\0';
    //restrict to 25 characters
}


void get_email_date(char *date){
    int year;
    char month[4];
    int day;
    int hour;
    int minute;
    char garbage[7];

    hour = 0;
    sscanf(date, "%s %d %s %d %d:%d", garbage, &day, month, &year, &hour, &minute);


    //get numeric value of month
    int month_value = 0;
    if(strcmp(month, "Jan") == 0){
        month_value = 1;
    }
    else if(strcmp(month, "Feb") == 0){
        month_value = 2;
    }
    else if(strcmp(month, "Mar") == 0){
        month_value = 3;
    }
    else if(strcmp(month, "Apr") == 0){
        month_value = 4;
    }
    else if(strcmp(month, "May") == 0){
        month_value = 5;
    }
    else if(strcmp(month, "Jun") == 0){
        month_value = 6;
    }
    else if(strcmp(month, "Jul") == 0){
        month_value = 7;
    }
    else if(strcmp(month, "Aug") == 0){
        month_value = 8;
    }
    else if(strcmp(month, "Sep") == 0){
        month_value = 9;
    }
    else if(strcmp(month, "Oct") == 0){
        month_value = 10;
    }
    else if(strcmp(month, "Nov") == 0){
        month_value = 11;
    }
    else if(strcmp(month, "Dec") == 0){
        month_value = 12;
    }



    //convert time to am or pm
    int pm = 0;
    if(hour > 12 ){
        pm = 1;
        hour = (hour % 13) + 1;
    }
    else if(hour == 12){
        pm = 1;
    }



    //convert min into array
    char min[3];
    if(minute < 10){
        sprintf(min, "0%d", minute);
    }
    else{
        sprintf(min, "%d", minute);
    }

    //convert yr into array
    char yr[3];
    year = (year%100);
    if(year < 10){
        sprintf(yr, "0%d", year);
    }
    else{
        sprintf(yr, "%d", year);
    }

    //convert month into array
    char mn[3];
    if(month_value < 10){
        sprintf(mn, "0%d", month_value);
    }
    else{
        sprintf(mn, "%d", month_value);
    }

    //convert day into array
    char dy[3];
    if(day < 10){
        sprintf(dy, "0%d", day);
    }
    else{
        sprintf(dy, "%d", day);
    }

    //if hour is 12am convert hour into string and print
    if(hour == 0){
        char hr[3] = "12";
        if(pm == 1){
            sprintf(date, "%s-%s-%s %s:%spm", mn, dy, yr, hr, min);
        }
        else{
            sprintf(date, "%s-%s-%s %s:%sam", mn, dy, yr, hr, min);
        }
    }

    else{
        //save date into date array
        if(pm == 1){
            sprintf(date, "%s-%s-%s %d:%spm", mn, dy, yr, hour, min);
        }
        else{
            sprintf(date, "%s-%s-%s %d:%sam", mn, dy, yr, hour, min);
        }
    }
}
