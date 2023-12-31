# Project22: research report on MPT

## MPT概述

Merkle Patricia Tree（又称为Merkle Patricia Trie）是一种经过改良的、融合了默克尔树和前缀树两种树结构优点的数据结构，是以太坊中用来组织管理账户数据、生成交易集合哈希的重要数据结构。
MPT树有以下几个作用：
- 存储任意长度的key-value键值对数据；
- 提供了一种快速计算所维护数据集哈希标识的机制；
- 提供了快速状态回滚的机制；
- 提供了一种称为默克尔证明的证明方法，进行轻节点的扩展，实现简单支付验证；
MPT提供了一种结合了字典树与默克尔树两种树结构的特点与优势的树结构。


## 字典树（Trie）
Trie又称前缀树或字典树，是一种有序多叉树。
### 应用场景
- 单词频次统计。
- 字符串匹配。
- 字符串字典序排序。
- 前缀匹配，比如一些搜索框的自动提示。
### 优势
- 插入和查询的效率都很高，都是O(m)，m是插入或查询字符串的长度。
- 可以对数据按照字典序排序。
- 相比于哈希表，在前缀树不会存在哈希冲突的问题。
### 劣势
- 直接查找效率低下
前缀树的查找效率是O(m)，m为所查找节点的key长度，而哈希表的查找效率为O(1)。且一次查找会有m次IO开销，相比于直接查找，无论是速率、还是对磁盘的压力都比较大。

- 可能会造成空间浪费
当存在一个节点，其key值内容很长（如一串很长的字符串），当树中没有与他相同前缀的分支时，为了存储该节点，需要创建许多非叶子节点来构建根节点到该节点间的路径，造成了存储空间的浪费。
## Merkle Tree
### 应用场景
在比特币网络中，merkle树被用来归纳一个区块中的所有交易，同时生成整个交易集合的数字指纹。
### 优势
- 可以高效安全的验证数据结构的内容。
### 劣势
- 存储空间开销大

## MPT结构
### 节点分类
MPT树中，树节点可以分为以下四类：

- 空节点（Hash Node）
- 分支节点（Branch Node）
- 叶子节点（Leaf Node）
- 扩展节点（Extension Node）

### key值编码
在以太坊中，MPT树的key值共有三种不同的编码方式，以满足不同场景的不同需求，在这里单独作为一节进行介绍。

三种编码方式分别为：

- 1.  Raw编码（原生的字符）；
- 2.  Hex编码（扩展的16进制编码）；
- 3.  Hex-Prefix编码（16进制前缀编码）；

###  MPT的改进

以上介绍的MPT树，可以用来存储内容为任何长度的key-value数据项。倘若数据项的key长度没有限制时，当树中维护的数据量较大时，仍然会造成整棵树的深度变得越来越深，会造成以下影响：

- 查询一个节点可能会需要许多次IO读取，效率低下；
- 系统易遭受Dos攻击，攻击者可以通过在合约中存储特定的数据，“构造”一棵拥有一条很长路径的树，然后不断地调用SLOAD指令读取该树节点的内容，造成系统执行效率极度下降；
- 所有的key其实是一种明文的形式进行存储；
为了解决以上问题，在以太坊中对MPT再进行了一次封装，对数据项的key进行了一次哈希计算，因此最终作为参数传入到MPT接口的数据项其实是(sha3(key), value)

#### 优势：

传入MPT接口的key是固定长度的（32字节），可以避免出现树中出现长度很长的路径；
#### 劣势：

每次树操作需要增加一次哈希计算；
需要在数据库中存储额外的sha3(key)与key之间的对应关系；

## MPT基本操作
### Get
将需要查找Key的Raw编码转换成Hex编码，得到的内容称之为搜索路径；
从根节点开始搜寻与搜索路径内容一致的路径；
- 若当前节点为叶子节点，存储的内容是数据项的内容，且搜索路径的内容与叶子节点的key一致，则表示找到该节点；反之则表示该节点在树中不存在。
- 若当前节点为扩展节点，且存储的内容是哈希索引，则利用哈希索引从数据库中加载该节点，再将搜索路径作为参数，对新解析出来的节点递归地调用查找函数。
- 若当前节点为扩展节点，存储的内容是另外一个节点的引用，且当前节点的key是搜索路径的前缀，则将搜索路径减去当前节点的key，将剩余的搜索路径作为参数，对其子节点递归地调用查找函数；若当前节点的key不是搜索路径的前缀，表示该节点在树中不存在。
- 若当前节点为分支节点，若搜索路径为空，则返回分支节点的存储内容；反之利用搜索路径的第一个字节选择分支节点的孩子节点，将剩余的搜索路径作为参数递归地调用查找函数。

### Insert
插入操作也是基于查找过程完成的，一个插入过程为：

- 根据4.1中描述的查找步骤，首先找到与新插入节点拥有最长相同路径前缀的节点，记为Node；
- 若该Node为分支节点：
剩余的搜索路径不为空，则将新节点作为一个叶子节点插入到对应的孩子列表中；
剩余的搜索路径为空（完全匹配），则将新节点的内容存储在分支节点的第17个孩子节点项中（Value）；
- 若该节点为叶子／扩展节点：
剩余的搜索路径与当前节点的key一致，则把当前节点Val更新即可；
剩余的搜索路径与当前节点的key不完全一致，则将叶子／扩展节点的孩子节点替换成分支节点，将新节点与当前节点key的共同前缀作为当前节点的key，将新节点与当前节点的孩子节点作为两个孩子插入到分支节点的孩子列表中，同时当前节点转换成了一个扩展节点（若新节点与当前节点没有共同前缀，则直接用生成的分支节点替换当前节点）；

### Delete
删除操作与插入操作类似，都需要借助查找过程完成，一次删除过程为：

根据4.1中描述的查找步骤，找到与需要插入的节点拥有最长相同路径前缀的节点，记为Node；
- 若Node为叶子／扩展节点：
若剩余的搜索路径与node的Key完全一致，则将整个node删除；
若剩余的搜索路径与node的key不匹配，则表示需要删除的节点不存于树中，删除失败；
若node的key是剩余搜索路径的前缀，则对该节点的Val做递归的删除调用；
- 若Node为分支节点：
删除孩子列表中相应下标标志的节点；
删除结束，若Node的孩子个数只剩下一个，那么将分支节点替换成一个叶子／扩展节点；
- 若删除成功，则将被修改节点的dirty标志置为true，hash标志置空（之前的结果已经不可能用），且将节点的诞生标记更新为现在；
### Update
更新操作就是4.2Insert与4.3Delete的结合。当用户调用Update函数时，若value不为空，则隐式地转为调用Insert；若value为空，则隐式地转为调用Delete。

## 参考文献
1.[Merkle Patricia Tree 详解_merkle patricia trie_跨链技术践行者的博客-CSDN博客](https://blog.csdn.net/shangsongwww/article/details/88884627)
