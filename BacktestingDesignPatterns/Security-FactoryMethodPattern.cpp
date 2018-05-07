/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description :Defining the Factory Method Design Pattern that creates the
object pointers that we might need during the program.
//============================================================================*/
#include "stdafx.h"
#include "Security-FactoryMethodPattern.h"
#include "Stock.h"

Security * StockFactory::createSecurity()
{
	return new Stock();
}

Security * FuturesFactory::createSecurity()
{
	return new Futures();
}
