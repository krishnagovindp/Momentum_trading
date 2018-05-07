/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description :Defining the Adaptor class that retrieves data from yahoo Finance.
//============================================================================*/
#pragma once
#include "dataTypes.h"
#include<vector>
#include<string>
class YahooFinanceAdaptee
{
	string stockCode;
	string fromDate;
	string toDate;
	stockQuotesMap stockQuoteSeries;
	StockQuotes stockQuote;
	int businessDays;

public:
	void loadStockPrice();
	void downloadFile(const string & szWebSite, stringstream &strStream);
	stockQuotesMap getStockPriceHistory();
	int getBusinessDays();
	YahooFinanceAdaptee(string _stockCode, string _fromDate, string _toDate);
};
class MarketDataTarget
{
public:
	void virtual getMarketData() = 0;
};
class MarketDataAdaptor :public MarketDataTarget 
{

public:
	YahooFinanceAdaptee *ptrYahooFinanceAdaptee;
	MarketDataAdaptor(YahooFinanceAdaptee *_ptrYahooFinanceAdaptee);
	void getMarketData();
	int getBusinessDays();
	stockQuotesMap getStockPriceHistory();

};