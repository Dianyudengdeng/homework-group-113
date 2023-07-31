# Project8:AES impl with ARM instruction  
**主要做的工作**：测试AES-NI加密效率；测试Openssl 加密效率  
注：这个Project并没有完成，由于使用ARM指令实现AES加密需要ARM架构的设备，计划使用qemu在x86主机安装ARM64架构的虚拟机以提供运行环境。 
***  
## 运行结果
**（ECB模式，160bytes明文）**
#### AES-NI:  
<img width="313" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/a6cecbf1-25aa-44e0-ad34-66eccba69df8">  

<img width="156" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/62fd2e78-6cc4-46d3-bdfe-9ce576b90a03">  


#### AES-Openssl:  
<img width="470" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/516186d8-dfe9-4175-bfdd-92c7606140e2">    

<img width="158" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/8bbd7477-84b9-40c4-a476-ed4e36e018e1">  

可以看到，运行效率上大致相差了**35000**倍，充分说明了硬件实现与软件实现间的差距，为后面使用AES-NI指令加速SM4提供了前提。  

