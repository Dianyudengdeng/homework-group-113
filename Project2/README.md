# Project2：Rho method of reduced SM3  
**主要做的工作**: 实现Rho Method寻找SM3碰撞的代码；修改Rho Method寻找SM3的部分字节碰撞；优化加速寻找碰撞；分析不同迭代方法的区别；  
***
## 实验原理
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/d7038fec-e88c-4125-9911-e7a66657460b)

## 实验说明
### input的迭代：
在一些参考文献中，要求Rho Method遵循哈希输入是上一轮哈希的输出，直接的想法是使用**memcpy**从Hash到input，但是实际上在小端序的系统中这意味着SM3的input并不严格等于上一轮的Hash结果；另一种是使用循环便遍历初始化input以严格按照大端序存储。  
 按照我的理解要求哈希输入是上一轮哈希的输出事实上是要求H_1和H_2的迭代路径相同以最终实现成环寻找碰撞的目的，只要保证H_1和H_2的迭代路径相同，是否还需要要求哈希输入与上一轮哈希的输出严格相等？  
以3bytes的碰撞为例：  
memcpy：  
<img width="451" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/5fb28fcd-f8bd-455f-9531-042059ae1af5">  
严格相等：  
<img width="459" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/b062b602-8902-4c31-8e5b-0cfd9195a950">  
  可以看到不严格相等的情况甚至更快完成了寻找碰撞的过程，说明了只要H_1和H_2的迭代路径相同即可实现部署Rho Method攻击的目的。  
### 方法优化：
#### 存在的问题：
使用多线程加速，寻找到的**4bytes**的碰撞：  
<img width="721" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/809fb700-21da-47df-b5b6-f5c802fb07b9">
以上是使用Rho Method寻找的部分字节的碰撞，但经过分析，Rho Method通过**寻找迭代形成的环**来发现碰撞，对于完整的Hash值，若要形成环则意味着已经出现了多对碰撞，这不符合SM3的安全要求，**因此使用完整的哈希值进行迭代寻找部分字节的碰撞实际上与随机生成两个哈希值进行比较没有区别**，所以可以看到寻找部分字节碰撞也需进行大量的哈希操作；  
#### 改进措施：
通过修改Rho Method以寻找部分字节的碰撞：保持输入的高地址段相同，每次迭代将Hash的部分复制到输入的低地址端，保证了Hash仅有部分字节发生碰撞即可形成环路。  
#### 更多的问题：
使用修改后的Rho Method，在寻找部分字节的碰撞中，经常会出现找到的结果是由相同的哈希输入产生的，由于输入是由先前的Hash值迭代而成，我认为这意味着已经形成了碰撞，于是尝试使用更多的碰撞检测/记录先前输入的方式尝试记录这些碰撞。但是经过测试，我发现，由于无法准确确定碰撞的位置，进行更多的碰撞检测以避免出现相同的输出或记录先前输入，往往需要跨越数轮迭代，而跨越的轮数是不可控的，比如记录先前的输入:  
<img width="785" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/0a5b388e-20ac-4c26-adf7-d18406a6c104">
在寻找四字节的碰撞中，我记录了两轮的初始输入，但是仍然全部相同，这意味着碰撞发生在更前面，因为程序的设计中无法准确定位，Hash函数具有单向性，动态定位则要耗费内存，不符合Rho Method的设计初衷，故该方法是不可行的。  
## 运行结果
最终使用memcmp(input_1[i],input_2[i],InputLength)!=0，在多线程加速下找到的**4bytes**的碰撞：  
<img width="622" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/712cba25-74fd-48d1-b25d-1abf11b62c61">  
