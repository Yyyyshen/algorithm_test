// sword_to_offer_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//《剑指Offer》
//

//
//面试形式
// 电面-》（远程桌面）-》现场
// 
// 电面
//  投简历后一两星期内保证能够正常通话一小时，尽快寻找安静环境
// 远程
//  上机操作，理清思路再开始，考察codystyle、调试能力、测试能力
// 现场
//  规划路线不要迟到，衣着整齐、注意面试邀请函的信息，准备一些问题
// 
//现场面试环节
// 行为
//  介绍经历，快速调整情绪，体现性格，暖场
//  项目经验。背景简述-》自身任务-》做了那些工作，如何解决问题-》自己的突出贡献
//  （项目规模，目标用户，软件功能；自己参与还是负责哪个模块，如何做设计，哪个平台，什么工具，哪些技术，如何测试；做了哪些优化，修改了多少bug，提高了团队效率等）
//  掌握的技能，谨慎使用 了解、熟悉 等程度词汇
//  为什么跳槽？不要带有负面情绪，一般说想要更高的发展，更有挑战的工作，对哪些方向感兴趣等，积极一些
// 技术
//  扎实基础，语言、数据结构、算法
//  正确、完整、鲁棒的高质量代码（多考虑边界，特殊情况、错误处理等）
//  思路清晰地分析问题，即使不能完全解出答案，也有思考能力
//  从空间、时间维度优化代码（会的题目如果知道多种解法，可以先给出简单地，再逐步导出优化的）
//  沟通能力、学习能力、发散思维等综合素质
// 
//

//
//基础知识
// 语言
// 算法、数据结构、复杂度优化
// 计算机原理
// 内存管理、IO、网络、并发
//

//
//编程语言
// C 底层、驱动
// C++ linux
// C# win
// JAVA 跨平台
// OC apple
// python 工具
//

//
//C++
// 概念理解，关键字（类型转换、sizeof）
// 看代码思考运行结果（一般考察比较微妙的特性）
// 
//推荐书
// effective C++
// C++ primer
// 深度探索C++对象模型
// the C++ programming language
// （前两个读过，后两个还在待读项里，不过估计有很多会忘，多看两遍）
//

//面试题
// sizeof
// 定义空类型，没有成员，sizeof其实例结果是什么
// 是1，为什么不是0，实例必须占有一定的空间，多少由编译器决定（VS中是1）
// 如果定义构造和析构，结果是多少
// 还是一样的，函数根据地址调用，实例里不会添加相关信息（而且空实例本身也会被编译器加上默认的构造函数、析构、转移等）
// 如果有虚函数，会有一个虚函数表，实例内部存一个指针指向它，sizeof获取后根据平台不同，指针大小不同
//
class EmptyClass {};
void
test_sizeof()
{
	EmptyClass empty;
	std::cout << sizeof(empty) << std::endl;
}
// 

//面试题
// 看运行结果
class A
{
private:
	int value;
public:
	A(int n) { value = n; }
	//A(A other) { value = other.value; } //应使用const &形式传参，不仅是因为避免拷贝成本，这里是编译错误；
	//因为如果是传值形式，调用拷贝构造，拷贝构造中又调用拷贝构造，无限递归，所以C++不允许这样
	A(const A& other) { value = other.value; } //正确
	void Print() { std::cout << value << std::endl; }
};
//

