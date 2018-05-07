/*============================================================================
// Name : BacktestingDesignPatterns.cpp
// Author : Jacob Varughese Moolappallathu, Krishna Praturi
// Version :
// Description :Defining the Factory Method Design Pattern that creates the
object pointers that we might need during the program.
//============================================================================*/
#pragma once
class Security
{
public:
	Security() {};
	virtual ~Security() {};
};

class Futures:public Security
{
public:
	Futures() {};
	virtual ~Futures() {};
};

class SecuritiesFactory
{
public:
	SecuritiesFactory() {};
	~SecuritiesFactory() {};
	virtual Security* createSecurity() = 0;
};

class StockFactory: public SecuritiesFactory
{
public:
	StockFactory() {};
	~StockFactory() {};
	virtual Security* createSecurity();
};

class FuturesFactory : public SecuritiesFactory
{
public:
	FuturesFactory() {};
	~FuturesFactory() {};
	virtual Security* createSecurity();
};
