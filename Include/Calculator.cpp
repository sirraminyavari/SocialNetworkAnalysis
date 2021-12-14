#ifndef __CALCULATOR_H
	#define __CALCULATOR_H
	#include "Calculator.h"
#endif

///////////////////////////////////////////////
//MathOperator
///////////////////////////////////////////////

SocialNetworksAnalysis::MathOperator::MathOperator()
{
	this->_operatorCode = NOT_SET;
	this->_operatorPriority = NOT_SET;
}

bool SocialNetworksAnalysis::MathOperator::set(int code)
{
	this->_operatorCode = code;
	
	switch(code)
	{
	case  SocialNetworksAnalysis::OperatorCodes::openParanthesisCode:
		this->_operatorPriority = OperatorCodes::openParanthesisPriority;
		return true;
	case SocialNetworksAnalysis::OperatorCodes::closeParanthesisCode:
		this->_operatorPriority = SocialNetworksAnalysis::OperatorCodes::closeParanthesisPriority;
		return true;
	case SocialNetworksAnalysis::OperatorCodes::plusCode:
		this->_operatorPriority = SocialNetworksAnalysis::OperatorCodes::plusPriority;
		return true;
	case SocialNetworksAnalysis::OperatorCodes::minusCode:
		this->_operatorPriority = SocialNetworksAnalysis::OperatorCodes::minusPriority;
		return true;
	case SocialNetworksAnalysis::OperatorCodes::multiplyCode:
		this->_operatorPriority = SocialNetworksAnalysis::OperatorCodes::multiplyPriority;
		return true;
	case SocialNetworksAnalysis::OperatorCodes::divideCode:
		this->_operatorPriority = SocialNetworksAnalysis::OperatorCodes::dividePriority;
		return true;
	default:
		this->_operatorCode = NOT_SET;
		this->_operatorPriority = NOT_SET;
		return false;
	} //end of swith(code)
}

int SocialNetworksAnalysis::MathOperator::get_operatorCode()
{
	return this->_operatorCode;
}

int SocialNetworksAnalysis::MathOperator::get_operatorPriority()
{
	return this->_operatorPriority;
}

///////////////////////////////////////////////
//MathPhraseElement
///////////////////////////////////////////////

SocialNetworksAnalysis::MathPhraseElement::MathPhraseElement()
{
	this->_constValue = 0;
	this->_variable = NULL;
	this->_elementType = ElementType::NotSet;
}

void SocialNetworksAnalysis::MathPhraseElement::clear()
{
	this->_elementType = ElementType::NotSet;
}

bool SocialNetworksAnalysis::MathPhraseElement::set_operator(int code)
{
	if(this->_operator.set(code))
	{
		this->_elementType = ElementType::Operator;
		return true;
	}
	else
	{
		this->_elementType = ElementType::NotSet;
		return false;
	}
}
	
void SocialNetworksAnalysis::MathPhraseElement::set_constValue(double val)
{
	this->_constValue = val;
	this->_elementType = ElementType::Constant;
}
	
void SocialNetworksAnalysis::MathPhraseElement::set_variable(double* varPointer)
{
	this->_variable = varPointer;
	this->_elementType = ElementType::Variable;
}
	
SocialNetworksAnalysis::ElementType SocialNetworksAnalysis::MathPhraseElement::get_elementType()
{
	return this->_elementType;
}

SocialNetworksAnalysis::MathOperator SocialNetworksAnalysis::MathPhraseElement::get_operator()
{
	return this->_operator;
}

int SocialNetworksAnalysis::MathPhraseElement::get_operatorCode()
{
	return this->_operator.get_operatorCode();
}

int SocialNetworksAnalysis::MathPhraseElement::get_operatorPriority()
{
	return this->_operator.get_operatorPriority();
}

double SocialNetworksAnalysis::MathPhraseElement::get_constValue()
{
	return this->_constValue;
}
	
double SocialNetworksAnalysis::MathPhraseElement::get_varValue()
{
	if(this->_elementType != ElementType::Variable)
		return 0;
	else
		return *this->_variable;
}

///////////////////////////////////////////////

bool SocialNetworksAnalysis::compare_variables(pair<double*, string>* first, pair<double*, string>* second)
{
	if(first->second < second->second)
		return true;
	else
		return false;
}

