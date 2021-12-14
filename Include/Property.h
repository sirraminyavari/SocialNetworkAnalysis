#ifndef __PROPERTYVALUE_H
	#define __PROPERTYVALUE_H
	#include "PropertyValue.h"
#endif

class SocialNetworksAnalysis::Property
{
	friend bool operator > (const Property& pFirst, const Property& pSecond);
	friend bool operator < (const Property& pFirst, const Property& pSecond);
	friend bool operator == (const Property& pFirst, const Property& pSecond);
	friend bool operator >= (const Property& pFirst, const Property& pSecond);
	friend bool operator <= (const Property& pFirst, const Property& pSecond);
	friend bool operator != (const Property& pFirst, const Property& pSecond);

	PropertyValue* _propertyValue;
	string* _propertyName;

	template <class T>
	void __constructor(string* strName, T value);

	template <class T>
	void _set(T value);

public:
	Property();
	Property(Property& p);
	Property(string* strName);
	Property(string* strName, int integerValue);
	Property(string* strName, double doubleValue);
	Property(string* strName, string stringValue);
	~Property();
	void clear();
	void set(int val);
	void set(double val);
	void set(string val);
	void get_value(void* returnValue, ValueType valueType);
	int get_int();
	double get_double();
	string get_string();
	PropertyValue get_propertyValue();
	ValueType get_valueType();
	string* get_name();
	void rename(string* strName);
	int compare_names(Property& p);
	bool is_similar_valueType(Property& p);
	void operator = (Property& p);
};

bool SocialNetworksAnalysis::operator > (const Property& pFirst, const Property& pSecond);
bool SocialNetworksAnalysis::operator < (const Property& pFirst, const Property& pSecond);
bool SocialNetworksAnalysis::operator == (const Property& pFirst, const Property& pSecond);
bool SocialNetworksAnalysis::operator >= (const Property& pFirst, const Property& pSecond);
bool SocialNetworksAnalysis::operator <= (const Property& pFirst, const Property& pSecond);
bool SocialNetworksAnalysis::operator != (const Property& pFirst, const Property& pSecond);