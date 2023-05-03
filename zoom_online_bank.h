//
// Created by DELL on 3/7/2023.
//

#ifndef DIPLOMAINCOMPUTING_ZOOM_ONLINE_BANK_H
#define DIPLOMAINCOMPUTING_ZOOM_ONLINE_BANK_H


#include "stdio.h"
#include "stdlib.h"
#include "time.h"
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

struct my_time{
    char c_time[25];

};

struct my_time Ctime[1];

// global index declaration
int users = 0;
int gValid = -1;
int emailExist = -1;
int passExist = -1;
int two_charArray = -1;
int nrc_valid = -1;
int strongPass = -1;
int phone_valid = -1;
int phone_found = -1;

int trans_limit = 0;

// global array
int space_array[30];
char integer_to_char_array_data[10];
unsigned int charArray_to_unsignedInt_data;

unsigned int current_day_to_transfer = 0;
unsigned int current_amount_to_transfer = 0;


// function declaration

void welcome();
void login();
void userSector();
void loadingAllDataFromFile();
void printingAllData();
void registration();
int charCounting(char toCount[50]);
void myGmailValidation(char toValidate[50]);
void emailExistChecking(char toCheck[50]);
void compare_twoCharArray(char first[50], char second[50]);
void nrc_validation(char nrc_toCheck[50]);
void myStrongPassword(char pass[50]);
//void phone_validation(unsigned int phone_toValid);
void myStringCopy(char first[50], char second[50]);
void copy_two_charArray(char receiver[200], char transmitter[200]);
void finding_phone_number(unsigned int toFind);
void transfer_money(int transfer, int receiver, unsigned int amount);
void space_counter();
void recording_allData_toFile();
void transaction_record(int transfer, int receiver, char who, unsigned int amount);
void integer_to_char(unsigned int value);
unsigned int charArray_to_unsignedInt_fun(char charArray[10]);
void get_time();
int integer_counting(unsigned long long int intCount);
void phone_validation(unsigned long long int phone_toValid);
void get_limit_amount(int user_index);
unsigned int calculate_amount_same_day(int to_calculate_index);
void current_data_to_transfer(int current_amount_toTransfer);
void receiver_limit();


void welcome(){

    int option = 0;
    printf("##### Welcome to Bank #####\n");
    printf("Press 1 for login, Press 2 for register, Press 3 to exit:");
    scanf("%d",&option);

    if( option == 1){

        login();

    }else if( option == 2){

        registration();

    }else if(option == 3){

        recording_allData_toFile();
        exit(1);

    }else{
        welcome();
    }

}

void get_time(){
    time_t tm;
    time(&tm);

    printf("Current time =%s\n", ctime(&tm));

    FILE *fptr = fopen("myTime.txt","w");
    fprintf(fptr,"%s", ctime(&tm));

    fclose(fptr);

    int index=0;
    int time_space_counter=0;

    Ctime[0].c_time[index]='-';
    index++;

    FILE *fptr2 = fopen("myTime.txt","r");
    char c = fgetc(fptr2);

    while (!feof(fptr2)){

        if( c==' '){

            time_space_counter++;

            if(time_space_counter == 1){
                Ctime[0].c_time[index]='!';
                c = fgetc(fptr2);
                index++;
            } else if(time_space_counter==4){
                Ctime[0].c_time[index]='@';
                c = fgetc(fptr2);
                index++;
            } else{
                Ctime[0].c_time[index]='-';
                c = fgetc(fptr2);
                index++;
            }


        } else{

            Ctime[0].c_time[index]=c;
            c = fgetc(fptr2);
            index++;

        }


    }

}


