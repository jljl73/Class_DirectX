#include "Global.h"

int main()
{
	int nMatDimension;
	cout << " 행렬 차수를 입력하시오 : ";
	cin >> nMatDimension;

	cMatrix mat(nMatDimension);
	mat = cMatrix::Identity(nMatDimension);

	for (int r = 0; r < nMatDimension; ++r)
	{
		for (int c = 0; c < nMatDimension; ++c)
		{
			printf("[ %d, %d ] : ", r + 1, c + 1);
			cin >> mat[r][c];
		}
	}

	cout << "[ 초기 행렬 ] " << endl;
	mat.Print();

	cout << "[ Determinant ] " << endl;
	cout << mat.Determinant() << endl;

	if (mat.Determinant() == 0)
	{
		cout << " 역행렬이 존재하지 않음" << endl;
		return 0;
	}

	cout << "[ Adjoint ] " << endl;
	mat.Adjoint().Print();

	float fDet = 0.0f;
	cMatrix matInv = mat.Inverse(fDet);
	cout << "[ 역행렬 ] " << endl;
	matInv.Print();

	cout << "[ 역행렬 확인 ] " << endl;
	(matInv*mat).Print();

}