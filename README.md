# 创新创业实践作业
## 说明
### 个人完成：
- 姓名：胡达
- 年级：2021级
- 学号：302100460030
- 本仓库包含已经完成的全部Project，以及对应的实验报告

### 实验环境：
CPU：11th Gen Intel(R) Core(TM) i7-11800H @ 2.30GHz
## 已经实现
### SM3
#### Project1: implement the naïve birthday attack of reduced SM3
主要工作：
- 修改Project4 SM3的实现方式，提供利于攻击的API以及避免多线程加速时出现混乱
- 完成各类数据结构相互转换的工作，实施基础的生日攻击

实验结果：经过约五万次哈希在一秒内找到了前32bits的碰撞

#### Project2: implement the Rho method of reduced SM3
主要工作：
- 实现Rho Method寻找SM3碰撞的代码
- 修改Rho Method寻找SM3的部分字节碰撞
- 优化加速寻找碰撞；分析不同迭代方法的区别

实验结果：经过约两万次哈希在一秒内找到了前32bits的碰撞

#### Project3: implement length extension attack for -  SM3, SHA256, etc.
主要工作：
- 修改Hash的主体算法，使得迭代压缩中可以利用已有的哈希值生成新的有效哈希对
- 编写独立的padding函数，直接获得哈希结果以验证长度扩展攻击效果

实验结果：实现了在不同攻击场景下的长度扩展攻击

#### Project4: do your best to optimize SM3 implementation (software)
主要工作：
- 实现SM3哈希函数
- 使用SIMD指令集进行优化
- 效率测试，数据分析

实验结果：
- openssl实现：3.7纳秒/分组
- SM3软件实现：0.3纳秒/分组，较openssl实现提升12.3倍
- SIMD指令集优化：0.13ns/分组，较openssl实现提升28.4倍

#### Project5: Impl Merkle Tree following RFC6962
主要工作：
- 根据RFC6962对于Merkle Tree的设计，实现了Merkle Tree的构建
- 利用Merkle Audit Paths实现Inclusion proof for specified element和Inclusion proof for specified element;实现Merkle Consistency Proofs
- 测试程序在进行Inclusion Proof时的效率

实验结果：可正常实现树的构建；由于Merkle Rree - InclusionProof的时间复杂度为O(log n)，所以在结点数量差异较大的情况下，尽管可以直观感受到树构建过程的时间差异，InclusionProof的时间开销并没有较大的差异。

#### Project6: impl this protocol with actual network communication
主要工作：
- 实现基础的对于年龄的Range Proof
- 模拟实际网络环境，进行数据传输，实现可信第三方、证明者、验证者的交互

实验结果：Bob最终得到了与可信第三方计算的相同的validity_period + c，顺利地通过了验证 [link](https://github.com/Dianyudengdeng/homework-group-113/blob/main/Project6/README.md)


### SM4
#### Project9: AES / SM4 software implementation
 主要工作：
- AES普通实现与查找表实现并测试效率
- SM4普通实现，查找表实现，AES-NI+SIMD指令集加速实现
- 各实现方式效率测试，数据分析   

实验结果：
**SM4**：
各版本加密效率对比：    
<img width="875" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/26bf1b6a-6e05-4254-a387-03147c15f5ac">  
最终SM4的加密效率位60ns/Block

#### Project10: report on the application of this deduce technique in Ethereum with ECDSA

### SM2
#### Project11: impl sm2 with RFC6979
主要工作：
- 实现RFC6979规定的生成确定性的随机数k的算法，使用该算法生成SM2签名所需的随机数
- 实现SM2签名算法  
实验结果：实现了SM2签名以及验签的流程，具体可参照代码及文献给出的流程。 
<img width="597" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/b0c54d92-028f-45cc-94ff-f951d734b37a">

#### Project12: verify the above pitfalls with proof-of-concept code
主要工作：
- 实现ECDSA，Schnorr，SM2签名，验签算法
- 提供以下漏洞的概念验证代码  
1.Leaking k leads to leaking of d: ECDSA、Schnorr、SM2-sig  
2.Reusing k leads to leaking of d: ECDSA、Schnorr、SM2-sig  
3.Reusing k by different users leads to leaking of d: ECDSA、Schnorr、SM2-sig  
4.(r,s) and (r,-s)are both valid signatures: ECDSA、Schnorr  
5.Same d and k with ECDSA, leads to leaking of d: Schnorr、SM2-sig  
实验结果：[link](https://github.com/Dianyudengdeng/homework-group-113/blob/main/Project12/README.md)

#### Project13: Implement the above ECMH scheme
主要工作：
- 阅读ECMH相关文献，实现Shallue-van de Woestijne (SW) 方法,将任意字节串哈希到椭圆曲线上

#### Project14: Implement a PGP scheme with SM2
主要工作：
- 使用gmssl库提供的SM2，SM4实现PGP方案
- 使用gmssl提供的接口完成SM2密钥对生成

实验结果：[link](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/49d6129b-8a0b-436d-950b-708cd5dea591)

#### Project15: implement sm2 2P sign with real network communication
主要工作：
- 实现sm2 2P sign签名算法
- 模拟实际网络环境进行交互

实验结果：
参与者1：[P1](https://user-images.githubusercontent.com/93588357/256998041-f1980dff-0024-4746-945f-735fc9a5be9e.png)
参与者2：[P2](https://user-images.githubusercontent.com/93588357/256998050-1d16dbb0-0f4a-4854-a83f-7c0613ff2959.png)
#### Project16: implement sm2 2P decrypt with real network communication
主要工作：
- 实现sm2加密算法
- 实现sm2 2P decrypt解密算法
- 模拟实际网络环境进行交互

实验结果：
参与者1：[P1](https://user-images.githubusercontent.com/93588357/257146874-131e312b-11f2-458c-aac8-a3085d5add15.png)
参与者2：[P2](https://user-images.githubusercontent.com/93588357/257146819-d274b3a0-a010-4142-9829-a1d186b32b96.png)
### Bitcon
#### Project19: forge a signature to pretend that you are Satoshi
主要工作：
- 实现根据公钥伪造ECDSA签名的代码
- 修改ECDSA验签函数，使其符合伪造签名攻击场景需要

实验结果：
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/dbe7384f-cf5f-49e1-b27b-818094767ed5)

#### Project21: Schnorr Bacth
主要工作：
- 实现对于schnorr签名的批量验证
- 利用批量验证漏洞伪造签名
- 改进批量验证代码以抵抗攻击

实验结果：[link](https://github.com/Dianyudengdeng/homework-group-113/blob/main/Project21/README.md)
### Eth
#### Project22: research report on MPT
## 部分实现
#### Project8: AES impl with ARM instruction
主要工作：
- 测试AES-NI加密效率
- 测试Openssl 加密效率

实验结果：[link](https://github.com/Dianyudengdeng/homework-group-113/blob/main/Project8/README.md)
## 未完成
- Project7: Try to Implement this scheme
- Project17：比较Firefox和谷歌的记住密码插件的实现区别
- Project18: send a tx on Bitcoin testnet, and parse the tx data down to every bit, better write script yourself
