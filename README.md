# homework-group-113  
实验环境：CPU：11th Gen Intel(R) Core(TM) i7-11800H @ 2.30GHz   2.30 GHz  
Project1：implement the naïve birthday attack of reduced SM3  
主要做的工作：修改Project4 SM3的实现方式，提供利于攻击的API以及避免多线程加速时出现混乱；完成各类数据结构相互转换的工作，实施基础的生日攻击。  
对于input的迭代，使用上一轮生成Hash值的进行赋值，即len(input)稳定在32bytes；一是保证SM3 padding的稳定，一轮迭代压缩即可完成；二是保证遍历完成一定会发生碰撞（256bit->256bit)。  
攻击结果：只计算了哈希结果前四个字节发生碰撞的情况，主要原因在于生日攻击的空间复杂度为O(2^(n/2))，若要求八字节的碰撞结果，大致需要2^32*（32+8）bytes约170GB的存储空间，显然是不现实的。  
<img width="461" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/f21a1401-be2e-4308-a7bb-c8bf87e0fb3d">

Project2：implement the Rho method of reduced SM3    
主要做的工作：实现Rho Method寻找SM3碰撞的代码；修改Rho Method寻找SM3的部分字节碰撞；优化加速寻找碰撞；分析不同迭代方法的区别；  
在一些参考文献中，要求Rho Method遵循哈希输入是上一轮哈希的输出，直接的想法是使用memcpy从Hash到input，但是实际上在小端序的系统中这意味着SM3的input并不严格等于上一轮的Hash结果；另一种是使用循环便遍历初始化input以严格按照大端序存储。  
按照我的理解要求哈希输入是上一轮哈希的输出事实上是要求H_1和H_2的迭代路径相同以最终实现成环寻找碰撞的目的，只要保证H_1和H_2的迭代路径相同，是否还需要要求哈希输入与上一轮哈希的输出严格相等？  
以3bytes的碰撞为例：  
memcpy：  
<img width="451" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/5fb28fcd-f8bd-455f-9531-042059ae1af5">  
严格相等：  
<img width="459" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/b062b602-8902-4c31-8e5b-0cfd9195a950">  
可以看到不严格相等的情况甚至更快完成了寻找碰撞的过程，说明了只要H_1和H_2的迭代路径相同即可实现部署Rho Method攻击的目的。  
对于多线程加速，
寻找到的4bytes的碰撞：  
<img width="721" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/809fb700-21da-47df-b5b6-f5c802fb07b9">
以上是使用Rho Method寻找的部分字节的碰撞，但经过分析，Rho Method通过寻找迭代形成的环来发现碰撞，对于完整的Hash值，若要形成环则意味着已经出现了多对碰撞，这不符合SM3的安全要求，因此使用完整的哈希值进行迭代寻找部分字节的碰撞实际上与随机生成两个哈希值进行比较没有区别，所以可以看到寻找部分字节碰撞也需进行大量的哈希操作；  
通过修改Rho Method以寻找部分字节的碰撞：保持输入的高地址段相同，每次迭代将Hash的部分复制到输入的低地址端，保证了Hash仅有部分字节发生碰撞即可形成环路。  
使用修改后的Rho Method，在寻找部分字节的碰撞中，经常会出现找到的结果是由相同的哈希输入产生的，由于输入是由先前的Hash值迭代而成，我认为这意味着已经形成了碰撞，于是尝试使用更多的碰撞检测/记录先前输入的方式尝试记录这些碰撞，但是经过实现，我发现，由于无法准确确定碰撞的位置，进行更多的碰撞检测->避免出现相同的输出/记录先前输入，往往需要跨越数轮迭代，而跨越的轮数是不可控的，比如记录先前的输入：  <img width="785" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/0a5b388e-20ac-4c26-adf7-d18406a6c104">
在寻找四字节的碰撞中，我记录了两轮的初始输入，但是仍然全部相同，这意味着碰撞发生在更前面，因为程序的设计中无法准确定位，Hash函数具有单向性，动态定位则要耗费内存，不符合Rho Method的设计初衷，故该方法是不可行的。  
最终使用memcmp(input_1[i],input_2[i],InputLength)!=0，在多线程加速下找到的

Project3：implement length extension attack for SM3, SHA256, etc  
这里使用了Project4的SM3实现以及参考了别人的SHA256实现，对于SM3和SHA256的长度扩展攻击设计了不同的攻击场景  
SM3：攻击场景是服务器在生成哈希时，在用户输入前加入secret信息使得攻击者无法在未知secret内容的前提下生成input对应的H(input)；  
通过长度扩展攻击，攻击者在知道一个input、H(secret||input)、以及secret长度的前提下，可以在不知道secret内容的情况下伪造一个M'=secret||input||padding||append以及对应的H(M')  
SHA256：攻击场景是secret内容未知，但已知H(M)、M的长度  
通过长度扩攻击，攻击者在不知道secret内容的情况下伪造一个M'=M||padding||append以及对应的H(M')
在生成有效哈希值的前提下开展进一步攻击。 
我所完成的工作主要是修改Hash的主体算法，使得迭代压缩中可以利用已有的哈希值生成新的有效哈希对；编写独立的padding函数，直接获得哈希结果以验证长度扩展攻击效果。  

Project4：do your best to optimize SM3 implementation (software)  
由于哈希函数受输入长度的影响较大，这里使用测试的都是<56bytes的输入。  
Openssl：  
hash单分组：0.0037 毫秒  
软件实现优化：省略了T和W_1的初始化  
hash单分组： 0.0005 毫秒 hash16个不同input：0.0049 毫秒  
SIMD优化：使用SIMD指令集优化迭代压缩CF函数，使得一次执行可以同时处理16个互不影响的message_buffer的输入。尽管当前还不能很好适配输入长度不同的情况，但是核心对于CF的优化已经实现，对于需要处理大量输入的情况已经可以起到优化的效果，测试环境中较未使用SIMD指令集的hash操作实现效率提升了一倍多。  
hash16个不同input：0.0022 毫秒  
