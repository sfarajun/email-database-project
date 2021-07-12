

//originally thought no line could exceed 512 characters,
// found out only header lines can't exceed 512,
// not enough time to fix
#define MAX_LINE 2000



//define datatype email that will hold info for each email
typedef struct EMAIL {
    char email_address[MAX_LINE];
    char email_raw_subject[MAX_LINE];
    char email_subject[MAX_LINE];
    char email_date[MAX_LINE];
    int start_email_body;      //number of lines into the file that starts
    int end_email_body;
} email;




void parse_database(FILE *, email *, char *, int *);
void get_email_address(char *);
void get_email_subject(char *subject, char *raw_subject);
void get_email_date(char *);
void print_summary_lines(email *, int *);
int prompt_and_check(int max_number, int scenario);
int perform_check(int max_number, int scenario);
void print_email_message(FILE *, email *, char *, int *);
void search_a_word(FILE *, email *, char *, int *);
