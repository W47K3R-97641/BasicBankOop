#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
class clsClientsListScreen : protected clsScreen
{
private:
    static void _PrintClientRecordLine(clsBankClient client)
    {
        cout << "| " << setw(16) << client.accountNumber;
        cout << "| " << setw(26) << client.FullName();
        cout << "| " << setw(12) << client.phone;
        cout << "| " << setw(20) << client.email;
        cout << "| " << setw(10) << client.pinCode;
        cout << "| " << setw(12) << client.accountBalance;

        cout << endl;
    }
public:
    static void ShowClientsList()
    {
        if (!_CheckAccessRight(clsUser::enPermissions::pListClients))
            return;

        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        string title = "\t  Client List Screen";
        string subTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        clsScreen::_DrawScreenHeader(title, subTitle);

        cout << "\n_______________________________________________________";
        cout << "_________________________________________________________________\n" << endl;
        cout << "| " << left << setw(16) << "ACCOUNT NUMBER";
        cout << "| " << left << setw(26) << "CLIENT NAME";
        cout << "| " << left << setw(12) << "PHONE";
        cout << "| " << left << setw(20) << "EMAIL";
        cout << "| " << left << setw(10) << "PIN_CODE";
        cout << "| " << left << setw(12) << "BALANCE";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________________________________\n" << endl;

        if (vClients.size() == 0)
        {
            cout << "\n\t\t\t\t\tNo Clients Available In the System!";
        }
        else
        {
            for (clsBankClient client : vClients)
            {
                _PrintClientRecordLine(client);

            }
        }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________________________________\n" << endl;
    }
};


