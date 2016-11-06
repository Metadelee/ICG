#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
// Splits a string in multiple parts which are separated by blanks
void tokenize(const std::string line, std::vector<std::string> &tokens)
{
	std::stringstream iss(line);
	std::string token;
	while( iss >> token)
		tokens.push_back(token);
}

// Loads a matrix from the file filename. The content of this file will be returned via
// the parameter matrix. rowCount and columnCount give the respective number of rows and columns
/*
1. The matrix parameter requires a double pointer because the matrix is a two dimensional int array.
A one dimensional array is referenced by one pointer and a two dimensional array is an array where each
array element points towards one other array.
*/

bool loadMatrix(const char *filename, int **matrix, int& rowCount, int& columnCount) 
{
	using namespace std;

	rowCount = 0;
	columnCount = 0;

	ifstream inFile;
	inFile.open(filename, ifstream::in);

	if( !inFile.good())
		return false;

	vector<vector<string>> lines;			// saves the content of the file

	// read data and determine row and column count.
	while( inFile.good()) {

		string line;
		getline(inFile, line);

		if(line == "")
			break;

		vector<string> tokens;
		tokenize(line, tokens);

		columnCount = tokens.size();
		rowCount++;

		lines.push_back(tokens);
	}

	// initialize matrix
	*matrix = new int[ rowCount * columnCount];

	for( size_t currentRow=0; currentRow<rowCount; currentRow++) 
	{
		for( size_t currentColumn=0; currentColumn<columnCount; currentColumn++) 
		{
			int value = stoi(lines[currentRow][currentColumn], 0, 10);
			(*matrix)[currentRow*columnCount+currentColumn]= value;

            }
	}
	

	return true;
}

bool writeMatrix(const char *filename, int *matrix, int rowCount, int columnCount)
{
	using namespace std;

	ofstream outFile;
	outFile.open(filename, ofstream::out);

	if( !outFile.good()) {
		return false;
	} else {

		for (size_t i = 0; i < rowCount; ++i) 
		{
			for (size_t j = 0; j < columnCount; ++j) 
			{
				outFile << matrix[i*columnCount + j] << " ";
			}
			outFile << endl;
		}
	}

	return true;
}

//Multiplies the vectors vector1 and vector2 and returns the result.
// There is no check as to the size similarity of vector1 and vector2!
int multiplyVectors(int *vector1, int size1, int offset1,
                    int *vector2, int size2, int offset2)
{
  int result = 0;

  // Multiply the two vectors with regard to "offset" being the difference between two different
  // values within the array vectorX
  for (int i = 0; i < size1; ++i) 
  {
  	result += vector1[i*offset1]*vector2[i*offset2];
  }

  return result;
}


// Multiplies the matrices matrix1 and matrix2 and stores the result in resultMatrix.
// rows and columns for the respective matrices are given.
// If the two matrices can't be multiplied, the function will return false.
bool multiplyMatrices(int *matrix1, int rows1, int columns1, 
                      int *matrix2, int rows2, int columns2,
                      int *resultMatrix)
{
  if (columns1 != rows2)
  {
    return false;
  }

  // Multiply the matrices matrix1 and matrix2. For that use the function
  // multiplyVectors. Hint: You have to use the column vectors for the second matrix,
  // but the values are stored in rows. Use the offset to correct that.
  for (int i = 0; i < rows1; ++i) 
  {
	for (int j = 0; j < columns2; j++)
	{
  		resultMatrix[i*columns2 + j] = multiplyVectors(&matrix1[i*columns1], columns1, 1, &matrix2[j], rows2, columns2);
	}
  }

}

int main()
{

  int *matrix1;
  int *matrix2;
  int rows1, rows2, columns1, columns2;

  if (loadMatrix("matrix1.txt", &matrix1, rows1, columns1)&&
      loadMatrix("matrix2.txt", &matrix2, rows2, columns2))
  {

    int *resultMatrix = new int[rows1*columns2];
    multiplyMatrices(matrix1, rows1, columns1, matrix2, rows2, columns2, resultMatrix);
    writeMatrix("matrix3.txt", resultMatrix, rows1, columns2);
    delete[] resultMatrix;
    delete[] matrix1;
    delete[] matrix2;
  }
  else
     printf("Matrixdateien nicht gefunden: ");

  return 0;
}
