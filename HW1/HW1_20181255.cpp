#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
#include <ctime>
using namespace std;

int main(int argc, char** argv)
{
	char* infile = argv[1];
	char* index = argv[2];
	FILE* input = fopen(infile, "r");
	if (input == NULL)
		return 0;

	char outfile[22] = "result_";
	strcat(outfile, infile);
	FILE* result = fopen(outfile, "w");
	clock_t start = clock();

	int N, M;
	fscanf(input, "%d %d", &N, &M);
	int ans = INT_MIN;
	vector<vector<int>>arr(N + 1, vector<int>(M + 1));

	if (!strcmp(index, "1"))
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				int num;
				fscanf(input, "%d", &num);
				arr[i][j] = num;
			}
		}

		for (int i1 = 0; i1 < N; i1++)
		{
			for (int i2 = i1; i2 < N; i2++)
			{
				for (int j1 = 0; j1 < M; j1++)
				{
					for (int j2 = j1; j2 < M; j2++)
					{
						int sum = 0;
						for (int i = i1; i <= i2; i++)
						{
							for (int j = j1; j <= j2; j++)
								sum += arr[i][j];
						}
						if (ans < sum)
							ans = sum;
					}
				}
			}
		}
	}

	else if (!strcmp(index, "2"))
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= M; j++)
			{
				int num;
				fscanf(input, "%d", &num);
				arr[i][j] = num + arr[i - 1][j] + arr[i][j - 1] - arr[i - 1][j - 1];
			}
		}

		for (int i1 = 1; i1 <= N; i1++)
		{
			for (int i2 = i1; i2 <= N; i2++)
			{
				for (int j1 = 1; j1 <= M; j1++)
				{
					for (int j2 = j1; j2 <= M; j2++)
					{
						int sum = arr[i2][j2] - arr[i1 - 1][j2] - arr[i2][j1 - 1] + arr[i1 - 1][j1 - 1];
						if (ans < sum)
							ans = sum;
					}
				}
			}
		}
	}

	else if (!strcmp(index, "3"))
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				int num;
				fscanf(input, "%d", &num);
				arr[i][j + 1] = arr[i][j] + num;
			}
		}

		vector<int>arr2(N);
		for (int j1 = 0; j1 < M; j1++)
		{
			for (int j2 = j1; j2 < M; j2++)
			{
				for (int i = 0; i < N; i++)
					arr2[i] = arr[i][j2 + 1] - arr[i][j1];

				int sum = 0, max = 0;
				for (int i = 0; i < N; i++)
				{
					sum += arr2[i];
					if (max < sum)
						max = sum;
					else if (sum < 0)
						sum = 0;
				}
				if (ans < max)
					ans = max;
			}
		}
	}
	clock_t end = clock();
	double time = end - start;

	fprintf(result, "%s\n", infile);
	fprintf(result, "%s\n", index);
	fprintf(result, "%d\n%d\n%d\n%.1f\n", N, M, ans, time);
	fclose(input);
	fclose(result);
	return 0;
}