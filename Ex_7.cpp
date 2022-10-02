#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

std::vector<int> citire_vector(std::ifstream& fin)
{
	int nr_elemente, element;
	std::vector<int>vector;
	fin >> nr_elemente;
	for (int i = 0; i < nr_elemente; i++)
	{
		fin >> element;
		vector.push_back(element);
	}
	return vector;
}

struct comparator
{
	bool operator()(std::vector<int> v1, std::vector<int>v2)
	{
		return v1.size() < v2.size();
	}
};

std::vector<int> interclasare_vectori(std::vector<int> v1, std::vector<int> v2)
{
	std::vector<int>v3;
	int i = 0, j = 0;
	while(i<v1.size() && j<v2.size())
	{
		if (v1[i] <= v2[j])
		{
			v3.push_back(v1[i]);
			if (v1[i] == v2[j])
			{
				v3.push_back(v2[j]);
				j++;
			}
			i++;
		}
		else
		{
			v3.push_back(v2[j]);
			j++;
		}
	}

	while (i < v1.size())
	{
		v3.push_back(v1[i]);
		i++;
	}

	while (j < v2.size())
	{
		v3.push_back(v2[j]);
		j++;
	}

	return v3;
}

void determinare_vector_interclasare_optimala(std::priority_queue <std::vector<int>, std::vector<std::vector<int>>, comparator>& coada_de_prioritate_vectori)
{
	std::vector<int>v1;
	std::vector<int>v2;
	while (coada_de_prioritate_vectori.size() != 1)
	{
		v1 = coada_de_prioritate_vectori.top();
		coada_de_prioritate_vectori.pop();
		v2 = coada_de_prioritate_vectori.top();
		coada_de_prioritate_vectori.pop();
		coada_de_prioritate_vectori.push(interclasare_vectori(v1, v2));
	}
}

void afisare_vector(std::vector<int>vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i] << " ";
	}
}

int main()
{
	int n;
	std::priority_queue <std::vector<int>, std::vector<std::vector<int>>, comparator> coada_de_prioritate_vectori;
	std::ifstream fin;
	fin.open("input.in");
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		coada_de_prioritate_vectori.push(citire_vector(fin));
	}
	fin.close();
	determinare_vector_interclasare_optimala(coada_de_prioritate_vectori);
	afisare_vector(coada_de_prioritate_vectori.top());

	return 0;
}