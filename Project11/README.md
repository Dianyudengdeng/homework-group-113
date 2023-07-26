Project11: impl sm2 with RFC6979  
主要做的工作：结合RFC6979完成sm2的python实现。  

RFC6979：Deterministic Usage of the Digital Signature Algorithm (DSA) and Elliptic Curve Digital Signature Algorithm (ECDSA)定义了一种基于HMAC的确定性随机数生成算法，通过使用哈希函数和HMAC来计算签名所需的随机数k，这种算法保证在相同的私钥和消息输入情况下，每次生成的随机数k都是确定性的，从而消除了传统随机数生成器可能导致的安全问题。  
确定性生成方式：k=SHA256(d+HASH(msg)),其中d是私钥，msg是消息，HASH选用sm3。    
