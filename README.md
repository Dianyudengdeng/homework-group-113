# homework-group-113
实验环境：CPU：11th Gen Intel(R) Core(TM) i7-11800H @ 2.30GHz   2.30 GHz
Project1：
Project2：
Project3：
Project4：do your best to optimize SM3 implementation (software)
由于哈希函数受输入长度的影响较大，这里使用测试的都是<56bytes的输入。
Openssl：
hash单分组：0.0037 毫秒
软件实现优化：省略了T和W_1的初始化
hash单分组： 0.0005 毫秒 hash16个不同input：0.0049 毫秒
SIMD优化：使用SIMD指令集优化迭代压缩CF函数，使得一次执行可以同时处理16个互不影响的message_buffer的输入。尽管当前还不能很好适配输入长度不同的情况，但是核心对于CF的优化已经实现，对于需要处理大量输入的情况已经可以起到优化的效果，测试环境中较未使用SIMD指令集的hash操作实现效率提升了一倍多。
hash16个不同input：0.0022 毫秒
