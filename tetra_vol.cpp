#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
using namespace std;

typedef struct point{
	double x;
	double y;
	double z;
} point_t;

typedef struct tetrahedron{
	double AB;
	double AC;
	double AD;
	double BC;
	double BD;
	double CD;
	double vol;
} tetra_t;

typedef struct tetra_desc{
	int a;
	int b;
	int c;
	int d;
}tetra_d;

double edge_len(point_t *p1, point_t *p2) {
	double xx, yy, zz;
	double len;

	xx = (p1->x - p2->x);
	yy = (p1->y - p2->y);
	zz = (p1->z - p2->z);

	len = sqrt(xx*xx + yy*yy + zz*zz);

	//debug
	cout << "len:" << len << endl;
	return len;
}

double vol_tetra(tetra_t *t) {
	double a1, a2, a3, a4, a5, a6; 
	double sq_vol_144, vol;

	a1 = t->AB * t->AB;
	a2 = t->AC * t->AC;
	a3 = t->AD * t->AD;
	a4 = t->BC * t->BC;
	a5 = t->BD * t->BD;
	a6 = t->CD * t->CD;

	sq_vol_144 =  a1*a5*(a2 + a3 + a4 + a6 - a1 - a5) +
                      a2*a6*(a1 + a3 + a4 + a5 - a2 - a6) +
                      a3*a4*(a1 + a2 + a5 + a6 - a3 - a4) -
		      a1*a2*a4 - a2*a3*a5 - a1*a3*a6 - a4*a5*a6; 

	vol = sqrt(sq_vol_144 / 144.0);

	//debug
	cout << "vol:" << vol<< endl;

	return vol;
}

vector<point_t> points;
vector<tetra_d> tetra_descs;
vector<tetra_t> tetras;

void read_points(string s) {
	string hline;
	string line;
	int dummy;
	double x, y, z;

	ifstream input(s.c_str()); 
	getline(input, hline);

	while (input && getline(input, line )) {
		istringstream iss (line);
		if (iss >> dummy >> x >> y >> z) {
			point_t p;
			p.x = x;
			p.y = y;
			p.z = z;

			//debug
			cout << "p.x :" << x <<" p.y :" << y << " p.z :" << z <<endl;
			points.push_back(p);
		}
	}
}

void read_tetras(string s) {
	string hline;
	string line;
	int dummy;
	double a, b, c, d;

	ifstream input(s.c_str()); 
	getline(input, hline);

	while (input && getline(input, line )) {
		istringstream iss (line);
		if (iss >> dummy >> a >> b >> c >> d) {
			tetra_d t;
			t.a = a;
			t.b = b;
			t.c = c;
			t.d = d;

			//debug
			cout << "t.a :" << a <<" t.b :" << b << " t.c :" << c << " t.d :" << d <<endl;
			tetra_descs.push_back(t);
		}
	}
}

void convert_desc_to_tetra(void) {
	int i, size;
	double vol;
	size = tetra_descs.size();

	for (i = 0; i < size; i++) {
		tetra_t t;
		point_t *A, *B, *C, *D;

		A = &points[tetra_descs[i].a];
		B = &points[tetra_descs[i].b];
		C = &points[tetra_descs[i].c];
		D = &points[tetra_descs[i].d];

		t.AB = edge_len(A, B);
		t.AC = edge_len(A, C);
		t.AD = edge_len(A, D);
		t.BC = edge_len(B, C);
		t.BD = edge_len(B, D);
		t.CD = edge_len(C, D);

		t.vol = vol_tetra(&t);

		tetras.push_back(t);
	}
}

int main(){
	int i, size;

	cout.precision(20);

	read_points("solution.node");
	read_tetras("solution.ele");
	convert_desc_to_tetra();

	size = tetras.size();
	for (i = 0; i < size;i++) {
		cout << "vol of tetrahedron " << i << " is: "<<tetras[i].vol<<endl;
	}

	return 0;
}
