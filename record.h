/********************
//  
//  Name:         Destiny Shishido
//
//  Homework:     project 2
//
//  Class:        ICS 212
//
//  Instructor:   Ravi Narayan
//
//  Date:         November 17, 2022
//
//  File:         record.h
//
//  Description:  defines struct record: account number, name,
//                address, pointer to next record
//
********************/
#ifndef RECORD_H
#define RECORD_H

struct record
{
    int accountno;
    char name[30];
    char address[60];
    struct record* next;
};

#endif
