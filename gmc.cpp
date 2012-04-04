#include<set>
#include<map>
#include<vector>
#include<utility>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cstdlib>

using namespace std;
typedef pair<int,int> edge;
typedef pair<edge,int> edgef;
typedef map<pair<int,int>,int> edgefMap;
typedef edgefMap::iterator edgefMapItr;

void printEdge(edge &e) {
	cout << "(" << e.first << "," << e.second << ")";
}

void printEdgenl(edge &e) {
	cout << "\n(" << e.first << "," << e.second << ")\n";
}

void printEdgeF(edgef &ef) {
	cout << "(" << ef.second << ")";
	printEdge(ef.first);
}

void printAllEdgeF(edgefMap &Edges) {
	cout << endl << "Number of edges in the map: " << Edges.size() << endl;
	for(edgefMapItr EdgesItr = Edges.begin(); EdgesItr!=Edges.end(); EdgesItr++) {
		edgef ef=*EdgesItr;
		printEdgeF(ef);
	}
	cout << endl;
}

void makeEdge(edge &e, int i, int j, int n=1) {
	if (i > j) {
		int t = i;
		i = j;
		j = t;
	}
	e.first = i;
	e.second = j;
}

int main1 (void) {


	edgefMap Edges;
	ifstream file("KargerAdjList.txt");
	//ifstream file("3.txt");
	string line;
	int vi,vj;
	int numberofVertices = 0;
	set<int> empty;
	vector<pair<int, set<int> > >  Adj(40, pair<int, set<int> >(0,empty));
	
	
	while(getline(file,line)) {
		numberofVertices++; 
		stringstream sline(line);
		sline >> vi;			
		while (sline >> vj){
			edge eij;			
			makeEdge(eij,vi,vj);
			Edges.insert(edgef(eij,1));
		}
	}
	
	int removedVertices = 0;	
	edgefMapItr EdgesItr;
	set<int> vertices;
	//cout << "====================================" << numberofVertices;
	//numberofVertices -= 2;
	for(int i=1; i<=numberofVertices-2; i++) { // while more than 2 vertices remaining
			vertices.clear();
		for( edgefMapItr e= Edges.begin(); e!=Edges.end(); e++) {
			vertices.insert((*e).first.first);
			vertices.insert((*e).first.second);
		}
		//printAllEdgeF(Edges);
		//cout << "Number of vertices remaining: " << vertices.size();
		//cout << "Running for the " << i << "th time\n";
			//srand(time(NULL));
		int nth = 1+ rand()%(Edges.size()); // get randome between 1 to x (inclusive 1,x), where x is number of edges remaining
		int ith = 1;
		edge edge2Delete;
		// remove nth edge  
		for(EdgesItr = Edges.begin(),ith=1; EdgesItr!=Edges.end() && ith != nth; EdgesItr++,ith++);
		//cout <<"Deleting : " << '(' << nth << "): "  ;
		edge2Delete = (*EdgesItr).first;
		//printEdgenl(edge2Delete);
		if ( (*EdgesItr).second == 1) {
			Edges.erase(EdgesItr);
		}
		else {
			(*EdgesItr).second -=1;
		}
		removedVertices++;					

		for(EdgesItr = Edges.begin(); EdgesItr!=Edges.end(); EdgesItr++) {			
			edge currEdge = (*EdgesItr).first;
			vi = 0; vj = 0;
			int n =1;
			if ((edge2Delete.second == currEdge.first)){
				//cout <<"Compressing: "; printEdgenl(currEdge);
				n = (*EdgesItr).second;
				Edges.erase(currEdge);

				EdgesItr = Edges.begin();
			
				if(edge2Delete.first != currEdge.second) {				
					vi = edge2Delete.first;
					vj = currEdge.second;			
				}
			}
			else if((edge2Delete.second == currEdge.second)){
				//cout <<"Compressing: ";printEdgenl(currEdge);
				Edges.erase(currEdge);
				n = (*EdgesItr).second;
				Edges.erase(currEdge);
				EdgesItr = Edges.begin();

				if(edge2Delete.first != currEdge.first) {
					vi = edge2Delete.first;
					vj = currEdge.first;			
				}
			}
			if (vi !=0 && vj!=0) {
				int k =1;
				if (n!=0) { k=n; }
				edge eij;			
				makeEdge(eij,vi,vj);
				edgefMapItr EdgesItrFind = Edges.find(eij);
				if (EdgesItrFind == Edges.end()) {
					//cout << "Inserting "; printEdgenl(eij);
					Edges.insert(edgef(eij,n));
									EdgesItr = Edges.begin();
				}else {
					//cout << "Incrementing +1:"; printEdgenl(eij);
					(*EdgesItrFind).second = (*EdgesItrFind).second + (n);
				}
			}			
		}		
	}
	//printAllEdgeF(Edges);	
	edgefMapItr e = Edges.begin();
	return (*e).second;	
}


int main(void) {
	int i = 40;
	vector<int> v;
	//while (i--) {
	//srand(time(NULL));
		//v.push_back(main1());
	//}
	srand(time(NULL));
	//cout << main1() << endl;	
	int runs = i *i *6;
	for (int j=0; j<runs; j++ ){			
		v.push_back(main1());		
	}
	for (int j=0; j<v.size(); j++ ){			
		cout << v.at(j) << "\t";		
	}
	int min = 1000000;
	for ( int k=0; k<v.size(); k++) {
		if ( min > v.at(k) ) {
			min = v.at(k);
		}
	}
	cout << min << endl;
	return 0;
}
