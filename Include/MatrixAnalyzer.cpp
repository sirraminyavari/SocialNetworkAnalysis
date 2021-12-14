#ifndef __SOCIALNETWORKSANALYSIS_H
	#define __SOCIALNETWORKSANALYSIS_H
	#include "SocialNetworksAnalysis.h"
#endif

#ifndef __MATRIXANALYZER_H
	#define __MATRIXANALYZER_H
	#include "MatrixAnalyzer.h"
#endif

void SocialNetworksAnalysis::MatrixAnalyzer::edgeType_fileReader(string& fileAddress)
{
	ifstream fin(fileAddress);

	if(!fin.is_open())
	{
		cout << "Error in reading the file";

		verticesCount = 0;
		matrix = NULL;
		degreeCentrality = NULL;
		closenessCentrality = NULL;
		betweennessCentrality = NULL;
		minDistance = NULL;
		predecessor = NULL;
		minDistanceCount = NULL;
		relationsCount = NOT_SET;

		return;
	}

	fin >> verticesCount;
	relationsCount = 0;

	//Fill the Matrix
	matrix = new int*[verticesCount];
	for (int i = 0; i < verticesCount; ++i)
		matrix[i] = new int[verticesCount];

	//Initialize the Matrix
	for(int i = 0; i < verticesCount; ++i)
		for(int j = 0; j < verticesCount; ++j)
			matrix[i][j] = NO_PATH;

	int first, second, value;
	while(!fin.eof())
	{
		fin >> first >> second >> value;
		if(!(first > verticesCount || second > verticesCount || value < 0))
		{
			matrix[first - 1][second - 1] = matrix[second - 1][first - 1] = value;
			++relationsCount;
		}
		//else return error
	}

	//Initialize other variables
	degreeCentrality = new int[verticesCount];
	closenessCentrality = new double[verticesCount];
	betweennessCentrality = new double[verticesCount];
	minDistance = new int*[verticesCount];
	predecessor = new int*[verticesCount];
	minDistanceCount = new int*[verticesCount];
	for(int i = 0; i < verticesCount; ++i)
	{
		degreeCentrality[i] = NOT_SET;
		closenessCentrality[i] = NOT_SET;
		betweennessCentrality[i] = NOT_SET;
		minDistance[i] = new int[verticesCount];
		predecessor[i] = new int[verticesCount];
		minDistanceCount[i] = new int[verticesCount];
		for(int j = 0; j < verticesCount; ++j)
		{
			minDistance[i][j] = NOT_SET;
			predecessor[i][j] = NOT_SET;
			minDistanceCount[i][j] = NOT_SET;
		}
	}
}

void SocialNetworksAnalysis::MatrixAnalyzer::merge_sort(int* arr[3], int startIndex, int endIndex)
{
	int difference = endIndex - startIndex;

	if(startIndex == endIndex) return;

	int median = startIndex + difference / 2;
	merge_sort(arr, startIndex, median);
	merge_sort(arr, median + 1, endIndex);

	int* temp[3];
	int l = startIndex, k = median + 1;
	for(int i = 0; i < 3; ++i) temp[i] = new int[difference + 1];
	for(int i = 0; i < difference + 1; ++i)
		if((l <= median && k <= endIndex && arr[2][l] < arr[2][k]) || k > endIndex)
		{
			temp[0][i] = arr[0][l];
			temp[1][i] = arr[1][l];
			temp[2][i] = arr[2][l];

			++l;
		}
		else
		{
			temp[0][i] = arr[0][k];
			temp[1][i] = arr[1][k];
			temp[2][i] = arr[2][k];

			++k;
		}

	for(int i = 0; i < difference + 1; ++i)
	{
		arr[0][startIndex + i] = temp[0][i];
		arr[1][startIndex + i] = temp[1][i];
		arr[2][startIndex + i] = temp[2][i];
	}

	//delete the allocated memory
	for(int i = 0; i < 3; ++i) delete[] temp[i];
}
	
void SocialNetworksAnalysis::MatrixAnalyzer::compute_allPair_minDistanceCount()
{

	int* distances[3];
	for(int i = 0; i < 3; ++i)
		distances[i] = new int[verticesCount * verticesCount];

	for(int i = 0 ; i < verticesCount; ++i)
		for(int j = 0; j < verticesCount; ++j)
		{
			distances[0][i * verticesCount + j] = i;
			distances[1][i * verticesCount + j] = j;
			distances[2][i * verticesCount + j] = minDistance[i][j];
		}

	//sort the distances matrix based on third column (third column: distances)
	this->merge_sort(distances, 0, verticesCount * verticesCount - 1);

	for(int i = 0; i < verticesCount; ++i)
		for(int j = 0; j < verticesCount; ++j)
			minDistanceCount[i][j] = 0;

	for(int i = 0, a, b; i < verticesCount * verticesCount; ++i)
	{
		a = distances[0][i]; //origin node
		b = distances[1][i]; //destination node

		if(a == b) continue;

		for(int j = 0; j < verticesCount; ++j)
			if(matrix[j][b] > 0 && minDistance[a][j] + minDistance[j][b] == minDistance[a][b] &&
				minDistance[a][j] != NO_PATH && minDistance[j][b] != NO_PATH)
			{
				if(a == j)
					minDistanceCount[a][b] += 1;
				else
					minDistanceCount[a][b] += minDistanceCount[a][j];
			}
	}

	//delete the allocated memory
	for(int i = 0; i < 3; ++i) delete[] distances[i];
}

