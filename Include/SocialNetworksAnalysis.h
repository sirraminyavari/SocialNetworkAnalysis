#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

#ifndef NO_PATH
	#define NO_PATH -1
#endif

#ifndef NOT_SET
	#define NOT_SET -1
#endif

#ifndef EXISTS
	#define EXISTS 1
#endif

#ifndef NOT_EXISTS
	#define NOT_EXISTS 0
#endif

using namespace std;

namespace SocialNetworksAnalysis
{
	class OperatorCodes;
	class MathOperator;
	enum ElementType
	{
		NotSet,
		Constant,
		Variable,
		Operator
	};
	class MathPhraseElement;
	bool compare_variables(pair<double*, string>*, pair<double*, string>*);
	class MathPhrase;
	bool compare_phrases(MathPhrase*, MathPhrase*);
	class Calculator;

	enum ValueType
	{
		integerValue,
		doubleValue,
		stringValue,
		notSet
	};
	union Value
	{
		int intVal;
		double dblVal;
		char* strVal;
	};
	class PropertyValue;
	bool operator > (const PropertyValue&, const PropertyValue&);
	bool operator == (const PropertyValue&, const PropertyValue&);
	bool operator < (const PropertyValue&, const PropertyValue&);
	bool operator >= (const PropertyValue&, const PropertyValue&);
	bool operator <= (const PropertyValue&, const PropertyValue&);
	bool operator != (const PropertyValue&, const PropertyValue&);

	class Property;
	bool operator > (const Property&, const Property&);
	bool operator < (const Property&, const Property&);
	bool operator == (const Property&, const Property&);
	bool operator >= (const Property&, const Property&);
	bool operator <= (const Property&, const Property&);
	bool operator != (const Property&, const Property&);

	bool compare_properties(Property*, Property*);

	class PropertiesOwner;

	class Relation;

	bool compare_relations(Relation*, Relation*);
	class GraphNode;

	bool compare_nodes(GraphNode*, GraphNode*);
	bool compare_names(string*, string*);
	class Graph;

	enum FileType
	{
		edgeType
	};
	class MatrixAnalyzer;
};

#ifndef __PROPERTIESOWNER_H
	#define __PROPERTIESOWNER_H
	#include "PropertiesOwner.h"
#endif

#ifndef __CALCULATOR_H
	#define __CALCULATOR_H
	#include "Calculator.h"
#endif

#ifndef __MATRIXANALYZER_H
	#define __MATRIXANALYZER_H
	#include "MatrixAnalyzer.h"
#endif

#ifndef __GRAPH_H
	#define __GRAPH_H
	#include "Graph.h"
#endif