void userSector(){

    int user_option = 0;
    unsigned int phone = 0;
    unsigned int amount_to_transfer = 0;

    printf("This is user profile:\n");
    printf("Press 1 for transfer money:\n Press 2 for Withdraw:\nPress 3 for update your information:\nPress 4 for Cash in:\n:Press 5 for Loan:\nPress 6 for to view your history:\nPress 7 for Exit:");
    scanf("%d",&user_option);

    if(user_option == 1){

        phone_found = -1;

        while (phone_found == -1){
            printf("Enter you transfer phone number:");
            scanf("%u",&phone);
            finding_phone_number(phone);

            if(phone_found == -1){
                printf("Your phone number does not belong to any user!\n");
            }
        }

        printf("Are you sure to transfer for %s : email- %s\n",db[phone_found].name,db[phone_found].email);

        while(amount_to_transfer < db[emailExist].cur_amount){

            printf("Enter amount to transfer:");
            scanf(" %u",&amount_to_transfer);

            if(db[emailExist].cur_amount-1000 > amount_to_transfer){
                break;
            }else{
                printf("not sufficient balance!\n");
                amount_to_transfer = 0;
            }

        }
        // confirm password for transaction
        two_charArray = -1;
        char trans_pass[50];

        while (two_charArray == -1){

            printf("Enter your password to confirm your transfer process:");
            scanf(" %[^\n]",&trans_pass[0]);

            compare_twoCharArray(db[emailExist].password,trans_pass);

            if(two_charArray == -1){
                printf("Your password does not match!\n");
            }
        }

        transfer_money(emailExist,phone_found,amount_to_transfer);
        userSector();

    }else if(user_option == 7){
        welcome();
    }
}

void finding_phone_number(unsigned int toFind){

    for(int i=0; i<users; i++){

        if(db[i].phNumber == toFind){
            phone_found = i;
            break;
        }

    }

}

void transfer_money(int transfer, int receiver, unsigned int amount){

    printf("loading to transfer....\n");

    db[transfer].cur_amount = db[transfer].cur_amount-amount;
    db[receiver].cur_amount = db[receiver].cur_amount+amount;

    printf("### Transaction success ###\n");

    transaction_record(transfer,receiver,'t',amount);
    transaction_record(transfer,receiver,'r',amount);

    printingAllData();

}


void transaction_record(int transfer, int receiver, char who, unsigned int amount){

    int trans_name_counter = charCounting(db[transfer].name);
    int receiver_name_counter = charCounting(db[receiver].name);
    integer_to_char(amount);
    int amount_counter = charCounting(integer_to_char_array_data);



    char from[5] = {'F','r','o','m','-'};
    char to[4] = {'-','t','o','-'};
    char kForm[2] = {'-','$'};




    // From-Nori-to-LoneLone-10000

    if(who == 't'){

        int index_point = 0;


        // for From- to trc note
        for(int i=0; i<5; i++){
            db[transfer].trc[space_array[transfer]-15].note[i] = from[i];
            index_point++;
        }

        // for transfer name after insert From-
        for(int a=0; a<trans_name_counter; a++){
            db[transfer].trc[space_array[transfer]-15].note[index_point] = db[transfer].name[a];
            index_point++;
        }

        // for to- after transfer name
        for(int a=0; a<4; a++){
            db[transfer].trc[space_array[transfer]-15].note[index_point] = to[a];
            index_point++;
        }

        // for receiver name after insert -to-
        for(int a=0; a<receiver_name_counter; a++){
            db[transfer].trc[space_array[transfer]-15].note[index_point] = db[receiver].name[a];
            index_point++;
        }

        for(int a=0; a<2; a++){
            db[transfer].trc[space_array[transfer]-15].note[index_point] = kForm[a];
            index_point++;
        }


        for(int a=0; a<amount_counter; a++){
            db[transfer].trc[space_array[transfer]-15].note[index_point] = integer_to_char_array_data[a];
            index_point++;
        }


        get_time();
        for(int i=0; i<25; i++){

            db[transfer].trc[space_array[transfer]-15].note[index_point]=Ctime[0].c_time[i];
            index_point++;
        }

        space_array[transfer]+=1;

    }else{

        // LoneLone-Receive-From-
        char rec[14] = {'-','R','e','c','e','i','v','e','-','F','r','o','m','-'};
        int index_point = 0;

        // insert receiver name
        for(int i=0; i<receiver_name_counter; i++){
            db[receiver].trc[space_array[receiver]-15].note[index_point] = db[receiver].name[i];
            index_point++;
        }
        // rec after insert receiver name
        for(int i=0; i<14; i++){
            db[receiver].trc[space_array[receiver]-15].note[index_point] = rec[i];
            index_point++;
        }

        // transfer name
        for(int i=0; i<trans_name_counter; i++){
            db[receiver].trc[space_array[receiver]-15].note[index_point] = db[transfer].name[i];
            index_point++;
        }

        for(int a=0; a<2; a++){
            db[receiver].trc[space_array[receiver]-15].note[index_point] = kForm[a];
            index_point++;
        }

        for(int a=0; a<amount_counter; a++){
            db[receiver].trc[space_array[receiver]-15].note[index_point] = integer_to_char_array_data[a];
            index_point++;
        }


        get_time();
        for(int a=0; a<25; a++){
            db[receiver].trc[space_array[receiver]-15].note[index_point]=Ctime[0].c_time[a];
            index_point++;
        }

        space_array[receiver] += 1;

    }
    
}

