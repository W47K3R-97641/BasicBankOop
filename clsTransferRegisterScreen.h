#pragma once
#include "clsScreen.h"
class clsTransferRegisterScreen : protected clsScreen
{
	static void _PrintTransferRegisterRecordLine(clsBankClient::stTransferLogRecord transferRegisterRecord)
	{
		
		cout << "| " << setw(20) << left << transferRegisterRecord.dateTime;
		cout << "| " << setw(9)  << left << transferRegisterRecord.sourceAccount;
		cout << "| " << setw(9)  << left << transferRegisterRecord.destinationAccount;
		cout << "| " << setw(19) << left << transferRegisterRecord.amount;
		cout << "| " << setw(19) << left << transferRegisterRecord.sourceAccountBalance;
		cout << "| " << setw(19) << left << transferRegisterRecord.destinationAccountBalance;
		cout << "| " << setw(15) << left << transferRegisterRecord.user;
		cout << endl;
	}
public:
	static void ShowTransferLogScreen()
	{
		vector<clsBankClient::stTransferLogRecord> vTransfersLogRecord = clsBankClient::GetTransfersLogList();

		string title = "\t  Transfer Log List Screen";
		string subTitle = "\t    (" + to_string(vTransfersLogRecord.size()) + ") Record(s).";
		clsScreen::_DrawScreenHeader(title, subTitle);
		
		cout << "\n________________________________________________________________________________________________________________________\n\n";
		cout << "| " << setw(20) << left << "DATE/TIME";
		cout << "| " << setw(9)	 << left << "S.ACC";
		cout << "| " << setw(9)  << left << "D.ACC";
		cout << "| " << setw(19) << left << "AMOUNT";
		cout << "| " << setw(19) << left << "S.BALANCE";
		cout << "| " << setw(19) << left << "D.BALANCE";
		cout << "| " << setw(15) << left << "USER";
		cout << "\n________________________________________________________________________________________________________________________\n\n";
		
		if (vTransfersLogRecord.size() == 0)
			cout << "\t\t\t\tNo Transfers Available In the System!";
		else
			for (clsBankClient::stTransferLogRecord record : vTransfersLogRecord)
			{
				_PrintTransferRegisterRecordLine(record);
			}

		cout << "________________________________________________________________________________________________________________________\n";

	}
};

