// datastruct_and_algorithm_04.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//
//第四阶段
// BM、KMP、AC自动机
// 红黑树
// 哈希算法
// 高级篇、实战篇
//

//
//BM算法
// 
//字符串匹配算法中，之前了解到
// BF 暴力匹配，用模式串与主串中所有子串匹配
// RK 借助哈希，对每个子串分别求哈希，之后与模式串对比，减少比较时间（由于哈希冲突，再实际比较一次）
// 当RK的哈希冲突严重时，RK退化为BF，时间复杂度O(n*m)
// 需要更高效的算法
// 
//核心思想
// 正常匹配模式串和主串过程中，是模式串再主串中不停的滑动并比较
// abcabd
// abd ->
// BF和RK是找所有子串，相当于每次滑动1位
// 而这样的例子中，用人眼看，可以发现，ab重复，c不重复
// 那么下一次比较应该直接移动到c之后，因为c不再模式串中，在模式串长度内怎么挪动都不会匹配
// 那么代码中，需要定义一些方法衡量这个移动值
// BM就是寻找这种规律，跳过一些一定不匹配的情况，提高效率
//
//原理分析
// BM引入两个规则
// 
// 坏字符规则：
// BM也是从头开始，一次比较模式串与子串，单次比较中，不同点在于
// 每个字符倒着进行比较
// [ abc ] acabdc
// [ abd ]
// <-----
// 发现某个字符（这里是c）无法匹配，则定义c为坏字符
// 接着用坏字符在模式串中查找，不存在则直接移动模式串长度，继续比较
// abc [ aca ] bdc
//     [ abd ]
//     <-----
// 发现a无法匹配，定义为坏字符，但此时a在模式串abd中存在
// 则移动长度 = 模式串长度 - 坏字符在模式串位置 ，让坏字符与在模式串中存在的位置对齐
// 此例中移动两位
// abcac [ abd ] c
//		 [ abd ]
// 规律，将坏字符对应模式串中的字符下标记为si
// abc
// abd
//   👆 d位置记为si = 2
// 坏字符在模式串中存在的位置下标记为xi
// abc					aca
// abd					abd
// 不存在记为xi = -1	👆存在a的位置xi = 0
// 则一次性移动的距离为 si - xi
// 另外，如果坏字符在模式串中多次出现，计算xi应选择靠后的，因为子串是从后往前对比的
// baab
// aab
//   👆 si = 2, xi = 1 ,移动1位，如果记靠前的，移动2位，本来可能匹配的情况被略过
// 坏字符规则能够避免很多无意义比较
// 例如 aaabaaab匹配aaaa，每次si = 3，xi = -1，移动4位，效率很高
// 但也存在无法处理的情况
// 例如 aaaa匹配baaa，坏字符为第一个a，si = 0，而xi = 3，出现负数，难道需要倒退比较？
// 所以仅仅一条规则不够
// 
// 好后缀规则：
// 例如，两字符串匹配到如下位置
// abcacabcbcbacabc		abc [ acabcbc ] bacabc
// abbcabc ->				  abbcabc
// 后两个字符匹配，倒数第三个开始不匹配
// 把已经匹配的{bc}称为好后缀，记为{u}，那么在模式串中查找，看是否还有另一个{u}，记为{u*}
// 如果有，则将模式串滑动到子串{u*}与主串{u}对齐的位置
// abcaca [ bcbcbac ] abc
//          abbcabc
//			  👆
// 若没有另一个{u}，借助坏字符思想，看是否能直接把模式串移动到主串{u}之后的位置继续比较
// 例
// abc [ acabcbc ] bacabc										abcacabcbc [ bacabc
//		 cbacabc 好后缀{bc}在模式串中没有重复，直接滑动为-》				 cbacabc
// 可见，刚好错过了正确的匹配情况
// 规则需要完善
// 如果模式串前缀（去掉好后缀的部分），与主串{u}有部分重合时
// 应该考察好后缀子串，是否存在根模式串前缀子串匹配的
// 如上例 好后缀{bc}存在两个子串{b}{c}，{c}刚好匹配模式串第一个{c}
// 则滑动到匹配的位置，刚好完全匹配
// abcacabcb [ cbacabc 
//			   cbacabc
//			   👆
// 但在这种串匹配中，其实坏字符也是能够起作用的
// 在每一次的对比中，如何衡量使用哪种规则？
// 
// 答案
// 分别计算坏字符和好后缀向后移动的位数，取更大的一个
// 避免了坏字符的负数情况，也进一步提高滑动的速度
// 
//代码实现
// 坏字符较简单，si是逐字对比时得到，xi查找坏字符在模式串出现位置
// xi如果使用遍历查找，相对效率并不高，可以将模式串每个字符和下标存到散列表
// 字符集不大的情况，例如ascii码表，直接用256大小的数组，记录每个字符可匹配位置
constexpr int ASCII_SIZE = 256;
int bc[ASCII_SIZE] = { -1 };
void generateBC(char* b, size_t m)
{
	//初始化辅助散列表
	for (int i = 0; i < ASCII_SIZE; ++i)
		bc[i] = -1;//没找到的都记-1
	//遍历模式串，将每个字符所在位置存入辅助表
	for (int i = 0; i < m; ++i)
		bc[b[i]] = i;
	//例如abda，a的ascii为97，则bc[97] = 0
	//之后如果出现重复，覆盖前面值 bc[97] = 3，刚好符合多个匹配时选后者的规则
}
int bm(char* a, size_t n,/* 前面主串，后面模式串 */ char* b, size_t m)
{
	//仅考虑坏字符规则的实现
	generateBC(b, m);//提前计算好每个字符出现的位置，后面匹配时直接取就可以了
	int i = 0;//对齐位置，也就是主串和模式串对齐的第一个字符
	while (i <= n - m)//最多可向后滑动的距离
	{
		int j;
		//从后向前匹配
		for (j = m - 1; j >= 0; --j)
			if (a[i + j] != b[j])
				break;//不匹配，break后j为坏字符对应模式串中的下标，也就是si
		if (j < 0)
			return i;//坏字符匹配后j为-1，则说明完全匹配，返回匹配位置
		i += j - bc[a[i + j]];//从辅助表中，取出坏字符在模式串中匹配的最后位置，也就是xi，计算移动值i = si - xi
	}
	//每匹配则返回-1
	return -1;
}
// 好后缀同样，除了暴力匹配，也可以进行优化
// 也是预先处理好模式串的后缀子串，计算好每个子串的可匹配位置
// 例如 对于模式串 cabcab 
// 引入一个记录数组，下标对应子串长度，值表示模式串中跟好后缀{u}匹配的子串起始下标（多个匹配同样取靠后的一个）
// 引入一个标记数组，标记后缀子串是否匹配前缀子串
// 后缀子串		长度	记录数组									 标记数组
// b			1		suffix[1] = 2 匹配到相同后缀在2开始的位置	 prefix[1] = false
// ab			2		suffix[2] = 1								 prefix[2] = false
// cab			3		suffix[3] = 0								 prefix[3] = true
// bcab			4		suffix[4] = -1未匹配到记为-1				 prefix[4] = false
// abcab		5		suffix[5] = -1								 prefix[5] = false
// 计算方式
void generateGS(char* b, size_t m, int* suffix, bool* prefix)
{
	//初始化两个辅助数组
	for (int i = 0; i < m; ++i)
	{
		suffix[i] = -1;
		prefix[i] = false;
	}
	for (int i = 0; i < m - 1; ++i)
	{
		int j = i;
		int k = 0;//公共后缀子串长度
		while (j >= 0 && b[j] == b[m - 1 - k])
		{
			--j; ++k;
			suffix[k] = j + i;
		}
		if (j == -1) prefix[k] = true;
	}
}
int moveByGS(int j/* 坏字符对应模式串的下标，用于好后缀处理 */, int m, int* suffix, bool* prefix)
{
	//计算好后缀情况的位移
	int k = m - 1 - j;
	if (suffix[k] != -1)
		return j - suffix[k] + 1;
	for (int r = j + 2; r <= m - 1; ++r)//j未坏字符下标，j+1为好后缀第一个字符，+2为第二个
		if (prefix[m - r] == true)
			return r;
	return m;
}
#define max(a,b) (((a) > (b)) ? (a) : (b))
int bm2(char* a, size_t n, char* b, size_t m)
{
	//初始化这些辅助数组
	generateBC(b, m);
	int* suffix = new int[m];
	bool* prefix = new bool[m];
	generateGS(b, m, suffix, prefix);
	//记录匹配的第一个字符位置
	int i = 0;
	while (i <= n - m)
	{
		int j;
		for (j = m - 1; j >= 0; --j)
			if (a[i + j] != b[j])
				break;
		if (j < 0)
			return i;//直接匹配成功
		//坏字符位移计算
		int x = j - bc[a[i + j]];
		int y = 0;//记录好后缀方式位移
		if (j < m - 1)//存在好后缀
			y = moveByGS(j, m, suffix, prefix);
		//以两个方式计算的偏移量较大的为准
		i += max(x, y);
	}
	return -1;
}
// 由于使用了三个额外的辅助数组
// 当处理大字符串匹配，内存消耗较多
// 可以选择性只是用好后缀规则，但效率相对会降低

