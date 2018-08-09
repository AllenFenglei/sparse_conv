#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;
//g++ CSR_MUL_CSC_2CSC.cpp -o CSR_MUL_CSC_2CSC

int CSRCSC2CSC(float* CSR_val, int* colidx, int* row_ptr, int row_ptr_size,
		float* CSC_val, int* rowidx, int* col_ptr, int col_ptr_size,
		float* output_val, int* output_rowidx, int* output_col_ptr)
{//INPUT:  weight matrix in CSR format & input matrix in CSC format
//OUTPUT: output matrix in CSC format  
	int output_count = 0;	//count the No. of nonzeros in output matrix
	int ptr_count = 0;	//count the No. of output_col_ptr
	int flag;	//flag for whether it is the first nonzero element in the column of output
	int c, r;
	int blank_row_flag;	//flag to deal with the case a column of output are all zeros
	float temp;
	for(int coln = 0;coln < col_ptr_size-1;coln++)
	{
		flag = 0;
		blank_row_flag = 0;
		for (int rown = 0; rown < row_ptr_size-1; rown++)
		{
			//printf("coln=%d, rown=%d, flag=%d\n",coln,rown,flag );
			c = row_ptr[rown];
			r = col_ptr[coln];
			temp = 0.0;
			while(c < row_ptr[rown+1] && r < col_ptr[coln+1])
			{
				//printf("	c=%d, r=%d\n",c,r );
				if(colidx[c]>rowidx[r])
					r++;
				else if(colidx[c]<rowidx[r])
					c++;
				else
				{
					temp += CSR_val[c] * CSC_val[r];
					c++;
					r++;
				}
			}
			if(temp!=0.0)
			{
				//printf("		temp=%f,output_count=%d,ptr_count=%d\n",temp,output_count,ptr_count);			
				output_val[output_count] = temp;
				output_rowidx[output_count] = rown;
				if(flag == 0){
					output_col_ptr[ptr_count] = output_count;
					flag = 1;
					ptr_count++;
				}
				output_count++;

			}
			else
				blank_row_flag++;

		}
		if(blank_row_flag == (row_ptr_size-1)){
			output_col_ptr[ptr_count] = output_count;
			ptr_count++;
		}
	}
	output_col_ptr[ptr_count] = output_count;
	return output_count;
}

int main()
{
	/*
	const int M = 4;
	const int K = 4;
	const int N = 4;
	float CSR_val[8]={5,6,7,8,4,5,6,7};
	int colidx[8]={0,1,2,3,0,1,2,3};
	int row_ptr[M+1]={0,0,4,4,8};
	float CSC_val[8]={3,7,4,8,2,6};
	int rowidx[8]={1,3,1,3,0,2};
	int col_ptr[N+1]={0,2,2,4,6};
	*/
	/*
	const int M = 4;
	const int K = 4;
	const int N = 4;
	float CSR_val[16]={1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7};
	int colidx[16]={0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};
	int row_ptr[M+1]={0,4,8,12,16};
	float CSC_val[8]={3,7,1,5,4,8,2,6};
	int rowidx[8]={1,3,0,2,1,3,0,2};
	int col_ptr[N+1]={0,2,4,6,8};
	*/
	
	const int M = 4;
	const int K = 2;
	const int N = 2;
	float CSR_val[8]={1,2,2,4,4,1,2,0.5};
	int colidx[8]={0,1,0,1,0,1,0,1};
	int row_ptr[M+1]={0,2,4,6,8};
	float CSC_val[4]={-1,0.5,-0.25,1};
	int rowidx[4]={0,1,0,1};
	int col_ptr[N+1]={0,2,4};
	
	float output_val[M*N];
	int output_rowidx[M*N];
	int output_col_ptr[N+1];
	int output_count = CSRCSC2CSC(CSR_val, colidx, row_ptr, M+1, CSC_val, rowidx, col_ptr, N+1, output_val, output_rowidx, output_col_ptr);
	printf("output_val:\n");
	for (int i = 0; i < output_count; ++i)
	{
		printf("%f ", output_val[i]);
	}
	printf("\n");
	printf("output_rowidx:\n");
	for (int i = 0; i < output_count; ++i)
	{
		printf("%d ", output_rowidx[i]);
	}
	printf("\n");
	printf("output_col_ptr:\n");
	for (int i = 0; i < N+1; ++i)
	{
		printf("%d ", output_col_ptr[i]);
	}
	printf("\n");
	return 0;
}