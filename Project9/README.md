Project9: AES / SM4 software implementation  
主要做的工作：AES普通实现与查找表实现并测试效率；  
注：Project8中已经使用AES-NI测试过了AES的加密效率，且AES优化的内容与SM4有较大的重叠，故本Project的实验重心放在对于SM4的软件实现优化以及使用AES-NI加速SM4的方法。  
AES：  
分别实现、测试了普通版本AES、查找表加入x->2x、x->(2x,x,x,3x)  
AES查找表实现与普通版本对比（python实现，运行效率较低）：  
<img width="418" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/40e93ae1-e403-43ea-acb1-b9a15d322c8f">
可以看到，查找表方法通过将原先加密时所需的大量有限域上的乘法运算转化为查找表表项的方式
