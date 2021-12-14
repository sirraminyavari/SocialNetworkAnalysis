#ifndef __SOCIALNETWORKSANALYSIS_H
	#define __SOCIALNETWORKSANALYSIS_H
	#include "Include\SocialNetworksAnalysis.h"
#endif

using namespace std;
using namespace SocialNetworksAnalysis;

template <class T>
void merge_sort(vector<T*>& arr, int startIndex, int endIndex)
{
	int difference = endIndex - startIndex;

	if(startIndex >= endIndex) return;

	int median = startIndex + difference / 2;
	merge_sort(arr, startIndex, median);
	merge_sort(arr, median + 1, endIndex);

	T** temp;
	int l = startIndex, k = median + 1;
	temp = new T*[difference + 1];
	for(int i = 0; i < difference + 1; ++i)
		if((l <= median && k <= endIndex && *arr[l] < *arr[k]) || k > endIndex)
		{
			temp[i] = arr[l];
			++l;
		}
		else
		{
			temp[i] = arr[k];
			++k;
		}

	for(int i = 0; i < difference + 1; ++i)
		arr[startIndex + i] = temp[i];

	//delete the allocated memory
	delete[] temp;
}

void calculator_test()
{
	cout << endl << "---------- Calculator Testing Started ----------" << endl;

	double val = 0;

	Calculator calc;
	calc.add_number("ramin", 23);
	calc.add_number("gesi", 2);
	calc.add_variable("shervin");
	calc.compute(val);
	cout << val << endl;
	calc.reassign_variable("shervin", 6);
	calc.add_number("shervin");
	calc.compute(val);
	cout << val << endl;

	calc.add_mathSentence("3.0023(5+20)5");
	calc.compute(val);
	cout << val << endl;

	//add new math phrase
	cout << endl;
	calc.add_mathSentence("3.0023(5+20)5", "new");
	calc.compute(val, "new");
	cout << val << endl;

	calc.clear("new");
	if(calc.compute(val, ""))
		cout << endl << val << endl;
	else
		cout << endl << "-- 1 --" << endl;
	if(calc.compute(val, "new"))
		cout << val << endl << endl;
	else
		cout << "-- 2 --" << endl << endl;

	calc.add_number(3, "new");
	calc.add_operator("*", "new");
	calc.add_operator("(", "new");
	calc.add_number(5, "new");
	calc.add_operator("+", "new");
	calc.add_number("ramin", 20, "new");
	calc.add_operator(")", "new");
	calc.add_operator("/", "new");
	calc.add_number(2, "new");
	if(!calc.compute(val, "new"))
		cout << "error" << endl;
	else
		cout << val << endl;

	calc.reassign_variable("ramin", 40, "new");
	calc.compute(val, "new");
	cout << val << endl;

	cout << endl << "---------- Calculator Testing Finished ----------" << endl << endl;
}

