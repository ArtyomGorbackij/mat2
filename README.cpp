
#include "stdafx.h"
#include <iostream>
#include <sstream>
using namespace std;
float **mat, **mat1, **c;
void inversiya(float **A, float **c, unsigned int x)

{
	float temp;
	float **E = new float *[x];
	for (unsigned int i = 0; i < x; i++)
	{
		E[i] = new float[x];
	}
	for (unsigned int i = 0; i < x; i++)
	{
		for (unsigned int j = 0; j < x; j++)
		{
			E[i][j] = 0;
			if (i == j)
			{
				E[i][j] = 1;
			}
		}
	}
	for (unsigned int k = 0; k < x; k++)
	{
		temp = A[k][k];
		for (unsigned int j = 0; j < x; j++)
		{
			A[k][j] /= temp;
			E[k][j] /= temp;
		}
		for (unsigned int i = k + 1; i < x; i++)
		{
			temp = A[i][k];
			for (unsigned int j = 0; j < x; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}
	for (int k = x - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = A[i][k];
			for (unsigned int j = 0; j < x; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}
	for (unsigned int i = 0; i < x; i++)
	{
		for (unsigned int j = 0; j < x; j++)
		{
			A[i][j] = E[i][j];
			c[i][j] = A[i][j];
		}
	}
}
int main()
{
	char s;
	int x, y;
	float r;
	cin >> x;
	cin.ignore(1);
	cin >> y;
	cin.ignore(1, '\n');
	mat = new float *[x];
	for (int i = 0; i < x; i++)
		mat[i] = new float[y];
	c = new float *[x];
	for (int i = 0; i < x; i++) {
		c[i] = new float[y];
		for (int j = 0; j < y; j++)
			mat[i][j] = 0.0f;
	}

	bool failure = false;
	for (int i = 0; i<x; i++) {
		for (string string; getline(cin, string); ) {
			istringstream stream(string);
			for (int j = 0; j <y; ++j) {
				if (!(stream >> mat[i][j])) {
					failure = true;
					break;
				}
			}
			break;
		}
	}
	cin >> s;
	cin.ignore(1, '\n');
	if (s == '+' || s == '-' || s == '*') {
		int h, k;
		cin >> h;
		cin.ignore(1);
		cin >> k;
		cin.ignore(1, '\n');
		mat1 = new float *[h];
		for (int i = 0; i < h; i++) {
			mat1[i] = new float[k];
			for (int j = 0; j < y; j++)
				mat1[i][j] = 0.0f;
		}
		bool failure1 = false;
		for (int i = 0; i < h; i++) {
			for (string string; getline(cin, string); ) {
				istringstream stream(string);
				for (int j = 0; j < k; ++j) {
					if (!(stream >> mat1[i][j])) {
						failure1 = true;
						break;
					}
				}
				break;
			}
		}
		if (!failure && !failure1) {
			if (s == '+')
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						float r = mat1[i][j] + mat[i][j];
						c[i][j] = r;
					}
				}
			if (s == '-')
				for (int i = 0; i < x; i++) {
					for (int j = 0; j < y; j++) {
						r = mat[i][j] - mat1[i][j];
						c[i][j] = r;
					}
				}
			if (s == '*')
				for (int i = 0; i < x; i++) {
					for (int j = 0; j < y; j++) {
						r = mat[i][0] * mat[0][j] + mat[i][1] * mat1[1][j] + mat[i][2] * mat1[2][j];
						c[i][j] = r;
					}
				}
			for (int i = 0; i < x; i++) {
				for (int j = 0; j < y; j++) {
					cout << c[i][j] << '\t';
				}
				cout << '\n';
			}
		}
		else {
			cout << "An error has occured while reading numbers from line.";
		}
	}
	else if (s == 'T') {
		c = new float *[y];
		for (int i = 0; i < y; i++)
			c[i] = new float[x];
		for (int i = 0; i < x; i++) {
			for (int j = 0; j <y; j++) {
				c[j][i] = mat[i][j];
			}
		}
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				cout << c[i][j] << '\t';
			}
			cout << '\n';
		}
	}
	if (s == 'R' && x == y) {
		inversiya(mat, c, x);
		for (int i = 0; i < x; i++) {
			for (int j = 0; j<x; j++) {
				cout << c[i][j] << '\t';
			}
			cout << '\n';
		}
	}

	for (int i = 0; i < x; i++) {
		delete[] mat[i];
	}
	delete[] mat;
	for (int i = 0; i < y; i++) {
		delete[] c[i];
	}
	delete[] c;
	cin.get();
	return 0;
}
