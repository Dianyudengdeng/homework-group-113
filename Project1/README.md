# Project1：birthday attack of reduced SM3  
**主要做的工作**: 修改Project4 SM3的实现方式，提供利于攻击的API以及避免多线程加速时出现混乱；完成各类数据结构相互转换的工作，实施基础的生日攻击。  
***
## 实验说明
### 数据存储：
使用C++提供的哈希表存储从**Hash->input**的映射，以实现常数时间的查表操作。
 ```c++
 unordered_map<string, string> hashToInputMap;
 hashToInputMap[hashString] = inputString;
 ```

### input的迭代：
使用上一轮生成Hash值的进行赋值，即len(input)稳定在32bytes；一是保证SM3 padding的稳定，一轮迭代压缩即可完成；二是保证遍历完成一定会发生碰撞（256bit->256bit)。  
```c++
 memcpy(input, Hash, InputLength);
```
## 运行结果
**攻击结果**：只计算了哈希结果前四个字节发生碰撞的情况，主要原因在于生日攻击的空间复杂度为O(2^(n/2))，若要求八字节的碰撞结果，大致需要**2 ^ 32*（32+8）bytes**约170GB的存储空间，显然是不现实的。  
在1秒内找到了前32bits的碰撞：  
<img width="461" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/f21a1401-be2e-4308-a7bb-c8bf87e0fb3d">
