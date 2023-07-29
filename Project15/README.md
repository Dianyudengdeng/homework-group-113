# Project15: implement sm2 2P sign with real network communication  
### 主要做的工作：实现sm2 2P sign签名算法；模拟实际网络环境进行交互    
#### SM2 2P签名算法：  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/53899964-99a9-4778-b60d-ba5fe55a597f)  
参考文献进行实现，最终对于生成的签名Sig以及公钥K，可使用Project11实现的验签算法验证通过。  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/7d737527-936e-4568-864c-bda1e9581557)  
#### 完整执行流程：
签名参与者2作为服务器端，参与者1作为客户端完成签名流程，故先执行Sign_P2.py程序后执行Sign_P1.py程序。  
##### 参与者1：  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/f1980dff-0024-4746-945f-735fc9a5be9e)  
##### 参与者2：  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/1d16dbb0-0f4a-4854-a83f-7c0613ff2959)  

为了模拟实际网络环境需要进行大量的数据传输，对于传输后的数据，作为bytes类型可直接传入签名流程函数中，但会导致错误的签名结果使得验签流程无法通过。  
为解决这个问题，需要首先进行decode，随后使用ast.literal_eval进行处理还原，还原后可得到正确的签名结果。  
