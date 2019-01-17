#include "../Headers/Utils.h"



Utils::Utils()
{














}

Utils::Utils(string fileName) {

	string tempPath = fileName;
	tempPath.pop_back();
	tempPath.pop_back();
	tempPath.pop_back();
	tempPath.pop_back();
	tempPath += "Sol.py";
	this->fileName = tempPath;
}

Utils::~Utils()
{
}


string Utils::colorTable(int colorIndex)
{
	string tabela[25] =
	{ "#000000", // 1-Black
		"#FF0000", // 2-Red
		"#00FF00", // 3-Lime
		"#0000FF", // 4-Blue
		"#FFFF00", // 5-Yellow
		"#00FFFF", // 6-Cyan
		"#FF00FF", // 7-Fuchsia
		"#C0C0C0", // 8-Silver
		"#800080", //9-Purple
		"#800000", //10-Maroon
		"#808000", //11-Olive
		"#008000", //12-Green
		"#808080", // 13-Gray
		"#008080", //14-Teal
		"#000080", //15-Navy
		"#DC143C", //16-crimson
		"#CD5C5C", //17-indian red
		"#FF4500", //18-orange red
		"#FF8C00", //19-dark orange
		"#DAA520", //20-golden rod
		"#2F4F4F", //21-dark slate gray
		"#8B4513", //22-saddle brown
		"#BC8F8F", //23-rosy brown
		"#B0C4DE", //24-light steel blue
		"#BDB76B", //25-dark khaki
	};
	return tabela[colorIndex % 25];
}


void Utils::printGraph(ShortSolution *solution)
{
	fstream a;
	a.open("graph.py", fstream::out);
	int size = 14;
	string corAtual;
	string corPreenchimento;




	a << "import matplotlib.pyplot as plt\n\n";



	vector <double> costClusters;
	vector <vector<int>> clusters = solution->getClusters();
	vector <Object*> graph = *solution->getObjects();
	

	for (size_t i = 0; i < graph.size(); i++) {
			//cout << "plt.plot(" << graph[clusters[i][j] - 1].getX() << "," << graph[clusters[i][j] - 1].getY() << "," << "'ro'" << "," << "color=" << colorTable(i) << ")" << "\n" << endl;
			a << "plt.plot(" << graph[i]->getNormDoubleAttr(0) << "," << graph[i]->getNormDoubleAttr(1) << "," << "'ro'" << ")" << "\n" << endl;
	}


	a << "plt.show()\n";
	a.close();

	

}

void Utils::ShowSolution(ShortSolution * solution)
{
	fstream a;
	a.open(fileName, fstream::out);
	int size = 14;
	string corAtual;
	string corPreenchimento;


	a << "import matplotlib.pyplot as plt\n\n";

	a << "plt.figure(figsize=(10,10))\n";

	vector <double> costClusters;
	vector <vector<int>> clusters = solution->getClusters();
	vector <Object*> graph = *solution->getObjects();
	costClusters.assign(clusters.size(), 0);


	for (size_t i = 0; i < clusters.size(); i++) {
		for (size_t j = 0; j < clusters[i].size(); j++) {
			a << "plt.plot(" << graph[clusters[i][j] - 1]->getNormDoubleAttr(0) << "," << graph[clusters[i][j] - 1]->getNormDoubleAttr(1) << "," << "'o'" << "," << "color='" << colorTable(i) << "')" << "\n" << endl;
		}
	}

	a << "plt.show()\n";
	a.close();




}

void Utils::ShowSolution(ShortSolution * solution,string fileName)
{
	fstream a;
	a.open(fileName, fstream::out);
	int size = 14;
	string corAtual;
	string corPreenchimento;
	

	a << "import matplotlib.pyplot as plt\n\n";

	a << "plt.figure(figsize=(10,10))\n";

	vector <double> costClusters;
	vector <vector<int>> clusters = solution->getClusters();
	vector <mean> *centers = solution->means;
	vector <Object*> graph = *solution->getObjects();
	costClusters.assign(clusters.size(), 0);


	for (size_t i = 0; i < clusters.size(); i++) {
		for (size_t j = 0; j < clusters[i].size(); j++) {
			a << "plt.plot(" << graph[clusters[i][j] - 1]->getNormDoubleAttr(0) << "," << graph[clusters[i][j] - 1]->getNormDoubleAttr(1) << "," << "'ro'" << "," << "color='" << colorTable(i) << "')" << "\n" << endl;
		}
	}

	for (size_t i = 0; i < centers->size(); i++) {
//		a << "plt.plot(" << centers->at(i).x << "," << centers->at(i).y  << "," << "'*'" << ",markersize=15," << "color='" << colorTable(0) << "')" << "\n" << endl;
	}


	a << "plt.show()\n";
	a.close();




}

void Utils::printEdges(ShortSolution * solution)
{
	fstream a;
	a.open("edges.py", fstream::out);
	int size = 14;
	string corAtual;
	string corPreenchimento;




	a << "import matplotlib.pyplot as plt\n\n";

	a << "plt.figure(figsize=(30,30))\n";

	vector <double> costClusters;
	vector <vector<int>> clusters = solution->getClusters();
	vector <Object*> graph = *solution->getObjects();
	vector <Edge> edges = solution->getEdges();

	string color;

	system("cls");

	// plt.plot([0,0.264789], [0.000796495,0.467606], 'go-', label='line 1', linewidth=1)
	for (size_t i = 0; i < edges.size(); i++) {
		//cout << "plt.plot(" << graph[clusters[i][j] - 1].getX() << "," << graph[clusters[i][j] - 1].getY() << "," << "'ro'" << "," << "color=" << colorTable(i) << ")" << "\n" << endl;
		
		a << "plt.plot([" << graph[ edges[i].getSrc()-1 ]->getNormDoubleAttr(0) << "," << graph[edges[i].getDest() - 1]->getNormDoubleAttr(0) << "],[" << graph[edges[i].getSrc() - 1]->getNormDoubleAttr(1) << "," << graph[edges[i].getDest() - 1]->getNormDoubleAttr(1) << "], 'go-', linewidth=1" << ")" << "\n" << endl;
	//	a << "plt.plot(" << graph[i]->getNormDoubleAttr(0) << "," << graph[i]->getNormDoubleAttr(1) << "," << "'ro'" << "," << "color='" << colorTable(0) << "')" << "\n" << endl;
	}

	for (size_t i = 0; i < graph.size(); i++) {
		a << "plt.plot(" << graph[i]->getNormDoubleAttr(0) << "," << graph[i]->getNormDoubleAttr(1) << "," << "'ro'" << "," << "color='" << colorTable(0) << "')" << "\n" << endl;

	}
	
	a << "plt.show()\n";
	a.close();



}
