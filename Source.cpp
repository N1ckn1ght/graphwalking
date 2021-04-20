#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;
typedef unsigned int unt;

const string inf = "./input.txt";
const string ouf = "./output.txt";

struct node
{
	unt n;	// node id
	unt d;	// distance
};

vector <vector <unt>> graph;
map <string, unt> nodes;
map <unt, string> names;
vector <bool> used;
queue <node> q;
ofstream out;

void bfs()
{
	while (q.size() != 0)
	{
		node cur = q.front();
		q.pop();
		
		out << names[cur.n] << " " << cur.d << "\n";

		for (unt next : graph[cur.n])
		{
			if (!used[next])
			{
				used[next] = true;
				q.push({ next, cur.d + 1 });
			}
		}
	}
}

bool read(vector <vector <unt>>& g, map <string, unt> toNode, map <unt, string>& toName, string path)
{
	ifstream in(path);

	if (!in.is_open())
	{
		return false;
	}

	cout << "Graph is being read, please be patient, because time complexity is REALLY awful...\n";
	string first, second;
	unt cur_size = 0;
	
	while (in >> first)
	{
		in >> second;
		
		if (nodes.find(first) == nodes.end())
		{
			names[cur_size] = first;
			nodes[first] = cur_size++;
		}
		if (nodes.find(second) == nodes.end())
		{
			names[cur_size] = second;
			nodes[second] = cur_size++;
		}

		g.resize(cur_size);
		g[nodes[first]].push_back(nodes[second]);
		g[nodes[second]].push_back(nodes[first]);
	}
	in.close();

	return true;
}

int main()
{
	bool r = read(graph, nodes, names, inf);
	if (!r)
	{
		cout << "Kernel panic!\nFile " << inf << " does not exist!\n";
		return 0;
	}

	string start;
	cout << "Reading complete, now for which node do you want to calculate distances: ";
	cin >> start;

	if (nodes.find(start) == nodes.end())
	{
		cout << "Kernel panic!\nNode " << start << " does not exist!\n";
		return 0;
	}

	unt ns = nodes[start];
	used.resize(graph.size(), false);
	used[ns] = true;
	q.push({ ns, 0 });
	
	out.open(ouf);
	bfs();
	out.close();
	cout << "Done!\nPlease check " << ouf << " file.\n";
}