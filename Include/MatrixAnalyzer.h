class SocialNetworksAnalysis::MatrixAnalyzer
{
private:

	int** matrix;
	int verticesCount; //number of vertices
	int* degreeCentrality;
	double* closenessCentrality;
	double* betweennessCentrality;
	int** minDistance;
	int** predecessor;
	int** minDistanceCount;
	int relationsCount;

	void edgeType_fileReader(string& fileAddress);
	void merge_sort(int* arr[3], int startIndex, int endIndex);
	void compute_allPair_minDistanceCount();
public:
	MatrixAnalyzer();
	MatrixAnalyzer(int n);
	MatrixAnalyzer(string& fileAddress, FileType ft);
	~MatrixAnalyzer();
	void degree_centrality();
	void closeness_centrality();
	void betweenness_centrality();
	double density();
	void print_matrix();
	void print_degree_centrality();
	void print_closeness_centrality();
	void print_betweenness_centrality();
	void print_min_distances();
	void print_predecessors();
	void print_min_distance_counts();
	//void betweenness_centrality();
};