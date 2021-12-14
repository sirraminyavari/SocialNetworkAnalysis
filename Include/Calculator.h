#ifndef __SOCIALNETWORKSANALYSIS_H
	#define __SOCIALNETWORKSANALYSIS_H
	#include "SocialNetworksAnalysis.h"
#endif

class SocialNetworksAnalysis::OperatorCodes
{
public:
	//Operator Codes
	static const int openParanthesisCode = 0;
	static const int closeParanthesisCode = 100;
	static const int plusCode = 1000;
	static const int minusCode = 1100;
	static const int multiplyCode = 2000;
	static const int divideCode = 2100;

	//Operator Priorities
	static const int openParanthesisPriority = 1000000;
	static const int closeParanthesisPriority = 1000000;
	static const int multiplyPriority = 1000;
	static const int dividePriority = 1000;
	static const int plusPriority = 500;
	static const int minusPriority = 500;
};

class SocialNetworksAnalysis::MathOperator
{
	int _operatorCode;
	int _operatorPriority;

public:
	MathOperator();
	bool set(int code);
	int get_operatorCode();
	int get_operatorPriority();
};

class SocialNetworksAnalysis::MathPhraseElement
{
	double _constValue;
	double* _variable;
	MathOperator _operator;

	ElementType _elementType;

public:
	MathPhraseElement();
	void clear();
	bool set_operator(int code);
	void set_constValue(double val);
	void set_variable(double* varPointer);
	ElementType get_elementType();
	MathOperator get_operator();
	int get_operatorCode();
	int get_operatorPriority();
	double get_constValue();	
	double get_varValue();
};

bool SocialNetworksAnalysis::compare_variables(pair<double*, string>* first, pair<double*, string>* second);

class SocialNetworksAnalysis::MathPhrase
{
	string _phraseName;
	vector<pair<double*, string>*> _variables; //the double* is a pointer to the variable and string is variable's name

	deque<MathPhraseElement*> _infixSentence;
	deque<MathPhraseElement*> _postfixSentenceStack;
	
	bool _isSortedVariables;
	bool _isValid_postfix;

	void _sort_variables();
	int _find_variable(string varName);
	void _infix2prefix(int& index);
	void infix2prefix();
	bool _compute(int& index, double& returnValue);
	void _add_mathSentence(string& mathSentence);
	void _check_before_number_addition();

public:
	MathPhrase();
	MathPhrase(string name);
	~MathPhrase();
	void clear();
	bool compute(double& returnValue);
	bool add_variable(string variableName, double value = 0);
	bool has_variable(string variableName);
	bool add_number(double value);
	bool add_number(string variableName);
	bool add_number(string variableName, double value);
	void add_operator(string op);
	void set_name(string name);
	string get_name();
	bool reassign_variable(string variableName, double value);
	void add_mathSentence(string mathSentence);
};

bool SocialNetworksAnalysis::compare_phrases(MathPhrase* first, MathPhrase* second);

class SocialNetworksAnalysis::Calculator
{
private:
	vector<MathPhrase*> _mathPhrases;
	bool _isSortedMathPhrases;

	int _last_phrase_used;

	void _sort_math_phrases();
	int _find_else_add_math_phrase(string phraseName);
	int _find_mathPhrase(string phraseName);
	bool _has_phrase(string phraseName);
	bool _has_variable(string varName, string phraseName = "");
	
public:
	Calculator();
	~Calculator();
	void clear();
	void clear(string phraseName);
	bool compute(double& returnValue, string phraseName = "");
	bool add_phrase(string phraseName);
	bool add_variable(string variableName, string phraseName = "", double value = 0);
	bool add_number(double value, string phraseName = "");
	bool add_number(string variableName, double value, string phraseName = "");
	bool add_number(string variableName, string phraseName = "");
	void add_operator(string op, string phraseName = "");
	bool reassign_variable(string variableName, double value, string phraseName = "");
	void add_mathSentence(string mathSentence, string phraseName = "");
};