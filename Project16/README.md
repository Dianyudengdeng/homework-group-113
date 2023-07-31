# Project16: implement sm2 2P decrypt with real network communication  
### 主要做的工作：实现sm2加密算法；实现sm2 2P decrypt解密算法；模拟实际网络环境进行交互   
#### sm2 2P decrypt解密算法：  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/ea2b67f3-57ab-4f43-a070-72e728f65841)

参考文献进行实现，可正常完成解密工作。  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/4a994ce9-c741-463c-ab0f-3f6a298d3920)  

#### 完整执行流程：
签名参与者2作为服务器端，参与者1作为客户端完成解密流程，故先执行decrypt_P2.py程序后执行decrypt_P1.py程序。  

##### 参与者1：
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/131e312b-11f2-458c-aac8-a3085d5add15)


##### 参与者2：
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/d274b3a0-a010-4142-9829-a1d186b32b96)


#### 解密过程中的问题：  
主要问题在于因为传输/输出需要而带来的数据格式问题，比如在加密端的XOR处理的M为普通的明文字符串，可直接按照字符串进行迭代：  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/bfa8b0f7-4685-4b6b-b15f-4738f394f03a)  
而解密端的XOR处理的C2则为由两个十六进制数为一组构成的字符串，需要采取不同的迭代方式：  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/5a262c55-9c36-4ec9-933b-1697303dd89c)  
