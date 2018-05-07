/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description :Defining basic data types that we will be using.
//============================================================================*/
#pragma once
#include<string>
#include<map>

using namespace std;

const double UPPER_LIMIT = 90.0;
const double LOWER_LIMIT = 35.0;
const double AMOUNT_OUTSTANDING = 10000.00;

struct StockQuotes
{
	double open;
	double high;
	double low;
	long double volume;
	double adjClose;
	double dailyChange;
	double dailyReturns;
	double avgNegativeReturn;
	double avgPositiveReturn;
	double RS;
	double RSI;
	string signalRSI;
	string actionTakenRSI;
	double sharesRSI;
	double amountRSI;
	double profitLossRSI;

	double maxHigh;
	double minLow;
	double stochasticIndicator;
	string signalSO;
	string actionTakenSO;
	double sharesSO;
	double amountSO;
	double profitLossSO;

	string tradeDate;
	double close;
};
typedef map<int, StockQuotes> stockQuotesMap;
typedef map<int, StockQuotes>::iterator stockQuotesMapIterator;
