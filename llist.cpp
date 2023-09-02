/********************
//  
//  Name:        Destiny Shishido
//
//  Homework:    project2
/
//  Class:       ICS 212
//
//  Instructor:  Ravi Narayan
//
//  Date:        November 20, 2022
//
//  File:        llist.cpp
//
//  Description: . 
//
********************/

#include "record.h"
#include "llist.h"

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

/*******************
//  
//  function name: llist
//
//  description:   default llist constructor from file "database.txt"
//
//  parameters:    n/a
//
//  return values: n/a
//
*******************/

llist::llist()
{
    strcpy(filename, "database.txt");    
    readfile();
}

/*******************
//  
//  function name: llist
//
//  description:   list constructor from file name
//
//  parameters:    char[] : file name to read from
//
//  return values: n/a
//
*******************/

llist::llist(char file[])
{
    strcpy(filename, file);
    readfile();
}

/*******************
//  
//  function name: ~llist
//
//  description:   destructor
//
//  parameters:    n/a
//
//  return values: n/a
//
*******************/

llist::~llist()
{
    writefile();
    cleanup();
}

/*******************
//  function name: readfile
//
//  description:   retrieves records from file
//
//  parameters:    N/A
//
//  return values: 0 : successful
//                 -1: unsuccessful
//
*******************/

int llist::readfile()
{
    int accountno, retval;
    char name[30], address[60];
    std::string namestr, addressstr, temp;
    std::ifstream ptr(filename); 

    start = NULL;
    if (ptr.good())
    {
       while(ptr >> accountno)
       {
            std::getline(ptr, temp);
            std::getline(ptr, namestr, '\n');
            std::getline(ptr, addressstr, '@');

            strcpy(name, namestr.c_str());
            strcpy(address, addressstr.c_str());
            llist::addRecord(accountno, name, address);
        }
        ptr.close();
        retval = 0;
    }
    else
    {
        retval = -1;
    }
    return retval;
}

/*******************
//  
//  function name: writefile
//
//  description:   writes list to file
//
//  parameters:    n/a
//  
//  return values: 0 : successful
//                 -1: unsuccessful
//
*******************/

int llist::writefile()
{
    int retval;
    struct record *current;
    std::ofstream ptr(filename);

    current = start;

    if(ptr.good())
    {
        while(current != NULL)
        {
            ptr << (*current).accountno;
            ptr << std::endl;
            ptr << (*current).name;
            ptr << std::endl;
            ptr << (*current).address;
            ptr << "@" << std::endl;
            current = (*current).next;
        }
        retval = 0;
        ptr.close();
    }
    else
    {
        /* couldnt open file */
        retval = -1;
    }
    
    return retval;
}

/******************
//  
//  function name: cleanup
//
//  description:   releases all allocated space in heap memory
//
//  parameters:    n/a
//
//  return values: n/a
//
*******************/

void llist::cleanup()
{
    struct record * temp;
    
    while(start != NULL)
    {
        temp = start;
        start = (*start).next;
        delete(temp);
    }
}

/*******************
//  
//  Functions name: addRecord
//
//  Description:
//
//  Parameters:     int : account number
//                  char [] : name
//                  char [] : address
//
//  Return values:  N/A
//
******************/

void llist::addRecord(int faccountno, char fname[], char faddress[])
{
    int done;
    struct record *newrecord;
    struct record *temp;
    struct record *iterator;
    done = 0;

    #ifdef DEBUG
    std::cout << "function called: addRecord" << std::endl;
    std::cout << "account number: " << faccountno << std::endl;
    std::cout << "name: " << fname << std::endl;
    std::cout << "address: " << faddress << std::endl;
    #endif

    /* creating new recorod */
    newrecord = new struct record;
    (*newrecord).accountno = faccountno;
    strcpy((*newrecord).name, fname);
    strcpy((*newrecord).address, faddress);
    (*newrecord).next = NULL;

    /* start inserting */
    if(start != NULL)
    {
        iterator = start;
        if(faccountno >= (*start).accountno)
        {
            /* add to beginning */
            (*newrecord).next = start;
            start = newrecord;
        }
        else
        {
            while(done == 0)
            {
                if(iterator != NULL)
                {
                    /* iterate through list */
                    temp = iterator;
                    iterator = (*iterator).next;
                    if(iterator != NULL && faccountno >= (*iterator).accountno)
                    {
                        /* add to middle */
                        (*temp).next = newrecord;
                        (*newrecord).next = iterator;
                        done = 1;
                    }
                }
                else
                {
                    /* add to end */
                    (*temp).next = newrecord;
                    (*newrecord).next = NULL;
                    done = 1;
                }
            }
        }
    }
    else
    {
        /* add to empty list */
        (*newrecord).next = NULL;
        start = newrecord;
    }
}