SocialNetworksAnalysis::MatrixAnalyzer::MatrixAnalyzer()
{
	this->verticesCount = 0;
	this->matrix = NULL;
	this->degreeCentrality = NULL;
	this->closenessCentrality = NULL;
	this->betweennessCentrality = NULL;
	this->minDistance = NULL;
	this->predecessor = NULL;
	this->minDistanceCount = NULL;
	this->relationsCount = NOT_SET;
}

SocialNetworksAnalysis::MatrixAnalyzer::MatrixAnalyzer(int n)
{
	verticesCount = verticesCount;
	relationsCount = NOT_SET;
	matrix = new int*[verticesCount];
	degreeCentrality = new int[verticesCount];
	closenessCentrality = new double[verticesCount];
	betweennessCentrality = new double[verticesCount];
	minDistance = new int*[verticesCount];
	predecessor = new int*[verticesCount];
	minDistanceCount = new int*[verticesCount];
	for(int i = 0; i < verticesCount; ++i)
	{
		matrix[verticesCount] = new int[verticesCount];
		minDistance[i] = new int[verticesCount];
		predecessor[i] = new int[verticesCount];
		minDistanceCount[i] = new int[verticesCount];
		degreeCentrality[i] = NOT_SET;
		closenessCentrality[i] = NOT_SET;
		betweennessCentrality[i] = NOT_SET;
	}

	for(int i = 0; i < verticesCount; ++i)
		for(int j = 0; j < verticesCount; ++j)
		{
			matrix[i][j] = NO_PATH;
			minDistance[i][j] = NOT_SET;
			predecessor[i][j] = NOT_SET;
			minDistanceCount[i][j] = NOT_SET;
		}
}

SocialNetworksAnalysis::MatrixAnalyzer::MatrixAnalyzer(string& fileAddress, FileType ft)
{
	switch (ft)
	{
	case FileType::edgeType:
		edgeType_fileReader(fileAddress);
	}
}

SocialNetworksAnalysis::MatrixAnalyzer::~MatrixAnalyzer()
{
	for(int i = 0; i < verticesCount; ++i)
		delete[] matrix[i];
	delete[] matrix;
}

void SocialNetworksAnalysis::MatrixAnalyzer::degree_centrality()
{
	for(int i = 0, count; i < verticesCount; ++i)
	{
		count = 0;
		for(int j = 0; j < verticesCount; ++j)
			if (matrix[i][j] != NO_PATH)
				++count;
		degreeCentrality[i] = count;
	}
}

void SocialNetworksAnalysis::MatrixAnalyzer::closeness_centrality()
{
	for(int i = 0; i < verticesCount; ++i)
		for(int j = 0; j < verticesCount; ++j)
		{
			if(matrix[i][j] <= 0 && i != j)
				minDistance[i][j] = NO_PATH;
			else
				minDistance[i][j] = matrix[i][j];

			predecessor[i][j] = i;
		}
	for(int i = 0; i < verticesCount; ++i) minDistance[i][i] = 0;

	for(int k = 0; k < verticesCount; ++k)
		for(int i = 0; i < verticesCount; ++i)
			for(int j = 0; j < verticesCount; ++j)
				if(minDistance[i][k] != NO_PATH && minDistance[k][j] != NO_PATH && 
					(minDistance[i][j] == NO_PATH || minDistance[i][k] + minDistance[k][j] < minDistance[i][j]))
				{
					minDistance[i][j] = minDistance[i][k] + minDistance[k][j];
					predecessor[i][j] = predecessor[k][j];
				}

	//calculate the Closeness Centrality for all nodes
	for(int i = 0; i < verticesCount; ++i)
		closenessCentrality[i] = 0;
	for(int i = 0; i < verticesCount; ++i)
		for(int j = 0; j < verticesCount; ++j)
			if(minDistance[i][j] != NO_PATH) closenessCentrality[i] += minDistance[i][j];
	//Closeness Centrality equals (1 / average distance)
	for(int i = 0; i < verticesCount; ++i)
		closenessCentrality[i] = verticesCount / closenessCentrality[i];
}

