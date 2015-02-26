#include "matrix_gen.h"

/*	A program that creates a file of integers that represents a NxN matrix.

	NOTE:  The file format of the text file for your matrix needs to be understood by both the matrix_gen and matrix_add programs.

	Usage:  matrix_gen size >matrix_file.size
		Generates a matrix of size “size x size” that contains a random set of integers from -100 .. 100.	*/
	
/*	main: size, blocks

	start_time = get current time;
	  scalar = random number;
	  block_size = size / blocks;

	for x = 1 ..blocks
		for y = 1 ..blocks
			  async read request matrix[x, y]
			  block = async read return matrix[x, y]
			  matrix_add(block, block_size, scaler)
			  async write request block
			  async write return block
		end for
	end for

	end_time = get the current time
	emit end_time - start_time	*/

int main()
{
	return SUCCESS;
}