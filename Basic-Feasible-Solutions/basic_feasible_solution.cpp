#include <iostream>
#include "generate_combinations_2.h"
#include "gaussian_elimination.h"

using namespace std;
void print_index_array(int* b, int n){
	for(int i=0; i<n; i++){
		cout<<b[i]<<" ";
	}
}
void copy_array(float* a, float* b, int m){
	
	for(int j=0; j<m; j++){
		a[j] = b[j];
	
	}
}
void get_matrix(int i,int** index_arr,float** apparent_arr,float** coefficient_matrix, int m){
	for(int count=0; count<m; count++){
		for(int j=0; j<m; j++){
			coefficient_matrix[count][j] = apparent_arr[count][index_arr[i][j]];
		}
	}
}
bool check_row(float** coefficient_matrix, int row, int m){
	// return true if all elements of a row are zero
	for(int i=0; i<m; i++){
		if(coefficient_matrix[row][i]!=0)
			return false;
	}
	return true;
}

bool check_invertible(float** coefficient_matrix, int m){
	// returns true if matrix is invertible
	for(int i=0; i<m; i++){
		if(check_row(coefficient_matrix, i, m))
			return false;
	}
	return true;
}
int main(){
	int m, n, sign;
	cout<<"enter number of variables(n) and number of equations(m) respectively:"<<endl;
	cin>>n>>m;
	cout<<"enter 0 if constraints are >= or 1 if constraints are <= type:";
	cin>>sign;
	float** arr = new float*[m];
	float** coefficient_matrix = new float*[m];
	float* b = new float[m];
	for(int i=0; i<m; i++){
		coefficient_matrix[i] = new float[m];
		arr[i] = new float[n];
	}
	cout<<"enter the coefficient matrix:"<<endl;
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			cin>>arr[i][j];
	cout<<"enter matrix b"<<endl;
	for(int i=0; i<m; i++)
		cin>>b[i];
	cout<<"introducing "<<m<<" slack variables."<<endl;
	float** apparent_arr = new float*[m];
	for(int i=0; i<m; i++)
		apparent_arr[i] = new float[n+m];
	cout<<"new apparent coefficient matrix:"<<endl;
	for(int i=0; i<m; i++){
		for(int j=0; j<n+m; j++){
			if(j<n){
				apparent_arr[i][j] = arr[i][j];
				cout<<arr[i][j]<<" ";
			}
			else if(j == n+i && sign == 1){
				apparent_arr[i][j] = 1;
				cout<<1<<" ";
			}
			else if(j == n+i){
				apparent_arr[i][j] = -1;
				cout<<-1<<" ";
			}
			else{
				apparent_arr[i][j] = 0;
				cout<<0<<" ";
			}
		}
		cout<<endl;
	}
	int** index_arr = return_combinations(n+m, m);
	int n_m_factorial = factorial(n+m);
	int n_factorial = factorial(n);
	int m_factorial = factorial(m);
	//cout<<"a"<<endl;
	int length = n_m_factorial / (n_factorial * m_factorial);
	//print_matrix(index_arr, length, m);
	cout<<"solutions of the system of inequations:"<<endl;
	float* copy_b = new float[m];
	for(int i=0; i<length; i++){
		//cout<<"1"<<endl;
		get_matrix(i, index_arr, apparent_arr, coefficient_matrix, m);
		//print_matrix(coefficient_matrix, m);
		//cout<<"2"<<endl;
		copy_array(copy_b, b, m);
		//print_matrix(coefficient_matrix, m);
		if(!check_invertible(coefficient_matrix, m)){
			cout<<"this combination is not invertible matrix"<<endl;
			continue;
		}
		float* result = matrix_solver(coefficient_matrix, copy_b, m);
		//print_index_array(index_arr[i], m);
		//print_array(result, m);
		//print_array(b, m);
		//cout<<"3"<<endl;
		int feasible_flag = 0;
		//cout<<"4"<<endl;
		for(int j=0; j<m; j++){
			int temp = index_arr[i][j] + 1;
			cout<<"x["<<temp<<"]:"<<result[j]<<" ,";
			if(result[j]<0)
				feasible_flag = 1;
		}
		//cout<<"5"<<endl;
		if(feasible_flag == 0)
			cout<<"other values are 0, the solution is feasible"<<endl;
		else
			cout<<"other values are 0, the solution is not feasible"<<endl;
	}
	

	return 0;
}