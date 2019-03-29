#include "../Headers/MasterProblem.h"
MasterProblem::MasterProblem(int id, int solver, Environment *env)
{
	this->id = id;
	this->solver = solver;
	this->env = env;
	if (env->getSolver() == 1)
		this->model = env->getMdlCplex();
	else if (env->getSolver() == -1)
		this->model = env->getMdlGRB();


}

MasterProblem::MasterProblem() {

}

void MasterProblem::buildMasterProblem() {

	int numClusterBound = 2;
	numClusters = solutions[0]->getNumClusters();
	int numObjs = solutions[0]->getNumObjs();
	const int numAllClusters = solutions.size() * numClusters;

	
	bestSolution = new ShortSolution(numObjs, numClusters);

	vector <int> exprs;
	exprs.assign(numObjs, 0);

	vector <double> costClusters;


	for (int j = 0; j < numObjs; j++) {
		model->addConstraint(1, "=", "Obj" + std::to_string(j), 1);
	}
	int indCnstNumClusters = -1;

	//criar param limite num clusters (0=nenhum,1=minimo,2=exato,3=maximo)
	string op = (numClusterBound == 1 ? "<=" : (numClusterBound == 2 ? "=" : ">="));
       if (param.fixedNumClusters) {
		model->addConstraint(numClusters, op, "numClusters", numClusters);
		indCnstNumClusters = model->getNumConstraints()-1;
	}

	double maxDist = numeric_limits<double>::min();
	double maxDisp= numeric_limits<double>::min();
	const int numConstr = model->getNumConstraints();
	


	model->addVar(100, 1, "maxDisp", "double", 0);
	int varMaxDisp = model->getNumVars() - 1;
	model->addVar(100, 1, "maxDist", "double",0);
	int varMaxDist = model->getNumVars() - 1;
	vector <double> coeffs;
	int idObj;


	for (int i = 0; i < solutions.size(); i++) {

		//cout << i << endl;
		vector <double> costs = solutions[i]->getCostClusters();
		vector <vector<int>> clusters = solutions[i]->getClusters();
		vector <double> dispersions = solutions[i]->dispersions;
		vector <double> extDists = solutions[i]->externalDists;



		for (int j = 0; j < numClusters; j++) {

			//model->addVar(1, costs[j], "cluster" + std::to_string(i + j), "int", 0);
			model->addVar(1, 0, "cluster" + std::to_string(i + j), "int", 0);
			int indVar = model->getNumVars() - 1;
			model->addConstraint(dispersions[j], varMaxDisp, indVar, "<=", "cluster" + std::to_string(i + j) + "maxDisp", 0);
			model->addConstraint(1 / extDists[j], varMaxDist, indVar, "<=", "cluster" + std::to_string(i + j) + "maxDist", 0);


			for (int k = 0; k < clusters[j].size(); k++) {
				int indCnstr = clusters[j][k] - 1;
				model->setConstraintCoeffs(1, indCnstr, indVar);
			}

			
			if (param.fixedNumClusters)
				model->setConstraintCoeffs(1, indCnstNumClusters, indVar);
		}


	}

	model->buildModel("minimize",varMaxDisp,varMaxDist);

	vector <double> x = model->getVarsInSol();


	
	int solution;
	int clusterSol;

	for (int a = 0; a <x.size(); a++) {
		solution = (floor)(x[a] / numClusters);
		clusterSol = x[a] - ((solution)* numClusters);
		vector <vector<int>> clusters = solutions[solution]->getClusters();
		clustersExactMethod.push_back(clusters[clusterSol]);
	}




	/*for (auto s : solutions) {
		delete s;
	}*/





}

void MasterProblem::setEnvironment(Environment * env)
{
	this->env = env;
}

void MasterProblem::setSolutions(vector<ShortSolution*> solutions)
{
	this->solutions = solutions;
}

vector<vector<int>> MasterProblem::getClusters()
{
	return  clustersExactMethod;
}

void MasterProblem::setParams(Param p)
{
	this->param = p;
}

MasterProblem::~MasterProblem()
{
}