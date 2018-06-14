//Coded By: Anthony Lim arl150130 1337.007
//Preprocessor Directives
#include "BaseNode.h"
#include "DoubleLinkNode.h"
#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>

using namespace std;

//Prototype Functions for Adding
bool checkAdd(string);
void addRecord(string, LinkedList&, ofstream&);

//Prototype Functions for Searching
bool checkSearch(string);
void searchRecord(string, LinkedList, ofstream&);

//Prototype Functions for Editing
bool checkEdit(string editline);
void editRecord(string editline, LinkedList linked, ofstream& log);

//Prototype Functions for Deleting
bool checkDelete(string deletestring);
void deleteRecord(string deletestring, LinkedList linked, ofstream& log);

//Prototype Functions for Sorting
void sortRecord(string sortstring, LinkedList linked, ofstream& log);
void swap(DoubleLinkNode*, DoubleLinkNode*);

//Main Function Drives The Program
int main()
{
    //Open Files
    ifstream input("freeplay.dat");
    ifstream update("update.txt");
    ofstream log("freeplay.log");

    //Create Linked List Object
    LinkedList linked;
    //While File has not reached the end
    while(!input.eof())
    {
        DoubleLinkNode *node = new DoubleLinkNode;
        input >> *node;
        linked.addNode(node);
    }
    input.close();
    ofstream output("freeplay.dat");
    char choice;
    char a;
    //Checks Update File and Drives Program
    while(update.get(choice) && update.get() == ' ')
    {
        if(isdigit(choice))
        {
            switch(choice)
            {
            case '1':
                {
                    string add;
                    getline(update, add);
                    if(checkAdd(add))
                    {
                        addRecord(add, linked, log);
                    }
                    else
                    {
                        log << "ERROR ADDING RECORD!";
                    }
                    break;
                }
            case '2':
                {
                    string searchline;
                    getline(update, searchline);
                    if(checkSearch(searchline))
                    {
                        searchRecord(searchline, linked, log);
                    }
                    else
                    {
                        log << "ERROR SEARCHING RECORD!";
                    }
                    break;
                }
            case '3':
                {
                    string editline;
                    getline(update, editline);
                    if(checkEdit(editline))
                    {
                        editRecord(editline, linked, log);
                    }
                    else
                    {
                        log << "ERROR EDITING RECORD!";
                    }
                    break;
                }
            case '4':
                {
                    string deleteline;
                    getline(update, deleteline);
                    if(checkDelete(deleteline))
                    {
                        deleteRecord(deleteline, linked, log);
                    }
                    break;
                }
            case '5':
                {

                    string sortstring;
                    getline(update, sortstring);
                    log << "ERROR SORTING RECORD!";
                    //sortRecord(sortstring, linked, log);
                }

            }
        }
    }
    int length = 0;
    while((linked[length] != NULL))
    {
        output << linked[length]->getName() << ", " << setw(9) << setfill('0') << linked[length]->getHighScore() << ", " << linked[length]->getInitials() << ", " << setw(4) << setfill('0') << linked[length]->getPlays() << ", $" << setw(7) << setfill('0') << linked[length]->getRevenue() << endl;
        length++;
    }
    //linked.printList(linked.getHead(), output);
    //Close Files
    output.close();
    update.close();
    log.close();
    return 0;
}

