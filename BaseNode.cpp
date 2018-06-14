//Coded By: Anthony Lim arl150130 1337.007
#include "BaseNode.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

//Default Constructor
BaseNode::BaseNode()
{
    name = "";
    highScore = "";
    initials = "";
    plays = "";
    revenue = "";
}

//Overloaded Constructor
BaseNode::BaseNode(string n, string hs, string init, string p, string r)
{
    name = n;
    highScore = hs;
    initials = init;
    plays = p;
    revenue = r;
}

//Overloaded Constructor
BaseNode::BaseNode(const BaseNode &obj)
{
    name = obj.name;
    highScore = obj.highScore;
    initials = obj.initials;
    plays = obj.plays;
    revenue = obj.revenue;
}

//Overload Output Operator
ostream& operator<<(ostream& out, const BaseNode& obj)
{
    out << "Name: " << obj.name << endl
       << "High Score: " << obj.highScore << endl
       << "Initials: " << obj.initials << endl
       << "Plays: " << obj.plays << endl
       << "Revenue: " << obj.revenue << endl << endl;

    return out;
}

//Overloaded Input Operator
istream& operator>>(istream& in, BaseNode& obj)
{
    string namz;
    string highz;
    string init;
    string playz;
    string revz;

    getline(in, namz, ',');
    obj.name = namz;
    in.ignore();

    getline(in, highz, ',');
    obj.highScore = highz;
    in.ignore();

    getline(in, init, ',');
    obj.initials = init;
    in.ignore();

    getline(in, playz, ',');
    obj.plays = playz;
    in.ignore(2);

    getline(in, revz);
    obj.revenue = revz;
    //in.clear();
    return in;
}
