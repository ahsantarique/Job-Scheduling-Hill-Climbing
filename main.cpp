#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>


using namespace std;


int **p;

vector<int> generateRandomState(int jobs){
	map<int,bool> taken;
	vector <int> ret;
	for(int i=0;i<jobs;i++){
		int r = rand()%jobs;
		while(taken[r]){
			r = rand()%jobs;
		}
		ret.push_back(r);
		taken[r]=true;
	}
	return ret;
}


vector <int> successorBySwap(vector <int> x){
	int r1 = rand()%(x.size());
	int r2 = rand()%(x.size());

	int temp = x[r1];
	x[r1] = x[r2];
	x[r2] = temp;

	return x;
}

vector <int> successorByInsertion(vector <int > x){
	int r1 = rand()%(x.size());
	int r2 = rand()%(x.size());

	int temp = x[r1];
	x.erase(x.begin()+r1);
	x.insert(x.begin()+r2-1, temp);

	return x;
}

int dp[100][100];

int cost(const vector <int> & x, int i, int j){
	if(dp[i][j]!=-1) return dp[i][j];
	getchar();
	cout << i <<" " <<  j << endl;
	if(x[i]==0 && j==0) return dp[i][j]= p[x[i]][j];
	if(j==0  && x[i]>0) return dp[i][j]= cost(x,i-1,j)+p[x[i]][j];
	if(x[i]==0 && j > 0) return dp[i][j]= cost(x,i,j-1)+p[x[i]][j];
	return dp[i][j]= max(cost(x,i-1,j), cost(x,i,j-1)) + p[x[i]][j];
}

int makespan(vector<int> &x, int n, int m){
	memset(dp,-1,sizeof(dp));
	int ret = cost(x,n-1,m-1);
	cout << ret << endl;
	return ret;
}
vector<int> HillClimb (vector<int> x, int t, int machines){
 	vector <int> current(x);
 	int max_step = 10;
 	int count = 1;
 	for(int i= 0; i < max_step; i++,count++){
 		int j;
 		for(j = 0; j < t; j++){

 			double r = rand()%1000 / 1000;
 			vector<int> neighbor;

 			if(r < 0.5){
 				neighbor =  successorByInsertion(current);
 			}
 			else{
 				neighbor = successorBySwap(current);
 			}
 			if(makespan(neighbor, t, machines) < makespan(current, t, machines)){
 				current = neighbor;
 				break;
 			}
 			getchar();
 		}
 		if(j == t) return current;
 	}
 	return current;
}


int main()
{
	int jobs, machines;
	cin>> jobs >> machines;

	p = new int*[jobs];
	for(int i = 0; i < jobs; i++){
		p[i]=new int[machines];
	}

	for(int i= 0; i < jobs; i++){
		for(int j = 0; j < machines; j++){
			cin >> p[i][j];
			cin >> p[i][j];
		}
	}

	// for(int i=0; i < 10; i++){
	// 	vector<int> x = generateRandomState(jobs);
	// 	x = HillClimb(x, jobs, machines);
	// 	for(int i = 0; i < x.size(); i++){
	// 		cout << x[i]<<" ";
	// 	}
	// 	cout << endl;
	// 	getchar();
	// }

	vector <int> x;
	x.push_back(0);
	x.push_back(1);
	x.push_back(2);
	x.push_back(3);

	makespan(x,jobs,machines);
	return 0;
}