//Input Validation for Adding
bool checkAdd(string line)
{
    int countNum = 0;
    if(line[0] != '"')
    {
        return false;
    }
    else if(line[0] == '"')
    {
        int pos = line.rfind('"');
        if(line[pos + 1] != ' ')
        {
            return false;
        }
        else if(line[pos + 1] == ' ')
        {
            int pos2 = pos + 2;
            if(isdigit(line[pos2]))
            {
                while(isdigit(line[pos2]))
                {
                    pos2++;
                    countNum++;
                }
                if(countNum > 9)
                {
                    return false;
                }
                else if(line[pos2] != ' ')
                {
                    return false;
                }
                else if(line[pos2] == ' ')
                {
                    int pos3 = pos2 + 1;
                    if(line[pos3] == ' ')
                    {
                        return false;
                    }
                    else if(isalnum(line[pos3]))
                    {
                        for(int i = 0; i < 3; i++)
                        {
                            if(isalnum(line[pos3]))
                            {
                                pos3++;
                            }
                            else
                            {
                                return false;
                            }
                        }
                        int pos4 = pos3;
                        if(line[pos4] != ' ')
                        {
                            return false;
                        }
                        else if(line[pos4] == ' ')
                        {
                            int pos5 = pos4+1;
                            int counter = 0;
                            if(!isdigit(line[pos5]))
                            {
                                return false;
                            }
                            else if(isdigit(line[pos5]))
                            {
                                while(isdigit(line[pos5]))
                                {
                                    pos5++;
                                    counter++;
                                }
                                if(counter > 4)
                                {
                                    return false;
                                }
                                int pos6 = pos5;
                                if(line[pos6] != ' ')
                                {
                                    return false;
                                }
                                else if(line[pos6] == ' ')
                                {
                                    if(line[pos6 + 1] != '$')
                                    {
                                        return false;
                                    }
                                    else if(line[pos6 +1] == '$')
                                    {
                                        int pos7 = pos6 + 2;
                                        if(!isdigit(line[pos7]))
                                        {
                                            return false;
                                        }
                                        else if(isdigit(line[pos7]))
                                        {
                                            counter = 0;
                                            while(isdigit(line[pos7]))
                                            {
                                                pos7++;
                                                counter++;
                                            }
                                            if(counter > 4)
                                            {
                                                return false;
                                            }
                                            else if(line[pos7] != '.')
                                            {
                                                return false;
                                            }
                                            else if(line[pos7] == '.')
                                            {
                                                if(!isdigit(line[pos7 + 1]))
                                                {
                                                    return false;
                                                }
                                                else if(isdigit(line[pos7 + 1]))
                                                {
                                                    int pos8 = pos7 + 1;
                                                    counter = 0;
                                                    while(isdigit(line[pos8]))
                                                    {
                                                        pos8++;
                                                        counter++;
                                                    }
                                                    if(counter > 2)
                                                    {
                                                        return false;
                                                    }
                                                    else
                                                    {
                                                        return true;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//Adds the Record to the Linked List
void addRecord(string line, LinkedList &linked, ofstream& log)
{
    DoubleLinkNode * temp = new DoubleLinkNode;
    char b;
    int pos = line.find('"');
    int pos2 = pos + 1;
    string nameTemp = "", scoreTemp = "", initialsTemp = "", playsTemp = "", revenueTemp = "";
    while(line[pos2] != '"')
    {
        nameTemp+= line[pos2];
        pos2++;
    }
    int pos3 = pos2 + 1;
    while(line[pos3] == ' ')
    {
        pos3++;
    }
    while(line[pos3] != ' ')
    {
        scoreTemp+= line[pos3];
        pos3++;
    }
    while(line[pos3] == ' ')
    {
        pos3++;
    }
    while(line[pos3] != ' ')
    {
        initialsTemp+= line[pos3];
        pos3++;
    }
    while(line[pos3] == ' ')
    {
        pos3++;
    }
    while(line[pos3] != ' ')
    {
        playsTemp+= line[pos3];
        pos3++;
    }
    while(line[pos3] == ' ')
    {
        pos3++;
    }
    pos3++;
    while(line[pos3])
    {
        revenueTemp+= line[pos3];
        pos3++;
    }
    temp->setName(nameTemp);
    temp->setHighScore(scoreTemp);
    temp->setInitials(initialsTemp);
    temp->setPlays(playsTemp);
    temp->setRevenue(revenueTemp);
    linked.addNode(temp);
    log << "RECORD ADDED" << endl;
    log << *temp;
}

//Input Validation for Searching
bool checkSearch(string line)
{
    int pos = 0;
    if(isalpha(line[pos]) || isdigit(line[pos]))
    {
        while(isalpha(line[pos]) || isdigit(line[pos]))
        {
            pos++;
        }
        return true;
    }
    else
    {
        return false;
    }
}

//Searches for the Record
void searchRecord(string searchline, LinkedList linked, ofstream& log)
{
    if(linked.getHead() == NULL)
    {
        log << "Empty List! \n\n";
    }
    else if(isalpha(searchline[0]))
    {
        int i = 0;
        while(linked[i] != NULL)
        {
            if(linked[i]->getName() == searchline || linked[i]->getName().substr(0, linked[i]->getName().find(' ')) == searchline || linked[i]->getName().substr(linked[i]->getName().find(' ')+1, linked[i]->getName().size()) == searchline)
            {
                log << searchline << " " << " FOUND" << endl;
                log << *linked[i];
                break;
            }
            i++;
        }
        return;
    }
    else if(isdigit(searchline[0]))
    {
        int i = 0;
        int searchNum = atoi(searchline.c_str());
        while(linked[i] != NULL)
        {
            if(i == searchNum)
            {
                log << searchline << " " << " FOUND" << endl;
                log << *linked[i];
                break;
            }
            i++;
        }
        return;
    }
    else
    {
        log << "SEARCH ERROR: " << searchline << " NOT IN LIST\n\n";
    }
}

//Input Validation for Editing
bool checkEdit(string editline)
{
    int countNum = 0;
    if(editline[countNum] == '"')
    {
        countNum++;
    }
    if(!isalnum(editline[countNum]))
    {
        return false;
    }
    else
    {
        while(isalpha(editline[countNum]) || editline[countNum] == ' ')
        {
            countNum++;
        }
        if(editline[countNum] == '"')
        {
            countNum++;
        }
        if(editline[countNum] != ' ')
        {
            return false;
        }
        else if(editline[countNum] == ' ')
        {
            countNum++;
            if(!isdigit(editline[countNum]))
            {
                return false;
            }
            else if(isdigit(editline[countNum]))
            {
                if((editline[countNum] != '1') && (editline[countNum] != '2') && (editline[countNum] != '3'))
                {
                    return false;
                }
                countNum++;
                if(editline[countNum] != ' ')
                {
                    return false;
                }
                else if(editline[countNum] == ' ')
                {
                    countNum++;
                    if(!isalnum(editline[countNum]))
                    {
                        return false;
                    }
                    else if(isalnum(editline[countNum]))
                    {
                        while(editline[countNum])
                        {
                            countNum++;
                        }
                        return true;
                    }
                }
            }
        }
    }
}

//Edits the Record
void editRecord(string editline, LinkedList linked, ofstream& log)
{
    int pos = 0;
    string name = "";
    string temp;
    char a;
    if(editline[pos] == '"')
    {
        pos++;
    }
    while(isalpha(editline[pos]) || editline[pos] == ' ')
    {
        if(editline[pos]== '"')
        {
            continue;
        }
        name +=editline[pos];
        pos++;
    }
    if(editline[pos] == '"')
    {
        pos++;
    }
    pos++;
    cout << editline[pos];
    int counter = 0;
    string newValue= "";
    int playValue;
    float newRevenue;
    string floattostr;
    stringstream ss(stringstream::in | stringstream::out);
    while(linked[counter] != nullptr)
    {
        if(linked[counter]->getName() == name)
        {
            if(editline[pos] == '1')
            {
                pos++;
                pos++;
                while(isalnum(editline[pos]))
                {
                    newValue+= editline[pos];
                    pos++;
                }
                linked[counter]->setHighScore(newValue);
                log << name << " UPDATED" << endl;
                log << *linked[counter];
            }
            else if(editline[pos] == '2')
            {
                pos++;
                pos++;
                while(isalnum(editline[pos]))
                {
                    newValue+= editline[pos];
                    pos++;
                }
                linked[counter]->setInitials(newValue);
                log << name << " UPDATED" << endl;
                log << *linked[counter];
            }
            else if(editline[pos] == '3')
            {
                pos++;
                pos++;
                while(isalnum(editline[pos]))
                {
                    newValue+= editline[pos];
                    pos++;
                }
                linked[counter]->setPlays(newValue);
                playValue = atoi(newValue.c_str());
                if(playValue <= 500)
                {
                    newRevenue = playValue * .50;
                    ss<< newRevenue;
                    floattostr = ss.str();
                    linked[counter]->setRevenue(floattostr);
                    log << name << " UPDATED" << endl;
                    log << *linked[counter];
                }
                else if(playValue > 500)
                {
                    newRevenue = playValue * .25;
                    ss<< newRevenue;
                    floattostr = ss.str();
                    linked[counter]->setRevenue(floattostr);
                    log << name << " UPDATED" << endl;
                    log << *linked[counter];
                }
            }
        }
        counter++;
    }
}

//Input Validation for Deleting
bool checkDelete(string deletestring)
{
    int countNum = 0;
    if(!isalpha(deletestring[countNum]))
    {
        return false;
    }
    else if(isalpha(deletestring[countNum]))
    {
        while(deletestring[countNum])
        {
            if(isdigit(deletestring[countNum]))
            {
                return false;
            }
            else
            {
                return true;
            }
            countNum++;
        }
    }
}

//Deletes The Record
void deleteRecord(string deletestring, LinkedList linked, ofstream& log)
{
    int i = 0;
    char a;
    while(linked[i] != NULL)
    {
        if(linked[i]->getName() == deletestring || linked[i]->getName().substr(0, linked[i]->getName().find(' ')) == deletestring || linked[i]->getName().substr(linked[i]->getName().find(' ')+1, linked[i]->getName().size()) == deletestring)
        {
            linked.deleteNode(linked[i]);
            log << "RECORD DELETED!";
            return;
        }
        i++;
    }
    log << "NAME NOT FOUND!" << endl;
    return;
}

//Sorts the Record
void sortRecord(string sortstring, LinkedList linked, ofstream& log)
{
    int counter = 0;
    int length = 0;
    char a;
    string type = "";
    string kind = "";
    while(linked[length] != NULL)
    {
        length++;
    }
    while(sortstring[counter] !=  ' ')
    {
        type +=sortstring[counter];
        counter++;
    }
    if(type == "ascending" || type == "Ascending" || type == "ASCENDING" || type == "asc" || type == "ASC")
    {
        counter++;
        while(sortstring[counter])
        {
            kind+= sortstring[counter];
            counter++;
        }
        if(kind == "name" || kind == "Name" || kind == "Name")
        {
            for(int i = 1; i <= (length-1); i++)
            {
                for(int j = 0; j < (length-2); j++)
                {
                    if(linked[j+1]->getName() > linked[j]->getName())
                    {
                        swap(linked[j], linked[j+1]);
                    }
                }
            }
            return;
        }
    }
}

void swap(DoubleLinkNode* ptr, DoubleLinkNode* ptr1)
{
    DoubleLinkNode temp = *ptr;
    *ptr = *ptr1;
    *ptr1 = temp;
    return;
}
