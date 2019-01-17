#pragma once

class Edge {
private:
	double pesoAresta;
	int dest; // Node destiNode
	int src;
public:
	Edge(int iD_Node, double pesoA, int idHead);
	~Edge();
	double getWeightEdge();
	int getDest();
	int getSrc();
	void setWeightEdge(double peso);
	bool operator<(const  Edge & other) //(1)
	{
		return pesoAresta < other.pesoAresta;
	}

	bool operator > (Edge& cmp1)
	{
		//Do your own calculations here
		if (cmp1.pesoAresta < pesoAresta)
		{
			return true;
		}

		return false;
	}
}; 
