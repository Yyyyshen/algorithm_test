// datastruct_and_algorithm_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//极客时间——数据结构与算法之美
//

//
//数组
//

//
//大部分语言数组都是从0开始的（lua从1开始）
// arr[i]_addr = base_addr + i * data_type_size
// 如果从1开始，寻址公式则成为
// arr[i]_addr = base_addr + (i - 1) * data_type_size
// 对于CPU来说，多做一次减法指令
// （不过，更多的应该还是历史问题；毕竟C语言开始这已经是共识和习惯）
//

//
//数组随机访问的复杂度为O(1)，而不能说是查找
// 只是更适合查找，不知道索引的情况，排好序的数组二分法查找O(logn)
// 
//插入删除有大量数据搬移
// 也都有方法优化
// 例如删除，在数组有剩余空间的情况下，删除的数据只是标记为删除，并不进行真正的数据搬移
// 没有空间时，再统一进行一次删除操作（类似JVM垃圾回收算法、MySQL的B+树中的删除、硬盘上的数据删除；都是“假删除”）
// 

//
//越界
void
test_out_of_range()
{
	int i = 0;
	int arr[3] = { 0 };
	for (; i <= 3; ++i)
	{
		arr[i] = 0;
		std::cout << "test_out_of_range()" << std::endl;
	}
}
//数组越界会导致不明确行为，依赖于编译器不同的处理方式
// 大部分高级语言，会直接检测到数据越界异常
// 在C中，只要不是受限内存都是可以自由访问的，所以即使越界也不会报错
// 如果按最早期gcc版本（或者新版本编译器关闭栈溢出保护）
// 例如， gcc -fno-stack-protector test.c
/*

linux下gdb调试，查看各变量地址，发现数组溢出位置与i刚好一致，i被重置为0，无限循环
(gdb) p &i
$4 = (int *) 0x7fffffffdc5c
(gdb) p &arr[0]
$5 = (int *) 0x7fffffffdc50
(gdb) p &arr[1]
$6 = (int *) 0x7fffffffdc54
(gdb) p &arr[2]
$7 = (int *) 0x7fffffffdc58
(gdb) p &arr[3]
$8 = (int *) 0x7fffffffdc5c
(gdb)

*/
// 很多病毒就是利用了溢出漏洞来攻击系统
//

//
//数组替代品，自动扩容的容器
// C++ vector等
//


//
//链表
//

int main()
{
	test_out_of_range();
}
