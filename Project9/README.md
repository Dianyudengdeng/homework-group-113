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
AES查找表实现与普通版本对比：  
