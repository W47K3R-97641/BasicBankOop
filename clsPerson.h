#pragma once
#include <iostream>
#include <string>
using namespace std;

class clsPerson
{

private:
    string _firstName;
    string _lastName;
    string _email;
    string _phone;
public:

    clsPerson(string firstName, string lastName, string email, string phone)
    {

        _firstName = firstName;
        _lastName = lastName;
        _email = email;
        _phone = phone;
    }

    //Property Set
    void SetFirstName(string firstName)
    {
        _firstName = firstName;
    }

    //Property Get
    string GetFirstName()
    {
        return _firstName;
    }
    __declspec(property(get = GetFirstName, put = SetFirstName)) string firstName;

    //Property Set
    void SetLastName(string lastName)
    {
        _lastName = lastName;
    }

    //Property Get
    string GetLastName()
    {
        return _lastName;
    }
    __declspec(property(get = GetLastName, put = SetLastName)) string lastName;

    //Property Set
    void SetEmail(string email)
    {
        _email = email;
    }

    //Property Get
    string GetEmail()
    {
        return _email;
    }
    __declspec(property(get = GetEmail, put = SetEmail)) string email;

    //Property Set
    void SetPhone(string phone)
    {
        _phone = phone;
    }

    //Property Get
    string GetPhone()
    {
        return _phone;
    }
    __declspec(property(get = GetPhone, put = SetPhone)) string phone;

    string FullName()
    {
        return _firstName + " " + _lastName;
    }

    

};