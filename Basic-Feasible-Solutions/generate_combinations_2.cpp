#include <iostream>
using namespace std;

void print_matrix(int** arr, int m, int n){
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			cout<<arr[i][j]<<" ";
		}
		cout<<endl;
	}
}
void print_array(int* b, int n){
	for(int i=0; i<n; i++){
		cout<<b[i]<<" ";
	}
	cout<<endl;
}
void write_array(int* current_arr, int** arr, int* counter, int R){
	for(int i=0; i<R; i++){
		arr[*counter][i] = current_arr[i];
	}
	//cout<<"writing, print current"<<endl;
	//print_array(current_arr, R);
}
void find_combination(int* current_arr, int** arr, int n, int R, int r, int* counter, int start_index, int current_index){
	//print_array(current_arr, start_index-1);
	//cout<<r<<endl;
	int temp = n-r;
	//cout<<"start:"<<start_index<<",end:"<<temp<<endl; // here
	if(current_index == R){
		write_array(current_arr, arr, counter, R);
		(*counter)++;
		//cout<<"f"<<endl;
		return;
	}
	//cout<<"e"<<endl;
	for(int i=start_index; i<=n-r; i++){
		
		current_arr[current_index] = i;
		find_combination(current_arr, arr, n, R, r-1, counter, i+1, current_index+1); // here
	}
}
int factorial(int n){
	if(n == 1){
		return 1;
	}
	else{
		return n * factorial(n-1);
	}
}
int** return_combinations(int n, int r){
	int n_factorial = factorial(n);
	int r_factorial = factorial(r);
	int n_r_factorial = factorial(n - r);
	//cout<<"a"<<endl;
	int length = n_factorial / (r_factorial * n_r_factorial);
	//cout<<length;
	//exit(0);
	int** arr = new int*[length];
	int* current_arr = new int[r];
	//cout<<"b"<<endl;
	for(int i=0; i<length; i++)
		arr[i] = new int[r];
	int counter = 0;
	//cout<<"c"<<endl;
	int temp = n-r;
	//cout<<"start:"<<0<<",end:"<<temp<<endl;
	int index = 0;
	for(int i=0; i<=n-r; i++){
		current_arr[index] = i;
		//cout<<"d"<<endl;
		find_combination(current_arr, arr, n, r, r-1, &counter, i+1, index+1); // n
	}	
	//print_matrix(arr, length, r);
	return arr;
}
/*int main(){
	cout<<"enter the values of n & r respectively:";
	int n,r;
	cin>>n>>r;
	
	return_combinations(n, r);
	
	return 0;
	
}*/