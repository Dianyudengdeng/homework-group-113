Impl Merkle Tree following RFC6962  
主要做的工作：根据RFC6962对于Merkle Tree的设计，实现了Merkle Tree的构建，利用Merkle Audit Paths实现Inclusion proof for specified element和Inclusion proof for specified element;实现Merkle Consistency Proofs；测试程序在进行Inclusion Proof时的效率。   
不同于普遍的Merkle Tree设计从叶子结点开始两两组合生成Merkle Root，RFC6962要求构建从Root开始递归构建二叉树  
<img width="449" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/450525be-db20-43b5-af64-21e92c02819a">  
例如添加五个结点：  
<img width="295" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/8641d4d4-c5c5-419d-9dfd-5ff1b99fbc16">
<img width="723" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/13ba8d8a-2fc0-4a86-b45a-ddb7e7ee8763">  
从计算hash值的过程中可以看出构建的树结构是相同的。  
在生成树的过程中，使用散列表MTH以存储内部结点的Hash值，注意这里为了演示存储了叶子结点的Hash值，实际运行中并不会存储。因为在进行Inclusion/Exclusion proof证明时，只会用到已经获取的叶子结点的Hash值，所以并不会产生影响。  
根据RFC6962，调整索引设计得到的的Audit Path与Subproof：  
<img width="571" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/d4393030-0374-42c1-9050-2431f111653c">
<img width="545" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/d1da97d9-9b0c-4104-a835-bcf1c9d86a62">  
而后的Inclusion/Exclusion proof都是基于Audit Path计算根节点索引值与MerkleRoot得到的结果相比进行判断。    
添加十万个结点后进行InclusionProof：  
<img width="628" alt="image" src="https://github.com/Dianyudengdeng/homework-group-113/assets/93588357/9ffedc59-5ac6-4a0b-8750-174cb1867d1a">

