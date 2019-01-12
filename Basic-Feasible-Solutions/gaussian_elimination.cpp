#include <iostream>

using namespace std;
void swap(float* a, float* b){
	float temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void print_matrix(float** arr, int n){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout<<arr[i][j]<<" ";
		}
		cout<<endl;
	}
}
void print_array(float* b, int n){
	for(int i=0; i<n; i++){
		cout<<b[i]<<" ";
	}
}
void swap_rows(float** arr, float* b, int n, int i, int j){
	float temp, temp2;
	for(int count=0; count<n; count++){
		//temp = arr[i][count];
		//arr[i][count] = arr[j][count];
		//arr[j][count] = temp;
		swap(&arr[i][count], &arr[j][count]);
		swap(&b[i], &b[j]);
	}

}
void reduce_coefficient(float** arr, float* b, int n, int i){
	float temp = arr[i][i];
	for(int count=i; count<n; count++){
		arr[i][count] = arr[i][count] / temp;
		
	}
	//cout<<b[i]<<"before"<<endl;
	b[i] = b[i] / temp;
	//cout<<b[i]<<"after"<<endl;
}
void subtract_row(float** arr, int j, int i, int n, float multiplier){
	for(int count=i; count<n; count++)
		arr[j][count] = arr[j][count] - arr[i][count]*multiplier;
}
void remove_coefficient(float** arr, float* b, int n, int i){
	for(int count=i+1; count<n; count++){
		//cout<<"count"<<count<<endl;
		float temp = arr[count][i];
		subtract_row(arr, count, i, n, temp);
		//arr[count][i] = arr[count][i] - arr[count][i]*arr[i][i];
		
		b[count] = b[count] - b[i]*temp;
	}
}
float* matrix_solver(float** arr, float* b,  int n){
	float* result = new float[n];
	for(int i=0; i<n; i++){
		if(arr[i][i] == 0){
			swap_rows(arr, b, n, i, i+1); // not solvable if i == n-1
		}
		reduce_coefficient(arr, b, n, i); // make arr[i][i] = 1
		//print_matrix(arr, n);
		//print_array(b, n);
		remove_coefficient(arr, b, n, i); // maker lower coefficient to be 0
		//print_matrix(arr, n);
		//print_array(b, n);
	}
	result[n-1] = b[n-1];
	for(int i=n-2; i>=0; i--){
		float sum = 0;
		for(int j=i+1; j<n; j++){
			sum += arr[i][j]*result[j];
		}
		result[i] = b[i] - sum;
	}
	
	return result;
}
void test_matrix_solver(){
	cout<<"test matric solver"<<endl;
	cout<<"enter dimension:";
	int n;
	cin>>n;
	float** arr = new float*[n];
	float* b = new float[n];
	for(int i=0; i<n; i++)
		arr[i] = new float[n];
	
	cout<<endl<<"enter values in coefficient matrix"<<endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)
			cin>>arr[i][j];
	}
	cout<<endl<<"enter values in b matrix"<<endl;
	for(int i=0; i<n; i++)
		cin>>b[i];
	float* result =	matrix_solver( arr, b, n);
	for(int i=0; i<n; i++)
		cout<<"x"<<i<<":"<<result[i]<<" ,";
	cout<<endl;
}
//int main(){
//	test_matrix_solver();
	/*int m, n;
	cout<<"enter number of variables:";
	cin>>n;
	cout<<endl<<"enter number of equations:";
	cin>>m;
	float** arr = new float*[n];
	float* b = new float[m];
	for(int i=0; i<n; i++)
		arr[i] = new float[m];
	cout<<endl<<"enter values in coefficient matrix"<<endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++)
			cin>>arr[i][j];
	}
	cout<<endl<<"enter values in b matrix"<<endl;
	for(int i=0; i<m; i++)
		cin>>b[i];
	int total_variables = m+n;
	int zero_variables = total_variables - m;
	//int** element_arr = choose_elements(n, r, count);
	
	GFG g;
	int []arr = {1, 2, 3, 4, 5}; 
        int r = 3; 
        int n = arr.Length; 
        g.printCombination(arr, n, r); 
	return 0;*/
//}





