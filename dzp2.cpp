#include <set>
#include <vector>
#include <iterator>
#include <stack>
#include <algorithm>
#include <queue>


#include <iostream>
using namespace std;

#define INFINITE 999

struct Field
{
	int weight;
	int edge;
	Field(int e, int w) :weight(w), edge(e) {};
	Field() = default;
};
Field** allocMat(int n, int k)
{
	Field** m;
	m = new Field * [n];
	for (int i = 0; i < n; i++)
	{
		m[i] = new Field[n];
		for (int j = 0; j < n; j++)
		{
			m[i][j].weight = k;
			m[i][j].edge = 0;
		}
	}
	return m;
}
struct Graph
{
	int nodes;
	Field** matrix;
	vector<int> d1;
	int mincena;
	Graph(int n, int k)
	{
		nodes = n;
		matrix = allocMat(n, k);
	}
};
struct Elem
{
	Field* field;
	Elem* next;
	Elem(Field* f, Elem* sl = nullptr) :field(f), next(sl) {};
	Elem() = default;
};

void delE(Graph* g, int i, int j)
{
	if (g->matrix[i][j].edge == 0)cout << "grana ne postoji" << endl;
	else
	{
		g->matrix[i][j].edge = 0;
		g->matrix[j][i].edge = 0;
	}
}
void addN(Graph* g)
{
	int k = g->nodes + 1;
	Field** newmat = allocMat(k, INFINITE);
	for (int i = 0; i < g->nodes; i++)
	{
		for (int j = 0; j < g->nodes; j++)
		{
			newmat[i][j].edge = g->matrix[i][j].edge;
		}
	}
	g->nodes++;
	g->matrix = newmat;
}
void addE(Graph* g, int i, int j, int w)
{
	if (i > g->nodes - 1 || j > g->nodes - 1)cout << "ne postoje uneseni cvorovi" << endl;
	else
	{
		g->matrix[i][j].edge = 1;
		g->matrix[j][i].edge = 1;
		g->matrix[i][j].weight = w;
		g->matrix[j][i].weight = w;
	}
}
int getindexI(Graph* g, int n)
{
	for (int i = 0; i < g->nodes; i++)
	{
		for (int j = 0; j < g->nodes; j++)
		{
			if (g->matrix[i][j].weight == n)return i;
		}
	}
}
int getIndexJ(Graph* g, int n)
{
	for (int i = 0; i < g->nodes; i++)
	{
		for (int j = 0; j < g->nodes; j++)
		{
			if (g->matrix[i][j].weight == n)return j;
		}
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
		Field** mat1 = allocMat(n, 0);
		for (int i = 0; i < k; i++)//gore levo
		{
			for (int j = 0; j < k; j++)
			{
				mat1[i][j].edge = g->matrix[i][j].edge;
			}
		}
		for (int i = 0; i < g->nodes - k; i++)//gore desno
		{
			for (int j = k + 1; j < g->nodes; j++)
			{
				mat1[i][j - 1].edge = g->matrix[i][j].edge;
			}
		}
		for (int i = k + 1; i < g->nodes; i++)//dole levo
		{
			for (int j = 0; j < k; j++)
			{
				mat1[i - 1][j].edge = g->matrix[i][j].edge;
			}
		}
		for (int i = k + 1; i < g->nodes; i++)//dole desno
		{
			for (int j = k + 1; j < g->nodes; j++)
			{
				mat1[i - 1][j - 1].edge = g->matrix[i][j].edge;
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
			cout << " " << g->matrix[i][j].edge;
			cout << " | " << g->matrix[i][j].weight;
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
set<int>Unija(set<int> s1, set<int> s2)
{
	set<int> s;
	set_union(s1.begin(), s1.end(),
		s2.begin(), s2.end(),
		inserter(s, s.begin()));
	return set<int>(s);
}
set<int>getpresek(set<int> v, set<int> s)
{
	set<int> result;
	set_difference(v.begin(), v.end(), s.begin(), s.end(),
		inserter(result, result.end()));
	return result;
}
int minKruskal(Graph* g)
{
	set<int> s;
	set<int>* sets = new set<int>[g->nodes];
	for (int i = 0; i < g->nodes; i++)
	{
		sets[i].insert(i);
	}
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < g->nodes; i++)
	{
		for (int j = 0; j < g->nodes; j++)
		{
			if (i < j && g->matrix[i][j].edge == 1)pq.push(g->matrix[i][j].weight);
		}
	}
	int num = 0;
	int min = 0;
	while (num < g->nodes - 1)
	{
		int x = pq.top();
		int i = getindexI(g, x);
		int j = getIndexJ(g, x);
		bool iii = false;
		bool jjj = false;
		int m = 0;
		while (!(iii = sets[m].find(i) != sets[m].end()))
		{
			m++;
		}
		int n = 0;
		while (!(jjj = sets[n].find(j) != sets[n].end()))
		{
			n++;
		}
		if (m != n && i != j)
		{
			sets[m] = Unija(sets[m], sets[n]);
			sets[n].erase(j);
			num++;
			min += x;
		}
		pq.pop();
	}
	return min;
}
void addE(Graph* g, int i, int j, int w, string izg)
{
	if (izg == "izgradjen")addE(g, i, j, w);
	else if (izg == "neizgradjen")
	{
		g->matrix[i][j].edge = 2;
		g->matrix[j][i].edge = 2;
		g->matrix[i][j].weight = w;
		g->matrix[j][i].weight = w;
	}

}
Elem* sortedInsert(Elem* first,int e,int w)
{
	Elem* tek = first, * preth = nullptr;
	while (tek && tek->field->weight < w)
	{
		preth = tek;
		tek = tek->next;
	}
	Field* f = new Field(e, w);
	Elem* novi = new Elem(f, tek);
	if (!preth)first = novi;
	else preth->next = novi;
	return first;
}
int findNum(Elem* first)
{
	Elem* curr = first;
	int k = 0;
	while (curr!=nullptr)
	{
		k++;
		curr = curr->next;
	}
	return k;
}
void Dijkstra(Graph* g, int x)
{
	Elem** first;
	first = new Elem*[g->nodes];
	set<int> s;
	s.insert(x);
	set<int> v;
	set<int>* sets = new set<int>[g->nodes];
	for (int i = 0; i < g->nodes; i++)
	{
		v.insert(i);
	}
	v.erase(x);
	set<int> presek = getpresek(v, s);
	priority_queue<int, vector<int>, greater<int>> pq;
	vector<int> d;
	int index;
	d.resize(g->nodes);
	for (int i = 0; i < x; i++)
	{
		pq.push(g->matrix[x][i].weight);
		d.insert(d.begin() + i, g->matrix[x][i].weight);
		if (g->matrix[x][i].weight != INFINITE)
		{
			sets[i].insert(x);
			if (g->matrix[x][i].edge == 2)
			{
				Field* f = new Field(x, 1);
				first[i] = new Elem(f);
			}
			else
			{
				Field* f = new Field(x, 0);
				first[i] = new Elem(f);
			}
		}
		else
		{
			Field* f = new Field(0, INFINITE);
			first[i] = new Elem(f);
		}
	}
	d.insert(d.begin() + x, INFINITE);
	for (int i = x + 1; i < g->nodes; i++)
	{
		pq.push(g->matrix[x][i].weight);
		d.insert(d.begin() + i, g->matrix[x][i].weight);
		if (g->matrix[x][i].weight != INFINITE)
		{
			if (g->matrix[x][i].edge == 2)
			{
				Field* f = new Field(x, 1);
				first[i] = new Elem(f);
			}
			else 
			{
				Field* f = new Field(x, 0);
				first[i] = new Elem(f);
			}
			sets[i].insert(x);

		}
		else
		{
			Field* f = new Field(0, INFINITE);
			first[i] = new Elem(f);
		}
	}
	for (int k = 0; k < g->nodes - 1; k++)
	{
		int d1 = pq.top();
		pq.pop();
		auto it = find(d.begin(), d.end(), d1);
		if (it != d.end())
			index = it - d.begin();
		if (presek.find(index) != presek.end())
		{
			if (d1 == INFINITE)break;
			s.insert(index);
			presek = getpresek(v, s);
			for (int j : presek)
			{
				if (d[index] + g->matrix[index][j].weight <= d[j])
				{
					if (d[index] + g->matrix[index][j].weight < d[j])
					{ 
						cout << "brise se lista za" << j << endl;
						Elem* c = first[j];
						while (c)
						{
							Elem* old = c;
							c = c->next;
							delete old;
						}
						first[j] = nullptr;
						int w=0;
						int r = g->matrix[x][index].edge;
						if (g->matrix[index][j].edge == 2)
						{
							w = r;
						}
						else if (g->matrix[index][j].edge == 1 && r == 2)
							w = 1;
						first[j]=sortedInsert(first[j], index, w);
					}
					else
					{
						Elem* curr = first[index];
						while (curr)
						{
							int w;
							if (g->matrix[index][j].edge == 2)
							{
								w = curr->field->weight + 1;
							}
							else if (g->matrix[index][j].edge == 1)
								w = curr->field->weight;
							first[j]=sortedInsert(first[j], index, w);
							curr = curr->next;
						}
					}
					d.at(j) = d[index] + g->matrix[index][j].weight;
					sets[j].erase(x);
					sets[j].insert(index);
					pq.push(d[index] + g->matrix[index][j].weight);
				}
			}
		}
	}
	g->d1 = d;
	cout << endl;
	cout << "\n putevi : "<<endl;
	for (int i = 0; i < g->nodes; i++)
	{
		Elem* curr = first[i];
		if (i != x)
		{
			cout<<"\nnajmanja udaljenost od cvora "<< i << " je " << d[i] << endl;
			cout << endl;
			while (curr != nullptr)
			{
				stack<int> stek;
				int t = curr->field->edge;
				stek.push(i);
				int y=0;
				if(t!=x)y = findNum(first[t]);
				int m = sets[t].size();
				int raz = y - m;
				m--;
				int a = t;
				while (t != x)
				{
					stek.push(t);
					Elem* c = first[t];
					while (raz != 0)
					{
						c = c->next;
						raz--;
					}
					t = c->field->edge;
					if (sets[a].find(t) != sets[a].end())
						sets[a].erase(t);
					
				}
				cout << x << " -> ";
				while (!stek.empty())
				{
					cout << " " << stek.top() << " ->";
					stek.pop();
				}
				cout << " broj neizgradjenih puteva je " << curr->field->weight << endl;
				curr = curr->next;
			}
		}
	}
};

int main()
{
	cout << "1.Stvaranje grafa" << endl;
	cout << "Unesite broj cvorova" << endl;
	int cvor;
	cin >> cvor;
	Graph g(cvor, INFINITE);
	cout << "2.Dodavanje cvora" << endl;
	cout << "3.Brisanje cvora" << endl;
	cout << "4.Dodavanje grane" << endl;
	cout << "5.Brisanje grane" << endl;
	cout << "6.Ispis matrice" << endl;
	cout << "7.Brisanje matrice" << endl;
	cout << "8.Izlazak iz programa" << endl;
	cout << "9.Minimalna cena je?" << endl;
	cout << "10.Pronalazak puteva " << endl;


	addE(&g, 0, 1, 5, "izgradjen");
	addE(&g, 0, 4, 8, "izgradjen");
	addE(&g, 1, 3, 5, "izgradjen");
	addE(&g, 3, 4, 3, "izgradjen");
	addE(&g, 0, 2, 2, "neizgradjen");
	addE(&g, 0, 3, 11, "neizgradjen");
	addE(&g, 2, 4, 5, "neizgradjen");
	addE(&g, 0, 5, 3, "izgradjen");
	addE(&g, 0, 6, 4, "izgradjen");
	addE(&g, 5, 3, 7, "neizgradjen");
	addE(&g, 6, 4, 3, "neizgradjen");
	Dijkstra(&g, 0);



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
		out: 
			cout << "Koji cvor zelite da obrisete? " << endl;
			int cv;
			cin >> cv;
			delN(&g, cv);
			break;
		case 4:
			cout << "Gde zelite da dodate granu? " << endl;
			int i1, j1;
			cin >> i1 >> j1;
			cout << " da li je put izgradjen? " << endl;
			bool izgr;
			cin >> izgr;
			cout << "unesite tezinu" << endl;
			int wh;
			cin >> wh;
			if (izgr)
			{
				addE(&g, i1, j1, wh,"izgradjen");
			}
			else addE(&g, i1, j1, wh, "neizgradjen");
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
		case 9:
			cout << "minimalna cena je : " << minKruskal(&g) << endl;
			break;
		case 10:
			cout << "unesite indeks pocetnog cvora" << endl;
			int x;
			cin >> x;
			Dijkstra(&g, x);
			break;

		}
	}
}
