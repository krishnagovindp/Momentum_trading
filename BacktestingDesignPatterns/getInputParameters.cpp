/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description :This function picks the inputs from the users.
//============================================================================*/
#include "stdafx.h"
#include "getInputParameters.h"
#include<iostream>
#include<string>
using namespace std;

int getInputParameters(string & _stock, string & _fromDate, string & _toDate)
{
	cout << "Enter the Stock that you want backtested:: " << endl;
	cin >> _stock;

	cout << "Enter the Date from when we need to backtest (MM/DD/YYYY):: " << endl;
	cin >> _fromDate;

	cout << "Enter the Date from when we need to backtest (MM/DD/YYYY):: " << endl;
	cin >> _toDate;
	return 0;
};