//void propertyValue_test()
//{
//	PropertyValue pv;
//	pv.set(12);
//	cout << pv.get_int() << endl;
//	cout << pv.get_double() << endl;
//	cout << pv.get_string() << endl;
//
//	pv.set(12.0);
//	cout << pv.get_int() << endl;
//	cout << pv.get_double() << endl;
//	cout << pv.get_string() << endl;
//
//	pv.set("12.0");
//	cout << pv.get_int() << endl;
//	cout << pv.get_double() << endl;
//	cout << pv.get_string() << endl;
//
//	string str1 = "shervin";
//	string str2 = "ramin";
//	pv.set(str1);
//	PropertyValue pv3(str2);
//	cout << endl << "-- " << str1 << " --  -- " << str2 << " --" << endl << endl;
//	if(pv > pv3) cout << "1 - Greater" << endl;
//	if(pv < pv3) cout << "2 - Lower" << endl;
//	if(pv == pv3) cout << "3 - Equal" << endl;
//	if(pv >= pv3) cout << "4 - Greater-Equal" << endl;
//	if(pv <= pv3) cout << "5 - Lower-Equal" << endl;
//	if(pv != pv3) cout << "6 - Not-Equal" << endl;
//
//	PropertyValue pv2;
//	pv2 = pv;
//	cout << endl;
//	cout << pv2.get_int() << endl;
//	cout << pv2.get_double() << endl;
//	cout << pv2.get_string() << endl;
//}
//
//void property_test()
//{
//	Property p;
//	p.set(12);
//	cout << p.get_int() << endl;
//	cout << p.get_double() << endl;
//	cout << p.get_string() << endl;
//
//	p.set(12.0);
//	cout << p.get_int() << endl;
//	cout << p.get_double() << endl;
//	cout << p.get_string() << endl;
//
//	p.set("12.0");
//	cout << p.get_int() << endl;
//	cout << p.get_double() << endl;
//	cout << p.get_string() << endl;
//
//	string strp1 = "shervin";
//	string strp2 = "ramin";
//	p.set(strp1);
//	Property p3(strp2);
//	cout << endl << "-- " << strp1 << " --  -- " << strp2 << " --" << endl << endl;
//	if(p > p3) cout << "1 - Greater" << endl;
//	if(p < p3) cout << "2 - Lower" << endl;
//	if(p == p3) cout << "3 - Equal" << endl;
//	if(p >= p3) cout << "4 - Greater-Equal" << endl;
//	if(p <= p3) cout << "5 - Lower-Equal" << endl;
//	if(p != p3) cout << "6 - Not-Equal" << endl;
//
//	Property p2;
//	p2 = p;
//	cout << endl;
//	cout << p2.get_int() << endl;
//	cout << p2.get_double() << endl;
//	cout << p2.get_string() << endl;
//}
//
//void relation_test()
//{
//	Relation r;
//	r.add_property("ramino", 23);
//	r.add_property("gesi", 20);
//	r.add_property("shervin", 24);
//	if(r.has_property("ramin"))
//		cout << "Ramin: Yes" << endl;
//	else
//		cout << "Ramin: No" << endl;
//}

void matrix_analyzer_test()
{
	cout << endl << "---------- Matrix Analyzer Testing Started ----------" << endl;

	cout << endl;
	string str = "in.txt";
	MatrixAnalyzer mt(str, FileType::edgeType);
	mt.degree_centrality();
	mt.closeness_centrality();
	mt.betweenness_centrality();
	mt.betweenness_centrality();
	mt.print_matrix();
	cout << endl;
	mt.print_min_distances();
	cout << endl;
	mt.print_predecessors();
	cout << endl;
	mt.print_min_distance_counts();
	cout << endl;
	mt.print_degree_centrality();
	cout << endl;
	mt.print_closeness_centrality();
	cout << endl;
	mt.print_betweenness_centrality();
	cout << endl << "The density of the network is: " << mt.density() << endl;

	cout << endl << "---------- Matrix Analyzer Testing Finished ----------" << endl << endl;
}

void graph_test()
{
	cout << endl << "---------- Graph Testing Started ----------" << endl;

	Graph graph;
	graph.add_node("ramin");
	graph.add_node("shervin");
	graph.add_node("payam");
	
	graph.add_relation_property_with("ramin", "shervin", "baradar", "yes");
	if(graph.has_relation_with("ramin", "shervin", "baradar"))
		cout << endl << "Y" << endl;
	else
		cout << endl << "N" << endl;

	if(graph.has_relation_with("ramin", "payam", "baradar"))
		cout << endl << "Y" << endl;
	else
		cout << endl << "N" << endl;

	if(graph.has_relation_with("ramin", "naser", "baradar"))
		cout << endl << "Y" << endl;
	else
		cout << endl << "N" << endl;

	cout << endl;
	for(int i = 0; i < graph.get_nodes_count(); ++i)
		cout << graph[i]->get_node_name() << " --- " << graph.element(i)->get_node_name() << endl;
	cout << endl << graph["ramin"]->get_node_name() << " --- " << graph.element("ramin")->get_node_name() << endl;	

	cout << endl << "---------- Graph Testing Finished ----------" << endl << endl;
}

void main()
{
	calculator_test();

	matrix_analyzer_test();

	graph_test();
}