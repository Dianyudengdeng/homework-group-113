# Project15: implement sm2 2P sign with real network communication  
**主要做的工作**：实现sm2 2P sign签名算法；模拟实际网络环境进行交互    
***
## 实验原理
### SM2 2P签名算法：  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/53899964-99a9-4778-b60d-ba5fe55a597f)  
参考文献进行实现，最终对于生成的签名Sig以及公钥K，可使用Project11实现的验签算法验证通过。  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/7d737527-936e-4568-864c-bda1e9581557) 
## 实验说明
### 数据传输过程中的问题：  
为了模拟实际网络环境需要进行大量的数据传输，对于传输后的数据，作为bytes类型可直接传入签名流程函数中，但会导致错误的签名结果使得验签流程无法通过。  
为解决这个问题，需要首先进行decode，随后使用ast.literal_eval进行处理还原，还原后可得到正确的签名结果。  
 ```python
 P = client_socket.recv(1024).decode()
 P = ast.literal_eval(P)
  ```
  ### 运算过程中的问题
  在域上做运算时由于数值过大溢出了python整型支持的范围。
  为解决这个问题，需要在对应可能发生溢出的地方先对变量使用gmpy2.mpz处理。
  ```python
  def Gen_Sig(d1, k1, s2,s3,r):
    d1=gmpy2.mpz(d1)
    k1 = gmpy2.mpz(k1)
    s2 = gmpy2.mpz(s2)
    s3 = gmpy2.mpz(s3)
    r = gmpy2.mpz(r)
    s = (d1*k1*s2+d1*s3-r)%N
    r=int(r)
    s=int(s)
    if s!=0 or s!=N-r:
        return (r,s)
    else:
        return None
```
## 完整运行结果
签名参与者2作为服务器端，参与者1作为客户端完成签名流程，故先执行[Sign_P2.py](https://github.com/Dianyudengdeng/homework-group-113/blob/main/Project15/Sign_P2.py)程序后执行[Sign_P1.py](https://github.com/Dianyudengdeng/homework-group-113/blob/main/Project15/Sign_P1.py)程序。  
### 参与者1：  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/f1980dff-0024-4746-945f-735fc9a5be9e)  
### 参与者2：  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/1d16dbb0-0f4a-4854-a83f-7c0613ff2959)  


