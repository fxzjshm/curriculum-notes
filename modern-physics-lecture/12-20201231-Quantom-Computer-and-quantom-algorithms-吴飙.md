# Quantom Computer and quantom algorithms
## Lessons
### Steven Weinburg: Four Golden Lessons
* 翻译：陈柳
* Nature 426(2003)389
* 没人知道所有的事情，你也无需知道所有事情
  * 必须先开始研究，在研究过程中获取相关的知识
* 游泳时不想被淹死，应该到波涛汹涌的水域去
* 原谅自己浪费时间
* 学习科学史，了解你所做工作的价值

### Frank Wilczek: The power of learning by doing 
* WSJ (Jan. 2017)

### Lessons:
* Don't be afraid of making mistakes
* You don't need to know everything
* Learning by doing

## Introduction to quantum computer 量子计算机简介
### 经典力学与量子力学的区别
* 经典力学：状态是确定的
  * (x, p)
  * 顺时针/逆时针
  * 活猫/死猫
* 量子力学：叠加态：状态不确定
  * 氢原子中的电子
  * $ |\phi> = {1\over\sqrt{2}}(|\uparrow> + |\downarrow>)$
  * $ |\psi> = {1\over\sqrt{2}}(|活猫> + |死猫>)$
* 经典计算机：比特
* 量子计算机：量子比特

### Brief history of Quantom Computer 量子计算机简史
* Concept Mainin(1980), Feynman(1981)
  * 经典计算机模拟量子系统会出现困难
* Theoretical models of quantom computer (Deutsch)
  * Quantom Turing machine (1985)
  * Quantom Circuit (1989)
* Shor's quantom algorithm (1994)  (105=3x5x7)
  * 首个解决实际难题的算法
* First experimental realization of two-qubit gates (1995)
* Primitive quantom conputers
### Concept
* Problem
  * Classical: n paticals $(x_1, x_2, ... ,x_n; p_1, p_2, ... , p_n)$
  * Quantom: 
    * one spin: $ |\uparrow> |\downarrow> $
    * two spins: $ | \uparrow \uparrow >   | \uparrow \downarrow >   | \downarrow \uparrow >   | \downarrow \downarrow > $
    * n spins, $ 2^n $ states
* Classical computer
  * (classical) bit
  * universal gate: NAND gate
* Quantom computer
  * Qubit: $ \alpha |0> + \beta|1> $
  * Quantom gates:
    * Hadamard $ H = {{1}\over{\sqrt{2}}} \begin{pmatrix}  1 & 1 \\  1 & -1 \\  \end{pmatrix} $
    * Phase $ S $
    * $ \pi /8 $
    * CNOT
* Compare:
  * classical: irreversible ?
    * Fredkin Gate is reversible
    * => classical computers **can** be reversible
  * quantom: reversible
  * fundamental differences: Hadamard gate
    * $ H|0> = {{1}\over{\sqrt{2}}} (|0> + |1>) $
    * Hadamard gate + classical states -> quantom states
    * Compare: CNOT gate + classical states -> classical states
  * quantom computer = reversible classical computer + **Hadamard gate** + Phase gates
    * => quantom computer >= classical computer
  * quantom computer without $h\bar$

### Technical difficulties of quantom computers
* Control error
  * $ X = {{1}\over{\sqrt{1+\epsilon^2}}} $
  * $ |1_\epsilon> = {{1}\over{\sqrt{1+\epsilon^2}}}(\epsilon |0> + |1> ) $
* error correction
  * classical: 0 -> 000, 1 -> 111
  * quantom:
    * |0> -> |000000>
    * |1> -> |111111>
    * logicla bit -> physical bit
    * 1 logical qubit -> 6+ physical qubits
* Decoherence
### 量子计算机现状
* 多种初级量子计算机
  * IBM, Google
  * USTC