///////////////////////////////////////////////
//MathPhrase
///////////////////////////////////////////////

void SocialNetworksAnalysis::MathPhrase::_sort_variables()
{
	sort(this->_variables.begin(), this->_variables.end(), SocialNetworksAnalysis::compare_variables);

	this->_isSortedVariables = true;
}

int SocialNetworksAnalysis::MathPhrase::_find_variable(string varName)
{
	if(!this->_isSortedVariables) this->_sort_variables();

	int startIndicator = 0;
	int endIndicator = this->_variables.size() - 1;
	int middleIndicator = (endIndicator - startIndicator) / 2;

	while(startIndicator <= endIndicator)
	{
		if(this->_variables[startIndicator]->second == varName)
			return startIndicator;
		else if(this->_variables[endIndicator]->second == varName)
			return endIndicator;
		else if(this->_variables[middleIndicator]->second == varName)
			return middleIndicator;
		else
		{
			if(this->_variables[middleIndicator]->second < varName)
			{
				startIndicator = middleIndicator + 1;
				--endIndicator;
			}
			else
			{
				endIndicator = middleIndicator - 1;
				++startIndicator;
			}

			middleIndicator = (endIndicator - startIndicator) / 2;
		}
	} //end of while(startIndicator <= endIndicator)

	return NOT_SET;
}

void SocialNetworksAnalysis::MathPhrase::_infix2prefix(int& index)
{
	if(index <= 0)
	{
		index = 0;
		this->_postfixSentenceStack.clear();
	}

	deque<MathPhraseElement*> operatorsStack;

	int infixSentenceSize = this->_infixSentence.size();
	for(; index < infixSentenceSize; ++index)
	{
		if(this->_infixSentence[index]->get_elementType() == ElementType::Operator)
		{
			if(this->_infixSentence[index]->get_operatorCode() == OperatorCodes::closeParanthesisCode)
			{
				++index;
				break;
			}
			else if(this->_infixSentence[index]->get_operatorCode() == OperatorCodes::openParanthesisCode)
			{
				++index;
				this->_infix2prefix(index);
				--index; //because the continue increments the index
				continue;
			}

			while(!operatorsStack.empty())
			{
				if(this->_infixSentence[index]->get_operatorPriority() > 
					operatorsStack.back()->get_operatorPriority()) 
					break;

				this->_postfixSentenceStack.push_back(operatorsStack.back());
				operatorsStack.pop_back();
			}
			operatorsStack.push_back(this->_infixSentence[index]);
		}
		else //infixSentence[index].isVariable = true
		{
			this->_postfixSentenceStack.push_back(this->_infixSentence[index]);
		}
	} //for(; index != infixSentence.size(); ++index)

	while(!operatorsStack.empty())
	{
		this->_postfixSentenceStack.push_back(operatorsStack.back());
		operatorsStack.pop_back();
	}
}

void SocialNetworksAnalysis::MathPhrase::infix2prefix()
{
	MathPhraseElement* openPeranthesis = new MathPhraseElement;
	openPeranthesis->clear();

	openPeranthesis->set_operator(OperatorCodes::openParanthesisCode);
	this->_infixSentence.push_front(openPeranthesis);

	MathPhraseElement* closePeranthesis = new MathPhraseElement;
	closePeranthesis->clear();

	closePeranthesis->set_operator(OperatorCodes::closeParanthesisCode);
	this->_infixSentence.push_back(closePeranthesis);

	int index = 0;
	_infix2prefix(index);
}

bool SocialNetworksAnalysis::MathPhrase::_compute(int& index, double& returnValue)
{
	if(index < 0) return 0;

	double first = 0, second = 0;
	ElementType et = this->_postfixSentenceStack[index]->get_elementType();
	if(et == ElementType::Constant)
	{
		returnValue = this->_postfixSentenceStack[index]->get_constValue();
		--index;
		return true;
	}
	else if(et == ElementType::Variable)
	{
		returnValue = this->_postfixSentenceStack[index]->get_varValue();
		--index;
		return true;
	}
	else
	{
		int operatorCode = this->_postfixSentenceStack[index]->get_operatorCode();
		--index;
		this->_compute(index, second);
		this->_compute(index, first);

		switch(operatorCode)
		{
		case OperatorCodes::plusCode:
			returnValue = first + second;
			break;
		case OperatorCodes::minusCode:
			returnValue = first - second;
			break;
		case OperatorCodes::multiplyCode:
			returnValue = first * second;
			break;
		case OperatorCodes::divideCode:
			if(second == 0.0) return false;
			returnValue = first / second;
			break;
		}

		return true;
	}
}

