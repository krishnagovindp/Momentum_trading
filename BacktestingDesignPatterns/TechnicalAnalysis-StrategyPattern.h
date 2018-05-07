/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description :Defining the Strategy Design Pattern that picks the RSI
and Stochastic Oscillator that provides all the methodologies. 
//============================================================================*/
#pragma once
#include "dataTypes.h"
class TechnicalAnalysis
{
public:
	virtual void performTechnicalAnalysis(stockQuotesMap &stockPriceHistory, int businessDays) = 0;
	virtual void findBuySellSignal(stockQuotesMap & stockPriceHistory, int businessDays)=0;
	virtual void findDecision(stockQuotesMap & stockPriceHistory, int businessDays)=0;
};

class RSI :public TechnicalAnalysis
{
	void performTechnicalAnalysis(stockQuotesMap &stockPriceHistory, int businessDays);
	void findBuySellSignal(stockQuotesMap & stockPriceHistory, int businessDays);
	void findDecision(stockQuotesMap & stockPriceHistory, int businessDays);
};

class StochasticOscillator :public TechnicalAnalysis
{
	void performTechnicalAnalysis(stockQuotesMap &stockPriceHistory, int businessDays);
	void findBuySellSignal(stockQuotesMap & stockPriceHistory, int businessDays);
	void findDecision(stockQuotesMap & stockPriceHistory, int businessDays);
};

