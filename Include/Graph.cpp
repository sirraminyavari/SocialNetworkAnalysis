#ifndef __GRAPH_H
	#define __GRAPH_H
	#include "Graph.h"
#endif

bool SocialNetworksAnalysis::compare_nodes(GraphNode* first, GraphNode* second)
{
	if(first->get_node_name() < second->get_node_name())
		return true;
	else
		return false;
}

bool SocialNetworksAnalysis::compare_names(string* first, string* second)
{
	if(*first < *second)
		return true;
	else
		return false;
}

void SocialNetworksAnalysis::Graph::_sort_nodes()
{
	sort(this->_nodes.begin(), this->_nodes.end(), SocialNetworksAnalysis::compare_nodes);
	this->_isSorted_nodes = true;
}

void SocialNetworksAnalysis::Graph::_sort_relationPropertyNames()
{
	sort(this->_relationPropertyNames.begin(), this->_relationPropertyNames.end(), SocialNetworksAnalysis::compare_names);
	this->_isSorted_relationPropertyNames = true;
}

void SocialNetworksAnalysis::Graph::_sort_nodePropertyNames()
{
	sort(this->_nodePropertyNames.begin(), this->_nodePropertyNames.end(), SocialNetworksAnalysis::compare_names);
	this->_isSorted_nodePropertyNames = true;
}

