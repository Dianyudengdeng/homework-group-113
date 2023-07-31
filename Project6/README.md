# Project6：Impl this protocol with actual network communication (Range Proof With Hash Function)  
**主要做的工作**：实现基础的对于年龄的Range Proof；模拟实际网络环境，进行数据传输，实现可信第三方、证明者、验证者的交互。
***
## 实验说明
### 实验所需：
[Cryptography.py](https://github.com/Dianyudengdeng/homework-group-113/blob/main/Project6/Cryptography.py) 定义了实现所需的签名、验签、以及哈希函数，哈希函数选用SHA224、SHA256 使用第三方库hashlib与cryptography实现。  
<img width="409" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/3fb9afad-79eb-4b86-beff-172741f45cbf">  
参照这张图完成了Range Proof With Hash Function各参与方对于接受的消息的处理逻辑。  
### 模拟网络环境：
为模拟实际网络环境，实验中使用ssl协议建立了安全的数据通讯连接，通过**证书、签名、加密**等手段保证了数据的安全。
共建立了两条C/S网络连接，服务器端分别为**Trusted_Issure**和**Bob_verifier**，客户端均为**Alice_Prover**,对应实际网络中可信第三放提供证明服务与验证者提供其他服务。
#### 由于网络环境限制做的一些优化：
通过Prover向Verifier提供证明的过程中，将原来传输的内容(p,Sigc),增加为(validity_period,p,Sigc),省去了验证者与可信第三方的连接，以及可信第三方对于相关信息的存储:
***Prover***:
```python
 message=f"{validity_period}||{p}||{sig}"
 ssl_conn_Alice.send(message.encode('utf-8'))  # 将字符串转换为字节串并发送消息
 ```

同时为了保证证明者不会通过修改validity_period对验证者进行欺骗，在可信第三方的签名中额外增加了对validity_period的签名，只有以上信息均正确才能通过检验: 
 ***Trusted Issuer***:
```python
 Sig_message = str(validity_period)+c
 sig=generate_signature(Sig_message,'E:\创新创业Project\Project6 Range Proof With Hash Function\Trusted_Issuer\Trusted_private_key.pem')
```
## 运行结果
### Alice：  
当Alice向Trusted_Issuer申请提供服务并提供相关信息后：  
<img width="722" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/9a5ab471-5695-4c6f-8011-763af82050c8">  
与Bob建立连接提供证明信息后：  
<img width="385" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/dadd2fc8-377d-4e03-92b9-98ac23215768">  
  
这一过程中：  
Trusted_Issuer:  
<img width="726" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/8678dad8-465c-408a-a364-fce20abcede1">  
  
### Bob:  
<img width="424" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/88a7d012-3954-4fb5-a3c0-3bfb550db339">    

通过打印的信息可以看到，Bob最终得到了与可信第三方计算的相同的validity_period + c，顺利地通过了验证。  

## 问题
实验中还遇到了一个问题：  
当bytes类型的签名被编码发送出去再解码后，尽管签名内容没有变，但是签名的数据类型会变成str，而验签的过程中需要传入bytes类型的数据，若编码传入则会改变签名内容导致验证无法通过。  
经过查找资料，最终通过导入ast模块，使用literal_eval函数成功地将签名解析为了字节串而没有改变其内容，通过了验证。    

 ```python
 bytes_sig = ast.literal_eval(sig)
 ```
