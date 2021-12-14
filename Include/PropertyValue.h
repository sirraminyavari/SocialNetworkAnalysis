#ifndef __SOCIALNETWORKSANALYSIS_H
	#define __SOCIALNETWORKSANALYSIS_H
	#include "SocialNetworksAnalysis.h"
#endif

class SocialNetworksAnalysis::PropertyValue
{
	friend bool operator > (const PropertyValue& pvRight, const PropertyValue& pvLeft);
	friend bool operator >= (const PropertyValue& pvRight, const PropertyValue& pvLeft);
	friend bool operator < (const PropertyValue& pvRight, const PropertyValue& pvLeft);
	friend bool operator <= (const PropertyValue& pvRight, const PropertyValue& pvLeft);
	friend bool operator == (const PropertyValue& pvRight, const PropertyValue& pvLeft);
	friend bool operator != (const PropertyValue& pvRight, const PropertyValue& pvLeft);

private:
	Value _value;
	ValueType _valueType;

	void _remove_string();

public:
	PropertyValue();
	PropertyValue(int val);
	PropertyValue(double val);
	PropertyValue(string val);
	PropertyValue(PropertyValue& prVal);
	~PropertyValue();
	void clear();
	void set(int val);
	void set(double val);
	void set(string val);
	void get_value(void* returnValue, ValueType valType);
	int get_int();
	double get_double();
	string get_string();
	ValueType get_valueType();
	void operator = (PropertyValue& p);
};

bool SocialNetworksAnalysis::operator > (const PropertyValue& pvRight, const PropertyValue& pvLeft);
bool SocialNetworksAnalysis::operator == (const PropertyValue& pvRight, const PropertyValue& pvLeft);
bool SocialNetworksAnalysis::operator < (const PropertyValue& pvRight, const PropertyValue& pvLeft);
bool SocialNetworksAnalysis::operator >= (const PropertyValue& pvRight, const PropertyValue& pvLeft);
bool SocialNetworksAnalysis::operator <= (const PropertyValue& pvRight, const PropertyValue& pvLeft);
bool SocialNetworksAnalysis::operator != (const PropertyValue& pvRight, const PropertyValue& pvLeft);