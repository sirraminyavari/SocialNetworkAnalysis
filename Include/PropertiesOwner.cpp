#ifndef __PROPERTY_H
	#define __PROPERTY_H
	#include "Property.h"
#endif

bool SocialNetworksAnalysis::compare_properties(Property* first, Property* second)
{
	if(first->compare_names(*second) < 0)
		return true;
	else
		return false;
}

void SocialNetworksAnalysis::PropertiesOwner::_sort_properties()
{
	sort(this->_properties.begin(), this->_properties.end(), SocialNetworksAnalysis::compare_properties);
	this->_isSorted_properties = true;
}

int SocialNetworksAnalysis::PropertiesOwner::_find_property(string* name)
{
	if(!this->_isSorted_properties) this->_sort_properties();

	int startIndicator = 0;
	int endIndicator = this->_properties.size() - 1;
	int middleIndicator = (endIndicator - startIndicator) / 2;

	while(startIndicator <= endIndicator)
	{
		if(this->_properties[startIndicator]->get_name() == name)
			return startIndicator;
		else if(this->_properties[endIndicator]->get_name() == name)
			return endIndicator;
		else if(this->_properties[middleIndicator]->get_name() == name)
			return middleIndicator;
		else
		{
			if(*this->_properties[middleIndicator]->get_name() < *name)
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

inline void SocialNetworksAnalysis::PropertiesOwner::_set_isSorted_properties_after_addition(string* name)
{
	if(this->_properties.size() && *this->_properties.back()->get_name() > *name)
		this->_isSorted_properties = false;
	else if(!this->_properties.size())
		this->_isSorted_properties = true;
}
	
template <class T>
inline bool SocialNetworksAnalysis::PropertiesOwner::_set_property(string* name, T val)
{
	int index = this->_find_property(name);
		
	if(index < 0) return false;

	this->_properties[index]->set(val);

	return true;
}

template <class T>
inline bool SocialNetworksAnalysis::PropertiesOwner::_add_property(string* name, T val)
{
	if(this->has_property(name)) return false;

	this->_set_isSorted_properties_after_addition(name);

	Property* temp = new Property(name, val);
	this->_properties.push_back(temp);

	return true;
}

SocialNetworksAnalysis::PropertiesOwner::PropertiesOwner()
{
	this->clear_properties();
}

SocialNetworksAnalysis::PropertiesOwner::~PropertiesOwner()
{
	this->clear_properties();
}

void SocialNetworksAnalysis::PropertiesOwner::clear_properties()
{
	for(int i = 0; i < this->_properties.size(); ++i)
		delete this->_properties[i];
	this->_properties.clear();
	this->_isSorted_properties = false;
}

bool SocialNetworksAnalysis::PropertiesOwner::has_property(string* name)
{
	if(this->_find_property(name) < 0)
		return false;
	else
		return true;
}

bool SocialNetworksAnalysis::PropertiesOwner::set_property(string* propertyName, int val)
{
	return this->_set_property<int>(propertyName, val);
}

bool SocialNetworksAnalysis::PropertiesOwner::set_property(string* propertyName, double val)
{
	return this->_set_property<double>(propertyName, val);
}

bool SocialNetworksAnalysis::PropertiesOwner::set_property(string* propertyName, string val)
{
	return this->_set_property<string>(propertyName, val);
}

bool SocialNetworksAnalysis::PropertiesOwner::add_property(string* propertyName, int value)
{
	return this->_add_property<int>(propertyName, value);
}

bool SocialNetworksAnalysis::PropertiesOwner::add_property(string* propertyName, double value)
{
	return this->_add_property<double>(propertyName, value);
}

bool SocialNetworksAnalysis::PropertiesOwner::add_property(string* propertyName, string value)
{
	return this->_add_property<string>(propertyName, value);
}

bool SocialNetworksAnalysis::PropertiesOwner::get_value(string* propertyName, void* returnValue, ValueType valueType)
{
	int index = this->_find_property(propertyName);

	if(index < 0) false;

	this->_properties[index]->get_value(returnValue, valueType);

	return true;
}

int SocialNetworksAnalysis::PropertiesOwner::get_int(string* propertyName)
{
	int retVal = 0;
	this->get_value(propertyName, &retVal, ValueType::integerValue);
	return retVal;
}

double SocialNetworksAnalysis::PropertiesOwner::get_double(string* propertyName)
{
	double retVal = 0;
	this->get_value(propertyName, &retVal, ValueType::doubleValue);
	return retVal;
}

string SocialNetworksAnalysis::PropertiesOwner::get_string(string* propertyName)
{
	string retVal = "";
	this->get_value(propertyName, &retVal, ValueType::stringValue);
	return retVal;
}

SocialNetworksAnalysis::PropertyValue SocialNetworksAnalysis::PropertiesOwner::get_propertyValue(string* propertyName)
{
	int index = this->_find_property(propertyName);

	if(index < 0) return NULL;
	return this->_properties[index]->get_propertyValue();
}

SocialNetworksAnalysis::PropertyValue SocialNetworksAnalysis::PropertiesOwner::get_propertyValue(int propertyIndex)
{
	if(propertyIndex < 0 || propertyIndex >= this->_properties.size())
		return NULL;
	else
		return this->_properties[propertyIndex]->get_propertyValue();
}

SocialNetworksAnalysis::Property SocialNetworksAnalysis::PropertiesOwner::get_property(string* propertyName)
{
	int index = this->_find_property(propertyName);

	if(index < 0) 
		return NULL;
	else
	{
		Property temp = *this->_properties[index];
		return temp;
	}
}

int SocialNetworksAnalysis::PropertiesOwner::get_properties_count()
{
	return this->_properties.size();
}

SocialNetworksAnalysis::ValueType SocialNetworksAnalysis::PropertiesOwner::get_valueType(string* propertyName)
{
	int index = this->_find_property(propertyName);
	if(index < 0) 
		return ValueType::notSet;
	else
		return this->_properties[index]->get_valueType();
}

SocialNetworksAnalysis::ValueType SocialNetworksAnalysis::PropertiesOwner::get_valueType(int propertyIndex)
{
	if(propertyIndex < 0 || propertyIndex >= this->_properties.size())
		return ValueType::notSet;
	else
		return this->_properties[propertyIndex]->get_valueType();
}

double SocialNetworksAnalysis::PropertiesOwner::get_weight(string& mathPhraseName, Calculator& calc, pair<string*, string*>* variable2property, int variablesCount)
{
	string variableName = NULL;
	double returnValue = 0;

	for(int i = 0; i < variablesCount; ++i)
	{
		int index = this->_find_property(variable2property[i].second);
		variableName = *variable2property[i].first;

		if(index < 0) 
		{
			calc.reassign_variable(variableName, NOT_EXISTS);
			continue;
		}

		PropertyValue pv = this->get_propertyValue(index);
		ValueType vt = pv.get_valueType();

		if(vt == ValueType::notSet)
			calc.reassign_variable(variableName, NOT_EXISTS);
		else if(vt == ValueType::stringValue)
			calc.reassign_variable(variableName, EXISTS);
		else if(vt == ValueType::doubleValue)
			calc.reassign_variable(variableName, pv.get_double());
		else
			calc.reassign_variable(variableName, pv.get_int());
	}

	calc.compute(returnValue, mathPhraseName);

	return returnValue;
}