void SocialNetworksAnalysis::MathPhrase::_add_mathSentence(string& mathSentence)
{
	int index = 0;

	int mathSentenceSize = mathSentence.size();
	while(index < mathSentenceSize)
	{
		switch(mathSentence[index])
		{
		case '(':
			add_operator("(");
			++index;
			break;
		case ')':
			add_operator(")");
			++index;
			break;
		case '+':
			add_operator("+");
			++index;
			break;
		case '-':
			add_operator("-");
			++index;
			break;
		case '*':
			add_operator("*");
			++index;
			break;
		case '/':
			add_operator("/");
			++index;
			break;
		default:
			double intPart;
			double floatPart;
			double floatPartDividened;
			double num;

			intPart = 0;
			floatPart = 0;
			floatPartDividened = 1;
			num = 0;

			for(; index < mathSentenceSize && mathSentence[index] >= '0' && mathSentence[index] <= '9'; ++index)
				intPart = (10 * intPart) + mathSentence[index] - '0';

			if(index < mathSentenceSize && mathSentence[index] == '.')
			{
				++index;
				for(; index < mathSentenceSize && mathSentence[index] >= '0' && mathSentence[index] <= '9'; ++index)
				{
					floatPart = (10 * floatPart) + mathSentence[index] - '0';
					floatPartDividened *= 10;
				}

				if(mathSentence[index] == '.' && index < mathSentenceSize)
					while(index < mathSentenceSize && 
						((mathSentence[index] >= '0' && mathSentence[index] <= '9') || mathSentence[index] == '.'))
						++index;
			}

			if(floatPartDividened == 0)
				num = intPart;
			else
				num = intPart + (floatPart / (10 * floatPartDividened));
			add_number(num);
		} //end of switch(mathSentence[index])
	} //end of while(index < mathSentence.size())
}

void SocialNetworksAnalysis::MathPhrase::_check_before_number_addition()
{
	if(!this->_infixSentence.empty())
	{
		bool isNum = this->_infixSentence.back()->get_elementType() == ElementType::Variable ||
			this->_infixSentence.back()->get_elementType() == ElementType::Constant; 

		if(isNum || this->_infixSentence.back()->get_operatorCode() == OperatorCodes::closeParanthesisCode)
			add_operator("*");
	}
}

SocialNetworksAnalysis::MathPhrase::MathPhrase()
{
	this->clear();
}

SocialNetworksAnalysis::MathPhrase::MathPhrase(string name)
{
	this->clear();
	this->_phraseName = name;
}

SocialNetworksAnalysis::MathPhrase::~MathPhrase()
{
	this->clear();
}

void SocialNetworksAnalysis::MathPhrase::clear()
{
	for(int i = 0; i < this->_variables.size(); ++i)
	{
		delete this->_variables[i]->first;
		delete this->_variables[i];
	}

	for(int i = 0; i < this->_infixSentence.size(); ++i)
		delete this->_infixSentence[i]; 
	//all elements in _postfixSentenceStack, already exist in _infixSentence
	//and no there is no reason for deleting _postfixSentenceStack's elements
		
	this->_variables.clear();
	this->_infixSentence.clear();
	this->_postfixSentenceStack.clear();
	this->_isSortedVariables = false;
	this->_isValid_postfix = false;
}

bool SocialNetworksAnalysis::MathPhrase::compute(double& returnValue)
{
	if(!this->_isValid_postfix)
	{
		this->infix2prefix();
		this->_isValid_postfix = true;
	}

	if(this->_postfixSentenceStack.empty()) return 0;

	int index = this->_postfixSentenceStack.size() - 1;
	return _compute(index, returnValue);
}

