#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"
class clsTotalBalancesScreen : protected clsScreen
{
private:
    static void _PrintClientRecordBalanceLine(clsBankClient client)
    {
        cout << setw(25) << left << "" << "| " << setw(15) << left << client.accountNumber;
        //cout << "| " << setw(15) << left << client.accountNumber;
        cout << "| " << setw(40) << left << client.FullName();
        cout << "| " << setw(12) << left << client.accountBalance;
    }

public:
    static void ShowTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        string title = "\t  Balances List";
        string subTitle = "\t  (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(title, subTitle);

        cout <<  "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;


        cout << setw(25) << left << "" << "| " << left << setw(15) << "ACCOUNT NUMBER";
        cout << "| " << left << setw(40) << "CLIENT NAME";
        cout << "| " << left << setw(12) << "BALANCE";
        cout << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        double totalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient client : vClients)
            {
                _PrintClientRecordBalanceLine(client);
                cout << endl;
            }

        cout << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << "\t\t\t Total Balances = " << totalBalances << endl;
        cout << "\t\t\t ( " << clsUtil::NumberToText(totalBalances) << ")";
    }
};

