/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description :Defining the Adaptor class that retrieves data from yahoo Finance.
//============================================================================*/
#include "stdafx.h"
#include "MarketData-AdaptorPattern.h"
#include<string>
#include<boost\filesystem.hpp>
#include <boost\algorithm\string.hpp>
#include <boost\lexical_cast.hpp>
#include <sstream> 
#include <urlmon.h>
#include <tchar.h>
#include<iomanip>

#pragma comment(lib, "urlmon.lib")

using namespace std;
using namespace boost;
using namespace boost::filesystem;
using namespace boost::algorithm;

class YahooFinanceAdaptee;
void YahooFinanceAdaptee::loadStockPrice()
{
	stringstream strStream;
	vector<string> _fromDate;
	vector<string> _toDate;

	boost::algorithm::split(_fromDate, fromDate, is_any_of("/."), token_compress_on);
	boost::algorithm::split(_toDate, toDate, is_any_of("/."), token_compress_on);

	vector < string > vec = { "http://chart.finance.yahoo.com/table.csv?s=",
		stockCode,
		"&a=",lexical_cast<string>(lexical_cast<int>(_fromDate[0]) - 1),
		"&b=",lexical_cast<string>(_fromDate[1]),
		"&c=",lexical_cast<string>(_fromDate[2]),
		"&d=",lexical_cast<string>(lexical_cast<int>(_toDate[0]) - 1),
		"&e=",lexical_cast<string>(_toDate[1]),
		"&f=",lexical_cast<string>(_toDate[2]),
		"&g=d&ignore=.csv" };
	//string szWebSite = "http://chart.finance.yahoo.com/table.csv?s=AMZN&a=10&b=16&c=2011&d=10&e=16&f=2016&g=d&ignore=.csv";

	string szWebSite;
	szWebSite = join(vec, "");
	this->downloadFile(szWebSite, strStream);

	char   TradeDate[26] = "";
	double OpenPrice = 0.0;
	double HighPrice = 0.0;
	double LowPrice = 0.0;
	double TodayClose = 0.0;
	long   Volume = 0;
	double AdjClose = 0.0;
	char szSub[100];

	strStream.ignore(1024, '\n'); // ignore first line
	string strStreamString = strStream.str();
	businessDays = count(strStreamString.begin(), strStreamString.end(), '\n') - 1;

	int counter = businessDays;
	while (strStream.good())
	{
		if (!strStream.getline(szSub, sizeof(szSub), ','))
			break;

		strcpy_s(TradeDate, sizeof(TradeDate), szSub); //trade date

		strStream.getline(szSub, sizeof(szSub), ',');
		OpenPrice = atof(szSub);					// open price

		strStream.getline(szSub, sizeof(szSub), ',');
		HighPrice = atof(szSub);					// high price

		strStream.getline(szSub, sizeof(szSub), ',');
		LowPrice = atof(szSub);					// Low price

		strStream.getline(szSub, sizeof(szSub), ',');
		TodayClose = atof(szSub);					// Today Close

		strStream.getline(szSub, sizeof(szSub), ',');
		Volume = atoi(szSub);						// Volume

		strStream.getline(szSub, sizeof(szSub));
		AdjClose = atof(szSub);					// Adjust Close

		stockQuote.tradeDate = TradeDate;
		stockQuote.open = OpenPrice;
		stockQuote.high = HighPrice;
		stockQuote.low = LowPrice;
		stockQuote.close = TodayClose;
		stockQuote.volume = Volume;
		stockQuote.adjClose = AdjClose;

		stockQuoteSeries[counter] = stockQuote;

		counter = counter - 1;
	};
}

void YahooFinanceAdaptee::downloadFile(const string & szWebSite, stringstream & strStream)
{
	IStream* pStream = 0;
	wstring stemp = wstring(szWebSite.begin(), szWebSite.end());
	LPCWSTR sw = stemp.c_str();
	URLOpenBlockingStream(0, sw, &pStream, 0, 0); // Open WebLink
	if (pStream == 0) return;  // failure 

	while (pStream != 0)
	{
		DWORD dwGot = 0;
		char szBuffer[200] = "";

		if (pStream->Read(szBuffer, sizeof(szBuffer) - 1, &dwGot) != S_OK)
			break;

		strStream << szBuffer;
	};

	if (pStream)	pStream->Release();
}

stockQuotesMap YahooFinanceAdaptee::getStockPriceHistory()
{
	return stockQuoteSeries;
}

int YahooFinanceAdaptee::getBusinessDays()
{
	return businessDays;
}

YahooFinanceAdaptee::YahooFinanceAdaptee(string _stockCode, string _fromDate, string _toDate)
{
	stockCode = _stockCode;
	fromDate = _fromDate;
	toDate = _toDate;
}

MarketDataAdaptor::MarketDataAdaptor(YahooFinanceAdaptee * _ptrYahooFinanceAdaptee)
{
	ptrYahooFinanceAdaptee = _ptrYahooFinanceAdaptee;
}

void MarketDataAdaptor::getMarketData()
{
	
	ptrYahooFinanceAdaptee->loadStockPrice();
}

int MarketDataAdaptor::getBusinessDays()
{
	return ptrYahooFinanceAdaptee->getBusinessDays();
}

stockQuotesMap MarketDataAdaptor::getStockPriceHistory()
{
	return ptrYahooFinanceAdaptee->getStockPriceHistory();
}
