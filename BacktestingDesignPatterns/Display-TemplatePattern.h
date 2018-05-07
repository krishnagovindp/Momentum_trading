/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description :Defining the Template Method Design Pattern.
//============================================================================*/
#pragma once

class Display
{
	virtual void displayStockData() = 0;
	virtual void writeStockData() = 0;

public:
	void displayTechnicalFindingsTemplateMethod()
	{
		displayStockData();
		writeStockData();
	}

};
