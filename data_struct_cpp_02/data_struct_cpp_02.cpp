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
/**
 * 快速排序
 *
 * 分治法思想，是冒泡的改进
 * 冒泡每次只交换相邻值，复杂度O(n^2)
 * 快速排序复杂度O(nlogn)
 */
class QuickSort {
	int* arr_;
	int len_;
public:
	QuickSort(int* arr, int len)
		:arr_(arr),
		len_(len)
	{

	}
	void sort() {
		quickSort(arr_, 0, len_ - 1);
	}
	void print() {
		cout << "arr: ";
		for (int i = 0; i < len_; i++) {
			cout << arr_[i] << " ";
		}
		cout << endl;
	}
	void quickSort(int* src, int begin, int end) {
		if (begin < end) {
			int key = src[begin];
			int i = begin;
			int j = end;
			while (i < j) {
				while (i < j && src[j] > key) {
					j--;
				}
				if (i < j) {
					src[i] = src[j];
					i++;
				}
				while (i < j && src[i] < key) {
					i++;
				}
				if (i < j) {
					src[j] = src[i];
					j--;
				}
			}
			src[i] = key;
			quickSort(src, begin, i - 1);
			quickSort(src, i + 1, end);
		}
	}
};

void test_quick_sort()
{
	int arr[9] = { 5, 9, 1, 9, 5, 3, 7, 6, 1 };
	QuickSort qs(arr, 9);
	cout << "排序前：" << endl;
	qs.print();
	qs.sort();
	cout << "排序后：" << endl;
	qs.print();
}

/**
 * 给定数组，返回数组
 * 新数组每个元素为除当前索引值之外所有值相乘
 */
int* findProduct(int arr[], int size) {
	int* product = new int[size];
	// 暴力解 复杂度O(n^2)
	for (int i = 0; i < size; i++)
	{
		int temp = 1;
		for (int j = 0; j < size; j++)
		{
			if (i == j)
			{
				continue;
			}
			temp *= arr[j];
		}
		product[i] = temp;
	}
	return product;

	//网站解法，从头遍历一遍把每个元素左边相乘的值写到当前索引，再从尾遍历把每个元素右边相乘的值与当前索引（此时是左边相乘值）相乘，复杂度O(n)
	int n = size;
	int i, temp = 1;
	int* product = new int[n];  // Allocate memory for the product array 

	// temp contains product of elements on left side excluding arr[i]
	for (i = 0; i < n; i++)
	{
		product[i] = temp;
		temp *= arr[i];
	}

	temp = 1;  // Initialize temp to 1 for product on right side 

	// temp contains product of elements on right side excluding arr[i]
	for (i = n - 1; i >= 0; i--)
	{
		product[i] *= temp;
		temp *= arr[i];
	}

	return product;
}

/**
 * 给定数组，返回最小值
 * 较简单，复杂度O(n)
 */
int findMinimum(int arr[], int size) {
	int minimum = arr[0];
	// Write your code here
	for (int i = 1; i < size; i++)
	{
		if (arr[i] < minimum)
		{
			minimum = arr[i];
		}
	}
	return minimum;
}

/**
 * 给定数组，找出第一个唯一的数
 */
int findFirstUnique(int arr[], int size) {
	//暴力解，嵌套for循环，复杂度O(n^2)，网站上是同解，等看到哈希，会有更好的方法
	int ret = -1;
	for (int i = 0; i < size; i++)
	{
		bool is_unique = true;
		for (int j = 0; j < size; j++)
		{
			if (i == j)
			{
				continue;
			}
			if (arr[i] == arr[j])
			{
				is_unique = false;
			}
		}
		if (is_unique)
		{
			ret = arr[i];
			break;
		}
	}
	return ret;
}

/**
 * 给定数组，找出第二大的数
 */
