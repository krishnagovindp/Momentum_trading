/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description :Defining the Strategy Design Pattern that picks the RSI
and Stochastic Oscillator that provides all the methodologies.
//============================================================================*/
#include "stdafx.h"
#include "TechnicalAnalysis-StrategyPattern.h"
#include<iostream>

using namespace std;
void RSI::performTechnicalAnalysis(stockQuotesMap & stockPriceHistory, int businessDays)
{
	cout << "perform RSI" << endl;
	//cout << businessDays << endl;
	for (int i = 14; i < businessDays; i++)
	{
		double sumPositive = 0.0;
		double sumNegative = 0.0;

		for (int j = i - 13; j <= i; j++)
		{
			if (stockPriceHistory[j].dailyChange > 0)
				sumPositive = sumPositive + stockPriceHistory[j].dailyChange;
			else if (stockPriceHistory[j].dailyChange < 0)
				sumNegative = sumNegative + stockPriceHistory[j].dailyChange;
		}

		stockPriceHistory[i].avgNegativeReturn = sumNegative / 14.0;
		stockPriceHistory[i].avgPositiveReturn = sumPositive / 14.0;

		if (sumNegative == 0)
			stockPriceHistory[i].RS = 10000000;
		else
			stockPriceHistory[i].RS = stockPriceHistory[i].avgPositiveReturn / abs(stockPriceHistory[i].avgNegativeReturn);

		stockPriceHistory[i].RSI = 100.0 - 100.0 / (1 + stockPriceHistory[i].RS);
	}

}
void RSI::findBuySellSignal(stockQuotesMap & stockPriceHistory, int businessDays)
{
	for (int i = 14; i < businessDays; i++)
	{
		if (stockPriceHistory[i].RSI > UPPER_LIMIT)
			stockPriceHistory[i].signalRSI = "Sell";
		else if (stockPriceHistory[i].RSI< LOWER_LIMIT)
			stockPriceHistory[i].signalRSI = "Buy";
	}
}
void RSI::findDecision(stockQuotesMap & stockPriceHistory, int businessDays)
{
	string actionTaken = "";
	bool firstDecision = true;
	double sharesOutstanding = 0.0;

	for (int i = 14; i < businessDays; i++)
	{
		if (stockPriceHistory[i].signalRSI == "Buy" && actionTaken == "" && firstDecision)
		{
			stockPriceHistory[i].actionTakenRSI = "Bought";
			actionTaken = "Bought";
			firstDecision = false;
			sharesOutstanding = AMOUNT_OUTSTANDING / stockPriceHistory[i].adjClose;

			stockPriceHistory[i].sharesRSI = sharesOutstanding;
			stockPriceHistory[i].amountRSI = -1.0*AMOUNT_OUTSTANDING;
			stockPriceHistory[i].profitLossRSI = 0.0;
		}
		else if (stockPriceHistory[i].signalRSI == "Sell" && actionTaken == "Bought")
		{
			stockPriceHistory[i].actionTakenRSI = "Sold";
			actionTaken = "Sold";



			stockPriceHistory[i].amountRSI = sharesOutstanding*stockPriceHistory[i].adjClose;
			sharesOutstanding = 0.0;
			stockPriceHistory[i].sharesRSI = sharesOutstanding;
			stockPriceHistory[i].profitLossRSI = stockPriceHistory[i].amountRSI - AMOUNT_OUTSTANDING;
		}
		else if (stockPriceHistory[i].signalRSI == "Buy" && actionTaken == "Sold")
		{
			stockPriceHistory[i].actionTakenRSI = "Bought";
			actionTaken = "Bought";

			sharesOutstanding = AMOUNT_OUTSTANDING / stockPriceHistory[i].adjClose;
			stockPriceHistory[i].sharesRSI = sharesOutstanding;
			stockPriceHistory[i].amountRSI = -1.0*AMOUNT_OUTSTANDING;
			stockPriceHistory[i].profitLossRSI = 0.0;
		}
		else
		{
			stockPriceHistory[i].actionTakenRSI = "";
			stockPriceHistory[i].sharesRSI = sharesOutstanding;
			stockPriceHistory[i].amountRSI = 0.0;
			stockPriceHistory[i].profitLossRSI = 0.0;
		}

	}
}