int SocialNetworksAnalysis::Graph::_find_node(string& name)
{
	if(!this->_isSorted_nodes) this->_sort_nodes();

	int startIndicator = 0;
	int endIndicator = this->_nodes.size() - 1;
	int middleIndicator = (endIndicator - startIndicator) / 2;

	while(startIndicator <= endIndicator)
	{
		if(this->_nodes[startIndicator]->get_node_name() == name)
			return startIndicator;
		else if(this->_nodes[endIndicator]->get_node_name() == name)
			return endIndicator;
		else if(this->_nodes[middleIndicator]->get_node_name() == name)
			return middleIndicator;
		else
		{
			if(this->_nodes[middleIndicator]->get_node_name() < name)
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

int SocialNetworksAnalysis::Graph::__find_property_name(string& propertyName, vector<string*>& vec, bool& isSorted, bool isRelation)
{
	if(!isSorted)
	{
		if(isRelation)
			this->_sort_relationPropertyNames();
		else
			this->_sort_nodePropertyNames();
	}

	int startIndicator = 0;
	int endIndicator = vec.size() - 1;
	int middleIndicator = (endIndicator - startIndicator) / 2;

	while(startIndicator <= endIndicator)
	{
		if(*vec[startIndicator] == propertyName)
			return startIndicator;
		else if(*vec[endIndicator] == propertyName)
			return endIndicator;
		else if(*vec[middleIndicator] == propertyName)
			return middleIndicator;
		else
		{
			if(*vec[middleIndicator] < propertyName)
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

int SocialNetworksAnalysis::Graph::_find_relation_property_name(string& propertyName)
{
	return this->__find_property_name(propertyName, this->_relationPropertyNames, 
		this->_isSorted_relationPropertyNames, true);
}

int SocialNetworksAnalysis::Graph::_find_node_property_name(string& propertyName)
{
	return this->__find_property_name(propertyName, this->_nodePropertyNames, 
		this->_isSorted_nodePropertyNames, false);
}

inline void SocialNetworksAnalysis::Graph::_set_isSorted_nodes_after_addition(string& nodeName)
{
	if(this->_nodes.size() && this->_nodes.back()->get_node_name() > nodeName)
		this->_isSorted_nodes = false;
	else if(!this->_nodes.size())
		this->_isSorted_nodes = true;
}

inline void SocialNetworksAnalysis::Graph::_set_isSorted_relationPropertyNames_after_addition(string& propertyName)
{
	if(this->_relationPropertyNames.size() && *this->_relationPropertyNames.back() > propertyName)
		this->_isSorted_relationPropertyNames = false;
	else if(!this->_relationPropertyNames.size())
		this->_isSorted_relationPropertyNames = true;
}

inline void SocialNetworksAnalysis::Graph::_set_isSorted_nodePropertyNames_after_addition(string& propertyName)
{
	if(this->_nodePropertyNames.size() && *this->_nodePropertyNames.back() > propertyName)
		this->_isSorted_nodePropertyNames = false;
	else if(!this->_nodePropertyNames.size())
		this->_isSorted_nodePropertyNames = true;
}

template <class T>
inline bool SocialNetworksAnalysis::Graph::_set_relation_property_with(string& sourceName, string& destinationName, string& propertyName, T value)
{
	int sourceIndex = this->_find_node(sourceName);
	int destinationIndex = this->_find_node(destinationName);
	int propertyIndex = this->_find_relation_property_name(propertyName);

	if(sourceIndex == NOT_SET || destinationIndex == NOT_SET || propertyIndex == NOT_SET)
		return false;

	return this->_nodes[sourceIndex]->set_relation_with(this->_nodes[destinationIndex], 
		this->_relationPropertyNames[propertyIndex], value);
}

template <class T>
inline bool SocialNetworksAnalysis::Graph::_set_node_property(string& nodeName, string& propertyName, T value)
{
	int nodeIndex = this->_find_node(nodeName);
	int propertyIndex = this->_find_node_property_name(propertyName);

	if(nodeIndex == NOT_SET || propertyIndex == NOT_SET)
		return false;

	return this->_nodes[nodeIndex]->set_property(this->_nodePropertyNames[propertyIndex], value);
}

template <class T>
inline bool SocialNetworksAnalysis::Graph::_add_relation_property_with(string& sourceName, string& destinationName, string& propertyName, T value)
{
	int sourceIndex = this->_find_node(sourceName);
	int destinationIndex = this->_find_node(destinationName);
	int propertyIndex = this->_find_relation_property_name(propertyName);

	if(propertyIndex == NOT_SET) 
	{
		this->add_relation_property(propertyName);
		propertyIndex = this->_relationPropertyNames.size() - 1;
	}

	if(sourceIndex == NOT_SET)
	{
		this->add_node(sourceName);
		sourceIndex = this->_nodes.size() - 1;
	}

	if(destinationIndex == NOT_SET)
	{
		this->add_node(destinationName);
		destinationIndex = this->_nodes.size() - 1;
	}

	return this->_nodes[sourceIndex]->add_relation_with(this->_nodes[destinationIndex], 
		this->_relationPropertyNames[propertyIndex], value);
}

template <class T>
inline bool SocialNetworksAnalysis::Graph::_add_property2node(string& nodeName, string& propertyName, T value)
{
	int nodeIndex = this->_find_node(nodeName);
	int propertyIndex = this->_find_node_property_name(propertyName);

	if(propertyIndex == NOT_SET) 
	{
		this->add_node_property(propertyName);
		propertyIndex = this->_nodePropertyNames.size() - 1;
	}

	if(nodeIndex == NOT_SET)
	{
		this->add_node(nodeName);
		nodeIndex = this->_nodes.size() - 1;
	}

	return this->_nodes[nodeIndex]->add_property(this->_nodePropertyNames[propertyIndex], value);
}

SocialNetworksAnalysis::Graph::Graph()
{
	this->clear();
}

SocialNetworksAnalysis::Graph::~Graph()
{
	this->clear();
}
	
void SocialNetworksAnalysis::Graph::clear()
{
	this->_graphName = "";

	for(int i = 0; i < this->_nodes.size(); ++i)
		delete this->_nodes[i];
	this->_nodes.clear();
	this->_isSorted_nodes = false;

	for(int i = 0; i < this->_relationPropertyNames.size(); ++i)
		delete this->_relationPropertyNames[i];
	this->_relationPropertyNames.clear();
	this->_isSorted_relationPropertyNames = false;

	for(int i = 0; i < this->_nodePropertyNames.size(); ++i)
		delete this->_nodePropertyNames[i];
	this->_nodePropertyNames.clear();
	this->_isSorted_nodePropertyNames = false;
}

bool SocialNetworksAnalysis::Graph::node_exists(string nodeName)
{
	if(this->_find_node(nodeName) < 0)
		return false;
	else
		return true;
}

bool SocialNetworksAnalysis::Graph::relation_property_exists(string propertyName)
{
	if(this->_find_relation_property_name(propertyName) < 0)
		return false;
	else
		return true;
}

bool SocialNetworksAnalysis::Graph::node_property_exists(string propertyName)
{
	if(this->_find_node_property_name(propertyName) < 0)
		return false;
	else
		return true;
}

bool SocialNetworksAnalysis::Graph::add_node(string nodeName)
{
	if(this->node_exists(nodeName)) return false;

	this->_set_isSorted_nodes_after_addition(nodeName);

	GraphNode* temp = new GraphNode();
	temp->set_node_name(nodeName);
	this->_nodes.push_back(temp);

	return true;
}

bool SocialNetworksAnalysis::Graph::add_relation_property(string propertyName)
{
	if(this->relation_property_exists(propertyName)) return false;

	this->_set_isSorted_relationPropertyNames_after_addition(propertyName);

	string* temp = new string;
	*temp = propertyName;
	this->_relationPropertyNames.push_back(temp);

	return true;
}

bool SocialNetworksAnalysis::Graph::add_node_property(string propertyName)
{
	if(this->node_property_exists(propertyName)) return false;

	this->_set_isSorted_nodePropertyNames_after_addition(propertyName);

	string* temp = new string;
	*temp = propertyName;
	this->_nodePropertyNames.push_back(temp);

	return true;
}

bool SocialNetworksAnalysis::Graph::has_relation_with(string sourceName, string destinationName)
{
	int sourceIndex = this->_find_node(sourceName);
	int destinationIndex = this->_find_node(destinationName);

	if(sourceIndex < 0 || destinationIndex < 0) return false;

	return this->_nodes[sourceIndex]->has_relation_with(this->_nodes[destinationIndex]);
}

bool SocialNetworksAnalysis::Graph::has_relation_with(string sourceName, string destinationName, string propertyName)
{
	int sourceIndex = this->_find_node(sourceName);
	int destinationIndex = this->_find_node(destinationName);
	int propertyIndex = this->_find_relation_property_name(propertyName);

	if(sourceIndex == NOT_SET || destinationIndex == NOT_SET || propertyIndex == NOT_SET) 
		return false;

	return this->_nodes[sourceIndex]->has_relation_with(this->_nodes[destinationIndex],
		this->_relationPropertyNames[propertyIndex]);
}

bool SocialNetworksAnalysis::Graph::set_relation_property_with(string sourceName, string destinationName, string propertyName, int value)
{
	return this->_set_relation_property_with<int>(sourceName, destinationName, propertyName, value);
}

bool SocialNetworksAnalysis::Graph::set_relation_property_with(string sourceName, string destinationName, string propertyName, double value)
{
	return this->_set_relation_property_with<double>(sourceName, destinationName, propertyName, value);
}

bool SocialNetworksAnalysis::Graph::set_relation_property_with(string sourceName, string destinationName, string propertyName, string value)
{
	return this->_set_relation_property_with<string>(sourceName, destinationName, propertyName, value);
}

bool SocialNetworksAnalysis::Graph::set_node_property(string nodeName, string propertyName, int value)
{
	return this->_set_node_property<int>(nodeName, propertyName, value);
}

bool SocialNetworksAnalysis::Graph::set_node_property(string nodeName, string propertyName, double value)
{
	return this->_set_node_property<double>(nodeName, propertyName, value);
}

bool SocialNetworksAnalysis::Graph::set_node_property(string nodeName, string propertyName, string value)
{
	return this->_set_node_property<string>(nodeName, propertyName, value);
}

bool SocialNetworksAnalysis::Graph::add_relation_property_with(string sourceName, string destinationName, string propertyName, int value)
{
	return this->_add_relation_property_with<int>(sourceName, destinationName, propertyName, value);
}

bool SocialNetworksAnalysis::Graph::add_relation_property_with(string sourceName, string destinationName, string propertyName, double value)
{
	return this->_add_relation_property_with<double>(sourceName, destinationName, propertyName, value);
}

bool SocialNetworksAnalysis::Graph::add_relation_property_with(string sourceName, string destinationName, string propertyName, string value)
{
	return this->_add_relation_property_with<string>(sourceName, destinationName, propertyName, value);
}

bool SocialNetworksAnalysis::Graph::add_property2node(string nodeName, string propertyName, int value)
{
	return this->_add_property2node<int>(nodeName, propertyName, value);
}

bool SocialNetworksAnalysis::Graph::add_property2node(string nodeName, string propertyName, double value)
{
	return this->_add_property2node<double>(nodeName, propertyName, value);
}

bool SocialNetworksAnalysis::Graph::add_property2node(string nodeName, string propertyName, string value)
{
	return this->_add_property2node<string>(nodeName, propertyName, value);
}

bool SocialNetworksAnalysis::Graph::get_node_value(int index, string propertyName, void* returnValue, ValueType valueType)
{
	if(index < 0 || index >= this->_nodes.size()) return false;

	int propertyIndex = this->_find_relation_property_name(propertyName);
	if(propertyIndex == NOT_SET) return false;

	return this->_nodes[index]->get_value(this->_nodePropertyNames[propertyIndex], returnValue, valueType);
}

bool SocialNetworksAnalysis::Graph::get_node_value(string nodeName, string propertyName, void* returnValue, ValueType valueType)
{
	int index = this->_find_node(nodeName);
	if(index == NOT_SET) return false;

	int propertyIndex = this->_find_relation_property_name(propertyName);
	if(propertyIndex == NOT_SET) return false;

	return this->_nodes[index]->get_value(this->_nodePropertyNames[propertyIndex], returnValue, valueType);
}

bool SocialNetworksAnalysis::Graph::get_relation_value(int sourceIndex, int destinationIndex, 
	string propertyName, void* returnValue, ValueType valueType)
{
	if(sourceIndex < 0 || sourceIndex >= this->_nodes.size() || destinationIndex < 0 || destinationIndex >= this->_nodes.size())
		return false;
	int propertyIndex = this->_find_relation_property_name(propertyName);
	if(propertyIndex == NOT_SET) return false;

	return this->_nodes[sourceIndex]->get_relation_value(this->_nodes[destinationIndex], this->_relationPropertyNames[propertyIndex],
		returnValue, valueType);
}

bool SocialNetworksAnalysis::Graph::get_relation_value(string sourceName, string destinationName,
	string propertyName, void* returnValue, ValueType valueType)
{
	int sourceIndex = this->_find_node(sourceName);
	if(sourceIndex == NOT_SET) return false;

	int destinationIndex = this->_find_node(destinationName);
	if(destinationIndex == NOT_SET) return false;

	int propertyIndex = this->_find_relation_property_name(propertyName);
	if(propertyIndex == NOT_SET) return false;

	return this->_nodes[sourceIndex]->get_relation_value(this->_nodes[destinationIndex], this->_relationPropertyNames[propertyIndex],
		returnValue, valueType);
}

int SocialNetworksAnalysis::Graph::get_nodes_count()
{
	return this->_nodes.size();
}

int SocialNetworksAnalysis::Graph::get_relations_count(string nodeName)
{
	int index = this->_find_node(nodeName);

	if(index == NOT_SET)
		return NOT_SET;
	else
		return this->_nodes[index]->get_relations_count();
}

int SocialNetworksAnalysis::Graph::get_node_properties_count(string nodeName)
{
	int index = this->_find_node(nodeName);

	if(index == NOT_SET)
		return NOT_SET;
	else
		return this->_nodes[index]->get_properties_count();
}

int SocialNetworksAnalysis::Graph::get_relation_properties_count(string sourceName, string destinationName)
{
	int sourceIndex = this->_find_node(sourceName);
	int destinationIndex = this->_find_node(destinationName);

	if(sourceIndex == NOT_SET || destinationIndex == NOT_SET) 
		return NOT_SET;
	else
		return this->_nodes[sourceIndex]->get_relation_properties_count(this->_nodes[destinationIndex]);
}

SocialNetworksAnalysis::GraphNode* SocialNetworksAnalysis::Graph::element (int index)
{
	return (*this)[index];
}

SocialNetworksAnalysis::GraphNode* SocialNetworksAnalysis::Graph::element (string nodeName)
{
	return (*this)[nodeName];
}

SocialNetworksAnalysis::GraphNode* SocialNetworksAnalysis::Graph::operator [] (int index)
{
	if(index < 0 || index >= this->_nodes.size())
		return NULL;
	else
		return this->_nodes[index];
}

SocialNetworksAnalysis::GraphNode* SocialNetworksAnalysis::Graph::operator [] (string nodeName)
{
	int index = this->_find_node(nodeName);

	if(index == NOT_SET)
		return NULL;
	else
		return this->_nodes[index];
}