* 没有在解决实际问题上能超越经典计算机的量子计算机
* 没有纠错机制，退相干时间很短
### Difficulties of building quantom computer
* Space project
  * believed to go to Mars
* Controlled nuclear fusion
  * have been primitive for a long time
* Quantom computer
  * maybe like controlled nuclear fusion

## Quantom algorithm 量子算法
* quantom computing
  * how to build a quantom computer
  * how to use quantom computer
    * -> quantom algorithms
* factors affecting computing speed
  * switch speed
  * programming language
  * algorithm
    * $ m_1 + m_2 + ... + m_n $
* Time compilexity
  * $ T = kf(n) $ -> $ O(f(n)) $
  * How computing time increases when the problem size $ n $ increases?
* P & NP problems
  * NP: **nondeterministic** polynomial
    * factor
  * P: polynomial $ O(n^k) $
* NP complete & NP-hard
  * Example: independent sets (ISs) of a graph
    * IS: O(1)
    * one non-trival IS: O(n)
    * one maximal IS: O(m+n)
    * whether there is an IS size of k: NP-complete
    * maximum IS (MIS): NP-hard
* Example: Circult for Quantom Fourier transformation
* Superposition does **not** necessarily lead to speed up
  * |0,0,0> -> |0,0,0>
  * |0,1,1> -> |1,1,0>
  * $ {{1}\over{\sqrt{2}}}(|0,0,0>+|0,1,1>) $ -> $ {{1}\over{\sqrt{2}}}(|0,0,0>+|1,1,0>) $
  * but measure only give one state
* Why so few good quantom algorithm?
  * must faster tham classical algorithm
* Can physics help us find faster quantom algorithms?
  * Hamiltonians mostly must be physical reasonable


* More: <www.koushare.com>


5. 两三个问题  
    * 在可遇见的将来具有实用性量子计算机仍看不到被研发出来的希望时投入如此大量的人力物力来研究量子算法难免有盲目跟风的嫌疑，这是否真的有必要？
    * 目前量子算法的研究看起来大多处于理论研究阶段，且看起来偏数学，那么这种研究对其他领域的发展是否有借鉴意义？
6. “真知灼见”“所思所感”  
  讲座开篇介绍了 Steven Weinburg 的处事哲学，让人受益匪浅。经过数百年知识的飞跃式发展与已经持续数十年的信息爆炸，人类的知识总量早已是今非昔比，远超人脑所能接受的范围；换言之，一个令人遗憾的事实是单个的（正常）人不可能掌握人类全部已有的知识。同时人“术业有专攻”，并非所有知识都对某个人从事的行业有正向的引导作用。在脑机接口尚不成熟、单个人所能利用的资源仍然受限于生理极限的当下，解决资源有限问题的一个策略即为类似“Lazy evaluation”的做法。当有需求时再去学习，在不影响研究进度的前提下，这样的学习策略看起来是效率最大化的一种做法。
  对于量子计算机的理论研究，由于既没有学过量子力学也没有看过相关科普读物，鄙人只能囫囵吞枣。但凭借对于量子论粗浅的理解，量子计算机研究不需要 Planck 常数这一事实确实令人错愕。大约量子计算机的理论研究已经可以被抽象为幺正矩阵的叠加而演变为纯数学的问题，而仅仅在实验实现的层面上才需要利用量子论与 Planck 常数。
  至于量子算法的研究，该讲座破除了媒体带给常人的一个常见误区。叠加态不一定带来加速，因为观测时波函数终究会坍缩而丢失叠加的各分量的数值，因而需要多次测量才能得到相对准确的结果，这很大程度上限制了量子算法的运行效率。曾阅读有关利用实物粒子量子特性寻找势函数最低点的相关报道，即便在构造出势场后单次测量远快于经典计算机的数值模拟，但多次运行结果也并非一定相同，且受热运动干扰较大，严重拖慢了量子计算机的运行效率。对此，光量子可能是未来的发展趋势，甚至可与传统意义上的光子计算相结合。
