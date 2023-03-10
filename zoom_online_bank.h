//
// Created by DELL on 3/7/2023.
//

#ifndef DIPLOMAINCOMPUTING_ZOOM_ONLINE_BANK_H
#define DIPLOMAINCOMPUTING_ZOOM_ONLINE_BANK_H


#include "stdio.h"
#define SIZE 1000

// transition records

struct trans{
    char note[200];
};

struct data{
    unsigned int id;
    char name[30];
    char nrc[50];
    char email[50];
    char password[50];

    char pOrb[20]; // personal or business
    char loan_s[2]; // loan status
    unsigned int monthly_income;
    unsigned int loan_amount; // ဘယ်လောက်ချေးထားသလဲ
    float loan_rate;
    char acc_s[10]; //account status
    int acc_level;
    unsigned long long int phNumber;
    unsigned int cur_amount; //current amount
    char address[100];
    unsigned  int transAmoLimitPerDay; // transAmountLimitPerDay minimize for our project 5min
    struct trans trc[100];

};

struct data db[SIZE];

// global index declaration
int users = 0;
int gValid = -1;
int emailExist = -1;
int two_charArray = -1;
int nrc_valid = -1;
int strongPass = -1;
int phone_valid = -1;
int login_valid = -1;
unsigned long long int phone_validation_code = 0;


// function declaration
void welcome();
void loadingAllDataFromFile();
void printingAllData();
void registration();
int charCounting(char toCount[50]);
void myGmailValidation(char toValidate[50]);
void emailExistChecking(char toCheck[50]);
void compare_twoCharArray(char first[50], char second[50]);
void nrc_validation(char nrc_toCheck[50]);
void myStrongPassword(char pass[50]);
void phone_validation(unsigned long long int phone_toValid);
void myStringCopy(char first[50], char second[50]);
void login(char lEmail[50],char lPassword[50]);
int integerCounting(unsigned long long int intToCount);


void welcome(){

    int option = 0;
    printf("##### Welcome to Bank #####\n");
    printf("Press 1 for login, Press 2 for register, Press 3 to exit:");
    scanf("%d",&option);

    if( option == 1){
        // login
        char loginEmail[50];
        char loginPassword[50];

        printf("Enter your email to login:");
        scanf(" %[^\n]",&loginEmail[0]);
        printf("Enter your password:");
        scanf(" %[^\n]",&loginPassword[0]);
        login_valid = -1;
        login(loginEmail,loginPassword);

        if(login_valid != -1){
            printf("***** Welcome to NCC bank *****\n");
        }else{
            printf("login failed\n");
        }



    }else if( option == 2){
        // register
        registration();
    }else if(option == 3){
        // exit
    }else{
        welcome();
    }
}


void userSector(){
    printf("This is user profile:\n");
}

void loadingAllDataFromFile(){

    FILE *fptr = fopen("online_bank.txt","r");

    if( fptr == NULL){
        printf("Error at loadingAllDataFromFile Function!\n");
    } else{
        for(int ncc=0; ncc<SIZE ; ncc++){

            fscanf(fptr ,"%u%s%s%s%s%s%s%u%u%f%s%d%llu%u%s%u%s",&db[ncc].id,&db[ncc].name,&db[ncc].nrc,&db[ncc].email,&db[ncc].password,&db[ncc].pOrb,&db[ncc].loan_s,&db[ncc].monthly_income,&db[ncc].loan_amount ,&db[ncc].loan_rate , &db[ncc].acc_s ,&db[ncc].acc_level,&db[ncc].phNumber , &db[ncc].cur_amount,&db[ncc].address ,&db[ncc].transAmoLimitPerDay,&db[ncc].trc[0].note );

            if(db[ncc].email[0] == '\0'){
                break;
            }
            users++;
        }
    }
    fclose(fptr);
}

void printingAllData(){

    for(int ncc=0; ncc<users ; ncc++){

        printf("%u-%s-%s-%s-%s-%s-%s-%u-%u-%f-%s-%d-%llu-%u-%s-%u-%s\n",db[ncc].id,db[ncc].name,db[ncc].nrc,db[ncc].email,db[ncc].password,
               db[ncc].pOrb, db[ncc].loan_s,db[ncc].monthly_income,db[ncc].loan_amount ,db[ncc].loan_rate , db[ncc].acc_s ,db[ncc].acc_level,
               db[ncc].phNumber , db[ncc].cur_amount,db[ncc].address ,db[ncc].transAmoLimitPerDay,db[ncc].trc[0].note);
    }

}

