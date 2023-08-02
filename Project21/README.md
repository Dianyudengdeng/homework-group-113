# Project21: Schnorr Batch
**主要做的工作**：实现对于schnorr签名得批量验证；利用批量验证漏洞伪造签名；改进批量验证代码
***
## 实验说明
实验基于Project12实现的Schnorr签名算法。
### 改进后的Batch Vertification
```python
def Batch_verify_pro(public_key, message, signature,num):  
    s = signature[0][1]  
    R = signature[0][0]  
    e = int(sm3.sm3_hash(func.bytes_to_list(bytes(str(signature[0][0]) + message[0], encoding='utf-8'))),16)  
    ep = point_multiply(e, public_key[0])  
    for i in range(1,num):  
        a = secrets.randbelow(100)  
        R = point_add(R,point_multiply(a,signature[i][0]))  
        s = (s+a*signature[i][1])%N  
        e = int(sm3.sm3_hash(func.bytes_to_list(bytes(str(signature[i][0])+message[i], encoding='utf-8'))),16)  
        ep = point_add(ep,point_multiply(a*e,public_key[i]))  
  
    sG = point_multiply(s,G)  
    R_ep = point_add(R,ep)  
    return sG == R_ep
   ```
## 运行结果
### Batch Vertification
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/c950cd49-1f38-45d9-bc6a-762beeed1a61)

### Forge Signature
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/5b92ea37-5c5e-447d-a9ef-7b62ff7600da)
### Batch Vertification Pro
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/9a98d2ca-6bf9-44ee-9188-e7f28798005c)
