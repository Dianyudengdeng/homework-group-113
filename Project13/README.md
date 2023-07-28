# Project13: Implement the above ECMH scheme  
### 主要做的工作：阅读ECMH相关文献，实现Shallue-van de Woestijne (SW) 方法,将任意字节串哈希到椭圆曲线上。  
#### 参考文献:"Hashing to Elliptic Curves" 、"Hashing to the secp256k1 Elliptic Curve"  
可以看到，hash_to_curve由以下部分组成：  
<img width="505" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/fd2ec4ae-bd78-40b0-87f3-45830c194c06">

hash_to_field:使用expand_message_xmd实现  
<img width="450" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/2d0958c4-faea-49ff-bfd0-a7f255ca4b74"> 
<img width="400" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/b61ff2c8-7976-4af8-85c9-004951a5144e">

综合比较Shallue-van de Woestijne (SW) 方法与Simplified SWU 方法，最终选择普通的Shallue-van de Woestijne (SW) 方法，椭圆曲线参数取secp256k1。 
算法流程：  
<img width="415" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/a85fb66b-7aad-4405-a365-3e88fa096843">    
使用给出的Sage程序求解椭圆曲线点Z：  
<img width="415" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/d9157a71-9f8a-4c27-85ef-7f49d0051bbb">  
 
