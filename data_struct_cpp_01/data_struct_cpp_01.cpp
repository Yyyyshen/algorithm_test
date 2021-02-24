// data_struct_cpp_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
/**
 * https://www.educative.io/
 * 算法课程
 * Data Structures for Coding Interviews in C++
 */

 //首先，分析算法复杂度是一个基本技能
int func_1()
{
	int x = 0; //变量分配，基本操作数1
	x += 1;//变量访问、添加、分配，操作数3
	cout << x;//可变访问、显示值，操作数2
	return x;//变量访问、返回值，操作数2
	//时间复杂度 1+3+2+2 = 8  O(1)
}
//for循环
int func_2()
{
	int n = 10;//1
	int sum = 0;//1
	for (int i = 0; i < n; i++)//初始化i执行1次；比较语句执行n+1次，每次3个操作数；增加操作执行n次，每次3个操作数
		sum += 2;//3*n
	cout << sum;//2
	return 0;//1
	//时间复杂度 1+1+1+3*(n+1)+3*n+3*n+2+1 = 9n+9  O(n)
}
//嵌套for循环
int func_3()
{
	int n = 5;//1
	int m = 7;//1
	int sum = 0;//1
	for (int i = 0; i < n; i++) {//1+3*(n+1)+3*n
		for (int j = 0; j < m; j++)//(1+3*(m+1)+3*m)*n
			sum += 1;//3*n*m
	}
	cout << sum;//2
	return 0;//1
	//时间复杂度 9nm+10n+10  O(mn)
}
/*
算法渐进号
(1)Θ（西塔）：紧确界。            相当于"="

(2)O （大欧）：上界。              相当于"<="

(3)o（小欧）：非紧的上界。       相当于"<"

(4)Ω（大欧米伽）：下界。          相当于">="

(5)ω（小欧米伽）：非紧的下界。 相当于">"

注：任何符号都可以用来描述最佳情况，最坏情况或平均情况。表示法与任何情况均无关
*/
//计算复杂度
int func_4()
{
	int n = 10;
	int sum = 0;
	float pie = 3.14;

	for (int i = 0; i < n; i += 3) {  // O(n/3)
		cout << pie << endl;        // O(n/3)
		for (int j = 0; j < n; j += 2) {    // O((n/3)*(n/2)) 
			sum += 1;        // O((n/3)*(n/2))
			cout << sum << endl;   // O((n/3)*(n/2))
		}
	}
	return 0; //O(n^2)
}
int func_5()
{
	int n = 10;   // n could be anything
	int sum = 0;
	float pie = 3.14;

	for (int i = n; i >= 1; i -= 3) {
		cout << pie << endl;
		for (int j = n; j >= 0; j--) {
			sum += 1;
		}
	}
	cout << sum << endl;
	return 0; //O(n^2)
}
int func_6()
{
	int n = 10; //n can be anything
	int sum = 0;
	float pie = 3.14;
	int var = 1;

	while (var < n) {
		cout << pie << endl;
		for (int j = 0; j < var; j++)
			sum += 1;
		var *= 2;
	}
	cout << sum;
	return 0; //O(n)
}
int func_7()
{
	int n = 10;    // you can change the value of n
	int sum = 0;
	int var = 1;
	float pie = 3.14;

	while (var < n) {
		cout << pie << endl;
		for (int j = 1; j < n; j += 2) {
			sum += 1;
		}
		var *= 3;
	}
	cout << sum << endl;
	return 0; //O(nlog3(n))
}
int func_8()
{
	int n = 10;  // you can change the value of n
	int sum = 0;
	int j = 1;
	float pie = 3.14;

	for (int i = 1; i < n; i += 3) {
		cout << pie << endl;
		while (j < n) {
			sum += 1;
			j *= 3;
		}
		j = 1;
	}
	cout << sum << endl;
	return 0;//同func_7
}
int func_8()
{
	int n = 10;    // you can change the value of n
	int sum = 0;
	float pie = 3.14;

	for (int i = 0; i < n; i++) {
		int j = 1;
		cout << pie << endl;
		while (j < i) {
			sum += 1;
			j *= 2;
		}
	}
	cout << sum << endl;
	return 0;//O(nlog2(n))
}
int func_9()
{
	int n = 10;    // you can change the value of n
	int sum = 0;
	int j = 1;
	float pie = 3.14;

	for (int i = 0; i < n; i++) {
		cout << pie << endl;
		while (j < i) {
			sum += 1;
			j *= 2;
		}
	}
	cout << sum << endl;
	return 0;//O(n)
}

int main()
{
	std::cout << "Hello World!\n";
}
