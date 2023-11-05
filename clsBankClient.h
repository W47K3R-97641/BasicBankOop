#pragma once
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"


class clsBankClient : public clsPerson
{
private:
	// Declare Struct stTransferRegisterRecord
	struct stTransferLogRecord;

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _mode;

	double _accountBalance;
	string _accountNumber;
	string _pinCode;
	bool _markedForDelete = false;

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], clsUtil::DecryptText(vClientData[5]), stod(vClientData[6]));
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClients;

		fstream myFile;
		myFile.open("Clients.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";

			while (getline(myFile, line))
			{
				clsBankClient client = _ConvertLinetoClientObject(line);
				vClients.push_back(client);
			}

			myFile.close();
		}
		return vClients;
	}

	static string _ConverClientObjectToLine(clsBankClient client, string seperator = "#//#")
	{
		string clientRecord = "";

		clientRecord += client.firstName + seperator;
		clientRecord += client.lastName + seperator;
		clientRecord += client.email + seperator;
		clientRecord += client.phone + seperator;
		clientRecord += client.accountNumber + seperator;
		clientRecord += clsUtil::EncryptText(client.pinCode) + seperator;
		clientRecord += to_string(client.accountBalance);

		return clientRecord;
	}

	static void _SaveCleintsDataToFile(vector<clsBankClient> vClients)
	{
		fstream myFile;
		myFile.open("Clients.txt", ios::out);//overwrite

		if (myFile.is_open())
		{
			for (clsBankClient client : vClients)
			{
				if (!client.MarkedForDeleted())
				{
					string dataLine = _ConverClientObjectToLine(client);
					myFile << dataLine << endl;
				}
			}
			myFile.close();
		}
	}

	void _AddDataLineToFile(string dataLine)
	{
		fstream myFile;
		myFile.open("Clients.txt", ios::out | ios::app);

		if (myFile.is_open())
		{
			myFile << dataLine << endl;
			myFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> _vClients = _LoadClientsDataFromFile();

		for (clsBankClient& client : _vClients)
		{
			if (client.accountNumber == accountNumber)
			{
				client = *this;
				break;
			}
		}

		_SaveCleintsDataToFile(_vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConverClientObjectToLine(*this));
		//We need to set the mode to update after add new
		_mode = enMode::UpdateMode;
	}

	string _PrepareTransferLogRecord(clsBankClient destinationClient, double amount, string seperator = "#//#")
	{
		string transferRecord = "";

		transferRecord += clsDate::GetSystemDateTimeNow() + seperator;
		transferRecord += this->accountNumber			  + seperator;
		transferRecord += destinationClient.accountNumber + seperator;
		transferRecord += to_string(amount)               + seperator;
		transferRecord += to_string(this->accountBalance) + seperator;
		transferRecord += to_string(destinationClient.accountBalance) + seperator;
		transferRecord += currentUser.username;
		
		return transferRecord;
	}

	void _RegisterTransferLog(clsBankClient destinationClient, double amount)
	{
		string transferRecord = _PrepareTransferLogRecord(destinationClient, amount);

		fstream myFile;
		myFile.open("TransferLog.txt", ios::out | ios::app);

		if (myFile.is_open())
		{
			myFile << transferRecord << endl;
			myFile.close();
		}

	}
	
	static stTransferLogRecord _ConvertTransferRegisterLineToRecord(string line, string seperator = "#//#")
	{
		stTransferLogRecord transferRegisterRecord;
		
		vector<string> vTransferRegisterDataLine = clsString::Split(line, seperator);
		
		transferRegisterRecord.dateTime             = vTransferRegisterDataLine[0];
		transferRegisterRecord.sourceAccount        = vTransferRegisterDataLine[1];
		transferRegisterRecord.destinationAccount   = vTransferRegisterDataLine[2];
		transferRegisterRecord.amount               = stod(vTransferRegisterDataLine[3]);
		transferRegisterRecord.sourceAccountBalance = stod(vTransferRegisterDataLine[4]);
		transferRegisterRecord.destinationAccountBalance = stod(vTransferRegisterDataLine[5]);
		transferRegisterRecord.user = vTransferRegisterDataLine[6];

		return transferRegisterRecord;
	}
public:

	struct stTransferLogRecord
	{
		string user;
		string dateTime;
		string sourceAccount;
		string destinationAccount;
		double amount;
		double sourceAccountBalance;
		double destinationAccountBalance;
	};

	clsBankClient(enMode mode, string firstName, string lastName,
		string email, string phone, string accountNumber, string pinCode,
		double accountBalance) :
		clsPerson(firstName, lastName, email, phone)
	{
		_accountBalance = accountBalance;
		_accountNumber = accountNumber;
		_pinCode = pinCode;
		_mode = mode;
	}

	void SetAccountBalance(double accountBalance)
	{
		_accountBalance = accountBalance;
	}
	double GetAccountBalance()
	{
		return _accountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double accountBalance;

	void SetPinCode(string pinCode)
	{
		_pinCode = pinCode;
	}
	string GetPinCode()
	{
		return _pinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string pinCode;

	string GetAccountNumber()
	{
		return _accountNumber;
	}
	__declspec(property(get = GetAccountNumber)) string accountNumber;


	static clsBankClient Find(string accountNumber)
	{
		fstream myFile;
		myFile.open("Clients.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";
			while (getline(myFile, line))
			{
				clsBankClient client = _ConvertLinetoClientObject(line);
				if (client.accountNumber == accountNumber)
				{
					myFile.close();
					return client;
				}
			}

			myFile.close();
		}

		return _GetEmptyClientObject();
	}
	static clsBankClient Find(string accountNumber, string pinCode)
	{
		clsBankClient client = Find(accountNumber);
		if (!client.IsEmpty() && client.pinCode == pinCode)
		{
			return client;
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string accountNumber)
	{
		clsBankClient client = clsBankClient::Find(accountNumber);
		return !(client.IsEmpty());
	}

	bool IsEmpty()
	{
		return (_mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return _markedForDelete;
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 3 };

	enSaveResults Save()
	{
		switch (_mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;
		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
		case enMode::AddNewMode:
			if (clsBankClient::IsClientExist(accountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();
				return enSaveResults::svSucceeded;
			}
		}
	}

	static clsBankClient GetAddNewClientObject(string accountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", accountNumber, "", 0);
	}

	bool Delete()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& client : vClients)
		{
			if (client.accountNumber == accountNumber)
			{
				client._markedForDelete = true;
				break;
			}
		}

		_SaveCleintsDataToFile(vClients);
		*this = _GetEmptyClientObject();

		return true;
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> vClients = GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient client : vClients)
		{
			TotalBalances += client.accountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double amount)
	{
		_accountBalance += amount;
		Save();
	}


	bool Withdraw(double amount)
	{
		if (amount <= accountBalance)
		{
			accountBalance -= amount;
			Save();
			return true;
		}
		return false;
	}

	bool Transfer(double amount, clsBankClient& destinationClient)
	{
		if (amount > this->accountBalance)
		{
			return false;
		}

		this->Withdraw(amount);
		destinationClient.Deposit(amount);
		
		_RegisterTransferLog(destinationClient, amount);
		
		return true;
	}


	static vector<stTransferLogRecord> GetTransfersLogList()
	{
		fstream myFile;
		
		vector<stTransferLogRecord> vTransfersLogList;
		
		myFile.open("TransferLog.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";
			while (getline(myFile, line))
			{
				stTransferLogRecord record = _ConvertTransferRegisterLineToRecord(line);
				vTransfersLogList.push_back(record);
			}

			myFile.close();
		}

		return vTransfersLogList;
	}

	
};