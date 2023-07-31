# Project16: implement sm2 2P decrypt with real network communication  
**主要做的工作**：实现sm2加密算法；实现sm2 2P decrypt解密算法；模拟实际网络环境进行交互   
***
## 实验原理
### sm2 2P decrypt解密算法：  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/ea2b67f3-57ab-4f43-a070-72e728f65841)

参考文献进行实现，可正常完成解密工作。  
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/4a994ce9-c741-463c-ab0f-3f6a298d3920)  
## 实验说明
### 解密过程中的问题：  
主要问题在于因为传输/输出需要而带来的数据格式问题，比如在加密端的XOR处理的M为普通的明文字符串，可直接按照字符串进行迭代：  
```python
def XOR_enc(m, t):
    m = bytes(m, encoding='utf-8')
    m = func.bytes_to_list(m)  # each element -> 8-bit
    n = len(m)  # n bytes
    ans = []
    for i in range(n):
        m_1 = m[i]
        t_1 = int(t[8 * i:8 * (i + 1)], 2)
        a = (hex(m_1 ^ t_1)[2:]).rjust(2, '0')
        ans.append(a)
    A = ''.join(ans)
    # length of A is klen/4
    return A
```

而解密端的XOR处理的C2则为由两个十六进制数为一组构成的字符串，需要采取不同的迭代方式：  
```python
def XOR_dec(C2, t):

    n = len(C2) // 2
    ans = []
    for i in range(n):
        c2c2 = int(C2[2 * i:2 * (i + 1)], 16)  # -> int
        tt = int(t[8 * i:8 * (i + 1)], 2)
        ans.append(chr(c2c2 ^ tt))
    A = ''.join(ans)
    return A
  ```

## 完整运行结果：
签名参与者2作为服务器端，参与者1作为客户端完成解密流程，故先执行[decrypt_P2.py](https://github.com/Dianyudengdeng/homework-group-113/blob/main/Project16/decrypt_P2.py)程序后执行[decrypt_P1.py](https://github.com/Dianyudengdeng/homework-group-113/blob/main/Project16/decrypt_P1.py)程序。  

### 参与者1：
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/131e312b-11f2-458c-aac8-a3085d5add15)


### 参与者2：
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/d274b3a0-a010-4142-9829-a1d186b32b96)



