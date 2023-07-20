Impl Merkle Tree following RFC6962  
主要做的工作：根据RFC6962对于Merkle Tree的设计，实现了Merkle Tree的构建，利用Merkle Audit Paths实现Inclusion proof for specified element和Inclusion proof for specified element;实现Merkle Consistency Proofs；测试程序在进行Inclusion Proof时的效率。   
不同于普遍的Merkle Tree设计从叶子结点开始两两组合生成Merkle Root，RFC6962要求构建从Root开始递归构建二叉树  
<img width="449" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/450525be-db20-43b5-af64-21e92c02819a">  
例如添加五个结点：  
<img width="95" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/8641d4d4-c5c5-419d-9dfd-5ff1b99fbc16">
<img width="723" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/13ba8d8a-2fc0-4a86-b45a-ddb7e7ee8763">  
从计算hash值的过程中可以看出构建的树结构是相同的。
