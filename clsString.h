#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class clsString
{

private:
    string _value;
public:
    clsString()
    {
        _value = "";
    }

    clsString(string Value)
    {
        _value = Value;
    }

    void SetValue(string Value) {
        _value = Value;
    }
    string GetValue() {
        return _value;
    }
    __declspec(property(get = GetValue, put = SetValue)) string Value;

    static short Length(string str)
    {
        return str.length();
    };
    short Length()
    {
        return _value.length();
    };

    static short CountWords(string str)
    {

        string delim = " "; // delimiter  
        short Counter = 0;
        short pos = 0;
        string sWord; // define a string variable  

        // use find() function to get the position of the delimiters  
        while ((pos = str.find(delim)) != std::string::npos)
        {
            sWord = str.substr(0, pos); // store the word   
            if (sWord != "")
            {
                Counter++;
            }

            //erase() until positon and move to next word.
            str.erase(0, pos + delim.length());
        }

        if (str != "")
        {
            Counter++; // it counts the last word of the string.
        }

        return Counter;

    }
    short CountWords()
    {
        return CountWords(_value);
    };

    static string  UpperFirstLetterOfEachWord(string str)
    {

        bool isFirstLetter = true;

        for (short i = 0; i < str.length(); i++)
        {

            if (str[i] != ' ' && isFirstLetter)
            {
                str[i] = toupper(str[i]);

            }

            isFirstLetter = (str[i] == ' ' ? true : false);

        }

        return str;
    }
    void  UpperFirstLetterOfEachWord()
    {
        // no need to return value , this function will directly update the object value  
        _value = UpperFirstLetterOfEachWord(_value);
    }

    static string  LowerFirstLetterOfEachWord(string str)
    {

        bool isFirstLetter = true;

        for (short i = 0; i < str.length(); i++)
        {

            if (str[i] != ' ' && isFirstLetter)
            {
                str[i] = tolower(str[i]);

            }

            isFirstLetter = (str[i] == ' ' ? true : false);

        }

        return str;
    }
    void  LowerFirstLetterOfEachWord()
    {


        // no need to return value , this function will directly update the object value  
        _value = LowerFirstLetterOfEachWord(_value);
    }

    static string  UpperAllString(string str)
    {
        for (short i = 0; i < str.length(); i++)
        {
            str[i] = toupper(str[i]);
        }
        return str;
    }
    void  UpperAllString()
    {
        _value = UpperAllString(_value);
    }

    static string  LowerAllString(string str)
    {
        for (short i = 0; i < str.length(); i++)
        {
            str[i] = tolower(str[i]);
        }
        return str;
    }
    void  LowerAllString()
    {
        _value = LowerAllString(_value);
    }

    static char  InvertLetterCase(char char1)
    {
        return isupper(char1) ? tolower(char1) : toupper(char1);
    }

    static string  InvertAllLettersCase(string str)
    {
        for (short i = 0; i < str.length(); i++)
        {
            str[i] = InvertLetterCase(str[i]);
        }
        return str;
    }
    void  InvertAllLettersCase()
    {
        _value = InvertAllLettersCase(_value);
    }

    enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 3 };
    static int CountLetters(string str, enWhatToCount WhatToCount = enWhatToCount::All)
    {


        if (WhatToCount == enWhatToCount::All)
        {
            return str.length();
        }

        int Counter = 0;

        for (int i = 0; i < str.length(); i++)
        {

            if (WhatToCount == enWhatToCount::CapitalLetters && isupper(str[i]))
                Counter++;


            if (WhatToCount == enWhatToCount::SmallLetters && islower(str[i]))
                Counter++;


        }

        return Counter;

    }
    short CountLetters(enWhatToCount WhatToCount = enWhatToCount::All)
    {
        return CountLetters(_value, WhatToCount);
    }

    static short  CountCapitalLetters(string str)
    {

        short Counter = 0;

        for (short i = 0; i < str.length(); i++)
        {

            if (isupper(str[i]))
                Counter++;

        }

        return Counter;
    }
    short  CountCapitalLetters()
    {
        return CountCapitalLetters(_value);
    }

    static short  CountSmallLetters(string str)
    {

        short Counter = 0;

        for (short i = 0; i < str.length(); i++)
        {

            if (islower(str[i]))
                Counter++;

        }

        return Counter;
    }
    short  CountSmallLetters()
    {
        return CountSmallLetters(_value);
    }

    static short  CountSpecificLetter(string str, char Letter, bool MatchCase = true)
    {

        short Counter = 0;

        for (short i = 0; i < str.length(); i++)
        {

            if (MatchCase)
            {
                if (str[i] == Letter)
                    Counter++;
            }
            else
            {
                if (tolower(str[i]) == tolower(Letter))
                    Counter++;
            }

        }

        return Counter;
    }
    short  CountSpecificLetter(char Letter, bool MatchCase = true)
    {
        return CountSpecificLetter(_value, Letter, MatchCase);
    }

    static bool IsVowel(char Ch1)
    {
        Ch1 = tolower(Ch1);

        return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));

    }

    static short  CountVowels(string str)
    {

        short Counter = 0;

        for (short i = 0; i < str.length(); i++)
        {

            if (IsVowel(str[i]))
                Counter++;

        }

        return Counter;
    }
    short  CountVowels()
    {
        return CountVowels(_value);
    }

    static vector<string> Split(string str, string Delim)
    {

        vector<string> vString;

        int pos = 0;
        string sWord; // define a string variable  

        // use find() function to get the position of the delimiters  
        while ((pos = str.find(Delim)) != std::string::npos)
        {
            sWord = str.substr(0, pos); // store the word   
            //if (sWord != "")
            //{
            vString.push_back(sWord);
            //}

            str.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
        }

        if (str != "")
        {
            vString.push_back(str); // it adds last word of the string.
        }

        return vString;

    }

    vector<string> Split(string Delim)
    {
        return Split(_value, Delim);
    }

    static string TrimLeft(string str)
    {


        for (short i = 0; i < str.length(); i++)
        {
            if (str[i] != ' ')
            {
                return str.substr(i, str.length() - i);
            }
        }
        return "";
    }
    void TrimLeft()
    {
        _value = TrimLeft(_value);
    }

    static string TrimRight(string str)
    {
        

        for (int i = str.length() - 1; i >= 0; i--)
        {
            if (str[i] != ' ')
            {
                return str.substr(0, i + 1);
            }
        }
        return "";
    }
    void TrimRight()
    {
        _value = TrimRight(_value);
    }

    static string Trim(string str)
    {
        return (TrimLeft(TrimRight(str)));

    }
    void Trim()
    {
        _value = Trim(_value);
    }

    static string Join(vector<string> vString, string Delim)
    {

        string str = "";

        for (string& s : vString)
        {
            str = str + s + Delim;
        }

        return str.substr(0, str.length() - Delim.length());


    }
    static string Join(string arrString[], short Length, string Delim)
    {

        string str = "";

        for (short i = 0; i < Length; i++)
        {
            str = str + arrString[i] + Delim;
        }

        return str.substr(0, str.length() - Delim.length());

    }

    static string ReverseWordsInString(string str)
    {

        vector<string> vString;
        string S2 = "";

        vString = Split(str, " ");

        // declare iterator
        vector<string>::iterator iter = vString.end();

        while (iter != vString.begin())
        {

            --iter;

            S2 += *iter + " ";

        }

        S2 = S2.substr(0, S2.length() - 1); //remove last space.

        return S2;
    }
    void ReverseWordsInString()
    {
        _value = ReverseWordsInString(_value);
    }

    static string ReplaceWord(string str, string StringToReplace, string sRepalceTo, bool MatchCase = true)
    {

        vector<string> vString = Split(str, " ");

        for (string& s : vString)
        {

            if (MatchCase)
            {
                if (s == StringToReplace)
                {
                    s = sRepalceTo;
                }

            }
            else
            {
                if (LowerAllString(s) == LowerAllString(StringToReplace))
                {
                    s = sRepalceTo;
                }

            }

        }

        return Join(vString, " ");
    }
    string ReplaceWord(string StringToReplace, string sRepalceTo)
    {
        return ReplaceWord(_value, StringToReplace, sRepalceTo);
    }

    static string RemovePunctuations(string str)
    {

        string S2 = "";

        for (short i = 0; i < str.length(); i++)
        {
            if (!ispunct(str[i]))
            {
                S2 += str[i];
            }
        }

        return S2;

    }
    void RemovePunctuations()
    {
        _value = RemovePunctuations(_value);
    }
};