// 
//KMP算法
// BM是最搞笑的字符串匹配算法
// KMP核心思想相近，较出名
// 使用坏字符和好前缀的规则
// 遇到坏字符时，模式串向后滑动，在滑动过程中，看模式串和好前缀是否有重合
// 相当于是好前缀的后缀子串与模式串的前缀子串比较
// 把最长的可匹配前缀子串作为基准
// 也可以提前构建一个数组，存储模式串中每个前缀的最长可匹配前缀子串的结尾字符下标
// 这个数组的构建需要用到动态规划
// 一般称为next（失效函数）
//

//
//AC自动机
// 
//问题引入：敏感词过滤功能的实现
// 最基本的方式是字符串匹配，维护一个敏感词字典，一段文字通过匹配算法查找是否包含这些敏感词
// BF、RK、BM、KMP、和Trie（字典）树，都是单模式串，也就是一个模式串和一个主串匹配
// 如果是体量很大的项目，需要更高效的方式
//
//多模式串匹配算法
// 就是在多个模式串和一个主串之间匹配
// 经典多模式串匹配——AC自动机
// 
//核心思想
// 实际上是Trie树基础之上，加入了类似KMP的next辅助数组
class AcNode {
public:
	char data;//存放的字符
	AcNode* children[26];//假设字符集只含a-z
	bool isEndingChar = false;//是否是结尾字符
	AcNode* fail;//失败指针，相当于KMP的失效函数next数组
};
/*
例 主串abcd 模式串c、bc、bcd、abcd
构建字典树
		\0
	↗	↑ ↖
	a	b	c
	b↗ c↗
	c↗	d -》root
	d↗ 
每个节点都有一个失败指针（箭头）
*/
// 匹配方式
// 主串从i=0开始，AC自动机从p=root开始
// p指向系欸但有一个等于b[i]的子节点x，更新p指向x，并检查一系列失败指针为结尾的路径是否是模式串
// 之后i+1继续这两个过程
// 如果p指向的节点没有等于b[i]的子节点，那么让p=p->fail，继续处理这两个过程
/*
java
public void match(char[] text) { // text是主串
  int n = text.length;
  AcNode p = root;
  for (int i = 0; i < n; ++i) {
	int idx = text[i] - 'a';
	while (p.children[idx] == null && p != root) {
	  p = p.fail; // 失败指针发挥作用的地方
	}
	p = p.children[idx];
	if (p == null) p = root; // 如果没有匹配的，从root开始重新匹配
	AcNode tmp = p;
	while (tmp != root) { // 打印出可以匹配的模式串
	  if (tmp.isEndingChar == true) {
		int pos = i-tmp.length+1;
		System.out.println("匹配起始下标" + pos + "; 长度" + tmp.length);
	  }
	  tmp = tmp.fail;
	}
  }
}
*/
// 
//

int main()
{
	std::cout << "Hello World!\n";
}
