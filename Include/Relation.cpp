#ifndef __RELATION_H
	#define __RELATION_H
	#include "Relation.h"
#endif

SocialNetworksAnalysis::Relation::Relation()
{
	this->clear();
}

SocialNetworksAnalysis::Relation::~Relation()
{
	this->clear();
}
	
SocialNetworksAnalysis::Relation::Relation(GraphNode* destination)
{
	this->clear();
	this->set_destination(destination);
}

SocialNetworksAnalysis::Relation::Relation(GraphNode* source, GraphNode* destination)
{
	this->clear();
	this->set_source(source);
	this->set_destination(destination);
}
	
void SocialNetworksAnalysis::Relation::clear()
{
	this->_destination = NULL;
	this->_source = NULL;
}

void SocialNetworksAnalysis::Relation::set_source(GraphNode* source)
{
	this->_source = source;
}
	
void SocialNetworksAnalysis::Relation::set_destination(GraphNode* destination)
{
	this->_destination = destination;
}

void SocialNetworksAnalysis::Relation::set_relation_nodes(GraphNode* source, GraphNode* destination)
{
	this->set_source(source);
	this->set_destination(destination);
}

SocialNetworksAnalysis::GraphNode* SocialNetworksAnalysis::Relation::get_source()
{
	return this->_source;
}

SocialNetworksAnalysis::GraphNode* SocialNetworksAnalysis::Relation::get_destination()
{
	return this->_destination;
}

string SocialNetworksAnalysis::Relation::get_source_name()
{
	return this->_source->get_node_name();
}

string SocialNetworksAnalysis::Relation::get_destination_name()
{
	return this->_destination->get_node_name();
}

int SocialNetworksAnalysis::Relation::compare_sourceNames(Relation& r)
{
	if(this->get_source_name() < r.get_source_name())
		return -1;
	else if(this->get_source_name() > r.get_source_name())
		return 1;
	else
		return 0;
}

int SocialNetworksAnalysis::Relation::compare_destinationNames(Relation& r)
{
	if(this->get_destination_name() < r.get_destination_name())
		return -1;
	else if(this->get_destination_name() > r.get_destination_name())
		return 1;
	else
		return 0;
}