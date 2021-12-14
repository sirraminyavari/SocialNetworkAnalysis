#ifndef __PROPERTY_H
	#define __PROPERTY_H
	#include "Property.h"
#endif

bool SocialNetworksAnalysis::compare_properties(Property* first, Property* second);

class SocialNetworksAnalysis::PropertiesOwner
{
protected:
	vector<Property*> _properties;
	bool _isSorted_properties;

	void _sort_properties();
	int _find_property(string* name);

	inline void _set_isSorted_properties_after_addition(string* name);
	
	template <class T>
	inline bool _set_property(string* name, T val);

	template <class T>
	inline bool _add_property(string* name, T val);

public:
	PropertiesOwner();
	~PropertiesOwner();
	void clear_properties();
	bool has_property(string* name);
	bool set_property(string* propertyName, int val);
	bool set_property(string* propertyName, double val);
	bool set_property(string* propertyName, string val);
	bool add_property(string* propertyName, int value);
	bool add_property(string* propertyName, double value);
	bool add_property(string* propertyName, string value);
	bool get_value(string* propertyName, void* returnValue, ValueType valueType);
	int get_int(string* propertyName);
	double get_double(string* propertyName);
	string get_string(string* propertyName);
	PropertyValue get_propertyValue(string* propertyName);
	PropertyValue get_propertyValue(int propertyIndex);
	Property get_property(string* propertyName);
	int get_properties_count();
	ValueType get_valueType(string* propertyName);
	ValueType get_valueType(int propertyIndex);
	double get_weight(string& mathPhraseName, Calculator& calc, pair<string*, string*>* variable2property, int variablesCount);
};