bool SocialNetworksAnalysis::MathPhrase::add_variable(string variableName, double value)// = 0)
{
	if(variableName == "") return false;
		
	int index = this->_find_variable(variableName);

	if(index != NOT_SET) 
		return false;
	else
	{
		if(this->_variables.size() && this->_variables.back()->second > variableName)
			this->_isSortedVariables = false;
		else if(!this->_variables.size())
			this->_isSortedVariables = true;

		pair<double*, string>* temp = new pair<double*, string>;
		temp->first = new double;
		*temp->first = value;
		temp->second = variableName;
		this->_variables.push_back(temp);

		return true;
	}
}

bool SocialNetworksAnalysis::MathPhrase::has_variable(string variableName)
{
	if(this->_find_variable(variableName) < 0)
		return false;
	else
		return true;
}

bool SocialNetworksAnalysis::MathPhrase::add_number(double value)
{
	this->_check_before_number_addition();

	MathPhraseElement* temp = new MathPhraseElement;
	temp->set_constValue(value);

	this->_infixSentence.push_back(temp);

	this->_isValid_postfix = false;

	return true;
}

bool SocialNetworksAnalysis::MathPhrase::add_number(string variableName)
{
	if(variableName == "") return false;

	this->_check_before_number_addition();

	int index = this->_find_variable(variableName);

	if(index == NOT_SET)
	{
		this->add_variable(variableName);
		index = this->_variables.size() - 1;
	}

	MathPhraseElement* temp = new MathPhraseElement;
	temp->set_variable(this->_variables[index]->first);

	this->_infixSentence.push_back(temp);

	this->_isValid_postfix = false;

	return true;
}

bool SocialNetworksAnalysis::MathPhrase::add_number(string variableName, double value)
{
	if(variableName == "") return false;

	this->_check_before_number_addition();

	int index = this->_find_variable(variableName);

	if(index == NOT_SET)
	{
		this->add_variable(variableName, value);
		index = this->_variables.size() - 1;
	}
	else
		*this->_variables[index]->first = value;

	MathPhraseElement* temp = new MathPhraseElement;
	temp->set_variable(this->_variables[index]->first);

	this->_infixSentence.push_back(temp);

	this->_isValid_postfix = false;

	return true;
}

void SocialNetworksAnalysis::MathPhrase::add_operator(string op)
{
	if(!this->_infixSentence.empty())
	{
		bool isNum = this->_infixSentence.back()->get_elementType() == ElementType::Variable ||
			this->_infixSentence.back()->get_elementType() == ElementType::Constant;

		if((isNum && op == "(") || 
			(!isNum && this->_infixSentence.back()->get_operatorCode() == OperatorCodes::closeParanthesisCode && op == "("))
			add_operator("*");
	}

	MathPhraseElement* temp = new MathPhraseElement;

	temp->clear();

	if(op == "(")
		temp->set_operator(OperatorCodes::openParanthesisCode);
	else if(op == ")")
		temp->set_operator(OperatorCodes::closeParanthesisCode);
	else if(op == "+")
		temp->set_operator(OperatorCodes::plusCode);
	else if(op == "-")
		temp->set_operator(OperatorCodes::minusCode);
	else if(op == "*")
		temp->set_operator(OperatorCodes::multiplyCode);
	else if(op == "/")
		temp->set_operator(OperatorCodes::divideCode);

	this->_infixSentence.push_back(temp);
	this->_isValid_postfix = false;
}

void SocialNetworksAnalysis::MathPhrase::set_name(string name)
{
	this->_phraseName = name;
}

string SocialNetworksAnalysis::MathPhrase::get_name()
{
	return this->_phraseName;
}

bool SocialNetworksAnalysis::MathPhrase::reassign_variable(string variableName, double value)
{
	int index = this->_find_variable(variableName);

	if(index < 0) 
		return false;
	else
	{
		*this->_variables[index]->first = value;
		return true;
	}
}

void SocialNetworksAnalysis::MathPhrase::add_mathSentence(string mathSentence)
{
	string str = "";
	for(int i = 0; i < mathSentence.size(); ++i)
		if(mathSentence[i] == '(' || mathSentence[i] == ')' || mathSentence[i] == '+' || mathSentence[i] == '-' ||
			mathSentence[i] == '*' || mathSentence[i] == '/' || mathSentence[i] == '.' ||
			(mathSentence[i] >= '0' && mathSentence[i] <= '9'))
			str += mathSentence[i];

	this->_add_mathSentence(str);
}

