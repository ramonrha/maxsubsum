#include <iostream>
#include <vector>
#include <random>

int maxSubSum1(std::vector<int> &a )
{
int maxSum = 0;
for( int i = 0; i < a.size(); i++ )
	for( int j = i ; j < a.size(); j++ ){
		int thisSum = 0;
		for( int k = i ; k <= j; k++ )
			thisSum += a[k];
		 if(thisSum > maxSum)
			 maxSum = thisSum;
	}
	return maxSum ;
}

int main (){
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(std::numeric_limits<int>::min() ,
			std::numeric_limits<int>::max());
	//int dice_roll = distribution(generator);  // generates number in the range 1..6
	std::vector<int> datos;

	const int Max_Data_Size = 25;
	for(int i=0; i < Max_Data_Size; i++){
		datos.push_back(distribution(generator));
	}

	for(int i=1; i<(int)datos.size(); i++){
		std::cout << "datos["<< i <<"] = ";
		std::cout << datos.at(i-1) << std::endl;
	}

	std::cout << "hola" << std::endl;
	std::cout << "value " << tope << " is " << datos.at(datos.size()-1) << std::endl;
	std::cout << "MaxSum is " << maxSubSum1(datos) << std::endl;
	return 0;
}
