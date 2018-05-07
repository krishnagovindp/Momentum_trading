/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description : Stock is the Class that is the center of all the activity.
//============================================================================*/
#pragma once
#include "stdafx.h"
#include "Security-FactoryMethodPattern.h"
#include "TechnicalAnalysis-StrategyPattern.h"
#include "MarketData-AdaptorPattern.h"
#include "Display-TemplatePattern.h"

class Stock:public Security,public Display
{
private:
	stockQuotesMap stockPriceHistory;
	int businessDays;
	TechnicalAnalysis * ptrTechAnalysis;
	string stockCode;

	void displayStockData();
	void writeStockData();

public:
	Stock();

	void setTechAnalysisTest(TechnicalAnalysis * _ptrTechAnalysis);
	void performTechAnalysisTest();
	void setPriceHistory(MarketDataAdaptor *_ptrMarketDataTarget);
	void setbusinessDays(MarketDataAdaptor * _ptrMarketDataTarget);
	void calculateReturns();
};