void registration(){

    char reEmail[50];
    char re_name[50];
    char re_nrc[50];
    char re_password[50];
    unsigned long long int re_phone[50];
    unsigned int re_amount = 0;

    printf("This is NCC bank registration:\n");
    printf("Enter your email:");
    scanf(" %[^\n]",&reEmail[0]);

    gValid = -1;
    myGmailValidation(reEmail);

    if(gValid != -1){

        printf("You can register now:\n");
        emailExist = -1;
        emailExistChecking(reEmail);

        if(emailExist == -1){

            printf("Your email is valid:\n");

            printf("Enter your name:");
            scanf(" %[^\n]",&re_name[0]);

            // NRC validation
            nrc_valid = -1;
            while(nrc_valid == -1){

                printf("Enter your nrc:");
                scanf(" %[^\n]",&re_nrc[0]);

                nrc_validation(re_nrc);

                if(nrc_valid == -1){
                    printf("Your NRC is not valid!\n");
                }
            }

//            myStringCopy(db[users].nrc,re_nrc);
            printf("Your NRC is valid:\n");

            // strong password validation
            while(strongPass == -1){

                printf("Enter your password:");
                scanf(" %[^\n]",&re_password[0]);
                strongPass = -1;
                myStrongPassword(re_password);

                if(strongPass == -1){
                    printf("Your password is too weak or must be at least 8 characters!\n");
                }
            }

//            myStringCopy(db[users].password,re_password);
            printf("Your password is strong and save.\n");


            // phone number validation
            phone_valid = -1;
            while(phone_valid == -1){

                printf("Enter your phone number:");
                scanf("%llu",&re_phone[0]);

                phone_validation(re_phone);

                if(phone_valid == -1){
                    printf("Your phone number is invalid or already taken!\n");
                }
            }

            printf("Your phone number registration success\n");

            // current amount
            printf("Enter your amount:");
            scanf("%u",&db[users].cur_amount);

            printf("Enter your address:");
            scanf(" %[^\n]",&db[users].address);

            printf("Enter your note:");
            scanf(" %[^\n]",&db[users].trc[0].note);

            myStringCopy(db[users].email,reEmail);
            myStringCopy(db[users].name,re_name);
            myStringCopy(db[users].nrc,re_nrc);
            myStringCopy(db[users].password,re_password);
            myStringCopy(db[users].pOrb,db[2].pOrb);
            myStringCopy(db[users].loan_s,db[2].loan_s);
            myStringCopy(db[users].acc_s,db[2].acc_s);

            db[users].id = users+1;
            db[users].monthly_income = db[2].monthly_income;
            db[users].loan_amount = db[2].loan_amount;
            db[users].loan_rate = db[2].loan_rate;
            db[users].acc_level = db[2].acc_level;
            db[users].transAmoLimitPerDay = db[2].transAmoLimitPerDay;

            users++;
            printingAllData();
            welcome();
//            printf("Break here!\n");


        }else{
            printf("Your email was already exist!\n");
            registration();
        }

    }else{
        printf("Your gmail format is not valid!\n");
        registration();
    }
}



void login(char lEmail[50],char lPassword[50]){

    int lEmail_count = charCounting(lEmail);
    int lPassword_count = charCounting(lPassword);
    int lEmailCounter = 0;
    int lPasswordCounter = 0;


    for(int i=0; i<users; i++){

        int db_email_count = charCounting(db[i].email);
        int db_password_count = charCounting(db[i].password);

        if(lEmail_count == db_email_count && lPassword_count == db_password_count){
            for(int gcc=0; gcc<lEmail_count; gcc++){
                if(lEmail[gcc] != db[i].email[gcc]){
                    break;
                }else{
                    lEmailCounter++;
                }
            }
            for(int gcc=0; gcc<lPassword_count; gcc++){
                if(lPassword[gcc] != db[i].password[gcc]){
                    break;
                }else{
                    lPasswordCounter++;
                }
            }
            if(lEmail_count == lEmailCounter && lPassword_count == lPasswordCounter){
                login_valid = 1;
                break;
            }
        }

    }

}


int charCounting(char toCount[50]){

    int charCount = 0;

    for(int gcc=0; gcc<50; gcc++){
        if(toCount[gcc] == '\0'){
            break;
        }else{
            charCount++;
        }
    }
    return charCount;
}

