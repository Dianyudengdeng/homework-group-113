# Project19:Forge a signature to pretend that you are Satoshi
**主要做的工作**：实现根据公钥伪造ECDSA签名的代码；修改ECDSA验签函数，使其符合伪造签名攻击场景需要
***
## 实验原理
伪造ECDSA签名利用了验签过程中只使用了Hash值进行验签，从而使得在根据公钥随机生成签名对后，可以计算得到对应的H（m）。
本质上这一漏洞的原因在于舍弃了Hash函数的单向性，若验签过程中仍保留对于明文m的Hash，则攻击者无法在未破解Hash函数抗原像特性的前提下得到伪造签名对对应的m。
## 实验说明
实验基于Project12实现的ECDSA签名算法，同时修改了验签算法，由传入m改为了传入e = H（m）。
### 代码实现
```python
def forge_signature(public_key):  
    u = secrets.randbelow(N)  
    v = secrets.randbelow(N)  
    R_1 = point_add(point_multiply(u,G),point_multiply(v,public_key))  
    # Choose (r_1 = x_1 mode n)  
  r_1 = R_1[0]  
    e_1 = r_1*u*mod_inverse(v,N)%N  
    s_1 = r_1 *mod_inverse(v,N)%N  
    return e_1,(r_1,s_1)
```
## 运行结果
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/dbe7384f-cf5f-49e1-b27b-818094767ed5)

可根据公钥生成可通过验签的 e - (r,s)对。
