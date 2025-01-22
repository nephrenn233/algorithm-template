# algorithm-template

自用算法竞赛模板，来源于到处抄。目前正在重构中。

附有 LaTeX 生成的 pdf 版本，使用 [ply-template](https://github.com/palayutm/ply-template) 模板生成。

## Feature
0-indexed、区间左闭右开

## 模板目录

### 数据结构 data structure

+ 树状数组 (fenwick_tree.cpp)，支持单点修改、前缀和查询
+ 并查集 (disjoint_set_union.cpp)，支持查询集合、查询集合大小、合并
+ 线段树
    + 区间加，单点改 (segment_tree_1.cpp)
+ 稀疏表 (sparse_table.cpp, with Info)

### 数学 math

+ 组合数 (binom.cpp, with mod_int.cpp)
+ 卢卡斯定理 (lucas.cpp, with binom.cpp)
+ 线性筛素数 (prime_sieve.cpp)
+ 线性求逆元 (1_to_n_inverse.cpp)
+ 线性基 (basis.cpp)

### 字符串 string

+ Manacher 算法 (manacher.cpp)
+ 字符串哈希 (string_hash.cpp)

### 图论 graph theory

### 杂项 various

+ 取模类 (mod_int.cpp)
+ 大整数类 (big_int.cpp)，支持高精加，高精减，高精乘，高精除，高精模
+ 对拍 (duipai.cpp)
+ 快速幂 (quick_pow.cpp)
+ 莫队
    + 普通莫队 (mo.cpp)
+ 分数类 (frac.cpp)