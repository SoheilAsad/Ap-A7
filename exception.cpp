#include <iostream>

#include "exception.h"

using namespace std;

void NotFound::what()
{
    cout << "Not Found" <<endl;
}

void BadRequest::what()
{
    cout <<"Bad Request" <<endl;
}

void PermissionDenied::what()
{
    cout <<"Permission Denied" <<endl;
}