//面试题
// 赋值运算符函数
class CMyString {
public:
	CMyString(char* pData = nullptr);
	CMyString(const CMyString& str);
	~CMyString();
	//为该类添加赋值运算符函数
	CMyString& operator=(const CMyString& r_value) { //传入参数是否为const&形式，避免拷贝和改变实例状态；返回值是否为*this自身引用，支持连续赋值
		//判断是否是自身赋值，直接返回，避免释放自身内存时出错
		if (this == &r_value)
			return *this;

		//自身内存释放，否则内存泄露
		delete[] m_pData;
		m_pData = nullptr;

		//分配新内存，赋值
		m_pData = new char[strlen(r_value.m_pData) + 1];//+1存放'\0'
		//strcpy(m_pData, r_value.m_pData);//拷贝内存

		//返回*this自身引用
		return *this;

		//考虑异常安全，new char因内存不足失败
		//解法1，先new，成功了才delete原内容
		//解法2，先创建临时实例，再交换
		if (this != &r_value)
		{
			CMyString temp(r_value);//把问题交给拷贝构造，如果异常，还没有修改原实例
			char* pData_temp = temp.m_pData;
			temp.m_pData = m_pData;
			m_pData = pData_temp;
		}
		//出if作用域，临时对象自动析构
		return *this;
	}
private:
	char* m_pData;
};
//

//面试题
// C++中struct和class定义类型，区别是什么
//  不指定访问权限时，class默认private，struct时public
//  （C#中不指定都是private）
//

//面试题
// 单例模式
//	饿汉
class Singleton2 {
public:
	static Singleton2* getInstance() {
		return g_pSingle;
	}
	static void deleteInstance() {
		if (g_pSingle)
		{
			delete g_pSingle;
			g_pSingle = nullptr;
		}
	}
private:
	//禁止外部构造
	Singleton2() = default;
	~Singleton2() = default;
	//禁用拷贝
	Singleton2(const Singleton2& s) = delete;
	Singleton2& operator=(const Singleton2& s) = delete;
private:
	static Singleton2* g_pSingle;//唯一的单例对象指针
};
Singleton2* Singleton2::g_pSingle = new Singleton2;//代码一运行就初始化实例
//（之前项目里都用了全局变量形式，但不太好，要改掉）
//	懒汉
class Singleton {
	//普通双重加锁懒汉掠过
	//利用C++11特性的懒汉，使用内部静态变量，*最推荐*
public:
	static Singleton& getInstance() {
		static Singleton single; //C++11中局部静态变量是线程安全的，只在第一次调用时创建一次实例
		return single;
	}
private:
	//禁止外部构造
	Singleton() = default;
	~Singleton() = default;
	//禁用拷贝
	Singleton(const Singleton& s) = delete;
	Singleton& operator=(const Singleton& s) = delete;
};
// 
// 突然想到，单例只是将所需要的对象做成单个的，为了方便讲解，学习的时候都是这样定义在一个类里，并不是必须要此类单例
// 所以，是不是能这样封装一下，结合工厂和单例
class ClassShouldBeSingle final
{
public:
	using this_type = ClassShouldBeSingle;
	using member_type = int;
public:
	ClassShouldBeSingle() = default;
	~ClassShouldBeSingle() = default;

	ClassShouldBeSingle(const this_type&) = delete;
	this_type& operator=(const this_type&) = delete;
private:
	member_type m_int = 0;
};
template<class T>	//如果有参数，是不是还能用Args...形式模板继续扩展
class SingletonFactory final
{
public:
	using obj_type = T;
	using obj_type_ref = obj_type&;
public:
	static
		obj_type_ref instance()
	{
		static obj_type single_obj;
		return single_obj;
	}
};
#include <thread>
void
test_single()
{
	auto f = []() {
		decltype(auto) single_obj = SingletonFactory<ClassShouldBeSingle>::instance();
		std::cout << "ClassShouldBeSingle:" << &single_obj << std::endl;
		decltype(auto) single_obj2 = SingletonFactory<ClassShouldBeSingle>::instance();
		std::cout << "ClassShouldBeSingle:" << &single_obj2 << std::endl;
		decltype(auto) single_obj3 = SingletonFactory<EmptyClass>::instance();
		std::cout << "EmptyClass:" << &single_obj3 << std::endl;
		decltype(auto) single_obj4 = SingletonFactory<EmptyClass>::instance();
		std::cout << "EmptyClass:" << &single_obj4 << std::endl;
	};
	std::thread thd1(f);
	std::thread thd2(f);
}
// 
//



int main()
{
	std::cout << "Hello World!\n";
	//test_sizeof();
	test_single();
}


