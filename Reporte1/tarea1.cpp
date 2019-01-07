#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <stdio.h>
#include <curses.h>
#include <bits/stdc++.h>
#include <chrono>

int indicador = 1;

void updateProgress(void){
	switch(indicador){
		case 1:
			indicador = 2;
			mvaddstr(1, 1, "/");
			refresh();
			break;

		case 2:
			indicador = 3;
			mvaddstr(1, 1, "-");
			refresh();
			break;

		case 3:
			indicador = 4;
			mvaddstr(1, 1, "\\");
			refresh();
			break;

		case 4:
			indicador = 1;
			mvaddstr(1, 1, "|");
			refresh();
			break;
	}
}

int maxSubSum1(const std::vector<int> &a )
{
	register int maxSum = 0;
	register int thisSum = 0;
	register int size = (int)a.size()-2;
	register int i,j,k;
	//if(size > 10000)
		//return -1;
	for(i = 0; i < size; i++ ){
		updateProgress();
		for(j = i ; j < size; j++ ){
			//std::cout<<"New sub vector"<<std::endl;
			thisSum = 0;
			for(k = i ; k <= j; k++ ){
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
int maxSubSum2( const std::vector<int> &a ){
	int maxSum = 0;
	int size = (int)a.size()-2;
	//if(size > 100000)
		//return -1;
	int thisSum = 0;
	for(int i = 0; i < size; i++ ){
		thisSum = 0;
		updateProgress();
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

int maxSumRec(const std::vector<int> &a,int left, int right){
	updateProgress();
	if(left == right){  // Base case
		if( a[left] > 0 ){
			//std::cout<<"-";
			return a[left];
		}
		else{
			//std::cout<<"+";
			return 0;
		}
	}
	int center = (int)(( (float)left + (float)right ) / 2.0);
	//std::cout<<"["<<left<<","<<center<<","<<right<<"]"<<std::endl;
	int maxLeftSum = maxSumRec( a, left, center );
	int maxRightSum = maxSumRec ( a, center+1, right);
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
	return maxSumRec( a, 0, a.size()-2 );
}

int maxSubSum4(const std::vector<int> &a){
	int maxSum = 0, thisSum = 0;
	int size = (int)a.size()-2;
	for(int j = 0; j < size; j++){
		updateProgress();
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

int main (int argc, char *argv[]){
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(std::numeric_limits<int>::min() ,
			std::numeric_limits<int>::max());
	//int dice_roll = distribution(generator);  // generates number in the range 1..6

	//ncurses code
	WINDOW *mainwin;

	int Max_Data_Size = 1000;
	std::cout<<"argv[1]: "<<argv[1]<<std::endl;
	if(argc > 1){
		Max_Data_Size = std::stoi(argv[1]);
	}

	std::string string_size = std::to_string(Max_Data_Size);
	int n = string_size.length();
	char char_array[n+1];
	strcpy(char_array, string_size.c_str());

	std::vector<int> datos;

	//creando variables de tiempo
	std::chrono::time_point<std::chrono::system_clock> start1,start2,start3,start4,end1,end2,end3,end4;

	std::cout<<"construyendo datos"<<std::endl;
	for(int i=0; i <= Max_Data_Size; i++){
		datos.push_back(distribution(generator));
	}
	std::cout<<"construyendo datos"<<std::endl;
	/*for(int i=1; i<(int)datos.size(); i++){
		std::cout << "datos["<< i <<"] = ";
		std::cout << datos.at(i-1) << std::endl;
	}*/

	/*  Initialize ncurses  */{
		mainwin = initscr();
		if(mainwin == NULL ) {
			std::cout << "error al iniciar el lienzo" << std::endl;
			fprintf(stderr, "Error initialising ncurses.\n");
			exit(EXIT_FAILURE);
		}
	}
	mvaddstr(1, 14, char_array);
	refresh();
	int temporal1,temporal2,temporal3,temporal4;
	mvaddstr(1, 3, "MaxSubSum1");
	refresh();
	start1 = std::chrono::system_clock::now();
	temporal1 = maxSubSum1(datos);
	end1 = std::chrono::system_clock::now();

	mvaddstr(1, 3, "MaxSubSum2");
	refresh();
	start2 = std::chrono::system_clock::now();
	temporal2 = maxSubSum2(datos);
	end2 = std::chrono::system_clock::now();

	mvaddstr(1, 3, "MaxSubSum3");
	refresh();
	start3 = std::chrono::system_clock::now();
	temporal3 = maxSubSum3(datos);
	end3 = std::chrono::system_clock::now();

	mvaddstr(1, 3, "MaxSubSum4");
	refresh();
	start4 = std::chrono::system_clock::now();
	temporal4 = maxSubSum4(datos);
	end4 = std::chrono::system_clock::now();
	/*  Clean up after ourselves  */

		delwin(mainwin);
		endwin();
		refresh();

	std::chrono::duration<double> elapsed_seconds1 = end1 - start1;
	std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
	std::chrono::duration<double> elapsed_seconds3 = end3 - start3;
	std::chrono::duration<double> elapsed_seconds4 = end4 - start4;
	std::cout <<"MaxSubSum1 = " << temporal1 <<"\t"<<elapsed_seconds1.count()<< std::endl;
	std::cout <<"MaxSubSum2 = " << temporal2 <<"\t"<<elapsed_seconds2.count()<< std::endl;
	std::cout <<"MaxSubSum3 = " << temporal3 <<"\t"<<elapsed_seconds3.count()<< std::endl;
	std::cout <<"MaxSubSum4 = " << temporal4 <<"\t"<<elapsed_seconds4.count()<< std::endl;



	//std::cout << "datos.size() = " << datos.size()-1 << std::endl;
	//std::cout << "Max Data sise - 2 = " << Max_Data_Size << " is " << datos.at(datos.size()-2) << std::endl;
	return 0;
}
