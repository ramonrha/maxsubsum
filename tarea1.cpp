#include <iostream>
#include <vector>
#include <random>

int maxSubSum1(std::vector<int> &a )
{
	int maxSum = 0;
	int size = (int)a.size()-2;
	for( int i = 0; i < size; i++ ){
		for( int j = i ; j < size; j++ ){
			//std::cout<<"New sub vector"<<std::endl;
			int thisSum = 0;
			for( int k = i ; k <= j; k++ ){
				thisSum += a[k];
				//std::cout<<"Adding item ["<<k<<"]"<<std::endl;
				if(thisSum > maxSum){
					maxSum = thisSum;
					//std::cout<<"i = "<<i<<", j = "<<j<<"------------>"<<std::endl;
				}
			}
		}
	}
	return maxSum ;
}
int
maxSubSum2( const std::vector<int> &a ){
	int maxSum = 0;
	int size = (int)a.size()-2;
	for(int i = 0; i < size; i++ ){
		int thisSum = 0;
		for( int j = i; j < size; j++ ){
			thisSum += a[j];
			if(thisSum > maxSum){
				maxSum = thisSum;
			}
		}
	}
	return maxSum;
}

int max3(int a, int b, int c){
	if(a > b){
		if(a > c){
			return a;
		}
		else
			return c;
	}else{
		if(b > c){
			return b;
		}else
			return c;
	}
}

int MaxSumRec(const std::vector<int> &a,int left, int right){
	if(left == right){  // Base case
		if( a[left] > 0 ){
			return a[left];
		}
		else{
			return 0;
		}
	}
	int center = (int)(( (float)left + (float)right ) / 2.0);
	int maxLeftSum = MaxSumRec( a, left, center );
	int maxRightSum = MaxSumRec ( a, center + 1, right);
	int maxLeftBorderSum = 0, leftBorderSum = 0;
	for(int i = center; i >= left; i--){
		leftBorderSum += a[i];
		if(leftBorderSum > maxLeftBorderSum)
			maxLeftBorderSum = leftBorderSum;
	}
	int maxRightBorderSum = 0, rightBorderSum = 0;
	for(int j = center + 1; j <= right; j++ ){
		rightBorderSum += a[j];
		if(rightBorderSum > maxRightBorderSum)
			maxRightBorderSum = rightBorderSum;
	}
	return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

int maxSubSum3(const std::vector<int> &a ){
	return MaxSumRec( a, 0, a.size()-2 );
}

int maxSubSum4(const std::vector<int> &a){
	int maxSum = 0, thisSum = 0;
	int size = (int)a.size()-2;
	for(int j = 0; j < size; j++){
		thisSum += a[j];
		if(thisSum > maxSum){
		maxSum = thisSum;
		}
		else{
			if(thisSum < 0)
				thisSum = 0;
		}
	}
	return maxSum;
}

int main (){
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(std::numeric_limits<int>::min() ,
			std::numeric_limits<int>::max());
	//int dice_roll = distribution(generator);  // generates number in the range 1..6

	std::vector<int> datos;

	const int Max_Data_Size = 20;
	for(int i=0; i <= Max_Data_Size; i++){
		datos.push_back(distribution(generator));
	}

	/*for(int i=1; i<(int)datos.size(); i++){
		std::cout << "datos["<< i <<"] = ";
		std::cout << datos.at(i-1) << std::endl;
	}*/

	std::cout << "MaxSubSum1 = " << maxSubSum1(datos) << std::endl;
	std::cout << "MaxSubSum2 = " << maxSubSum2(datos) << std::endl;
	std::cout << "MaxSubSum3 = " << maxSubSum3(datos) << std::endl;
	std::cout << "MaxSubSum4 = " << maxSubSum3(datos) << std::endl;
	std::cout << "datos.size() = " << datos.size()-1 << std::endl;
	std::cout << "Max Data sise - 2 = " << Max_Data_Size << " is " << datos.at(datos.size()-2) << std::endl;
	return 0;
}
