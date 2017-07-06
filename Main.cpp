#include <iostream>
using namespace std;

int Target;
//streetArray[N][0] = point
const int STREET_NUMBER = 22;
const int STREETARRAY_SIZE = 22;
int streetArray[STREET_NUMBER][STREETARRAY_SIZE];

//routeArray[N][0] = 1;
const int ROUTESARRAY_SIZE = 65536;
int routeArray[ROUTESARRAY_SIZE][STREET_NUMBER];
bool routeCompleteArray[ROUTESARRAY_SIZE];

int caseCounter = 0;
int routesCounter = 0;
int routesPointer = 1;

//function 
void findRoutes(int, int, int);
bool checkRepeatRoutes(int, int, int);
void copyPrviousRoutes(int, int);
void initArray();
void sortStreetArray(int);
void quickSort(int, int, int);
void swap(int , int , int);


int main() {

	while (cin >> Target) {
		caseCounter++;

		//Step0: Initialize
		routesCounter = 0;
		routesPointer = 1;
		initArray();

		//Step1: Input routes
		int input1, input2;
		int maxRouteNumber = 1;
		while (cin >> input1 >> input2) {
			if (input1 == 0 && input2 == 0)break;
			if (input1 > maxRouteNumber) maxRouteNumber = input1;
			if (input2 > maxRouteNumber) maxRouteNumber = input2;
			streetArray[input1][0]++;
			streetArray[input1][streetArray[input1][0]] = input2;
			streetArray[input2][0]++;
			streetArray[input2][streetArray[input2][0]] = input1;
		}//end while

		//Step2: Sort the contents of the array from small to large
		sortStreetArray( maxRouteNumber );


		//Step3: Alogorithm
		if (streetArray[1][0] >= 1) {
			routeArray[routesCounter][0] = routesPointer;
			routeArray[routesCounter][routesPointer] = 1;
			findRoutes(1, routesCounter, ++routesPointer);
		}

		//Step4: Print Information
		cout << "CASE " << caseCounter << ":\n";
		for (int i = 0; i < routesCounter; i++) {
			for (int j = 1; j <= routeArray[i][0]; j++) {
				cout << routeArray[i][j];
				if (j != routeArray[i][0]) {cout << " ";}
			}
			cout << "\n";
		}
		cout << "There are " << routesCounter << " routes from the firestation to streetcorner "<< Target <<".\n";

	}//end while

	//system("pause");
	return 0;
}//end main



void findRoutes(int _index, int _routesCounter, int _routesPointer) {

	for (int i = 1; i <= streetArray[_index][0]; i++) {

		//check repeat "routes i".
		if (checkRepeatRoutes(streetArray[_index][i], _routesCounter, _routesPointer)) continue;

		routeArray[_routesCounter][0] = _routesPointer;
		routeArray[_routesCounter][_routesPointer] = streetArray[_index][i];

		//探索成功
		if (streetArray[_index][i] == Target) {
			routeCompleteArray[_routesCounter] = true;
			//複製之前的路徑，到新的陣列空間
			routesCounter++;
			copyPrviousRoutes(routesCounter, _routesPointer-1);
		}

		if (streetArray[_index][i] == Target && (i == streetArray[_index][0])) {
			//探索成功，後面沒有路徑
			return;
		}
		else if (streetArray[_index][i] == Target && (i != streetArray[_index][0])) {
			//探索成功，後面還有路徑
			_routesCounter = routesCounter;
			continue;
		}

		findRoutes(streetArray[_index][i], _routesCounter, _routesPointer+1 );

		//遞迴分枝
		if (routeCompleteArray[_routesCounter] && (i != streetArray[_index][0])) {
			//探索成功，後面還有路徑，再探索
			_routesCounter = routesCounter;
			continue;
		}
		else if ( routeCompleteArray[_routesCounter] && (i == streetArray[_index][0]) ) {
			return;
		}
		else if ( !routeCompleteArray[_routesCounter] && (i == streetArray[_index][0]) ) {
			//探索失敗
			_routesCounter--;
			return;
		}

	}//end for

}//end findRoutes



bool checkRepeatRoutes(int _value, int _routesCounter, int _routesPointer) {
	bool isRepeat = false;
	
	//check _value is not repate route
	for (int i = 1; i <= _routesPointer; i++) {
		if (_value == routeArray[_routesCounter][i]) {
			isRepeat = true;
			return isRepeat;
		}
	}//end for

	return isRepeat;
}//end checkRepate



void copyPrviousRoutes(int _routesCounter, int _routesPoint) {

	routeArray[_routesCounter][0] = _routesPoint;
	for (int i = 1; i <= _routesPoint; i++) {
		routeArray[_routesCounter][i] = routeArray[_routesCounter - 1][i];
	}//end for

}//end copyPrviousRoutes



void initArray() {
	for (int i = 0; i < STREET_NUMBER; i++) {
		for (int j = 0; j < STREETARRAY_SIZE; j++) {
			streetArray[i][j] = 0;
		}
	}
	for (int i = 0; i < ROUTESARRAY_SIZE; i++) {
		routeCompleteArray[i] = false;
		for (int j = 0; j < STREET_NUMBER; j++) {
			routeArray[i][j] = 0;
		}
	}
}//end initArray



void sortStreetArray(int _maxRouteNumber) {
	for (int i = 1; i <= _maxRouteNumber; i++) {
		//qucik sort
		quickSort(i, 1, streetArray[i][0]);
	}
}//end sortStreetArray



/* 
	Quick Sort Algorithm
	http://notepad.yehyeh.net/Content/Algorithm/Sort/Quick/Quick.php 
*/
void quickSort(int _streetCounter, int _left, int _right) {
	int i, j;
	if (_left < _right) {
		i = _left;
		j = _right + 1;
		while (true) {

			// Find the position below the value of Pivot
			while (i + 1 < streetArray[_streetCounter][0] && streetArray[_streetCounter][++i] < streetArray[_streetCounter][_left]);

			// Find the left to find a position greater than the value of Pivot
			while (j - 1 > 0 && streetArray[_streetCounter][--j] > streetArray[_streetCounter][_left]);

			//i, j position cross
			if (i >= j) break;

			swap(_streetCounter, i, j);
		}//end while

		// move Pivot to the middle
		swap(_streetCounter, _left, j);
		// Quick sort the left child tandem
		quickSort(_streetCounter, _left, j - 1);
		// Quick sort of right tiles
		quickSort(_streetCounter, j + 1, _right);

	}//end if

}//end quickSort



void swap(int _streetCounter, int _i, int _j) {
	int buffer = streetArray[_streetCounter][_i];
	streetArray[_streetCounter][_i] = streetArray[_streetCounter][_j];
	streetArray[_streetCounter][_j] = buffer;
}//end swap