void myGmailValidation(char toValidate[50]){

    int toEndpoint = charCounting(toValidate);
    char format[10] = {'@','g','m','a','i','l','.','c','o','m'};

    int count = 0;
    for(int i=0; i<toEndpoint; i++){
        if(toValidate[i] == '@' || toValidate[i] == ' '){
            break;
        }else{
            count++;
        }
    }

    int tocheck = 0;
    for(int i=0; i<toEndpoint; i++){
        if(toValidate[count] != format[i]){
            break;
        }else{
            count++;
            tocheck++;
        }
    }
    if(tocheck == 10){
        gValid = 1;
    }
}

void emailExistChecking(char toCheck[50]){

    int toCheckCount = charCounting(toCheck);
    int sameCounting = 0;

    for(int ncc=0; ncc<users; ncc++){
        int dbEmailCount = charCounting(db[ncc].email);
        sameCounting = 0;

        if(toCheckCount == dbEmailCount){
            for(int gcc=0; gcc<toCheckCount; gcc++){

                if(toCheck[gcc] != db[ncc].email[gcc]){
                    break;
                }else{
                    sameCounting++;
                }
            }
        }
        if(toCheckCount == sameCounting){
            emailExist = ncc;
        }
    }
}

struct nrc_region{
    char region[10];
};

// ) = 41 in ascii table

struct nrc_region nrc[3];

void nrc_validation(char nrc_toCheck[50]){

    int nrc_code[3] = {9,10,11};
    int nrc_counter = charCounting(nrc_toCheck);
    int nrc_char = 0;

    for(register int i=0; i<nrc_counter; i++){

        if(nrc_toCheck[i] == ')'){
            break;
        }else{
            nrc_char++;
        }
    }
    for(int i=0; i<3; i++){

        two_charArray = -1;
        compare_twoCharArray(nrc_toCheck,db[i].nrc);

        if(two_charArray == 1){
            nrc_valid = 1;
            break;
        }
    }
}

void compare_twoCharArray(char first[50], char second[50]){

    int first_counter = charCounting(first);
    int second_counter = charCounting(second);
    int same_counter = 0;
    if(first_counter == second_counter){

        for(register int i=0; i<first_counter; i++){
            if(first[i] != second[i]){
                break;
            }
            same_counter++;
        }

        if(first_counter == second_counter){
            two_charArray = 1;
        }

    }
}

void myStrongPassword(char pass[50]){

    int i = 0;
    int special = 0;
    int number = 0;
    int capChar = 0;
    int smallChar = 0;
    int pass_counter = charCounting(pass);

    while(strongPass == -1){

        if(i == pass_counter){
            strongPass = -1;
            break;
        }

        if(pass_counter >= 8){
            if(pass[i] >= 33 && pass[i] <= 42){
                special++;
            }else if(pass[i] >= 48 && pass[i] <= 57){
                number++;
            }else if(pass[i] >= 65 && pass[i] <= 90){
                capChar++;
            }else if(pass[i] >= 97 && pass[i] <= 122){
                smallChar++;
            }
        }else{
            strongPass = -1;
        }

        i++;

        if(special > 0 && number > 0 && capChar > 0 && smallChar > 0){
            strongPass = 1;
        }
    }
}

int integerCounting(unsigned long long int intToCount){

    int intCount = 0;

    for(int i=0; i<12; i++){
        if(intToCount == 32){
            break;
        }else{
            intCount++;
        }
    }

    return intCount;
}

void phone_validation(unsigned long long int phone_toValid){


    int phone_format[3] = {9,5,9};
    int count[50];

    int phone_counter = integerCounting(phone_toValid);

    int phone_count = 0;

    int phone_format_count = 0;

    for(int i=0; i<phone_counter; i++){

        if(phone_format[i] != phone_toValid){
            phone_count++;
        }else{
            break;
        }

    }






//    for(int i=0; i<users; i++){
//
//       if(phone_toValid != db[i].phNumber){
//          phone_counter++;
//       }else{
//          phone_valid = -1;
//          break;
//       }
//    }
//
//    if(phone_counter == users){
//        phone_valid = 1;
//    }
}

void myStringCopy(char first[50], char second[50]){

    int second_counter = charCounting(second);
    for(int i=0; i<50; i++){
        first[i] = '\0';
    }

    for(int a=0; a<second_counter; a++){
        first[a] = second[a];
    }

}


#endif //DIPLOMAINCOMPUTING_ZOOM_ONLINE_BANK_H
