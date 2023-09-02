/********************
//  
//  Name:         Destiny Shishido
//
//  Homework:     project2
//
//  Class:        ICS 212
//
//  Instructor:   Ravi Narayan
//
//  Date:         November 17, 2022
//
//  File:         llist.h
//
//  Description:  desc
//
********************/
#include "record.h"
#ifndef LLIST_H
#define LLIST_H

#ifdef DEBUGMODE
    #define DEBUGMODE
#endif

class llist
{
private:
    record  *start;
    char    filename[20];
    int     readfile();
    int     writefile();
    void    cleanup();

public:
    llist();
    llist(char[]);
    ~llist();
    void addRecord(int, char[], char []);
    int findRecord(int);
    void printAllRecords();
    int deleteRecord(int);
};

#endif
