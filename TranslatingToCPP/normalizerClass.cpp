//https://github.com/scikit-learn/scikit-learn/blob/a5ab948/sklearn/preprocessing/data.py#L1377
#include <string>
using namespace std;

class Normalizer()
{
private:
	string m_norm;
	bool m_copy;
public:
	Normalizer()
	{
		m_norm = "l2";
		m_copy = true;
	}
	//copy should always be true though
	Normalizer(string norm = "l2", bool copy = true)
	{
		m_norm = norm;
		m_copy = copy;
	}

	void fit()
	{

	}

	void transform(double normalize[][9], double x[][9], int rows)
	{
		for(int i = 0; i< rows; i++)
		{
			double rowSum = 0;
			for (int j = 0; j < 8; j++)
			{
				rowSum+= x[i][j]*x[i][j];
			}
			double mag = pow(rowSum, 0.5);
			for(int j = 0; j<8; j++)
			{
				normalize[i][j] = x[i][j]/mag;
			}
			normalize[i][8] = x[i][8];
		}
	}

	//idk what it returns yet
	void fit_transform(double x[][9])
	{
		//check_array x
		.
		.
		.

	}

};

