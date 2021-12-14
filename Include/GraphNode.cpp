#ifndef __PROPERTY_H
	#define __PROPERTY_H
	#include "Property.h"
#endif

#ifndef __RELATION_H
	#define __RELATION_H
	#include "Relation.h"
#endif

#ifndef __GRAPHNODE_H
	#define __GRAPHNODE_H
	#include "GraphNode.h"
#endif

bool SocialNetworksAnalysis::compare_relations(Relation* first, Relation* second)
{
	if(first->get_destination()->get_node_name() < second->get_destination()->get_node_name())
		return true;
	else
		return false;
}

void SocialNetworksAnalysis::GraphNode::_sort_relations()
{
	sort(this->_relations.begin(), this->_relations.end(), SocialNetworksAnalysis::compare_relations);
	this->_isSorted_relations = true;
}

int SocialNetworksAnalysis::GraphNode::_find_relation_with(GraphNode* destination)
{
	if(!this->_isSorted_relations) this->_sort_relations();

	int startIndicator = 0;
	int endIndicator = this->_relations.size() - 1;
	int middleIndicator = (endIndicator - startIndicator) / 2;

	while(startIndicator <= endIndicator)
	{
		if(this->_relations[startIndicator]->get_destination() == destination)
			return startIndicator;
		else if(this->_relations[endIndicator]->get_destination() == destination)
			return endIndicator;
		else if(this->_relations[middleIndicator]->get_destination() == destination)
			return middleIndicator;
		else
		{
			if(this->_relations[middleIndicator]->get_destination_name() < destination->get_node_name())
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

int SocialNetworksAnalysis::GraphNode::_find_relation_with(string destinationName)
{
	if(!this->_isSorted_relations) this->_sort_relations();

	int startIndicator = 0;
	int endIndicator = this->_relations.size() - 1;
	int middleIndicator = (endIndicator - startIndicator) / 2;

	while(startIndicator <= endIndicator)
	{
		if(this->_relations[startIndicator]->get_destination_name() == destinationName)
			return startIndicator;
		else if(this->_relations[endIndicator]->get_destination_name() == destinationName)
			return endIndicator;
		else if(this->_relations[middleIndicator]->get_destination_name() == destinationName)
			return middleIndicator;
		else
		{
			if(this->_relations[middleIndicator]->get_destination_name() < destinationName)
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

inline void SocialNetworksAnalysis::GraphNode::_set_isSorted_relations_after_addition(GraphNode* destination)
{
	if(this->_relations.size() && this->_relations.back()->get_destination()->get_node_name() > destination->get_node_name())
		this->_isSorted_relations = false;
	else if(!this->_relations.size())
		this->_isSorted_relations = true;
}

template <class T>
inline bool SocialNetworksAnalysis::GraphNode::_set_relation_with(GraphNode* destination, string* propertyName, T value)
{
	int index = this->_find_relation_with(destination);

	return this->_relations[index]->set_property(propertyName, value);
}

template <class T>
inline bool SocialNetworksAnalysis::GraphNode::_add_relation_with(GraphNode* destination, string* propertyName, T value)
{
	int index = this->_find_relation_with(destination);

	if(index == NOT_SET) 
	{
		this->_set_isSorted_relations_after_addition(destination);

		Relation* temp = new Relation(this, destination);
		temp->add_property(propertyName, value);
		this->_relations.push_back(temp);

		return true;
	}
	else
		return this->_relations[index]->add_property(propertyName, value);
}

SocialNetworksAnalysis::GraphNode::GraphNode()
{
	this->clear();
}

SocialNetworksAnalysis::GraphNode::GraphNode(string nodeName)
{
	this->clear();
	this->_nodeName = nodeName;
}

SocialNetworksAnalysis::GraphNode::~GraphNode()
{
	this->clear();
}

void SocialNetworksAnalysis::GraphNode::clear()
{
	for(int i = 0; i < this->_relations.size(); ++i)
		delete this->_relations[i];
	this->_nodeName = "";
	this->_relations.clear();
	this->_isSorted_relations = false;
}

bool SocialNetworksAnalysis::GraphNode::has_relation_with(GraphNode* nodeName)
{
	if(this->_find_relation_with(nodeName) < 0)
		return false;
	else
		return true;
}
	
bool SocialNetworksAnalysis::GraphNode::has_relation_with(GraphNode* nodeName, string* propertyName)
{
	int index = this->_find_relation_with(nodeName);

	if(index < 0)
		return false;
	else
	{
		if(this->_relations[index]->has_property(propertyName))
			return true;
		else
			return false;
	}
}

SocialNetworksAnalysis::Property SocialNetworksAnalysis::GraphNode::get_property_with(GraphNode* nodeName, string* propertyName)
{
	int index = this->_find_relation_with(nodeName);

	if(index < 0)
		return NULL;
	else
		return this->_relations[index]->get_property(propertyName);
}

//bool SocialNetworksAnalysis::GraphNode::get_relation_value(int destinationIndex, string* propertyName,
//	void* returnValue, ValueType valueType)
//{
//	if(destinationIndex < 0 || destinationIndex >= this->_relations.size()) return false;
//
//	return this->_relations[destinationIndex]->get_value(propertyName, returnValue, valueType);
//}

bool SocialNetworksAnalysis::GraphNode::get_relation_value(GraphNode* destination, string* propertyName,
	void* returnValue, ValueType valueType)
{
	int destinationIndex = this->_find_relation_with(destination);

	if(destinationIndex == NOT_SET) return false;

	return this->_relations[destinationIndex]->get_value(propertyName, returnValue, valueType);
}

int SocialNetworksAnalysis::GraphNode::get_relations_count()
{
	return this->_relations.size();
}

int SocialNetworksAnalysis::GraphNode::get_relation_properties_count(GraphNode* destination)
{
	int index = this->_find_relation_with(destination);

	if(index == NOT_SET)
		return NOT_SET;
	else
		return this->_relations[index]->get_properties_count();
}

void SocialNetworksAnalysis::GraphNode::set_node_name(string nodeName)
{
	this->_nodeName = nodeName;
}

string SocialNetworksAnalysis::GraphNode::get_node_name()
{
	return this->_nodeName;
}

bool SocialNetworksAnalysis::GraphNode::set_relation_with(GraphNode* destination, string* propertyName, int value)
{
	return this->_set_relation_with<int>(destination, propertyName, value);
}

bool SocialNetworksAnalysis::GraphNode::set_relation_with(GraphNode* destination, string* propertyName, double value)
{
	return this->_set_relation_with<double>(destination, propertyName, value);
}

bool SocialNetworksAnalysis::GraphNode::set_relation_with(GraphNode* destination, string* propertyName, string value)
{
	return this->_set_relation_with<string>(destination, propertyName, value);
}

bool SocialNetworksAnalysis::GraphNode::add_relation_with(GraphNode* destination, string* propertyName, int value)
{
	return this->_add_relation_with<int>(destination, propertyName, value);
}

bool SocialNetworksAnalysis::GraphNode::add_relation_with(GraphNode* destination, string* propertyName, double value)
{
	return this->_add_relation_with<double>(destination, propertyName, value);
}

bool SocialNetworksAnalysis::GraphNode::add_relation_with(GraphNode* destination, string* propertyName, string value)
{
	return this->_add_relation_with<string>(destination, propertyName, value);
}

SocialNetworksAnalysis::Relation* SocialNetworksAnalysis::GraphNode::element(int index)
{
	return (*this)[index];
}

SocialNetworksAnalysis::Relation* SocialNetworksAnalysis::GraphNode::element(string destinationName)
{
	return (*this)[destinationName];
}

SocialNetworksAnalysis::Relation* SocialNetworksAnalysis::GraphNode::operator [] (int index)
{
	if(index < 0 || index >= this->_relations.size())
		return NULL;
	else
		return this->_relations[index];
}

SocialNetworksAnalysis::Relation* SocialNetworksAnalysis::GraphNode::operator [] (string destinationName)
{
	int index = this->_find_relation_with(destinationName);

	if(index == NOT_SET)
		return NULL;
	else
		return this->_relations[index];
}