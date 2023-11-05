#pragma once
#include <iostream>
#include "clsUtil.h"
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyRateScreen :protected clsScreen

{
private:

    static float _ReadRate()
    {
        cout << "\nEnter New Rate: ";
        float newRate = 0;

        newRate = clsInputValidate::ReadFloatNumber();
        return newRate;
    }

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }

public:

    static void ShowUpdateCurrencyRateScreen()
    {

        _DrawScreenHeader("\tUpdate Currency Screen");

        string currencyCode = clsInputValidate::ReadString("\nPlease Enter Currency Code: ");

        while (!clsCurrency::IsCurrencyExist(currencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            currencyCode = clsInputValidate::ReadString();
        }

        clsCurrency currency = clsCurrency::FindByCode(currencyCode);
        _PrintCurrency(currency);


        if (clsUtil::Confirm("\nAre you sure you want to update the rate of this Currency"))
        {

            cout << "\n\nUpdate Currency Rate:";
            cout << "\n____________________\n";

            currency.UpdateRate(_ReadRate());

            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrency(currency);
        }

    }
};

