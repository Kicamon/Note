# 数学错题本

## 数列极限（ε–N 定义）——按定义证明极限

**原题：** 按定义证明下述极限：

$$
\lim_{n\to\infty}\sqrt[n]{3n+2}=1
$$

---

**证明：** 即证

$$
\forall\varepsilon>0,\ \exists N\in\mathbb N^*,\ \forall n>N,\quad
\left|\sqrt[n]{3n+2}-1\right|<\varepsilon.
$$

因为

$$
3n+2>1 \quad\Longrightarrow\quad \sqrt[n]{3n+2}>1
$$

令

$$
\sqrt[n]{3n+2}=1+y_n,\qquad y_n>0.
$$

则

$$
3n+2
=
\sum_{i=0}^{n}\binom{n}{i}y_n^i
>
1+\frac{n(n-1)}{2}y_n^2.
$$

因此

$$
y_n^2 < \frac{6n+2}{n(n-1)}
$$

从而

$$
y_n < \sqrt{\frac{6n+2}{n(n-1)}}.
$$

当 $n>3$ 时，

$$
\sqrt{\frac{6n+2}{n(n-1)}}
<
\sqrt{\frac{10n-10}{n(n-1)}}
=
\sqrt{\frac{10}{n}}.
$$

若

$$
n>\frac{10}{\varepsilon^2}
$$

则

$$
\sqrt{\frac{10}{n}}<\varepsilon.
$$

故

$$
\left|\sqrt[n]{3n+2}-1\right|
=
y_n
<
\sqrt{\frac{10}{n}}
<
\varepsilon.
$$

取

$$
\boxed{N=\max\left\{3,\frac{10}{\varepsilon^2}\right\}}
$$

则当 $n>N$ 时，

$$
\left|\sqrt[n]{3n+2}-1\right|<\varepsilon.
$$

故

$$
\boxed{\lim_{n\to\infty}\sqrt[n]{3n+2}=1}.
$$

---

## 数列极限（ε–N 定义）——根号函数连续性

**原题：** 设 $x_n\geqslant 0$，且 $\lim\limits_{n\to\infty}x_n=a\geqslant 0$，证明：

$$
\lim_{n\to\infty}\sqrt{x_n}=\sqrt{a}.
$$

---

**证明：** 分两种情况讨论。

**① 当 $a=0$ 时：**

对任意 $\varepsilon>0$，因为 $x_n\to 0$，存在 $N\in\mathbb N^*$，使得当 $n>N$ 时，有

$$
|x_n-0|<\varepsilon^2.
$$

又 $x_n\geqslant 0$，故 $0\leqslant x_n<\varepsilon^2$，从而

$$
\sqrt{x_n}<\varepsilon.
$$

即

$$
|\sqrt{x_n}-\sqrt{a}|=|\sqrt{x_n}|<\varepsilon.
$$

**② 当 $a>0$ 时：**

由有理化，

$$
|\sqrt{x_n}-\sqrt{a}|
=
\frac{|x_n-a|}{\sqrt{x_n}+\sqrt{a}}
\leqslant
\frac{|x_n-a|}{\sqrt{a}}.
$$

对任意 $\varepsilon>0$，因为 $x_n\to a$，存在 $N\in\mathbb N^*$，使得当 $n>N$ 时，有

$$
|x_n-a|<\sqrt{a}\,\varepsilon.
$$

于是

$$
|\sqrt{x_n}-\sqrt{a}|
\leqslant
\frac{|x_n-a|}{\sqrt{a}}
<
\varepsilon.
$$

**综上所述：** 无论 $a=0$ 还是 $a>0$，都有

$$
\boxed{\lim_{n\to\infty}\sqrt{x_n}=\sqrt{a}}.
$$
