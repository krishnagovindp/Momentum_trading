/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description :Defining the Singleton pattern with logging features.
//============================================================================*/
#pragma once
#include <stdio.h>
#include<boost\filesystem.hpp>
#define LOG_FILE	"TestResult.txt"

class Logger
{
public:
	static Logger* GetInstance();     // get Instance
	void printLogs(char *format, ...);  // print into file

private:
	Logger(void);				// cannot intantiate an object 
	Logger(Logger const&) {};    // cannot copy
	~Logger(void);

	boost::filesystem::ofstream outputStockAnalysis;
	boost::filesystem::path outputLogPath = "Log-StockAnalysis.dat";
	//FILE *m_pf;
	static Logger* m_pInstance;
};