void integer_to_char(unsigned int value){

    FILE *fptr = fopen("nori.txt","w");

    if(fptr == NULL){
        printf("File opening error at integer_to_char\n");
    }else{
        fprintf(fptr,"%u",value);
    }
    fclose(fptr);

    FILE *fptr2 = fopen("nori.txt","r");

    fscanf(fptr2,"%s", &integer_to_char_array_data[0]);

    for(int i=0; i<4; i++){
        printf("%c ",integer_to_char_array_data[i]);
    }

}
unsigned int charArray_to_unsignedInt_fun(char charArray[10]){

    unsigned int data;

    FILE *fptr = fopen("nori.txt","w");

    if(fptr == NULL){
        printf("File opening error at integer_to_char\n");
    }else{
        fprintf(fptr,"%s",charArray);
    }
    fclose(fptr);

    FILE *fptr2 = fopen("nori.txt","r");

    fscanf(fptr2,"%u", &data);

    return data;

}

void loadingAllDataFromFile(){

    FILE *fptr = fopen("online_bank.txt","r");

    if( fptr == NULL){
        printf("Error at loadingAllDataFromFile Function!\n");
    } else{
        for(int ncc=0; ncc<SIZE ; ncc++){

            fscanf(fptr ,"%u%s%s%s%s%s%s%u%u%f%s%d%u%llu%s%u",&db[ncc].id,&db[ncc].name,&db[ncc].nrc,&db[ncc].email,&db[ncc].password,&db[ncc].pOrb,&db[ncc].loan_s,&db[ncc].monthly_income,&db[ncc].loan_amount ,&db[ncc].loan_rate , &db[ncc].acc_s ,&db[ncc].acc_level,&db[ncc].phNumber , &db[ncc].cur_amount,&db[ncc].address[0] ,&db[ncc].transAmoLimitPerDay);

            for(int gcc=0; gcc<space_array[ncc]-15; gcc++){
                fscanf(fptr,"%s",&db[ncc].trc[gcc].note[0]);
            }

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

        printf("%u-%s-%s-%s-%s-%s-%s-%u-%u-%f-%s-%d-%u-%llu-%s-%u",db[ncc].id,db[ncc].name,db[ncc].nrc,db[ncc].email,db[ncc].password,
               db[ncc].pOrb, db[ncc].loan_s,db[ncc].monthly_income,db[ncc].loan_amount ,db[ncc].loan_rate , db[ncc].acc_s ,db[ncc].acc_level,
               db[ncc].phNumber , db[ncc].cur_amount,db[ncc].address ,db[ncc].transAmoLimitPerDay);

        for(int gcc=0; gcc<space_array[ncc]-15; gcc++){
            printf("-%s",db[ncc].trc[gcc].note);
        }
        printf("\n");

    }

}

void recording_allData_toFile(){

    FILE *fptr = fopen("online_bank.txt","w");
    if(fptr == NULL){
        printf("file cannot open!\n");
    }

    for(int ncc=0; ncc<users; ncc++){
        fprintf(fptr,"%u%c%s%c%s%c%s%c%s%c%s%c%s%c%u%c%u%c%f%c%s%c%d%c%llu%c%u%c%s%c%u",db[ncc].id,' ',db[ncc].name,' ',db[ncc].nrc,' ',db[ncc].email,' ',db[ncc].password,' ',db[ncc].pOrb,' ', db[ncc].loan_s,' ',db[ncc].monthly_income,' ',db[ncc].loan_amount ,' ',db[ncc].loan_rate ,' ', db[ncc].acc_s ,' ',db[ncc].acc_level,' ',db[ncc].phNumber ,' ', db[ncc].cur_amount,' ',db[ncc].address ,' ',db[ncc].transAmoLimitPerDay);

        for(int gcc=0; gcc<space_array[ncc]-15; gcc++){
            fprintf(fptr," %s",&db[ncc].trc[gcc].note[0]);
        }

        fprintf(fptr,"%c",'\n');
    }

}

void space_counter(){

    FILE *fptr = fopen("online_bank.txt","r");

    if(fptr == NULL){
        printf("File opening error at space counter function!\n");
    }else{

        char c = fgetc(fptr);
        int index = 0;

        while (!feof(fptr)){

            if(c != '\n'){

                if(c == ' '){
                    space_array[index]+=1;
                }
                c = fgetc(fptr);

            }else{
                index++;
                c = fgetc(fptr);
            }

        }

        for(int aaa=0; aaa<30; aaa++){
            printf("%d ",space_array[aaa]);
        }
        printf("\n");

    }

}

void registration(){

    char reEmail[50];
    char re_name[50];
    char re_nrc[50];
    char re_password[50];
    unsigned long long int re_phone = 0;

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

            printf("Your password is strong and save.\n");

            // phone number validation
            phone_valid= -1;
            while (phone_valid== -1){
                printf("Enter Your phone number: +959");
                scanf("%llu", &re_phone);
                phone_validation(re_phone);

                if(phone_valid == -1){
                    printf("Your phone number is already registered!!\n");
                }

            }

            printf("Your phone number registration success\n");

            printf("Enter your monthly income amount:");
            scanf("%u", &db[users].monthly_income);

            printf("Enter your amount:");
            scanf("%u",&db[users].cur_amount);

            printf("Enter your address:");
            scanf(" %[^\n]",&db[users].address[0]);

            printf("Enter your note:");
            scanf(" %[^\n]",&db[users].trc[0].note[0]);

            db[users].id = users+1;
            copy_two_charArray(db[users].name,re_name);
            copy_two_charArray(db[users].nrc,re_nrc);
            copy_two_charArray(db[users].email,reEmail);
            copy_two_charArray(db[users].password,re_password);
            copy_two_charArray(db[users].pOrb,db[2].pOrb);
            copy_two_charArray(db[users].acc_s,db[2].acc_s);
            db[users].loan_amount = db[2].loan_amount;
            db[users].loan_rate = db[2].loan_rate;
            copy_two_charArray(db[users].loan_s,db[2].loan_s);
            db[users].acc_level = db[2].acc_level;
            db[users].phNumber = re_phone;
            db[users].transAmoLimitPerDay = db[2].transAmoLimitPerDay;

            users++;
            printingAllData();
            welcome();

        }else{
            printf("Your email was already exist!\n");
            registration();
        }

    }else{
        printf("Your gmail format is not valid!\n");
        registration();
    }
}