///////////////////////////////////////////////

bool SocialNetworksAnalysis::compare_phrases(MathPhrase* first, MathPhrase* second)
{
	if(first->get_name() < second->get_name())
		return true;
	else
		return false;
}

///////////////////////////////////////////////
//Calculator
///////////////////////////////////////////////

void SocialNetworksAnalysis::Calculator::_sort_math_phrases()
{
	sort(this->_mathPhrases.begin(), this->_mathPhrases.end(), SocialNetworksAnalysis::compare_phrases);

	this->_isSortedMathPhrases = true;
	this->_last_phrase_used = NOT_SET;
}

int SocialNetworksAnalysis::Calculator::_find_else_add_math_phrase(string phraseName)
{
	int index = this->_find_mathPhrase(phraseName);

	if(index < 0) 
	{
		if(this->_mathPhrases.size() && this->_mathPhrases.back()->get_name() > phraseName)
			this->_isSortedMathPhrases = false;
		else if(!this->_mathPhrases.size())
			this->_isSortedMathPhrases = true;

		MathPhrase* temp = new MathPhrase(phraseName);
		this->_mathPhrases.push_back(temp);

		this->_last_phrase_used = this->_mathPhrases.size() - 1;

		return this->_last_phrase_used;
	}
	else
		return index;
}

int SocialNetworksAnalysis::Calculator::_find_mathPhrase(string phraseName)
{
	if(!this->_isSortedMathPhrases) this->_sort_math_phrases();

	int startIndicator = 0;
	int endIndicator = this->_mathPhrases.size() - 1;
	int middleIndicator = (endIndicator - startIndicator) / 2;

	while(startIndicator <= endIndicator)
	{
		if(this->_mathPhrases[startIndicator]->get_name() == phraseName)
			return startIndicator;
		else if(this->_mathPhrases[endIndicator]->get_name() == phraseName)
			return endIndicator;
		else if(this->_mathPhrases[middleIndicator]->get_name() == phraseName)
			return middleIndicator;
		else
		{
			if(this->_mathPhrases[middleIndicator]->get_name() < phraseName)
			{
				startIndicator = middleIndicator + 1;
				--endIndicator;
			}
			else
			{
				endIndicator = middleIndicator - 1;
				++startIndicator;
			}

			middleIndicator = (endIndicator - startIndicator) / 2;
		}
	} //end of while(startIndicator <= endIndicator)

	return NOT_SET;
}

bool SocialNetworksAnalysis::Calculator::_has_phrase(string phraseName)
{
	if(this->_find_mathPhrase(phraseName) < 0)
		return false;
	else
		return true;
}

bool SocialNetworksAnalysis::Calculator::_has_variable(string varName, string phraseName)// = "")
{
	if(this->_last_phrase_used == NOT_SET || this->_mathPhrases[this->_last_phrase_used]->get_name() != phraseName)
		this->_last_phrase_used = this->_find_mathPhrase(phraseName);

	if(this->_last_phrase_used == NOT_SET)
		return false;
	else
		return this->_mathPhrases[this->_last_phrase_used]->has_variable(varName);
}

SocialNetworksAnalysis::Calculator::Calculator()
{
	this->clear();
}

SocialNetworksAnalysis::Calculator::~Calculator()
{
	this->clear();
}
	
void SocialNetworksAnalysis::Calculator::clear()
{
	this->_isSortedMathPhrases = false;

	for(int i = 0; i < this->_mathPhrases.size(); ++i)
		delete this->_mathPhrases[i];

	this->_mathPhrases.clear();

	this->_last_phrase_used = NOT_SET;
}

void SocialNetworksAnalysis::Calculator::clear(string phraseName)
{
	int index = this->_find_mathPhrase(phraseName);

	if(index == NOT_SET) return;

	delete this->_mathPhrases[index];
	this->_mathPhrases.erase(this->_mathPhrases.begin() + index);

	this->_last_phrase_used = NOT_SET;
}
	
