# Project3：Length extension attack for SM3, SHA256
**主要做的工作**:修改Hash的主体算法，使得迭代压缩中可以利用已有的哈希值生成新的有效哈希对；编写独立的padding函数，直接获得哈希结果以验证长度扩展攻击效果。  

## 实验说明
这里使用了Project4的SM3实现以及参考了别人的SHA256实现，对于SM3和SHA256的长度扩展攻击设计了不同的攻击场景
### SM3：
**攻击场景**:服务器在生成哈希时，在用户输入前加入secret信息使得攻击者无法在未知secret内容的前提下生成input对应的H(input)；  
通过长度扩展攻击，攻击者在知道一个input、H(secret||input)、以及secret长度的前提下，可以在不知道secret内容的情况下伪造一个M'=secret||input||padding||append以及对应的H(M')  
### SHA256：
**攻击场景**:secret内容未知，但已知H(M)、M的长度  
通过长度扩展攻击，攻击者可以在不知道secret内容的情况下伪造一个M'=M||padding||append以及对应的H(M')


## 运行结果
### SM3：
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/e0349905-6268-4e51-8335-6de1a80aace7)
### SHA256：
![image](https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/335c48ee-2c3a-43aa-81fd-f40a1e768268)

**通过长度扩展攻击，生成有效哈希对以实现进一步攻击。*
