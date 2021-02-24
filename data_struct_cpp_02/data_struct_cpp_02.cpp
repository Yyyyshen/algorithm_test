// data_struct_cpp_02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
/**
 * 数组
 */

 //静态声明 datatype arrayName [size];
int arr_0[3] = { 0 };

//动态声明 datatype * arrayName = new datatype[size];
int func_1()
{
	const int size = 10;

	//Dynamic array initialization
	int* dynamicArray = new int[size];
	for (int i = 0; i < size; i++) {
		dynamicArray[i] = i;
	}

	//Static array initialization
	int staticArray[size] = { 1,2,3,4,5,6,7,8,9,10 };
	float staticArray2[] = { 2.3, 7.9, 5.6, 4.2, 9.1 };

	//Printing an static Array 
	cout << "Static Array: ";
	for (int i = 0; i < size; i++) {
		cout << staticArray[i] << " ";
	}
	cout << endl;

	//Printing an static Array 
	cout << "Static Array 2:  ";
	for (int i = 0; i < 5; i++) {
		cout << staticArray2[i] << "  ";
	}
	cout << endl;

	//Printing an Dynamic Array 
	cout << "Dynamic Array: ";
	for (int i = 0; i < size; i++) {
		cout << dynamicArray[i] << " ";
	}

	// deleting allocated memory
	delete[] dynamicArray;

	return 0;
}

//动态数组resize
class ArrayList {
	int* arr;
	int num_elements;
	int capacity;

public:
	ArrayList(int size) {
		arr = new int[size];
		num_elements = 0;
		capacity = size;
	}
	void insert(int val) {
		if (num_elements < capacity) {
			arr[num_elements] = val;
			num_elements++;
		}
		else {
			resize();
			arr[num_elements] = val;
			num_elements++;
		}
	}

	int getAt(int index) {
		return arr[index];
	}

	void resize() {
		int* tempArr = new int[capacity * 2];
		capacity *= 2;

		for (int i = 0; i < num_elements; i++) {
			tempArr[i] = arr[i];
		}

		delete[] arr;
		arr = tempArr;
	}

	int length() {

		return num_elements;
	}

	void print() {
		for (int i = 0; i < num_elements; i++)
			cout << arr[i] << " ";
		cout << endl;
	}

	int* getArr() {
		return arr;
	}
};
//二维数组 
//静态二维数组
//data_type arr[x][y];
//动态二维数组
//datatype** arr = new datatype * [rowSize];
//for (int i = 0; i < rowSize; i++)
//	arr[i] = new datatype[colSize];
void func_2()
{
	const int row = 2, col = 2;

	// static array initialization
	int staticArr[row][col] = { {1, 2}, {3, 4} };

	cout << "Static two-dimensional array: ";
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			cout << staticArr[i][j] << " ";     // printing static array

	cout << endl;

	// dynamic array initialization
	int** dynamicArr = new int* [row];

	for (int i = 0; i < row; i++)
		dynamicArr[i] = new int[col];

	int k = 0;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			dynamicArr[i][j] = ++k;   // assgining values 

	cout << "Dynamic two-dimensional array: ";
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			cout << dynamicArr[i][j] << " ";

	cout << endl;
	// freeing memory
	for (int j = 0; j < row; j++) {
		delete[] dynamicArr[j];
	}
	delete[] dynamicArr;
}
/**
 * 删除数组中的偶数元素
 */
int* removeEven(int*& Arr, int size) {
	//使用上面的数组类
	ArrayList tempArr(size);
	for (int i = 0; i < size; i++)
	{
		if (Arr[i] % 2 != 0)
		{
			tempArr.insert(Arr[i]);
		}
	}
	delete[] Arr;
	Arr = tempArr.getArr();
	return Arr;
	//原生操作，记录下不是偶数的个数并放到原数组最前端，然后用一个新数组放结果
	int m = 0;
	for (int i = 0; i < size; i++)
	{
		if (Arr[i] % 2 != 0)  // if odd number found
		{
			if (i != m)
			{
				Arr[m] = Arr[i];   //inserting odd values in array
			}
			++m;		// number of odd number in an array
		}
	}
	int* temp = new int[m];
	for (int i = 0; i < m; i++)
		temp[i] = Arr[i];

	delete[] Arr;		// deleting old array
	Arr = temp;  // pointing it to new array
	return Arr;  // returning array containing odd elements only
}
/**
 * 两个有序数组组合，要求组合后依然有序
 */
int* mergeArrays(int arr1[], int arr2[], int arr1Size, int arr2Size)
{
	int* arr3 = new int[arr1Size + arr2Size]; // creating new array
	int i = 0, j = 0, k = 0;

	// Traverse both array
	while (i < arr1Size && j < arr2Size) {
		//两数组本身有序，直接对位开始比较，较小的放入新数组并后移继续对比，以此类推
		if (arr1[i] < arr2[j])
			arr3[k++] = arr1[i++];
		else
			arr3[k++] = arr2[j++];
	}

	//若长度不一致，最后将剩下的补充到结尾
	while (i < arr1Size)
		arr3[k++] = arr1[i++];

	while (j < arr2Size)
		arr3[k++] = arr2[j++];
	return arr3;
}
/**
 * 在数组中找到两数之和，同leetcode第一题
 * 由于没有用stl，解思路有些不同
 */
 //Helper Function to sort given Array (Quick Sort)          
int partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = (low - 1); // index of smaller element 
	for (int j = low; j < high; j++) {
		// If current element is <= to pivot 
		if (arr[j] <= pivot) {
			i++;

			// swap arr[i] and arr[j] 
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	// swap arr[i+1] and arr[high] (or pivot) 
	int temp = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = temp;

	return i + 1;
}
void sort(int arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		sort(arr, low, pi - 1);
		sort(arr, pi + 1, high);
	}
}
int* findSum(int arr[], int value, int size) {
	sort(arr, 0, size - 1);   //Sort the array in Ascending Order
	//先排序再从两端开始相加
	int Pointer1 = 0;    //Pointer 1 -> At Start
	int Pointer2 = size - 1;   //Pointer 2 -> At End

	int* result = new int[2];
	int sum = 0;

	while (Pointer1 != Pointer2) {

		sum = arr[Pointer1] + arr[Pointer2];  //Calulate Sum of Pointer 1 and 2

		if (sum < value)
			Pointer1++;  //if sum is less than given value => Move Pointer 1 to Right
		else if (sum > value)
			Pointer2--;
		else {
			result[0] = arr[Pointer1];
			result[1] = arr[Pointer2];
			return result; // containing 2 number 
		}
	}
	return arr;
}

int main()
{
	std::cout << "Hello World!\n";
}

