#ifndef __PROPERTY_H
	#define __PROPERTY_H
	#include "Property.h"
#endif

template <class T>
void SocialNetworksAnalysis::Property::__constructor(string* strName, T value)
{
	this->_propertyName = strName;
	this->_propertyValue = NULL;
	this->_set<T>(value);
}

template <class T>
void SocialNetworksAnalysis::Property::_set(T value)
{
	if(!this->_propertyValue) 
		this->_propertyValue = new PropertyValue(value);
	else
		this->_propertyValue->set(value);
}

SocialNetworksAnalysis::Property::Property()
{
	this->_propertyName = NULL;
	this->_propertyValue = NULL;
}

SocialNetworksAnalysis::Property::Property(Property& p)
{
	*this = p;
}
	
SocialNetworksAnalysis::Property::Property(string* strName)
{
	this->_propertyName = strName;
	this->_propertyValue = NULL;
}

SocialNetworksAnalysis::Property::Property(string* strName, int integerValue)
{
	this->__constructor<int>(strName, integerValue);
}

SocialNetworksAnalysis::Property::Property(string* strName, double doubleValue)
{
	this->__constructor<double>(strName, doubleValue);
}

SocialNetworksAnalysis::Property::Property(string* strName, string stringValue)
{
	this->__constructor<string>(strName, stringValue);
}

SocialNetworksAnalysis::Property::~Property()
{
	this->clear();
}

void SocialNetworksAnalysis::Property::clear()
{
	if(this->_propertyValue) delete this->_propertyValue;
	this->_propertyName = NULL;
}

void SocialNetworksAnalysis::Property::set(int val)
{
	this->_set<int>(val);
}

void SocialNetworksAnalysis::Property::set(double val)
{
	this->_set<double>(val);
}

void SocialNetworksAnalysis::Property::set(string val)
{
	this->_set<string>(val);
}

void SocialNetworksAnalysis::Property::get_value(void* returnValue, ValueType valueType)
{
	this->get_value(returnValue, valueType);
}

int SocialNetworksAnalysis::Property::get_int()
{
	return this->_propertyValue->get_int();
}

double SocialNetworksAnalysis::Property::get_double()
{
	return this->_propertyValue->get_double();
}

string SocialNetworksAnalysis::Property::get_string()
{
	return this->_propertyValue->get_string();
}

SocialNetworksAnalysis::PropertyValue SocialNetworksAnalysis::Property::get_propertyValue()
{
	PropertyValue retVal = *this->_propertyValue;
	return retVal;
}
	
SocialNetworksAnalysis::ValueType SocialNetworksAnalysis::Property::get_valueType()
{
	return this->_propertyValue->get_valueType();
}
	
string* SocialNetworksAnalysis::Property::get_name()
{
	return this->_propertyName;
}
	
void SocialNetworksAnalysis::Property::rename(string* strName)
{
	this->_propertyName = strName;
}
	
int SocialNetworksAnalysis::Property::compare_names(Property& p)
{
	if(*this->_propertyName < *p._propertyName)
		return -1;
	else if(*this->_propertyName > *_propertyName)
		return 1;
	else
		return 0;
}
	
bool SocialNetworksAnalysis::Property::is_similar_valueType(Property& p)
{
	if(this->get_valueType() == p.get_valueType())
		return true;
	else
		return false;
}
	
void SocialNetworksAnalysis::Property::operator = (Property& p)
{
	this->clear();

	this->_propertyValue = new PropertyValue;

	switch(p.get_valueType())
	{
	case ValueType::integerValue:
		this->set(p.get_int());
		break;
	case ValueType::doubleValue:
		this->set(p.get_double());
		break;
	case ValueType::stringValue:
		this->set(p.get_string());
		break;
	default:
		this->_propertyValue->clear();
	}

	this->_propertyName = p.get_name();
}

bool SocialNetworksAnalysis::operator > (const Property& pFirst, const Property& pSecond)
{
	return (*pFirst._propertyValue > *pSecond._propertyValue);
}

bool SocialNetworksAnalysis::operator < (const Property& pFirst, const Property& pSecond)
{
	return (*pFirst._propertyValue < *pSecond._propertyValue);
}

bool SocialNetworksAnalysis::operator == (const Property& pFirst, const Property& pSecond)
{
	return (*pFirst._propertyValue == *pSecond._propertyValue);
}

bool SocialNetworksAnalysis::operator >= (const Property& pFirst, const Property& pSecond)
{
	return (*pFirst._propertyValue >= *pSecond._propertyValue);
}

bool SocialNetworksAnalysis::operator <= (const Property& pFirst, const Property& pSecond)
{
	return (*pFirst._propertyValue <= *pSecond._propertyValue);
}

bool SocialNetworksAnalysis::operator != (const Property& pFirst, const Property& pSecond)
{
	return (*pFirst._propertyValue != *pSecond._propertyValue);
}