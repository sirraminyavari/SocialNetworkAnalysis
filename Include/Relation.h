#ifndef __SOCIALNETWORKSANALYSIS_H
	#define __SOCIALNETWORKSANALYSIS_H
	#include "SocialNetworksAnalysis.h"
#endif

#ifndef __PROPERTIESOWNER_H
	#define __PROPERTIESOWNER_H
	#include "PropertiesOwner.h"
#endif

#ifndef __GRAPHNODE_H
	#define __GRAPHNODE_H
	#include "GraphNode.h"
#endif

class SocialNetworksAnalysis::Relation : public PropertiesOwner
{
	GraphNode* _source;
	GraphNode* _destination;
public:
	Relation();
	~Relation();
	Relation(GraphNode* destination);
	Relation(GraphNode* source, GraphNode* destination);
	void clear();
	void set_source(GraphNode* source);
	void set_destination(GraphNode* destination);
	void set_relation_nodes(GraphNode* source, GraphNode* destination);
	GraphNode* get_source();
	GraphNode* get_destination();
	string get_source_name();
	string get_destination_name();
	int compare_sourceNames(Relation& r);
	int compare_destinationNames(Relation& r);
};