#pragma once

int openfile();
//
char* gettime();
//
char* getyear();
//
int turndate(char*);
//
int turnyear(char a[]);
//
record*  read_and_link(doctor*);
//
void printf_number(record*);
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
void freerec(record*);
//
void freedoc(doctor*);
//
void freepill(pill_term*);
//
void freeche(che_term*);
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
void search(record* , doctor* , pill_term* , che_term* );