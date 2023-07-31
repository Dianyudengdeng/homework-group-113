# Project8:AES impl with ARM instruction  
**主要做的工作**：测试AES-NI加密效率；测试Openssl 加密效率  
注：这个Project并没有完成，由于使用ARM指令实现AES加密需要ARM架构的设备，计划使用qemu在x86主机安装ARM64架构的虚拟机以提供运行环境。 
***  
## 运行结果
**（ECB模式，160bytes明文）**
#### AES-NI:  
```c++
for (int i = 0; i < repetitions; ++i) {
        aes_key_expansion(key, expanded_key);
        aes_encrypt(plaintext, expanded_key, ciphertext, 160);
    }
```
<img width="156" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/62fd2e78-6cc4-46d3-bdfe-9ce576b90a03">  


#### AES-Openssl:  
```c++
 for (int i = 0; i < repetitions; ++i) {
        if (aes_encrypt(plaintext, plaintext_len, key, ciphertext, &encrypted_length) != 1) {
            fprintf(stderr, "AES encryption failed.\n");
            return 1;
        }
    }
```
<img width="158" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/8bbd7477-84b9-40c4-a476-ed4e36e018e1">  

可以看到，运行效率上大致相差了35000倍，充分说明了硬件实现与软件实现间的差距，为后面使用AES-NI指令加速SM4提供了前提。  
