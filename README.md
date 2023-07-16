# homework-group-113  
实验环境：CPU：11th Gen Intel(R) Core(TM) i7-11800H @ 2.30GHz   2.30 GHz  
Project1：implement the naïve birthday attack of reduced SM3
主要做的工作：修改Project4 SM3的实现方式，提供利于攻击的API以及避免多线程加速时出现混乱；完成各类数据结构相互转换的工作，实施基础的生日攻击。  
对于input的迭代，使用上一轮生成Hash值的进行赋值，即len(input)稳定在32bytes；一是保证SM3 padding的稳定，一轮迭代压缩即可完成；二是保证遍历完成一定会发生碰撞（256bit->256bit)。  
攻击结果：只计算了哈希结果前四个字节发生碰撞的情况，主要原因在于生日攻击的空间复杂度为O(2^(n/2))，若要求八字节的碰撞结果，大致需要2^32*（32+8）bytes约170GB的存储空间，显然是不现实的。  
<img width="461" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/f21a1401-be2e-4308-a7bb-c8bf87e0fb3d">

Project2：implement the Rho method of reduced SM3    
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
