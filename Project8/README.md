Project8:AES impl with ARM instruction  
主要做的工作：测试AES-NI加密效率；测试Openssl 加密效率  
注：这个Project并没有完成，由于使用ARM指令实现AES加密需要ARM架构的设备，计划使用qemu在x86主机安装ARM64架构的虚拟机以提供运行环境。 
  
测试结果：（ECB模式，160bytes明文）  
AES-NI:  
<img width="313" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/a6cecbf1-25aa-44e0-ad34-66eccba69df8">  
<img width="156" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/62fd2e78-6cc4-46d3-bdfe-9ce576b90a03">  
  
AES-Openssl:  


