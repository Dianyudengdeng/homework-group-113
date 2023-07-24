Project9: AES / SM4 software implementation  
主要做的工作：AES普通实现与查找表实现并测试效率；SM4普通实现，查找表实现，AES-NI+SIMD指令集加速实现，测试效率；   
注：Project8中已经使用AES-NI测试过了AES的加密效率，且AES优化的内容与SM4有较大的重叠，故本Project的实验重心放在对于SM4的软件实现优化以及使用AES-NI加速SM4的方法。  
  
AES：  
分别实现、测试了普通版本AES、查找表实现x->2x、x->(2x,x,x,3x)  
AES查找表实现与普通版本对比（python实现，运行效率较低）：  
<img width="425" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/c898c711-2a58-4ce3-86b2-9dab74b84dfd">  
可以看到，查找表方法通过将原先加密时所需的大量有限域上的乘法运算转化为查找表表项的方式，使用16次内存访问操作和若干次异或操作代替一次列混淆操作，获得了接近一倍的性能提升。  

SM4：
分别实现、测试了普通版本SM4、查找表替代线性变换+Sbox版本、AES-NI+SIMD指令集加速版本  
各版本加密效率对比：    
<img width="875" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/26bf1b6a-6e05-4254-a387-03147c15f5ac">  
可以看到，由于开始加密时出现cache缺失，待加密分组较少时受影响较大，平均每分组加密时间较长，也因此采用更多内存存储的T-Table版本此时效率较普通版本更低。  
当待加密分组数量达到一定规模，各版本加密分组的时间趋于稳定，最终定格在了175ns/block、105ns/blcok、60ns/block。  
关于AES-NI+SIMD指令集优化的方法，为了适配AES-NI指令一次处理128bit数据，这里采用的时SSE寄存器（128bit），理论上应当由四倍的性能提升，但实际上：  
<img width="426" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/07548fc9-d395-402d-87ce-3c373c990909">  
由于内存存取的限制，使用128bit寄存器进行并行实际只能带来不到一倍的性能提升，但是通过AES-NI指令同构计算，利用硬件加速的同时打破了内存存取对于并行计算的限制，最终得到了接近三倍的性能提升。