void login(){

    char lEmail[50];
    char lPassword[50];

    emailExist = -1;
    two_charArray = -1;

    while(emailExist == -1 || two_charArray == -1){
        printf("Enter your email:");
        scanf(" %[^\n]",&lEmail[0]);

        printf("Enter your password:");
        scanf(" %[^\n]",&lPassword[0]);

        emailExistChecking(lEmail);

        compare_twoCharArray(db[emailExist].password, lPassword);

        if(emailExist == -1 || two_charArray == -1){
            emailExist = -1;
            two_charArray = -1;
            printf("Your login credential was wrong!\n");
        }

    }

    printf("### Welcome Mr/Mrs: %s ###\n",db[emailExist].name);
    printf("Your current amount : %u\n",db[emailExist].cur_amount);
    userSector();

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

void phone_validation(unsigned long long int phone_toValid){

    int phone_counter= 0;
    int phone_charCount=0;
    phone_charCount= integer_counting( phone_toValid);
    if(phone_charCount == 8 || phone_charCount == 9 ){
        for (int i = 0; i < users; ++i) {

            if(phone_toValid != db[i].phNumber){
                phone_counter++;
            }else{
                phone_valid = -1;

                break;
            }
        }
        if(phone_counter == users){
            phone_valid= 1;
        }else{
            printf("Invalid Phone number or Phone number is already taken!:\n");
        }
    }
}

int integer_counting(unsigned long long int intCount){

    int count= 0;

    while ( intCount != 0){
        intCount = intCount/10;
        count++;
    }

    return  count;
}


//void phone_validation(unsigned int phone_toValid){
//
//    int phone_counter = 0;
//
//    for(int i=0; i<users; i++){
//
//        if(phone_toValid != db[i].phNumber){
//            phone_counter++;
//        }else{
//            phone_valid = -1;
//            break;
//        }
//    }
//
//    if(phone_counter == users){
//        phone_valid = 1;
//    }
//
//}

void copy_two_charArray(char receiver[200], char transmitter[200]){

    int transmit_counter = charCounting(transmitter);

    for(int i=0; i<transmit_counter; i++){
        receiver[i] = transmitter[i];
    }

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

void get_limit_amount(int user_index){
    // 1 for personal , 2 for business
    int acc_level = db[user_index].acc_level;
    char pOrb = db[user_index].pOrb[0];
    int p_or_b = 0;

    if(pOrb == 'p'){
        p_or_b = 1;
    }else{
        p_or_b = 2;
    }

    switch (acc_level) {
        case 1:
            if(p_or_b == 1){
                trans_limit = 100000;
            }else{
                trans_limit = 1000000;
            }
            break;
        case 2:
            if(p_or_b == 1){
                trans_limit = 50000;
            }else{
                trans_limit = 500000;
            }
            break;
        case 3:
            if(p_or_b == 1){
                trans_limit = 10000;
            }else{
                trans_limit = 100000;
            }
        default:
            break;
    }
}

void current_data_to_transfer(int current_amount_toTransfer){

    char get_current_day[2];
    get_time();

    printf("Current time: %s\n",Ctime[0].c_time);
    printf("Current amount to transfer: %d\n",current_amount_toTransfer);

    get_current_day[0] = Ctime[0].c_time[9];
    get_current_day[1] = Ctime[0].c_time[10];

    unsigned int current_day_to_transferL = charArray_to_unsignedInt_fun(get_current_day);

    printf("\nCurrent day: %u\n",charArray_to_unsignedInt_data);

    current_day_to_transfer = current_day_to_transferL;
    current_amount_to_transfer = current_amount_toTransfer;
}

unsigned int calculate_amount_same_day(int to_calculate_index){

    int record_counter = space_array[to_calculate_index]-15;

    int index_counter = 0;

    char amount_char_array[10];

    char day_char_array[3];

    for(int a=record_counter-1; a>=0; a--){

        int current_record_counter = charCounting(db[to_calculate_index].trc[a].note);

        // -Wed!Mar-29-10:53:04@2023
        // to get $
        for(int aa=0; aa<current_record_counter; aa++){

            if(db[to_calculate_index].trc[a].note[aa] == '$'){
                break;
            }
            index_counter++;

        }

        // stop -
        int quantity_of_amount = 0;
        for(int aaa=index_counter; aaa<current_record_counter; aaa++){

            if(db[to_calculate_index].trc[a].note[aaa] == '-'){
                break;
            }
            quantity_of_amount++;

        }

        index_counter++;
        for(int x=0; x<quantity_of_amount-1; x++){

            amount_char_array[x] = db[to_calculate_index].trc[a].note[index_counter];
            index_counter++;
        }

        unsigned int current_record_amount = charArray_to_unsignedInt_fun(amount_char_array);
        printf("current record amount : %d\n",current_record_amount);

        // to get day of current record
        for(int xx=index_counter; xx<current_record_counter; xx++){

            if(db[to_calculate_index].trc[a].note[xx] == '!'){
                break;
            }
            index_counter++;

        }

        day_char_array[0] = db[to_calculate_index].trc[a].note[index_counter+5];
        day_char_array[1] = db[to_calculate_index].trc[a].note[index_counter+6];

        unsigned int current_record_day = charArray_to_unsignedInt_fun(day_char_array);
        printf("Current record day : %d\n",current_record_day);

        if(current_record_day != current_day_to_transfer){
            break;
        }

        index_counter = 0;

    }

}

void receiver_limit(){

    int index_forLimit = -1;
    get_limit_amount(0);

    






}

#endif //DIPLOMAINCOMPUTING_ZOOM_ONLINE_BANK_H
