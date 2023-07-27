Project12: verify the above pitfalls with proof-of-concept code  
主要做的工作：提供以下漏洞的概念验证代码  
1.Leaking k leads to leaking of d: ECDSA、Schnorr、SM2-sig  
2.Reusing k leads to leaking of d: ECDSA、Schnorr、SM2-sig  
3.Reusing k by different users leads to leaking of d: ECDSA、Schnorr、SM2-sig  
4.(r,s) and (r,-s)are both valid signatures: ECDSA、Schnorr  
5.Same d and k with ECDSA, leads to leaking of d: Schnorr、SM2-sig  
<img width="581" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/d3e30eb3-0298-44d8-91aa-71435090b75f">
  
由于前四项不涉及不同的密码算法间的交互，故均存储在单独的文件中完成：  
SM2.pitfalls：  


ECDSA.pitfalls:  

Schnorr.pitfalls:
