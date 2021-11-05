// explore_learn_hash_table.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//leetcode-explore-learn-hash-table
//

//
//原理
// 定义一个哈希函数，将key映射到bucket
//设计
// 散列函数应尽量保证键和桶一一对应，但没有完美的
// 碰撞无法避免，需要解决
// 如何组织同一个桶内的数据，太多怎么办，存储后怎么搜索
// 
// 假设最大存储桶含N个键，N为常数时，可以用数组，如果N可变或很大，则可能需要高度平衡的二叉搜索树
//

int main()
{
    std::cout << "Hello World!\n";
}
