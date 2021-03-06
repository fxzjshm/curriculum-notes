# 基本数学运算
## （一）导数的计算
> 05 基本数学运算（一）P5 - 10:40
* 三点式比两点式误差小，收敛快
* 三点式： 
    * $$
    \left.
    \begin{matrix}
        f_1 & = f_0 + h f' + {1 \over 2} h^2 f'' + O(h^3) \\
        f_{-1} & = f_0 - h f' + {1 \over 2} h^2 f'' + O(h^3) \\
    \end{matrix}
    \right\}
    \Rightarrow f' = {{f_{1} - f_{-1}}\over{2 h}} + O(h^3)
    $$
* 五点式： 
    * $$ 
    \begin{matrix}
        & f_2 - f_{-2} = 4hf' + { 8 \over 3 } h^3 f''' + O(h^3) \\
        \Rightarrow & 8(f_1 - f_{-1}) - (f_2 - f_{-2}) = 16hf' - 4f' + O(h^5) \\
        \Rightarrow & f' = {{8(f_1 - f_{-1}) - (f_2 - f_{-2})}\over{12h}} + O(h^4) \\
    \end{matrix}
    $$ 
    * (1.5)
* $f''$, $f'''$, $f''''$ 见 Table 1.2

> 05 基本数学运算（一）P5 - 15:15
* 没有 $f''''$ 的四点式
    * Taylor 展式代入已知数值看作方程，方程数少于已知数

## （二）数值积分
> 05 基本数学运算（一）P5 - 16:26
1. 梯形法则（单项式近似）
    * 计算小梯形面积
    * $$\int_{-h}^{h} f(x) {\rm d}x = {h \over 2}(f_{-1} + f_0 + f_0 + f_1)) + O(h^2)$$
    * (1.9)
2. Simpson 法则（二项式近似）
    * Taylor 级数
    * $$f(x) = f_0 + ({{f_1 - f_{-1}} \over {2h}})x + {1 \over 2}({{f_{-1} - 2f_0 + f_1} \over h^3})x^2 + O(x^3)$$
    * (1.7) 或 表1.2
    * $$
    \begin{aligned} 
        \Rightarrow \int_{-h}^{h} f(x){\rm d}x & = \left. f_0 x +{1 \over 2}({{f_{-1} - 2f_0 + f_1} \over h^3}){x^3 \over 3} + O(x^5) \right|_{-h}^{h} \\
        & = 2hf_0 + {h \over 3}(f_{-1} - 2f_0 + f_1) + O(h^5) \\
        & = {h \over 3}(f_{-1} + 4f_0 + f_1) + O(h^5) \\
    \end{aligned}
    $$
    * $$
    \begin{aligned}
        \int_{a}^{b} f(x){\rm d}x & = \int_{a}^{a+h} f(x){\rm d}x + \int_{a+h}^{a+2h} f(x){\rm d}x + ... +\int_{b-h}^{b} f(x){\rm d}x \\
        \stackrel{\text{Simpson}}{\longrightarrow} & = {h \over 3} \big( (f(a) + 4f(a+h) + f(a+2h)) + (f(a+2h) + 4f(a+3h) + f(a+4h)) + ... + 4f(b-h) + f(b) \big)
    \end{aligned}
    $$

## （三）求根
> 06 基本数学运算（二）P6 - 06:28
* 应用：分子振动模型的半经典量子化
* 试题：运动粒子被一个中心势的经典散射
* 对不同算法，比较收敛速度、精确度
1. Search 法
    * 初试一个数
    * 每次步长减半
    * 函数变号 $\rightarrow$ 反向
2. Newton-Rampson 法
    * $$f'(x) = \lim_{x^i \rightarrow x^{i-1}} {{f(x^{i-1}) - f(x^i)} \over {x^{i-1} - x^i}}$$
    * 一级近似时 $$f'(x^i) = {{0 - f(x^i)} \over {x^{i-1} - x^i}}$$
    * 收敛快于(1)，但要求有解析的$f'(x)$
3. Secant(割线)法
    * 用另一点 $x^{i-1}$ 与 $x^i$ 一起算 $f'(x^i)$ ，i.e. $f'(x^i) \approx {{f(x^{i-1}) - f(x^i)} \over {x^{i-1} - x^i}}$ ，代入得 (2.15)
    * 收敛速率约等于(2)，无需解析导数
* 注意：当函数 $f(x)$ 在根附近有拐点或有多根时，Newton-Rampson 法与 Secant(割线)法容易失效，此时应该用 Search法大概把根的范围找出，然后再用 Newton-Rampson 法和 Secant(割线)法

## Exercise 1.3
$$
\begin{aligned}
    & \int_0^1 t^{-{2 \over 3}} (1-t)^{-{1 \over 3}} {\rm d}t \\
  = & \int_0^m t^{-{2 \over 3}} (1-t)^{-{1 \over 3}} {\rm d}t +
      \int_m^1 t^{-{2 \over 3}} (1-t)^{-{1 \over 3}} {\rm d}t \\
  = & \int_0^m 3 (1-t)^{-{1 \over 3}} {\rm d}(t^{1 \over 3}) +
      \int_m^1 -{3 \over 2} t^{-{2 \over 3}} {\rm d}{\big( (1-t)^{2 \over 3} \big) } \\
  \stackrel{u = t^{1 \over 3} \text{,} s = (1-t)^{2 \over 3}}{\longrightarrow} & 
      \int_0^{m^{1 \over 3}} 3(1-u^3)^{-{1 \over 3}} {\rm d}u +
      \int_0^{({1-m})^{2 \over 3}} {3 \over 2} {(1-s^{3 \over 2})}^{-{2 \over 3}} {\rm d}s \\
\end{aligned}
$$
