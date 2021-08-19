#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <map>
#include <iterator>
#include <vector>
using namespace std;

class Edge {
public:
  string p1;
  string p2;
  int weight;
  Edge(string n1, string n2, int w);
  bool operator< (const Edge &other) const {
        return weight < other.weight;
    }
};

class set {
public:
  int p;
  int rank;
};
  

Edge::Edge(string n1, string n2, int w) {
  p1 = n1;
  p2 = n2;
  weight = w;
}

int find(set s[], int i) {
  if (s[i].p != i) {
    s[i].p = find(s, s[i].p);
  }
  return s[i].p;
}

void onion(set s[], int x, int y) {
  int xroot = find(s, x);
  int yroot = find(s, y);

  if (s[xroot].rank < s[yroot].rank) {
    s[xroot].p = yroot;
  }
  else if (s[xroot].rank > s[yroot].rank) {
    s[yroot].p = xroot;
  }
  else {
    s[xroot].p = yroot;
    s[yroot].rank++;
  }
}

int main() {
  int J, C;
  map <string, string> names;
  map <string, string> depends;
  map <string, int> IDs;
  int leftVertices = 0;
  int rightVertices = 0;
  int id = 0;
  cin >> J >> C;
  string currentswitch;
  for (int i = 0; i < J; i++) {
    string name, type;
    cin >> name >> type;
    if (type == "breaker" || type == "box" || type == "outlet") {
      leftVertices++;
    }
    else if (type == "switch" || type == "light") {
      rightVertices++;
    }
    if (type == "switch") {
      currentswitch = name;
    }
    IDs.insert(pair<string, int>(name, id));
    id++;
    names.insert(pair<string, string>(name, type));
    if (type == "light") {
      //cout << "current switch is: " << currentswitch << endl;
      depends.insert(pair<string, string>(name, currentswitch));
    }
  }
  /*
  map<string, string>::iterator itr1; 
  map<string, string>::iterator itr2;
  map<string, int>::iterator itr3;
  cout << "names" << endl;
  for (itr1 = names.begin(); itr1 != names.end(); ++itr1) {
    cout << itr1->first << itr1->second << endl;
  }
  cout << "dependencies" << endl;
  for (itr2 = depends.begin(); itr2 != depends.end(); ++itr2) {
    cout << itr2->first << itr2->second << endl;
  }
  cout << "IDs" << endl;
  for (itr3 = IDs.begin(); itr3 != IDs.end(); ++itr3) {
    cout << itr3->first << itr3->second << endl;
  }
  */
 
  vector<Edge> valid;
  vector<Edge> left;
  vector<Edge> mid;
  vector<Edge> right;

  for (int q = 0; q < C; q++) {
    string src, dest;
    int w;
    cin >> src >> dest >> w;
    if (names.at(src) == "switch" && names.at(dest) == "switch") {
    }
    else if (names.at(src) == "breaker" && names.at(dest) == "light") {
    }
    else if (names.at(src) == "light" && names.at(dest) == "breaker") {
    }
    else if (names.at(src) == "box" && names.at(dest) == "light") {
    }
    else if (names.at(src) == "light" && names.at(dest) == "box") {
    }
    else if (names.at(src) == "outlet" && names.at(dest) == "light") {
    }
    else if (names.at(src) == "light" && names.at(dest) == "outlet") {
    }
    else if (names.at(src) == "light" && names.at(dest) == "light") {
      if (depends.at(src) == depends.at(dest)) {
	valid.push_back(Edge(src, dest, w));
	right.push_back(Edge(src, dest, w));
      }
    }
    else if (names.at(src) == "light" && names.at(dest) == "switch") {
      if (depends.at(src) == dest) {
	valid.push_back(Edge(src, dest, w));
	right.push_back(Edge(src, dest, w));
      }
    }
    else if (names.at(src) == "switch" && names.at(dest) == "light") {
      if (src == depends.at(dest)) {
	valid.push_back(Edge(src, dest, w));
	right.push_back(Edge(src, dest, w));
      }
    }
    else {
      valid.push_back(Edge(src, dest, w));
      if ((names.at(src) == "breaker" || names.at(src) == "box" || names.at(src) == "outlet") && (names.at(dest) == "breaker" || names.at(dest) == "box" || names.at(dest) == "outlet")) {
	left.push_back(Edge(src, dest, w));
      }
      else {
	mid.push_back(Edge(src, dest, w));
      }
    }
  }
  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());
  std::sort(mid.begin(), mid.end());
  /*
  cout << "printing valid" << endl;
  for (int x = 0; x < valid.size(); ++x) {
    cout << valid[x].p1 << " " << valid[x].p2 << " "<< valid[x].weight << endl;
  } 
  
  cout << "printing left" << endl;
  for (int x = 0; x < left.size(); ++x) {
    cout << left[x].p1 << " " << left[x].p2 << " "<< left[x].weight << endl;
  }

  cout << "printing right" << endl;
  for (int x = 0; x < right.size(); ++x) {
    cout << right[x].p1 << " " << right[x].p2 << " "<< right[x].weight << endl;
  }
  cout << "printing mid" << endl;
  for (int x = 0; x < mid.size(); ++x) {
    cout << mid[x].p1 << " " << mid[x].p2 << " "<< mid[x].weight << endl;
  }
    
  cout << "left vertices: " << leftVertices << endl;
  cout << "right vertices: " << rightVertices << endl;
  cout << "removing: " << mid[0].p1 << " " << mid[0].p2 << " "<< mid[0].weight << endl;
  mid.erase(mid.begin());
  for (int x = 0; x < mid.size(); ++x) {
    cout << mid[x].p1 << " " << mid[x].p2 << " "<< mid[x].weight << endl;
  } 
  */
  

  int leftEdgesAccepted = 0;

  int rightEdgesAccepted = 0;
  int leftResult = 0;
  int rightResult = 0;
  set* s = new set[(J*sizeof(s))];

  for (int o = 0; o < J; ++o) {
    s[o].p = o;
    s[o].rank = 0;
  }

  while (leftEdgesAccepted < leftVertices - 1 && left.empty() == false) {
    Edge e = left[0];
    left.erase(left.begin());
    int uset = find(s, IDs.at(e.p1));
    int vset = find(s, IDs.at(e.p2));
    //cout << "uset: " << uset << endl;
    //cout << "vset: " << vset << endl;
    if (uset != vset) {
      /*
      cout << "source: " << e.p1 << " dest: " << e.p2 << " weight: " << e.weight << endl;
      for (int n = 0; n < J; ++n) {
	cout << s[n].p << " " << s[n].rank << endl;
      }
      */
      leftEdgesAccepted++;
      onion(s, uset, vset);
      /*
      cout << "source id: " << IDs.at(e.p1) << endl;
      cout << "dest id: " << IDs.at(e.p2) << endl;
      for (int n = 0; n < J; ++n) {
	cout << s[n].p << " " << s[n].rank << endl;
      }
      */
      leftResult += e.weight;
    }
  }
  while (rightEdgesAccepted < rightVertices - 1 && right.empty() == false) {
    //cout << "hi" << endl;
    Edge e = right[0];
    right.erase(right.begin());
    int uset = find(s, IDs.at(e.p1));
    int vset = find(s, IDs.at(e.p2));
    if (uset != vset) {
      rightEdgesAccepted++;
      onion(s, uset, vset);
      //cout << "weight: " << e.weight << endl;
      rightResult += e.weight;
    }
  }
  int EdgesAccepted = leftEdgesAccepted + rightEdgesAccepted;
  int result = leftResult + rightResult;
  /*
  cout << "leftResult: " << leftResult << endl;
  cout << "rightResult: " << rightResult << endl;
  cout << "left accepted: " << leftEdgesAccepted << endl;
  cout << "right accepted: " << rightEdgesAccepted << endl;
  cout << "total accepted: " << EdgesAccepted << endl;
  */

  while (EdgesAccepted < J - 1 && mid.empty() == false) {
    Edge e = mid[0];
    mid.erase(mid.begin());
    int uset = find(s, IDs.at(e.p1));
    int vset = find(s, IDs.at(e.p2));
    if (uset != vset) {
      EdgesAccepted++;
      onion(s, uset, vset);
      //cout << "weight: " << e.weight << endl;
      result += e.weight;
    }
  }

  cout << result << endl;
}