bool SocialNetworksAnalysis::Calculator::compute(double& returnValue, string phraseName)// = "")
{
	if(this->_last_phrase_used == NOT_SET || this->_mathPhrases[this->_last_phrase_used]->get_name() != phraseName)
		this->_last_phrase_used = this->_find_mathPhrase(phraseName);

	if(this->_last_phrase_used == NOT_SET)
		return false;
	else
		return this->_mathPhrases[this->_last_phrase_used]->compute(returnValue);
}

bool SocialNetworksAnalysis::Calculator::add_phrase(string phraseName)
{
	int index = this->_find_mathPhrase(phraseName);

	if(index >= 0) 
	{
		this->_last_phrase_used = NOT_SET;
		return false;
	}
	else
	{
		if(this->_mathPhrases.size() && this->_mathPhrases.back()->get_name() > phraseName)
			this->_isSortedMathPhrases = false;
		else if(!this->_mathPhrases.size())
			this->_isSortedMathPhrases = true;

		MathPhrase* temp = new MathPhrase(phraseName);
		this->_mathPhrases.push_back(temp);

		this->_last_phrase_used = this->_mathPhrases.size() - 1;

		return true;
	}
}

bool SocialNetworksAnalysis::Calculator::add_variable(string variableName, string phraseName/* = "" */, double value)// = 0)
{
	if(this->_last_phrase_used == NOT_SET || this->_mathPhrases[this->_last_phrase_used]->get_name() != phraseName)
		this->_last_phrase_used = this->_find_else_add_math_phrase(phraseName);

	return this->_mathPhrases[this->_last_phrase_used]->add_variable(variableName, value);
}

bool SocialNetworksAnalysis::Calculator::add_number(double value, string phraseName)// = "")
{
	if(this->_last_phrase_used == NOT_SET || this->_mathPhrases[this->_last_phrase_used]->get_name() != phraseName)
		this->_last_phrase_used = this->_find_else_add_math_phrase(phraseName);

	this->_mathPhrases[this->_last_phrase_used]->add_number(value);

	return true;
}

bool SocialNetworksAnalysis::Calculator::add_number(string variableName, double value, string phraseName)// = "")
{
	if(variableName == "") return false;

	if(this->_last_phrase_used == NOT_SET || this->_mathPhrases[this->_last_phrase_used]->get_name() != phraseName)
		this->_last_phrase_used = this->_find_else_add_math_phrase(phraseName);

	return this->_mathPhrases[this->_last_phrase_used]->add_number(variableName, value);
}

bool SocialNetworksAnalysis::Calculator::add_number(string variableName, string phraseName)// = "")
{
	if(variableName == "") return false;

	if(this->_last_phrase_used == NOT_SET || this->_mathPhrases[this->_last_phrase_used]->get_name() != phraseName)
		this->_last_phrase_used = this->_find_else_add_math_phrase(phraseName);

	return this->_mathPhrases[this->_last_phrase_used]->add_number(variableName);
}

void SocialNetworksAnalysis::Calculator::add_operator(string op, string phraseName)// = "")
{
	if(this->_last_phrase_used == NOT_SET || this->_mathPhrases[this->_last_phrase_used]->get_name() != phraseName)
		this->_last_phrase_used = this->_find_else_add_math_phrase(phraseName);

	this->_mathPhrases[this->_last_phrase_used]->add_operator(op);
}

bool SocialNetworksAnalysis::Calculator::reassign_variable(string variableName, double value, string phraseName)// = "")
{
	if(this->_last_phrase_used == NOT_SET || this->_mathPhrases[this->_last_phrase_used]->get_name() != phraseName)
		this->_last_phrase_used = this->_find_mathPhrase(phraseName);

	if(this->_last_phrase_used == NOT_SET)
		return false;
	else
		return this->_mathPhrases[this->_last_phrase_used]->reassign_variable(variableName, value);
}

void SocialNetworksAnalysis::Calculator::add_mathSentence(string mathSentence, string phraseName)// = "")
{
	if(this->_last_phrase_used == NOT_SET || this->_mathPhrases[this->_last_phrase_used]->get_name() != phraseName)
		this->_last_phrase_used = this->_find_else_add_math_phrase(phraseName);

	this->_mathPhrases[this->_last_phrase_used]->add_mathSentence(mathSentence);
}