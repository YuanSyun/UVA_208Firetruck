# UVA_208Firetruck

## Solbe the problem

My Step:

0. Initialize
1. Input routes
2. Sort the contents of the array from small to large
3. Double DFS Alogorithm
4. Print Information

## Step0: Initialize
The path solution will be great.

	const int ROUTESARRAY_SIZE = 65536;

## Step1: Input routes
Input1 and input2 routes is connect.

	if (input1 > maxRouteNumber) maxRouteNumber = input1;
		if (input2 > maxRouteNumber) maxRouteNumber = input2;
		streetArray[input1][0]++;
		streetArray[input1][streetArray[input1][0]] = input2;
		streetArray[input2][0]++;
		streetArray[input2][streetArray[input2][0]] = input1;
		
## Step2: Sort the contents of the array from small to large
Quick Sort Algorithm

http://notepad.yehyeh.net/Content/Algorithm/Sort/Quick/Quick.php 

## Step3: Double DFS Alogorithm

	void findRoutes(int _index, int _routesCounter, int _routesPointer) {

		for (int i = 1; i <= streetArray[_index][0]; i++) {

			//check repeat "routes i".
			if (checkRepeatRoutes(streetArray[_index][i], _routesCounter, _routesPointer)) continue;

			routeArray[_routesCounter][0] = _routesPointer;
			routeArray[_routesCounter][_routesPointer] = streetArray[_index][i];

			//explore success
			if (streetArray[_index][i] == Target) {
				routeCompleteArray[_routesCounter] = true;
				//Copy the previous path to the new array space
				routesCounter++;
				copyPrviousRoutes(routesCounter, _routesPointer-1);
			}

			if (streetArray[_index][i] == Target && (i == streetArray[_index][0])) {
				//Explore success, there is no path after the current index
				return;
			}
			else if (streetArray[_index][i] == Target && (i != streetArray[_index][0])) {
				//To explore success. There is still a path after the current index.
				_routesCounter = routesCounter;
				continue;
			}

			findRoutes(streetArray[_index][i], _routesCounter, _routesPointer+1 );

			//Recursive branching
			if (routeCompleteArray[_routesCounter] && (i != streetArray[_index][0])) {
				//To explore success. There is still a path after the current index.
				_routesCounter = routesCounter;
				continue;
			}
			else if ( routeCompleteArray[_routesCounter] && (i == streetArray[_index][0]) ) {
				return;
			}
			else if ( !routeCompleteArray[_routesCounter] && (i == streetArray[_index][0]) ) {
				//Exploratory failure
				_routesCounter--;
				return;
			}

		}//end for

	}//end findRoutes
	
## Step4: Print Information
None.

## My algorithm is not fast enough
My algorithm is too slow to lead to a failed upload.
I've checked uDebug and the result is correct

![AcceableAlgorithm](/Image/AcceableAlgorithm.png)
Time: 5.349s 

![MyAlgorithmSpeed](/Image/The speed of my algorithm.png)
Time: 7.579s

Test Data: https://www.udebug.com/UVa/208