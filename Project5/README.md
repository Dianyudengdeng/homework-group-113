Impl Merkle Tree following RFC6962  
主要做的工作：根据RFC6962对于Merkle Tree的设计，实现了Merkle Tree的构建，利用Merkle Audit Paths实现Inclusion proof for specified element和Inclusion proof for specified element;实现Merkle Consistency Proofs；测试程序在进行Inclusion Proof时的效率。   
不同于普遍的Merkle Tree设计从叶子结点开始两两组合生成Merkle Root，RFC6962要求构建从Root开始递归构建二叉树  
