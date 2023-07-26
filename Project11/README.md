Project11: impl sm2 with RFC6979  
主要做的工作：实现RFC6979规定的生成确定性的随机数k的算法，使用该算法生成SM2签名所需的随机数；实现SM2签名算法  
  
RFC6979：Deterministic Usage of the Digital Signature Algorithm (DSA) and Elliptic Curve Digital Signature Algorithm (ECDSA)定义了一种基于HMAC的确定性随机数生成算法，通过使用哈希函数和HMAC来计算签名所需的随机数k，这种算法保证在相同的私钥和消息输入情况下，每次生成的随机数k都是确定性的，从而消除了传统随机数生成器可能导致的安全问题。  
确定性生成方式：  
<img width="445" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/5ecebeee-a5be-4d5c-982c-41c4729d999c">  
<img width="450" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/d7134987-dd5f-40fb-8979-7577259dd766">  
<img width="457" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/71426582-8f2f-41ac-8909-7f7f1618901b">  
