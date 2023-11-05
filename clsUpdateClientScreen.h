#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
class clsUpdateClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& client)
    {
        cout << "\nEnter FirstName:";
        client.firstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName:";
        client.lastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        client.email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        client.phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        client.pinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        client.accountBalance = clsInputValidate::ReadFloatNumber();

    }
    static void _PrintClient(clsBankClient client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.firstName;
        cout << "\nLastName    : " << client.lastName;
        cout << "\nFull Name   : " << client.FullName();
        cout << "\nEmail       : " << client.email;
        cout << "\nPhone       : " << client.phone;
        cout << "\nAcc. Number : " << client.accountNumber;
        cout << "\nPassword    : " << client.pinCode;
        cout << "\nBalance     : " << client.accountBalance;
        cout << "\n___________________\n";
    }
public:
    static void ShowUpdateClientScreen()
    {
        if (!_CheckAccessRight(clsUser::enPermissions::pUpdateClient))
            return;

        _DrawScreenHeader("\t  Update Client Screen");

        cout << "\nPlease enter client account number :";
        string accountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(accountNumber))
        {
            cout << "\nAccount number is not found, choose another one : ";
            accountNumber = clsInputValidate::ReadString();
        }

        clsBankClient client = clsBankClient::Find(accountNumber);
        _PrintClient(client);
        if (clsUtil::Confirm("\nAre You Sure Do you Want to Update This Client ?"))
        {
            cout << "\nUpdate Client Info:\n";
            cout << "\n____________________\n";

            _ReadClientInfo(client);

            clsBankClient::enSaveResults saveResult = client.Save();

            switch (saveResult)
            {
            case  clsBankClient::enSaveResults::svSucceeded:
                cout << "\nAccount updated successfully :-)\n";
                _PrintClient(client);
                break;
            case clsBankClient::enSaveResults::svFaildEmptyObject:
                cout << "\nError account was not saved because it's Empty";
                break;
            }
        }
        else
        {
            cout << "\nClient update has been cancelled.\n";
        }


    }
};

