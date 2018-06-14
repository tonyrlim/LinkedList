//Coded By: Anthony Lim arl150130 1337.007
#include "DoubleLinkNode.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

//Default Constructor
DoubleLinkNode::DoubleLinkNode()
{
    next = NULL;
    last = NULL;
}

//Overloaded Constructor
DoubleLinkNode::DoubleLinkNode(string n, string hs, string init, string p, string r, DoubleLinkNode * nptr, DoubleLinkNode * lptr) : BaseNode(n, hs, init, p, r)
{
    next = nptr;
    last = lptr;
}

//Overloaded Constructor calls BaseNode Constructor
DoubleLinkNode::DoubleLinkNode(const DoubleLinkNode &obj, DoubleLinkNode* nptr, DoubleLinkNode* lptr) : BaseNode(obj)
{
    next = nptr;
    last = lptr;
}



