#ifndef __PROPERTYVALUE_H
	#define __PROPERTYVALUE_H
	#include "PropertyValue.h"
#endif

void SocialNetworksAnalysis::PropertyValue::_remove_string()
{
	if(this->_valueType == ValueType::stringValue)
	{
		delete[] this->_value.strVal;
		this->_value.strVal = NULL;
		this->_valueType = ValueType::notSet;
	}
}

SocialNetworksAnalysis::PropertyValue::PropertyValue()
{
	clear();
}

SocialNetworksAnalysis::PropertyValue::PropertyValue(int val)
{
	this->set(val);
}

SocialNetworksAnalysis::PropertyValue::PropertyValue(double val)
{
	this->set(val);
}

SocialNetworksAnalysis::PropertyValue::PropertyValue(string val)
{
	this->set(val);
}
	
SocialNetworksAnalysis::PropertyValue::PropertyValue(PropertyValue& prVal)
{
	*this = prVal;
}

SocialNetworksAnalysis::PropertyValue::~PropertyValue()
{
	this->_remove_string();
}
	
void SocialNetworksAnalysis::PropertyValue::clear()
{
	this->_remove_string();
	this->_value.intVal = 0;
	this->_value.dblVal = 0;
}
	
void SocialNetworksAnalysis::PropertyValue::set(int val)
{
	this->_remove_string();

	this->_value.intVal = val;
	this->_valueType = ValueType::integerValue;
}

void SocialNetworksAnalysis::PropertyValue::set(double val)
{
	this->_remove_string();

	this->_value.dblVal = val;
	this->_valueType = ValueType::doubleValue;
}

void SocialNetworksAnalysis::PropertyValue::set(string val)
{
	this->_remove_string();

	this->_value.strVal = new char[val.size() + 1];

	for(int i = 0; i < val.size(); ++i)
		this->_value.strVal[i] = val[i];
	this->_value.strVal[val.size()] = NULL;

	this->_valueType = ValueType::stringValue;
}

void SocialNetworksAnalysis::PropertyValue::get_value(void* returnValue, ValueType valType)
{
	valType = this->_valueType;

	switch(this->_valueType)
	{
	case ValueType::integerValue:
		*(int*)returnValue = this->_value.intVal;
		break;
	case ValueType::doubleValue:
		*(double*)returnValue = this->_value.dblVal;
		break;
	case ValueType::stringValue:
		*(string*)returnValue = this->get_string();
		break;
	}
}

int SocialNetworksAnalysis::PropertyValue::get_int()
{
	if(this->_valueType == ValueType::integerValue)
		return this->_value.intVal;
	else
		return 0;
}

double SocialNetworksAnalysis::PropertyValue::get_double()
{
	if(this->_valueType == ValueType::doubleValue)
		return this->_value.dblVal;
	else
		return 0.0;
}

string SocialNetworksAnalysis::PropertyValue::get_string()
{
	if(this->_valueType != ValueType::stringValue) return "";

	string str = "";

	for(int i = 0; i < strlen(this->_value.strVal); ++i)
		str += this->_value.strVal[i];

	return str;
}

SocialNetworksAnalysis::ValueType SocialNetworksAnalysis::PropertyValue::get_valueType()
{
	return this->_valueType;
}

void SocialNetworksAnalysis::PropertyValue::operator = (PropertyValue& p)
{
	if(p.get_valueType() == ValueType::integerValue)
		this->set(p.get_int());
	else if(p.get_valueType() == ValueType::doubleValue)
		this->set(p.get_double());
	else if(p.get_valueType() == ValueType::stringValue)
		this->set(p.get_string());
	else
		clear();
}

bool SocialNetworksAnalysis::operator > (const PropertyValue& pvRight, const PropertyValue& pvLeft)
{
	if(pvRight._valueType == ValueType::integerValue && pvLeft._valueType == ValueType::integerValue)
	{
		if(pvRight._value.intVal > pvLeft._value.intVal) 
			return true;
		else
			return false;
	}
	else if(pvRight._valueType == ValueType::doubleValue && pvLeft._valueType == ValueType::doubleValue)
	{
		if(pvRight._value.dblVal > pvLeft._value.dblVal) 
			return true;
		else
			return false;
	}
	else if(pvRight._valueType == ValueType::stringValue && pvLeft._valueType == ValueType::stringValue)
	{
		if(strcmp(pvRight._value.strVal, pvLeft._value.strVal) > 0) 
			return true;
		else
			return false;
	}

	return false;
}

bool SocialNetworksAnalysis::operator == (const PropertyValue& pvRight, const PropertyValue& pvLeft)
{
	if(pvRight._valueType == ValueType::integerValue && pvLeft._valueType == ValueType::integerValue)
	{
		if(pvRight._value.intVal == pvLeft._value.intVal) 
			return true;
		else
			return false;
	}
	else if(pvRight._valueType == ValueType::doubleValue && pvLeft._valueType == ValueType::doubleValue)
	{
		if(pvRight._value.dblVal == pvLeft._value.dblVal) 
			return true;
		else
			return false;
	}
	else if(pvRight._valueType == ValueType::stringValue && pvLeft._valueType == ValueType::stringValue)
	{
		if(strcmp(pvRight._value.strVal, pvLeft._value.strVal) == 0) 
			return true;
		else
			return false;
	}

	return false;
}

bool SocialNetworksAnalysis::operator < (const PropertyValue& pvRight, const PropertyValue& pvLeft)
{
	return !(pvRight > pvLeft || pvRight == pvLeft);
}

bool SocialNetworksAnalysis::operator >= (const PropertyValue& pvRight, const PropertyValue& pvLeft)
{
	return !(pvRight < pvLeft);
}

bool SocialNetworksAnalysis::operator <= (const PropertyValue& pvRight, const PropertyValue& pvLeft)
{
	return !(pvRight > pvLeft);
}

bool SocialNetworksAnalysis::operator != (const PropertyValue& pvRight, const PropertyValue& pvLeft)
{
	return !(pvRight == pvLeft);
}