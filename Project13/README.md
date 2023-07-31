# Project13: Implement the above ECMH scheme  
**主要做的工作**：阅读ECMH相关文献，实现Shallue-van de Woestijne (SW) 方法,将任意字节串哈希到椭圆曲线上。
***
## 实验说明  
**参考文献**:[Hashing to Elliptic Curves](https://www.ietf.org/archive/id/draft-irtf-cfrg-hash-to-curve-16.html#straightline-svdw)、[Hashing to the secp256k1 Elliptic Curve]()  
### hash_to_curve：  
<img width="505" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/fd2ec4ae-bd78-40b0-87f3-45830c194c06">

### hash_to_field:
使用expand_message_xmd实现 ：
#### 算法流程：
<img width="450" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/2d0958c4-faea-49ff-bfd0-a7f255ca4b74">  

#### 算法实现：
```python
def expand_message_xmd(msg, DST, len_in_bytes):
    # Step 1: Calculate ell
    b_in_bytes = 32  # 假设 b = 256，即 SHA-256 输出大小为 32 字节
    ell = (len_in_bytes + b_in_bytes - 1) // b_in_bytes

    # Step 2: Check conditions
    if ell > 255 or len_in_bytes > 65535 or len(DST) > 255:
        raise ValueError("Invalid parameters: ell > 255 or len_in_bytes > 65535 or len(DST) > 255")

    # Step 3: Calculate DST_prime
    I2OSP_DST = len(DST).to_bytes(1, 'big')
    DST_prime = DST + I2OSP_DST

    # Step 4: Calculate Z_pad
    s_in_bytes = 64  # 假设使用 SHA-256，输入块大小为 64 字节
    Z_pad = b'\x00' * s_in_bytes

    # Step 5: Calculate l_i_b_str
    l_i_b_str = len_in_bytes.to_bytes(2, 'big')

    # Step 6: Construct msg_prime
    msg_prime = Z_pad + msg + l_i_b_str + b'\x00' + DST_prime

    # Step 7: Calculate b_0
    b_0 = hashlib.sha256(msg_prime).digest()

    # Step 8: Calculate b_1
    b_1 = hashlib.sha256(b_0 + b'\x01' + DST_prime).digest()

    # Steps 9-10: Calculate b_i for i in (2, ..., ell)
    uniform_bytes = b_1
    for i in range(2, ell + 1):
        b_i = hashlib.sha256(bytes([a ^ b for a, b in zip(b_0, uniform_bytes)]) + bytes([i]) + DST_prime).digest()
        uniform_bytes += b_i

    # Step 12: Return the first len_in_bytes bytes of uniform_bytes
    return uniform_bytes[:len_in_bytes]
```

### Shallue-van de Woestijne (SW) 方法：
综合比较Shallue-van de Woestijne (SW) 方法与Simplified SWU 方法，最终选择普通的Shallue-van de Woestijne (SW) 方法，椭圆曲线参数取secp256k1。   
#### 算法流程：  
<img width="415" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/a85fb66b-7aad-4405-a365-3e88fa096843">    

#### 求解曲线点Z：  
<img width="415" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/d9157a71-9f8a-4c27-85ef-7f49d0051bbb">  

 #### 算法实现：
 ```python
 def map_to_curve_svdw(u, F, A, B, Z):
    # Constants
    c1 = F(Z)
    c2 = -Z / 2
    c3_positive, c3_negative = sqrt(-c1 * (3 * Z ** 2 + 4 * A), F)
    if c3_positive is not None and sgn0(c3_positive) == 0:
        c3 = c3_positive
    elif c3_negative is not None and sgn0(c3_negative) == 0:
        c3 = c3_negative
    else:
        raise ValueError("No valid c3 found.")
    c4 = -4 * c1 / (3 * Z**2 + 4 * A)
    c2 = Rational(c2)
    c4 = Rational(c4)
    tv1 = u**2
    tv1 = tv1 * c1
    tv2 = 1 + tv1
    tv1 = 1 - tv1
    tv3 = tv1 * tv2
    tv3 = inv0(tv3,F)
    tv4 = u * tv1
    tv4 = tv4 * tv3
    tv4 = tv4 * c3
    x1 = c2 - tv4
    # Step 11
    gx1 = x1**2
    gx1 = gx1 + A
    gx1 = gx1 * x1
    gx1 = gx1 + B
    e1 = is_square(gx1,F)
    x2 = c2 + tv4
    gx2 = x2**2
    gx2 = gx2 + A

    gx2 = gx2 * x2
    gx2 = gx2 + B
    e2 = is_square(gx2,F) and not e1
    x3 = tv2**2
    x3 = x3 * tv3
    x3 = x3**2
    x3 = x3 * c4
    x3 = x3 + Z
    x = CMOV(x3, x1, e1, F)
    x = CMOV(x, x2, e2, F)
    gx = x**2
    gx = gx + A
    gx = gx * x
    gx = gx + B
    y = sqrt(gx,F)
    e3 = sgn0(u) == sgn0(y)
    y = CMOV(-y, y, e3, F)
    return (x, y)
```
获得Q0、Q1后，最终使用使用点加计算R = Q0 + Q1获得msg在椭圆曲线上最终的对应点。  