void StochasticOscillator::performTechnicalAnalysis(stockQuotesMap & stockPriceHistory, int businessDays)
{
	cout << "perform Stochastic" << endl;
	//cout << businessDays << endl;
	for (int i = 14; i < businessDays; i++)
	{
		double minLow = stockPriceHistory[i].low;
		double maxHigh = stockPriceHistory[i].high;

		for (int j = i - 13; j <= i; j++)
		{
			if (stockPriceHistory[j].high > maxHigh)
				maxHigh = stockPriceHistory[j].high;
			else if (stockPriceHistory[j].low < minLow)
				minLow = stockPriceHistory[j].low;
		}
		stockPriceHistory[i].minLow = minLow;
		stockPriceHistory[i].maxHigh = maxHigh;
		stockPriceHistory[i].stochasticIndicator = (stockPriceHistory[i].adjClose - stockPriceHistory[i].minLow) / (stockPriceHistory[i].maxHigh - stockPriceHistory[i].minLow)*100.00;
	}
}

void StochasticOscillator::findBuySellSignal(stockQuotesMap & stockPriceHistory, int businessDays)
{
	for (int i = 14; i < businessDays; i++)
	{
		if (stockPriceHistory[i].stochasticIndicator > UPPER_LIMIT)
			stockPriceHistory[i].signalSO = "Sell";
		else if (stockPriceHistory[i].stochasticIndicator< LOWER_LIMIT)
			stockPriceHistory[i].signalSO = "Buy";
	}
}


void StochasticOscillator::findDecision(stockQuotesMap & stockPriceHistory, int businessDays)
{
	string actionTaken = "";
	bool firstDecision = true;
	double sharesOutstanding = 0.0;

	for (int i = 14; i < businessDays; i++)
	{
		if (stockPriceHistory[i].signalSO == "Buy" && actionTaken == "" && firstDecision)
		{
			stockPriceHistory[i].actionTakenSO = "Bought";
			actionTaken = "Bought";
			firstDecision = false;
			sharesOutstanding = AMOUNT_OUTSTANDING / stockPriceHistory[i].adjClose;

			stockPriceHistory[i].sharesSO = sharesOutstanding;
			stockPriceHistory[i].amountSO = -1.0*AMOUNT_OUTSTANDING;
			stockPriceHistory[i].profitLossSO = 0.0;
		}
		else if (stockPriceHistory[i].signalSO == "Sell" && actionTaken == "Bought")
		{
			stockPriceHistory[i].actionTakenSO = "Sold";
			actionTaken = "Sold";

			stockPriceHistory[i].amountSO = sharesOutstanding*stockPriceHistory[i].adjClose;
			sharesOutstanding = 0.0;
			stockPriceHistory[i].sharesSO = sharesOutstanding;
			stockPriceHistory[i].profitLossSO = stockPriceHistory[i].amountSO - AMOUNT_OUTSTANDING;
		}
		else if (stockPriceHistory[i].signalSO == "Buy" && actionTaken == "Sold")
		{
			stockPriceHistory[i].actionTakenSO = "Bought";
			actionTaken = "Bought";

			sharesOutstanding = AMOUNT_OUTSTANDING / stockPriceHistory[i].adjClose;
			stockPriceHistory[i].sharesSO = sharesOutstanding;
			stockPriceHistory[i].amountSO = -1.0*AMOUNT_OUTSTANDING;
			stockPriceHistory[i].profitLossSO = 0.0;
		}
		else
		{
			stockPriceHistory[i].actionTakenSO = "";
			stockPriceHistory[i].sharesSO = sharesOutstanding;
			stockPriceHistory[i].amountSO = 0.0;
			stockPriceHistory[i].profitLossSO = 0.0;
		}

	}
}

