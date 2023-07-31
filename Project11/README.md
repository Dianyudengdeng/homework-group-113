# Project11: impl sm2 with RFC6979  
**主要做的工作**：实现RFC6979规定的生成确定性的随机数k的算法，使用该算法生成SM2签名所需的随机数；实现SM2签名算法  
***
## 实验说明
结合Project要求以及PPT上下文，RFC 6979 给出的 k 的生成方法是针对签名方案的，用于提高签名的安全性，故本Project应当需要实现的是SM2签名算法而不是加密算法。  
  
### RFC6979：
Deterministic Usage of the Digital Signature Algorithm (DSA) and Elliptic Curve Digital Signature Algorithm (ECDSA)定义了一种基于HMAC的**确定性随机数生成算法**，通过使用哈希函数和HMAC来计算签名所需的随机数k，这种算法保证在相同的私钥和消息输入情况下，每次生成的随机数k都是确定性的，从而消除了传统随机数生成器可能导致的安全问题。  
#### 确定性生成方式：  
```python
def generate_k(msg, private_key, q, q_bits=256, hash_function=hashlib.sha256):  
	  hlen = hash_function().digest_size * 8  
	  qlen = math.ceil(q_bits / 8) * 8  
	  
	  h1 = hash_function(msg.encode()).digest()  

	  V = b'\x01' * math.ceil(hlen / 8)  

	  K = b'\x00' * math.ceil(hlen / 8)  
	  
	  K = hmac.new(K, V + b'\x00' + private_key.to_bytes(math.ceil(q_bits / 8), byteorder='big') + h1, hash_function).digest()  

	  V = hmac.new(K, V, hash_function).digest()  

	  K = hmac.new(K, V + b'\x01' + private_key.to_bytes(math.ceil(q_bits / 8), byteorder='big') + h1, hash_function).digest()  
	  
	  V = hmac.new(K, V, hash_function).digest()  
	  
	  T = b''  
	  tlen = 0  
  
	  while tlen < qlen:  
	        V = hmac.new(K, V, hash_function).digest()  
	        T = T + V  
	  
	        tlen = len(T) * 8  
	        k = bits2int(int.from_bytes(T, byteorder='big'), qlen)  
	  
	        if 1 <= k < q - 1:  
	            return k  
	  
	        K = hmac.new(K, V + b'\x00', hash_function).digest()  
	        V = hmac.new(K, V, hash_function).digest()  
	  
	   raise ValueError("Failed to generate a valid k value.")
```
依照给定的流程进行实现，对于bits2int(bits, qlen)、bits2octets(bits, mlen)函数，实现中因为 bits 参数的值过大，超出了整数类型所能表示的范围，导致无法将其转换为相应长度的字节序列，触发了 OverflowError: cannot fit 'int' into an index-sized integer 错误。  
通过使用 gmpy2 等库来替代 Python 原生的整数类型，以处理超出标准整数范围的大整数，解决了这一问题：  
```python
def bits2octets(bits, mlen):
    full_bytes = bits // 8
    extra_bits = bits % 8
    if extra_bits > 0:
        full_bytes += 1
    padding_bytes = mlen - full_bytes
    # 使用 gmpy2 进行大整数转换
    bits_bigint = gmpy2.mpz(bits)
    return b'\x00' * padding_bytes + gmpy2.digits(bits_bigint, 256)

def bits2int(bits, qlen):
    q = 1 << qlen
    # 使用 gmpy2 进行大整数转换
    bits_bigint = gmpy2.mpz(bits)
    return gmpy2.f_mod(bits_bigint, q)
 ```
[tools.py](https://github.com/Dianyudengdeng/homework-group-113/blob/main/Project11/tools.py)文件实现了SM2签名过程中使用的数论计算及其他操作，共包含以下函数：  
```python
get_bit_num(x) #获得任意结构数据的二进制长度  
extended_euclidean(j, k) #拓展欧几里得算法  
mod_inverse(j, n) #模逆算法  
point_add (p, q) #椭圆曲线点加  
point_double(p) #椭圆曲线倍乘  
point_multiply(s, p) #椭圆曲线点乘  
generate_key() #随机生成密钥对  
```
[SM2 Signature.py](https://github.com/Dianyudengdeng/homework-group-113/blob/main/Project11/SM2%20Signature.py)实现了SM2签名以及验签的流程，具体可参照代码及文献给出的流程。  


## 运行结果
<img width="597" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/b0c54d92-028f-45cc-94ff-f951d734b37a">


## 运行结果
<img width="597" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/b0c54d92-028f-45cc-94ff-f951d734b37a">
