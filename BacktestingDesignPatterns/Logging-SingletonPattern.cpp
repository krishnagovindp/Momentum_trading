/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description :Defining the Singleton pattern with logging features.
//============================================================================*/
//#include "StdAfx.h"
#include "stdafx.h"
#include "Logging-SingletonPattern.h"
#include <stdarg.h>

using namespace std;

Logger* Logger::m_pInstance = NULL;

Logger::Logger(void)
{
	outputStockAnalysis.open(outputLogPath, ios::out); // open file at first time
}

Logger::~Logger(void)
{
	outputStockAnalysis.close(); // close file
}

Logger*  Logger::GetInstance()
{
	if (!m_pInstance)   // Only allow one instance of class to be generated.
		m_pInstance = new Logger;

	return m_pInstance;
}

void Logger::printLogs(char *format, ...) // wrie formated string into file
{
	outputStockAnalysis << format;

}