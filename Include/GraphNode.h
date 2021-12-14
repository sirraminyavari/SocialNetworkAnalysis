#ifndef __SOCIALNETWORKSANALYSIS_H
	#define __SOCIALNETWORKSANALYSIS_H
	#include "SocialNetworksAnalysis.h"
#endif

#ifndef __RELATION_H
	#define __RELATION_H
	#include "Relation.h"
#endif

extern SocialNetworksAnalysis::PropertiesOwner;

bool SocialNetworksAnalysis::compare_relations(Relation* first, Relation* second);

class SocialNetworksAnalysis::GraphNode : public SocialNetworksAnalysis::PropertiesOwner
{
	string _nodeName;
	vector<Relation*> _relations;
	bool _isSorted_relations;

	void _sort_relations();
	int _find_relation_with(GraphNode* destination);
	int _find_relation_with(string destinationName);

	inline void _set_isSorted_relations_after_addition(GraphNode* destination);

	template <class T>
	inline bool _set_relation_with(GraphNode* destination, string* propertyName, T value);

	template <class T>
	inline bool _add_relation_with(GraphNode* destination, string* propertyName, T value);
public:
	GraphNode();
	GraphNode(string nodeName);
	~GraphNode();
	void clear();
	bool has_relation_with(GraphNode* nodeName);
	bool has_relation_with(GraphNode* nodeName, string* propertyName);
	Property get_property_with(GraphNode* nodeName, string* propertyName);
	//bool get_relation_value(int destinationIndex, string* propertyName,
	//	void* returnValue, ValueType valueType = ValueType::doubleValue);
	bool get_relation_value(GraphNode* destination, string* propertyName,
		void* returnValue, ValueType valueType = ValueType::doubleValue);
	int get_relations_count();
	int get_relation_properties_count(GraphNode* destination);
	void set_node_name(string name);
	string get_node_name();
	bool set_relation_with(GraphNode* destination, string* propertyName, int value);
	bool set_relation_with(GraphNode* destination, string* propertyName, double value);
	bool set_relation_with(GraphNode* destination, string* propertyName, string value);
	bool add_relation_with(GraphNode* destination, string* propertyName, int value);
	bool add_relation_with(GraphNode* destination, string* propertyName, double value);
	bool add_relation_with(GraphNode* destination, string* propertyName, string value);
	Relation* element(int index);
	Relation* element(string destinationName);
	Relation* operator [] (int index);
	Relation* operator [] (string destinationName);
	//double* get_weights();
};