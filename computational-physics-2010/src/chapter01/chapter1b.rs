use prettytable::{Table};
use num::pow;
use std::f64::consts::PI;
use num::integer::sqrt;
use num::traits::Pow;
use std::f64::EPSILON;

// Exercise 1.2

pub fn f(x: f64) -> f64 {
    return x.exp();
}

pub fn f_integrate(x: f64) -> f64 {
    return x.exp();
}

pub fn exercise_1_2() {
    let mut n = 4;
    let mut table = Table::new();
    table.set_titles(row!["N", "h", "integrate_trapezoidal", "integrate_simpson", "integrate_bode"]);
    while (n <= 128) {
        let h = 1.0 / (n as f64);
        table.add_row(row![n,
                                format!("{:+.7}", h),
                                format!("{:+.6}", integrate_trapezoidal(f, 0.0, 1.0, h) - (f_integrate(1.0) - f_integrate(0.0))),
                                format!("{:+.6}", integrate_simpson(f, 0.0, 1.0, h) - (f_integrate(1.0) - f_integrate(0.0))),
                                format!("{:+.6}", integrate_bode(f, 0.0, 1.0, h) - (f_integrate(1.0) - f_integrate(0.0)))]);
        n *= 2;
    }
    table.printstd();
}

pub fn integrate_trapezoidal<F: Fn(f64) -> f64>(f: F, a: f64, b: f64, h: f64) -> f64 {
    let n = ((b - a) / h).floor() as i64;
    // i64 so that `n-1` will not overflow
    let mut u; // x_i
    let mut v = a; // x_{i+1}
    let mut ret = 0.0;
    for i in 1..=n {
        u = v;
        v = a + ((i as f64) * h);
        ret += (f(u) + f(v)) * h / 2.0;
    }
    if (v < b) {
        ret += (f(v) + f(b)) * h / 2.0;
    }
    return ret;
}

pub fn integrate_simpson<F: Fn(f64) -> f64>(f: F, a: f64, b: f64, h: f64) -> f64 {
    let n = ((b - a) / h / 2.0).floor() as i64 * 2;
    let mut x;
    let mut ret = 0.0;

    ret += f(a);

    for i in (1..=n - 1).step_by(2) {
        x = a + ((i as f64) * h);
        ret += 4.0 * f(x);
    }

    for i in (2..=n - 2).step_by(2) {
        x = a + ((i as f64) * h);
        ret += 2.0 * f(x);
    }

    x = a + ((n as f64) * h);
    ret += f(x);

    ret *= h / 3.0;

    if (x < b) {
        ret += (f(x) + f(b)) * h / 2.0;
    }

    return ret;
}

pub fn integrate_bode<F: Fn(f64) -> f64>(f: F, a: f64, b: f64, h: f64) -> f64 {
    let n = ((b - a) / h / 4.0).floor() as i64 * 4;
    let mut x;
    let mut ret = 0.0;

    for i in (0..n).step_by(4) {
        x = a + ((i as f64) * h);
        ret += 7.0 * f(x) + 32.0 * f(x + h) + 12.0 * f(x + 2.0 * h) + 32.0 * f(x + 3.0 * h) + 7.0 * f(x + 4.0 * h);
    }

    ret *= 2.0 * h / 45.0;

    x = a + ((n as f64) * h);
    if (x < b) {
        ret += (f(x) + f(b)) * h / 2.0;
    }

    return ret;
}

// Exercise 1.3

pub fn g(t: f64) -> f64 {
    return t.pow(-2.0 / 3.0) * (1.0 - t).pow(-1.0 / 3.0);
}

pub fn exercise_1_3() {
    let ans = 2.0 * PI / (3.0 as f64).sqrt();
    let mut n;
    let mut mid;
    let mut table = Table::new();
    table.set_titles(row!["mid", "N", "h", "integrate_trapezoidal", "integrate_simpson", "integrate_bode"]);

    n = 1024;
    while (n <= 16384) {
        mid = 0.1;
        while (mid < 0.99) {
            let h = 1.0 / (n as f64);
            table.add_row(row![format!("{:+.1}", mid),
                                n,
                                format!("{:+.7}", h),
                                format!("{:+.6}", 3.0 * integrate_trapezoidal(g1, 0.0, mid.pow(1.0 / 3.0), h) + 3.0 / 2.0 * integrate_trapezoidal(g2, 0.0, (1.0 - mid).pow(2.0 / 3.0), h) - ans),
                                format!("{:+.6}", 3.0 * integrate_simpson(g1, 0.0, mid.pow(1.0 / 3.0), h) + 3.0 / 2.0 * integrate_simpson(g2, 0.0, (1.0 - mid).pow(2.0 / 3.0), h) - ans),
                                format!("{:+.6}", 3.0 * integrate_bode(g1, 0.0, mid.pow(1.0 / 3.0), h) + 3.0 / 2.0 * integrate_bode(g2, 0.0, (1.0 - mid).pow(2.0 / 3.0), h) - ans)
            ]);
            mid += 0.1;
        }
        n *= 2;
    }
    table.printstd();
}

pub fn g1(u: f64) -> f64 {
    return (1.0 - u * u * u).pow(-1.0 / 3.0);
}

pub fn g2(s: f64) -> f64 {
    return (1.0 - s.pow(3.0 / 2.0 as f64)).pow(-2.0 / 3.0);
}