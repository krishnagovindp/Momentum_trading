/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description : Stock is the Class that is the center of all the activity.
//============================================================================*/
#include "stdafx.h"
#include "Security-FactoryMethodPattern.h"
#include"Stock.h"
#include "dataTypes.h"
#include<iostream>
#include<boost\filesystem.hpp>
#include<iomanip>
#include <boost\algorithm\string.hpp>
using namespace std;
using namespace boost;
using namespace boost::filesystem;
Stock::Stock()
{
}

void Stock::setTechAnalysisTest(TechnicalAnalysis * _ptrTechAnalysis)
{
	ptrTechAnalysis = _ptrTechAnalysis;
}

void Stock::performTechAnalysisTest()
{
	ptrTechAnalysis->performTechnicalAnalysis(stockPriceHistory, businessDays);
	ptrTechAnalysis->findBuySellSignal(stockPriceHistory, businessDays);
	ptrTechAnalysis->findDecision(stockPriceHistory, businessDays);
}

void Stock::setPriceHistory(MarketDataAdaptor * _ptrMarketDataTarget)
{
	stockPriceHistory = _ptrMarketDataTarget->getStockPriceHistory();
}

void Stock::setbusinessDays(MarketDataAdaptor * _ptrMarketDataTarget)
{
	businessDays = _ptrMarketDataTarget->getBusinessDays();
}

void Stock::calculateReturns()
{
	for (int i = 2; i < businessDays; i++)
	{
		stockPriceHistory[i].dailyChange = stockPriceHistory[i].adjClose - stockPriceHistory[i - 1].adjClose;
		stockPriceHistory[i].dailyReturns = (stockPriceHistory[i].adjClose - stockPriceHistory[i - 1].adjClose) / stockPriceHistory[i - 1].adjClose;
	}

}




void Stock::displayStockData()
{
	for (stockQuotesMapIterator stockQuotesMapIterator = stockPriceHistory.begin(); stockQuotesMapIterator != stockPriceHistory.end(); stockQuotesMapIterator++)
	{
		if (stockQuotesMapIterator->second.actionTakenSO != "" || stockQuotesMapIterator->second.actionTakenRSI != "")
		{
			cout<<setw(2) << stockQuotesMapIterator->second.tradeDate
				<< setw(2) << "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.open
				<< setw(2) << "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.high
				<< setw(2) << "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.low
				<< setw(2) << "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.close
				<< setw(2) << "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.adjClose
				<< setw(2) << "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.dailyChange
				<< setw(2) << "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.dailyReturns
				<< setw(2) << "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.RSI
				<< setw(2) << "\t" << stockQuotesMapIterator->second.signalRSI
				<< setw(2) << "\t" << stockQuotesMapIterator->second.actionTakenRSI
				<< setw(5) << "\t" << left << fixed  << setprecision(2) << stockQuotesMapIterator->second.amountRSI
				<< setw(5) << "\t" << left << fixed << setprecision(2) << stockQuotesMapIterator->second.profitLossRSI
				<< setw(2) << "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.stochasticIndicator
				<< setw(2) << "\t" << stockQuotesMapIterator->second.signalSO
				<< setw(2) << "\t" << stockQuotesMapIterator->second.actionTakenSO
				<< setw(5) << "\t" << left << fixed << setprecision(2) << stockQuotesMapIterator->second.amountSO
				<< setw(5) << "\t" << left << fixed << setprecision(2) << stockQuotesMapIterator->second.profitLossSO
				<< endl;
		}
	}
}

void Stock::writeStockData()
{
	boost::filesystem::ofstream outputStockAnalysis;
	boost::filesystem::path outputPath = "StockAnalysis.xls";
	outputStockAnalysis.open(outputPath, ios::out);
	cout << "entering output to file" << endl;
	outputStockAnalysis << "\t" << "Sr No"
		<< "\t" << "Trade Date"
		<< "\t" << "Open"
		<< "\t" << "High"
		<< "\t" << "Low"
		<< "\t" << "Close"
		<< "\t" << "Adj Close"
		<< "\t" << "Daily Change"
		<< "\t" << "Daily Returns"
		<< "\t" << "Avg Negative Return"
		<< "\t" << "Avg Positive Return"
		<< "\t" << "RS"
		<< "\t" << "RSI"
		<< "\t" << "Signal RSI"
		<< "\t" << "Action Taken RSI"
		<< "\t" << "Shares RSI"
		<< "\t" << "Amount RSI"
		<< "\t" << "Profit/Loss RSI"
		<< "\t" << "Min Low SO"
		<< "\t" << "Max High SO"
		<< "\t" << "Stochastic Oscillator"
		<< "\t" << "Signal SO"
		<< "\t" << "Action Taken SO"
		<< "\t" << "Shares SO"
		<< "\t" << "Amount SO"
		<< "\t" << "Profit/Loss SO" << endl;

	for (stockQuotesMapIterator stockQuotesMapIterator = stockPriceHistory.begin(); stockQuotesMapIterator != stockPriceHistory.end(); stockQuotesMapIterator++)
	{
		outputStockAnalysis << "\t" << stockQuotesMapIterator->first
			<< "\t" << stockQuotesMapIterator->second.tradeDate
			<< "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.open
			<< "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.high
			<< "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.low
			<< "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.close
			<< "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.adjClose
			<< "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.dailyChange
			<< "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.dailyReturns

			<< "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.avgNegativeReturn
			<< "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.avgPositiveReturn
			<< "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.RS
			<< "\t" << fixed << setprecision(2) << stockQuotesMapIterator->second.RSI
			
			<< "\t" << stockQuotesMapIterator->second.signalRSI
			<< "\t" << stockQuotesMapIterator->second.actionTakenRSI
			<< "\t" << stockQuotesMapIterator->second.sharesRSI
			<< "\t" << stockQuotesMapIterator->second.amountRSI
			<< "\t" << stockQuotesMapIterator->second.profitLossRSI

			<< "\t" << stockQuotesMapIterator->second.minLow
			<< "\t" << stockQuotesMapIterator->second.maxHigh
			<< "\t" << stockQuotesMapIterator->second.stochasticIndicator

			<< "\t" << stockQuotesMapIterator->second.signalSO
			<< "\t" << stockQuotesMapIterator->second.actionTakenSO
			<< "\t" << stockQuotesMapIterator->second.sharesSO
			<< "\t" << stockQuotesMapIterator->second.amountSO
			<< "\t" << stockQuotesMapIterator->second.profitLossSO
			<< endl;
	}
	outputStockAnalysis.close();
	}