int findSecondMaximum(int arr[], int size) {
	int secondmax = INT_MIN;
	// 暴力解，每个元素查找比自身大的数量，大1的为结果，复杂度O(n^2)
	for (int i = 0; i < size; i++)
	{
		int num_bigger = 0;
		for (int j = 0; j < size; j++)
		{
			if (arr[j] > arr[i])
			{
				num_bigger++;
			}
		}
		if (num_bigger == 1)
		{
			secondmax = arr[i];
			break;
		}
	}
	return secondmax;

	// 网站解1：遍历两次数组，第一次找最大值，第二次找比最大值小的最大值，复杂度O(n)
	int max = INT_MIN;
	int secondmax = INT_MIN;
	for (int i = 0; i < size; i++) {
		if (arr[i] > max)
			max = arr[i];
	}//end of for-loop

	for (int i = 0; i < size; i++) {
		if (arr[i] > secondmax && arr[i] < max)
			secondmax = arr[i];
	}//end of for-loop

	return secondmax;

	//网站解2：一次遍历，但需要使用else if
	for (int i = 0; i < size; i++) {
		if (arr[i] > max) {
			secondmax = max;
			max = arr[i];
		}
		else if (arr[i] > secondmax && arr[i] != max) {
			secondmax = arr[i];
		}
	}//end of for-loop
	return secondmax;
}

/**
 * 数组右旋一次
 */
void rotateArray(int arr[], int size) {

	//Store Last Element of Array.
	//Start from last and Right Shift the Array by one.
	//Store the last element saved to be the first element of array.
	int lastElement = arr[size - 1];
	//所有元素后移一位，把最后一位填到第一位
	for (int i = size - 1; i > 0; i--) {
		arr[i] = arr[i - 1];
	}
	arr[0] = lastElement;

}

/**
 * 给定数组，让负数在同一边，正数在另一边，例如：{-1，-1，1，1}
 */
void reArrange(int arr[], int size) {

	int* newArray = new int[size];
	int newArray_index = 0;

	//两次循环分别将负值与正值填入一个新数组，再整体拷贝
	for (int i = 0; i < size; i++) {
		if (arr[i] < 0)
			newArray[newArray_index++] = arr[i];
	}

	for (int i = 0; i < size; i++) {

		if (arr[i] >= 0)
			newArray[newArray_index++] = arr[i];
	}

	for (int j = 0; j < newArray_index; j++) {
		arr[j] = newArray[j];
	}
	delete[] newArray;

	//在同数组内操作
	int j = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i] < 0) {   // if negative number found
			if (i != j)
				swap(arr[i], arr[j]);  // swapping with leftmost positive 
			j++;
		}
	}
}
/**
 * 给定数组（已经排序），重新排序为最大、最小值排列（最大，最小、第二大、第二小...类推）
 */
void maxMin(int arr[], int size) {
	//创建新数组
	int* result = new int[size];

	int pointerSmall = 0,     //PointerSmall => Start of arr
		pointerLarge = size - 1;   //PointerLarge => End of arr

		//Flag which will help in switching between two pointers
	bool switchPointer = true;

	for (int i = 0; i < size; i++) {
		if (switchPointer)
			result[i] = arr[pointerLarge--]; // copy large values
		else
			result[i] = arr[pointerSmall++]; // copy small values

		switchPointer = !switchPointer;   // switching between samll and large
	}

	for (int j = 0; j < size; j++) {
		arr[j] = result[j];    // copying to original array
	}
	delete[] result;

	//不使用额外空间
	int maxIdx = size - 1;
	int minIdx = 0;
	int maxElem = arr[maxIdx] + 1; // store any element that is greater than the maximum element in the array 
	for (int i = 0; i < size; i++) {
		// at even indices we will store maximum elements
		if (i % 2 == 0) {
			arr[i] += (arr[maxIdx] % maxElem) * maxElem;
			maxIdx -= 1;
		}
		else { // at odd indices we will store minimum elements
			arr[i] += (arr[minIdx] % maxElem) * maxElem;
			minIdx += 1;
		}
	}
	// dividing with maxElem to get original values.
	for (int i = 0; i < size; i++) {
		arr[i] = arr[i] / maxElem;
	}
}

/**
 * 给定未排序数组，计算最大子数组和（有负数）
 */
int maxSumArr(int arr[], int arrSize) {
	//暴力解法为计算所有子数组和

	//动态规划，是个比较关键的点，后面还需要细看
	if (arrSize < 1) {
		return 0;
	}

	int currMax = arr[0];
	int globalMax = arr[0];

	for (int i = 1; i < arrSize; i++) {
		if (currMax < 0) {
			currMax = arr[i];
		}
		else {
			currMax += arr[i];
		}

		if (globalMax < currMax) {
			globalMax = currMax;
		}
	}
	return globalMax;
	//Kadane算法的基本思想是扫描整个数组，并在每个位置找到到此结束的子数组的最大和。
}

int main()
{
	test_quick_sort();
	std::cout << "Hello World!\n";
}

