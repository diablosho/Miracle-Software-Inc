#include "matrix_add.h"

/*	A program that performs matrix addition on a given matrix, and emits the amount of time to perform the operation on standard error.

	NOTE:  The file format of the text file for your matrix needs to be understood by both the matrix_gen and matrix_add programs.

	Usage: matrix_add size blocks < matrix_file.size-1 >matrix_file.size-2
	Performs matrix addition on an integer matrix with a random scalar value.
	The operation is performed on the matrix in bites of size “size x size”.

	matrix_add: block, size, scalar
		for i = 1 .. size
			for j = 1 .. size
				block[i][j] += scalar;
			end for
		end for
	end.	*/

int main()
{
	return SUCCESS;
}