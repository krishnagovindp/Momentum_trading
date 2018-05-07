/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description : Backtesting Technical Trading Strategies RSI and Stochastic Oscillator
to determine the best strategy
//============================================================================*/

/*
The following directory should be added to compiler include paths:

D:\boost_1_62_0

The following directory should be added to linker library paths:

D:\boost_1_62_0\stage\lib
BacktestingDesignPatterns.cpp : Defines the entry point for the console application.
*/
#include "stdafx.h"
#include<iostream>
#include "getInputParameters.h"
#include "Stock.h"
#include"MarketData-AdaptorPattern.h"
#include"TechnicalAnalysis-StrategyPattern.h"
#include "Security-FactoryMethodPattern.h"
#include "Logging-SingletonPattern.h"
using namespace std;
int main()
{	//Calling the Singleton Design Pattern
	Logger::GetInstance()->printLogs("start running \n");
	//Calling the Adaptor Design Pattern Implementation
	Logger::GetInstance()->printLogs("Loading Stock price history. \n");
	string stock, fromDate, toDate;
	getInputParameters(stock, fromDate, toDate);

	YahooFinanceAdaptee *ptrYahooFinance = new YahooFinanceAdaptee(stock,fromDate,toDate);

	MarketDataAdaptor *ptrMarketDataTarget = new MarketDataAdaptor(ptrYahooFinance);
	ptrMarketDataTarget->getMarketData();
	//Calling the Factory Method Design Pattern
	StockFactory stockFactory;
	Stock * stock1= dynamic_cast<Stock*>(stockFactory.createSecurity());

	stock1->setbusinessDays(ptrMarketDataTarget);
	stock1->setPriceHistory(ptrMarketDataTarget);
	stock1->calculateReturns();

	Logger::GetInstance()->printLogs("Performing Technical Analysis engine. \n");
	//Calling the Strategy Design Pattern Implementation
	RSI rsi;
	stock1->setTechAnalysisTest(&rsi);
	stock1->performTechAnalysisTest();

	StochasticOscillator so;
	stock1->setTechAnalysisTest(&so);
	stock1->performTechAnalysisTest();

	Logger::GetInstance()->printLogs("Outputting data files.\n");
	//Calling the Template Design Pattern
	stock1->displayTechnicalFindingsTemplateMethod();
	delete stock1;
	string a; cout << "Completed Backtesting. Enter any key to close command window" << endl; cin >> a;
	return 0;
}

