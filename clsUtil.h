#pragma once
#include "clsDate.h"
class clsUtil
{
public:

    static void Srand()
    {
        srand((unsigned)time(NULL));
    }

    static int RandomNumber(int from, int to = INT_MAX)
    {
        /*
        We Should Add Line Of Code In Main Funtions For Start Point
        srand((unsigned)time(NULL));
        */
        int RandNum = rand() % (to - from + 1) + from; // Not Include The End. So We Add 1 => To
        return RandNum;
    }

    enum enCharType { SmallLetter = 1, CapitalLetter = 2, Digit = 3, SpecialCharacter = 4, Mix = 5 };
    static char GetRandomCharacter(enCharType charType)
    {
        if (charType == Mix)
        {
            //Capital/Samll/Digits only
            charType = (enCharType)RandomNumber(1, 3);
        }
        switch (charType)
        {
        case enCharType::SmallLetter: return RandomNumber(97, 122);
        case enCharType::CapitalLetter: return RandomNumber(65, 90);
        case enCharType::SpecialCharacter: return RandomNumber(33, 47);
        case enCharType::Digit: return RandomNumber(48, 57);
        
        default: return rand();
        }
    }

    static string GenrateWord(enCharType charType, short length)
    {
        string word = "";
        for (int i = 1; i <= length; i++)
            word += GetRandomCharacter(charType);
        return word;
    }

    static string GenrateKey(enCharType charType = enCharType::Mix)
    {
        string key = "";

        key += GenrateWord(charType, 4) + '-';
        key += GenrateWord(charType, 4) + '-';
        key += GenrateWord(charType, 4) + '-';
        key += GenrateWord(charType, 4);

        return key;
    }

    static void GenrateKeys(int numberOfKeys, enCharType charType = enCharType::Mix)
    {
        for (int i = 1; i <= numberOfKeys; i++)
            cout << GenrateKey(charType) << endl;
    }

    static void Swap(int& var1, int& var2)
    {
        int temp = var1;
        var1 = var2;
        var2 = temp;
    }
    static void Swap(unsigned int& var1, unsigned int& var2)
    {
        unsigned int temp = var1;
        var1 = var2;
        var2 = temp;
    }
    static void Swap(long int& var1, long int& var2)
    {
        long int temp = var1;
        var1 = var2;
        var2 = temp;
    }
    static void Swap(unsigned long int& var1, unsigned long int& var2)
    {
        unsigned long temp = var1;
        var1 = var2;
        var2 = temp;
    }
    static void Swap(long long int& var1, unsigned long long int& var2)
    {
        unsigned long long temp = var1;
        var1 = var2;
        var2 = temp;
    }
    static void Swap(unsigned long long int& var1, unsigned long long int& var2)
    {
        unsigned long long int temp = var1;
        var1 = var2;
        var2 = temp;
    }

    static void Swap(float& var1, float& var2)
    {
        float temp = var1;
        var1 = var2;
        var2 = temp;
    }

    static void Swap(double& var1, double& var2)
    {
        double temp = var1;
        var1 = var2;
        var2 = temp;
    }
    static void Swap(long double& var1, long double& var2)
    {
        long double temp = var1;
        var1 = var2;
        var2 = temp;
    }

    static void Swap(char& var1, char& var2)
    {
        char temp = var1;
        var1 = var2;
        var2 = temp;
    }
    static void Swap(unsigned char& var1, unsigned char& var2)
    {
        unsigned char temp = var1;
        var1 = var2;
        var2 = temp;
    }
    static void Swap(wchar_t& var1, wchar_t& var2)
    {
        wchar_t temp = var1;
        var1 = var2;
        var2 = temp;
    }
    static void Swap(string& var1, string& var2)
    {
        string temp = var1;
        var1 = var2;
        var2 = temp;
    }
    static void Swap(clsDate& date1, clsDate& date2)
    {
        clsDate::SwapDates(date1, date2);
    }

    static void ShuffleArray(int arr[], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            swap(arr[RandomNumber(0, arrLength - 1)], arr[RandomNumber(0, arrLength - 1)]);
        }
    }

    static void ShuffleArray(string arr[], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            swap(arr[RandomNumber(0, arrLength - 1)], arr[RandomNumber(0, arrLength - 1)]);
        }
    }

    static void FillArrayWithRandomNumbers(int arr[], int arrLength, int from, int to)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = RandomNumber(from, to);
    }

    static void FillArrayWithRandomWords(string arr[], int arrLength, enCharType charType, int wordLength)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenrateWord(charType, wordLength);
    }

    static void FillArrayWithRandomKeys(string arr[], int arrLength, enCharType charType)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GenrateKey(charType);
    }

    static string Tabs(short numberOfTabs)
    {
        string tabs = "";
        for (int i = 0; i < numberOfTabs; i++)
            tabs += " ";
        return tabs;
    }

    static string EncryptText(string text, int key=2)
    {
        for (char& charecter : text)
        {
            charecter = ((int)charecter + key);
        }
        return text;
    }

    static string DecryptText(string text, int key=2)
    {
        for (char& charecter : text)
        {
            charecter = ((int)charecter - key);
        }
        return text;
    }

    static string NumberToText(int number)
    {

        if (number == 0)
        {
            return "";
        }

        if (number >= 1 && number <= 19)
        {
            string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
        "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
          "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

            return  arr[number] + " ";

        }

        if (number >= 20 && number <= 99)
        {
            string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
            return  arr[number / 10] + " " + NumberToText(number % 10);
        }

        if (number >= 100 && number <= 199)
        {
            return  "One Hundred " + NumberToText(number % 100);
        }

        if (number >= 200 && number <= 999)
        {
            return   NumberToText(number / 100) + "Hundreds " + NumberToText(number % 100);
        }

        if (number >= 1000 && number <= 1999)
        {
            return  "One Thousand " + NumberToText(number % 1000);
        }

        if (number >= 2000 && number <= 999999)
        {
            return   NumberToText(number / 1000) + "Thousands " + NumberToText(number % 1000);
        }

        if (number >= 1000000 && number <= 1999999)
        {
            return  "One Million " + NumberToText(number % 1000000);
        }

        if (number >= 2000000 && number <= 999999999)
        {
            return   NumberToText(number / 1000000) + "Millions " + NumberToText(number % 1000000);
        }

        if (number >= 1000000000 && number <= 1999999999)
        {
            return  "One Billion " + NumberToText(number % 1000000000);
        }
        else
        {
            return   NumberToText(number / 1000000000) + "Billions " + NumberToText(number % 1000000000);

        }

    }
    
    static bool Confirm(string message)
    {
        char answer = 'n';
        cout << message + " y / n ? ";
        cin >> answer;
        return toupper(answer) == 'Y';
    }
};