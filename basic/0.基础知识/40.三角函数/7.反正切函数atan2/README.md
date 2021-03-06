# 反正切函数

## atan2()
反正切函数，atan() 的增强版，能确定象限
double atan2(double y，double x);
atan2() 函数的功能是求 y/x 的反正切值。atan2() 是 atan() 的增强版，能够确定角度所在的象限。

反正切函数 atan2() 和正切函数 tan() 的功能恰好相反：tan() 是已知一个角的弧度值，求该角的正切值；而 atan2() 是已知一个角的正切值（也就是 y/x），求该角的弧度值。 
##参数
> + y
表示位于 Y 轴上的值。
> + x
表示位于 X 轴上的值。

注意，x 和 y 同时为 0 时将导致域错误（domain error），因为此时的角度是不存在的，或者说是没有意义的。

## 返回值
返回 y/x 的反正切值，以弧度表示，取值范围为(-π,π]。如上图所示，tan(θ) = y/x，θ = atan2(y, x)。

> + 当 (x, y) 在象限中时： 
> + 当 (x, y) 在第一象限，0 < θ < π/2
> + 当 (x, y) 在第二象限，π/2 < θ ≤ π
> + 当 (x, y) 在第三象限，-π < θ < -π/2
> + 当 (x, y) 在第四象限，-π/2 < θ < 0

> + 当 (x, y) 在象限的边界（也就是坐标轴）上时： 
> + 当 y 是 0，且 x 为非负值，θ = 0
> + 当 y 是 0，且 x 是负值，θ = π
> + 当 y 是正值，且 x 是 0，θ = π/2
> + 当 y 是负值，且 x 是 0，θ = -π/2

由此可知，一般情况下用 atan() 即可，当对所求出角度的象限有特殊要求时，应使用 atan2()。