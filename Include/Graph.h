#ifndef __SOCIALNETWORKSANALYSIS_H
	#define __SOCIALNETWORKSANALYSIS_H
	#include "SocialNetworksAnalysis.h"
#endif

#ifndef __GRAPHNODE_H
	#define __GRAPHNODE_H
	#include "GraphNode.h"
#endif

#ifndef __CALCULATOR_H
	#define __CALCULATOR_H
	#include "Calculator.h"
#endif

bool SocialNetworksAnalysis::compare_nodes(GraphNode* first, GraphNode* second);

bool SocialNetworksAnalysis::compare_names(string* first, string* second);

class SocialNetworksAnalysis::Graph
{
	string _graphName;
	vector<GraphNode*> _nodes;
	vector<string*> _relationPropertyNames;
	vector<string*> _nodePropertyNames;
	bool _isSorted_nodes;
	bool _isSorted_relationPropertyNames;
	bool _isSorted_nodePropertyNames;

	void _sort_nodes();
	void _sort_relationPropertyNames();
	void _sort_nodePropertyNames();
	int _find_node(string& name);
	int __find_property_name(string& propertyName, vector<string*>& vec, bool& isSorted, bool isRelation);
	int _find_relation_property_name(string& propertyName);
	int _find_node_property_name(string& propertyName);

	inline void _set_isSorted_nodes_after_addition(string& nodeName);
	inline void _set_isSorted_relationPropertyNames_after_addition(string& propertyName);
	inline void _set_isSorted_nodePropertyNames_after_addition(string& propertyName);

	template <class T>
	inline bool _set_relation_property_with(string& sourceName, string& destinationName, string& propertyName, T value);

	template <class T>
	inline bool _set_node_property(string& nodeName, string& propertyName, T value);

	template <class T>
	inline bool _add_relation_property_with(string& sourceName, string& destinationName, string& propertyName, T value);

	template <class T>
	inline bool _add_property2node(string& nodeName, string& propertyName, T value);
public:
	Graph();
	~Graph();
	void clear();
	bool node_exists(string nodeName);
	bool relation_property_exists(string propertyName);
	bool node_property_exists(string propertyName);
	bool add_node(string nodeName);
	bool add_relation_property(string propertyName);
	bool add_node_property(string propertyName);
	bool has_relation_with(string sourceName, string destinationName);
	bool has_relation_with(string sourceName, string destinationName, string propertyName);
	bool set_relation_property_with(string sourceName, string destinationName, string propertyName, int value);
	bool set_relation_property_with(string sourceName, string destinationName, string propertyName, double value);
	bool set_relation_property_with(string sourceName, string destinationName, string propertyName, string value);
	bool set_node_property(string nodeName, string propertyName, int value);
	bool set_node_property(string nodeName, string propertyName, double value);
	bool set_node_property(string nodeName, string propertyName, string value);
	bool add_relation_property_with(string sourceName, string destinationName, string propertyName, int value);
	bool add_relation_property_with(string sourceName, string destinationName, string propertyName, double value);
	bool add_relation_property_with(string sourceName, string destinationName, string propertyName, string value);
	bool add_property2node(string nodeName, string propertyName, int value);
	bool add_property2node(string nodeName, string propertyName, double value);
	bool add_property2node(string nodeName, string propertyName, string value);
	bool get_node_value(int index, string propertyName, void* returnValue, ValueType valueType = ValueType::doubleValue);
	bool get_node_value(string nodeName, string propertyName, void* returnValue, ValueType valueType = ValueType::doubleValue);
	bool get_relation_value(int sourceIndex, int destinationIndex, 
		string propertyName, void* returnValue, ValueType valueType = ValueType::doubleValue);
	bool get_relation_value(string sourceName, string destinationName,
		string propertyName, void* returnValue, ValueType valueType = ValueType::doubleValue);
	int get_nodes_count();
	int get_relations_count(string nodeName);
	int get_node_properties_count(string nodeName);
	int get_relation_properties_count(string sourceName, string destinationName);
	GraphNode* element(int index);
	GraphNode* element(string nodeName);
	GraphNode* operator [] (int index);
	GraphNode* operator [] (string nodeName);
};