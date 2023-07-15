# homework-group-113  
实验环境：CPU：11th Gen Intel(R) Core(TM) i7-11800H @ 2.30GHz   2.30 GHz  
Project1：  
Project2：  
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
