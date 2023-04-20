#include <iostream>
using namespace std;
#include <queue>
#include <stack>

int** allocMat(int n)
{
	int** m;
	m = new int* [n];
	for (int i = 0; i < n; i++)
	{
		m[i] = new int[n];
		for (int j = 0; j < n; j++)m[i][j] = 0;
	}
	return m;
}
struct Graph
{
	int nodes;
	int** matrix;
	Graph(int n)
	{
		nodes = n;
		matrix = allocMat(n);
	}
};

void addE(Graph* g, int i, int j)
{
	if (i > g->nodes - 1 || j > g->nodes - 1)cout<<"ne postoje cvorovi izmedju kojih zelite da dodate granu";
	else
	{
		g->matrix[i][j] = 1;
		g->matrix[j][i] = 1;
	}
}
void delE(Graph* g, int i, int j)
{
	if (g->matrix[i][j] == 0)cout << "grana ne postoji" << endl;
	else
	{
		g->matrix[i][j] = 0;
		g->matrix[j][i] = 0;
	}
}
void addN(Graph* g)
{
	int k = g->nodes + 1;
	int** newmat = allocMat(k);
	for (int i = 0; i < g->nodes; i++)
	{
		for (int j = 0; j < g->nodes; j++)
		{
			newmat[i][j] = g->matrix[i][j];
		}
	}
	g->nodes++;
	g->matrix = newmat;
}
void addE(Graph* g, int i, int j, int w)
{
	if (i > g->nodes - 1 || j > g->nodes - 1)cout << "ne postoje cvorovi izmedju kojih zelite da dodate granu";
	else
	{
		g->matrix[i][j] = w;
		g->matrix[j][i] = w;
	}
}
void delN(Graph* g, int k)
{
	while (1)
	{
		if (k > g->nodes)
		{
			cout << "cvor ne postoji" << endl;
			break;
		}
		int n = g->nodes - 1;
		int** mat1 = allocMat(n);
		for (int i = 0; i < k; i++)//gore levo
		{
			for (int j = 0; j < k; j++)
			{
				mat1[i][j] = g->matrix[i][j];
			}
		}
		for (int i = 0; i < g->nodes - k; i++)//gore desno
		{
			for (int j = k + 1; j < g->nodes; j++)
			{
				mat1[i][j - 1] = g->matrix[i][j];
			}
		}
		for (int i = k + 1; i < g->nodes; i++)//dole levo
		{
			for (int j = 0; j < k; j++)
			{
				mat1[i - 1][j] = g->matrix[i][j];
			}
		}
		for (int i = k + 1; i < g->nodes; i++)//dole desno
		{
			for (int j = k + 1; j < g->nodes; j++)
			{
				mat1[i - 1][j - 1] = g->matrix[i][j];
			}
		}
		g->nodes--;
		g->matrix = mat1;
	}
}
void ispismat(Graph* g)
{
	cout << "\n matrica susednosti:";
	for (int i = 0; i < g->nodes; ++i) {
		cout << "\n";
		for (int j = 0; j < g->nodes; ++j) {
			cout << " [ ";
			cout << " " << g->matrix[i][j];
			cout << " ] ";
		}
	}
}
void dealloc(Graph* g)
{
	for (int i = 0; i < g->nodes; i++)delete[]g->matrix[i];
	delete[] g->matrix;
	g->matrix = nullptr;
}
void bfs(Graph* g, int v)
{
	queue<int> q;
	bool* visit = new bool[g->nodes];
	for (int i = 0; i < g->nodes; i++)
	{
		visit[i] = false;
	}
	visit[v] = true;
	q.push(v);
	cout << v << endl;
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		for (int i = 0; i < g->nodes; i++)
		{
			if (g->matrix[i][v] == 1)
			{
				if (!visit[i])
				{
					visit[i] = true;
					q.push(i);
					cout << i << endl;
				}
			}
		}
	}
}
void dfs(Graph* g, int v)
{
	bool* visit = new bool[g->nodes];
	for (int i = 0; i < g->nodes; i++)visit[i] = false;
	stack<int> s;
	visit[v] = true;
	s.push(v);
	while (!s.empty())
	{
		v = s.top();
		s.pop();
		if (!visit[v])visit[v] = true;
		cout << v << endl;
		for (int i = 0; i < g->nodes; i++)
		{
			if (g->matrix[v][i] == 1)
			{
				if (!visit[i])
				{
					s.push(i);
				}
			}
		}
		/*int j = 0;
		while (visit[j] && j<g->nodes-1)
		{
			j++;
		}*/
		//while (g->matrix[v][j] == 0)j++;
		/*if (!visit[j])
		{
			visit[j] = true;
			s.push(j);
			cout << j << endl;
		}
		int k = 0;
		int t = 0;
		for (int i = 0; i < g->nodes; i++)
		{
			if (g->matrix[v][i] == 1)
			{
				k++;
				if (visit[i])t++;
			}
		}
		if (t == k)s.pop();*/
	}
	
}

int main()
{
	cout << "1.Stvaranje grafa" << endl;
	cout << "Unesite broj cvorova" << endl;
	int cvor;
	cin >> cvor;
	Graph g(cvor);
	cout << "2.Dodavanje cvora" << endl;
	cout << "3.Brisanje cvora" << endl;
	cout << "4.Dodavanje grane" << endl;
	cout << "5.Brisanje grane" << endl;
	cout << "6.Ispis matrice" << endl;
	cout << "7.Brisanje matrice" << endl;
	cout << "8.Izlazak iz programa" << endl;
	addE(&g, 0, 1);
	addE(&g, 1,3);
	addE(&g, 2,0);
	/*addE(&g, 0, 1);
	addE(&g, 0, 2);
	addE(&g, 0, 3);
	addE(&g, 2,5);
	addE(&g, 3,6);
	addE(&g, 4, 1);
	bfs(&g, 0);*/
	dfs(&g, 0);

	while (1)
	{
		cout << " Unesite zeljenu opciju : " << endl;
		int odabir;
		cin >> odabir;
		switch (odabir)
		{

		case 2:
			addN(&g);
			break;
		case 3:
			cout << "Koji cvor zelite da obrisete? " << endl;
			int cv;
			cin >> cv;
			delN(&g, cv);
			break;
		case 4:
			cout << "Gde zelite da dodate granu? " << endl;
			int i1, j1;
			cin >> i1 >> j1;
			cout << "da li zelite da unesete tezinu" << endl;
			bool weig;
			cin >> weig;
			if (weig == 0)
				addE(&g, i1, j1);
			else
			{
				cout << "unesite tezinu" << endl;
				int wh;
				cin >> wh;
				addE(&g, i1, j1, wh);
			}
			break;
		case 5:
			cout << "Koju zelite granu da obrisete? " << endl;
			int i2, j2;
			cin >> i2 >> j2;
			delE(&g, i2, j2);
			break;
		case 6:
			ispismat(&g);
			break;
		case 7:
			dealloc(&g);
			break;
		case 8:
			exit(-1);
			break;

		}
	}
}