void SocialNetworksAnalysis::MatrixAnalyzer::betweenness_centrality()
{
	compute_allPair_minDistanceCount();

	for(int i = 0; i < verticesCount; ++i) betweennessCentrality[i] = 0;
		
	for(int k = 0; k < verticesCount; ++k)
		for(int i = 0; i < verticesCount; ++i)
			for(int j = 0; j < verticesCount; ++j)
				if(i != j && i != k && j != k && minDistance[i][k] != NO_PATH && minDistance[k][j] != NO_PATH &&
					minDistance[i][k] + minDistance[k][j] == minDistance[i][j])
					betweennessCentrality[k] += double((minDistanceCount[i][k] * minDistanceCount[k][j]) / minDistanceCount[i][j]);

	for(int i = 0; i < verticesCount; ++i)
		betweennessCentrality[i] /= (verticesCount - 1) * (verticesCount - 1) - verticesCount + 1;
}

double SocialNetworksAnalysis::MatrixAnalyzer::density()
{
	double temp = verticesCount * (verticesCount - 1);
	temp = double(relationsCount / temp);
	return temp;
}

void SocialNetworksAnalysis::MatrixAnalyzer::print_matrix()
{
	for(int i = 0; i < verticesCount; ++i)
	{
		for(int j = 0; j < verticesCount; ++j)
			if(matrix[i][j] != NO_PATH)
				cout << matrix[i][j] << "  ";
			else
				cout << 0 << "  ";
		cout << endl;
	}
}
	
void SocialNetworksAnalysis::MatrixAnalyzer::print_degree_centrality()
{
	for(int i = 0; i < verticesCount; ++i)
		cout << "Degree Cenrality of node " << i + 1 << " is: " << degreeCentrality[i] << endl;
}

void SocialNetworksAnalysis::MatrixAnalyzer::print_closeness_centrality()
{
	for(int i = 0; i < verticesCount; ++i)
		cout << "Closeness Cenrality of node " << i + 1 << " is: " << closenessCentrality[i] << endl;
}

void SocialNetworksAnalysis::MatrixAnalyzer::print_betweenness_centrality()
{
	for(int i = 0; i < verticesCount; ++i)
		cout << "Betweenness Cenrality of node " << i + 1 << " is: " << betweennessCentrality[i] << endl;
}

void SocialNetworksAnalysis::MatrixAnalyzer::print_min_distances()
{
	for(int i = 0; i < verticesCount; ++i)
	{
		for(int j = 0; j < verticesCount; ++j)
			cout << minDistance[i][j] << "  ";
		cout << endl;
	}
}

void SocialNetworksAnalysis::MatrixAnalyzer::print_predecessors()
{
	for(int i = 0; i < verticesCount; ++i)
	{
		for(int j = 0; j < verticesCount; ++j)
			cout << predecessor[i][j] + 1 << "  ";
		cout << endl;
	}
}

void SocialNetworksAnalysis::MatrixAnalyzer::print_min_distance_counts()
{
	for(int i = 0; i < verticesCount; ++i)
	{
		for(int j = 0; j < verticesCount; ++j)
			cout << minDistanceCount[i][j] << "  ";
		cout << endl;
	}
}

//void SocialNetworksAnalysis::MatrixAnalyzer::betweenness_centrality()
//{
//	deque<int> st;
//	deque<int> que;
//	deque<int>* P = new deque<int>[verticesCount];
//	int* sigma = new int[verticesCount];
//	int* d = new int[verticesCount];
//	double* z = new double[verticesCount];

//	for(int i = 0; i < verticesCount; ++i)
//	{
//		st.clear();
//		
//		for(int k = 0; k < verticesCount; ++k) 
//		{
//			P[k].clear();
//			sigma[k] = 0;
//			d[k] = NO_PATH;
//		}
//		sigma[i] = 1;
//		d[i] = 0;

//		que.clear();
//		que.push_back(i);
//		while(!que.empty())
//		{
//			st.push_back(que.front());
//			que.pop_front();

//			for(int j = 0; j < verticesCount; ++j)
//			{
//				if(matrix[st.back()][j] == NO_PATH) continue;

//				// j found for the first time?
//				if(d[j] == NO_PATH)
//				{
//					que.push_back(j);
//					d[j] = d[i] + 1;
//				}

//				//shortest path to j via i
//				if(d[j] == d[i] + 1)
//				{
//					sigma[j] += sigma[i];
//					P[j].push_back(i);
//				}
//			} //end of for(int j = 0; j < verticesCount && matrix[st.back()][j] != NO_PATH; ++j)
//		} //end of while(!que.empty())

//		for(int j = 0; j < verticesCount; ++j) z[j] = 0;
//		// S returns vertices in order of non-increasing distance from i
//		while(!st.empty())
//		{
//			int w, pwSize, v;
//			w = st.back();
//			st.pop_back();
//			pwSize = P[w].size();
//			for(int j = 0; j < pwSize; ++j)
//			{
//				v = P[w][j];
//				z[v] += double(sigma[v] / sigma[w]) * (1 + z[w]);
//			}
//			if(w != i) betweennessCentrality[w] += z[w];
//		}
//	} //end of for(int i = 0; i < verticesCount; ++i)

//	//delete the allocations
//	delete[] P;
//	delete[] sigma;
//	delete[] d;
//	delete[] z;
//}