/********************
//  
//  function name: findRecord
//
//  description:   finds records associated with account number
//
//  parameters:    int : account number
//
//  return values: 0 : successful
//                 -1: unsuccessful
//
********************/

int llist::findRecord(int accountNumber)
{
    int retval, found;
    found = 0;
    struct record *current;
    current = start;
    
    #ifdef DEBUG
    std::cout << "function called: findRecord" << std::endl;
    std::cout << "account number: " << accountNumber << std::endl;
    #endif

    if (current == NULL)
    {
        printf("No records exist.\n");
    }
    else
    {
        while (current != NULL)
        {
            if ((*current).accountno == accountNumber)
            {
                printf("Account Number: %d\n", (*current).accountno);
                printf("Name: %s\n", (*current).name);
                printf("Address: %s\n\n", (*current).address);
                found++;
            }
            /* iterate through list */
            current = (*current).next;
        }

        if (found == 0)
        {
            printf("Record not found.\n");
            retval = -1;
        }
        else
        {
            printf("%d records found.\n", found);
            retval = 0;
        }
    }

    return retval;
}

/********************
//  
//  function name: printAllRecords
//
//  description:   prints all the records
//
//  parameters:    n/a
//
//  return values: n/a
//
********************/

void llist::printAllRecords()
{
    struct record *current;
    current = start;

    #ifdef DEBUG
    std::cout << "function called: printAllRecords" << std::endl;
    #endif

    if (current == NULL)
    {
        std::cout << "No records exist." << std::endl;
    }

    while (current != NULL)
    {
        std::cout << "Account Number: " << (*current).accountno << std::endl;
        std::cout << "Name: " << (*current).name << std::endl;
        std::cout << "Address: " << (*current).address << std::endl;
        std::cout << std::endl;
        current = (*current).next;
    }
}

/******************
//  
//  function name: deleteRecord
//
//  description:   deletes records with given account number
//
//  parameters:    int : record acc number to delete
//
//  return values: 0 : successful
//                 -1: unsuccessful
//
********************/

int llist::deleteRecord(int accountNumber)
{
    int retval, deleted;
    struct record *temp, *current, *prev;
    deleted = 0;

    #ifdef DEBUG
    std::cout << "function called:deletedRecord" << std::endl;
    std::cout << "account number: " << accountNumber << std::endl;
    #endif
    if (start != NULL)
    {
        current = start;

        /* list not empty */
        if ((*current).accountno == accountNumber)
        {
            /* deleting from beginning */
            while ((*current).next != NULL && (*current).accountno == accountNumber)
            {
                temp = current;
                current = (*current).next;
                start = current;
                delete(temp);
                deleted++;
                retval = 0;
            }
            /* if deleting the only record(s) */
            if ((*current).next == NULL && (*current).accountno == accountNumber)
            {
                delete(current);
                start = NULL;
                deleted++;
                retval = 0;
            }
        }
        else
        {
            while ((*current).next != NULL)
            {
                /* iterate through list */
                prev = current;
                current = (*current).next;
                while ((*current).next != NULL && (*current).accountno == accountNumber)
                {
                    /* delete from  middle */
                    temp = current;
                    (*prev).next = (*current).next;
                    delete(temp);
                    deleted++;
                    retval = 0;

                    current = (*prev).next;
                }
            }
            if ((*current).next == NULL && (*current).accountno == accountNumber)
            {
                /* delete at end */
                (*prev).next = NULL;
                delete(current);
                deleted++;
                retval = 0;
            }
        }
    }
    else
    {
        /* empty list */
        std::cout << "No records exist.\n";
        retval = -1;
    }

    if (deleted == 0)
    {
        std::cout << "Record not found.\n";
    }
    else
    {
        std::cout << deleted << " records deleted.\n";
    }
    return retval;
}



