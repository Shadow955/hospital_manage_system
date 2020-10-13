#pragma once

int openfile();
//
char* gettime();
//
char* getyear();
//
int turndate(char*);

int turnyear(char a[]);
//
record*  read_and_link();
//
void printf_number(record* , pill_term* , che_term* , doctor* );
//
void stdprint(record* p);
//
record* FindEnd(record* head);
//
pill_term* link_pill();
//
che_term* link_che();
//
doctor* link_doc();
//
void docprint(doctor*);
//
void pillprint(pill_term*);
//
void cheprint(che_term*);
//
void singleprint(record*);
//
void save(record*);
//