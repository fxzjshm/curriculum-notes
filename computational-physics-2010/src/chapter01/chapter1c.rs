use prettytable::Table;
use std::cmp::max;
use num::integer::sqrt;

// Exercise 1.4

pub fn f(x: f64) -> f64 {
    return x * x - 5.0;
}

pub fn f_derivative_1st(x: f64) -> f64 {
    return 2.0 * x;
}

pub fn exercise_1_4() {
    let x0 = 1.0;
    let dx = 0.5;
    let tol_x = 1E-6;
    let ans = (5.0 as f64).sqrt();
    test_find_root_search(f, x0, dx, tol_x, ans);

    let x0 = -3.0;
    let dx = 6.0;
    test_find_root_search(f, x0, dx, tol_x, ans); // this hangs as it never finds the root, until overflow
}

pub fn test_find_root_search<F: Fn(f64) -> f64>(f: F, x0: f64, dx: f64, tol_x: f64, ans: f64) {
    println!("x0 = {}, dx = {}", x0, dx);
    let v = find_root_search(f, x0, dx, tol_x).1;
    let mut table = Table::new();
    table.set_titles(row!["Iteration", "find_root_search"]);
    for i in 0..v.len() {
        table.add_row(row![i, format!("{:+.6}", v[i] - ans)]);
    }
    table.printstd();
}

pub fn exercise_1_5() {
    let x0 = 1.0;
    let x1 = 0.5;
    let dx = 0.5;
    let tol_x = 1E-6;
    let ans = (5.0 as f64).sqrt();
    let vs = [find_root_search(f, x0, dx, tol_x).1, find_root_newton_raphson(f, x0, tol_x).1, find_root_secant(f, x1, x0, tol_x).1];

    let mut ls = vec![0; vs.len()];
    let mut l = 0;
    for i in 0..vs.len() {
        ls[i] = vs[i].len();
        l = max(l, ls[i]);
    }

    let mut table = Table::new();
    table.set_titles(row!["Iteration", "find_root_search", "find_root_newton_raphson", "find_root_secant"]);
    let mut strs = vec![String::new(); vs.len()];
    for i in 0..l {
        for j in 0..vs.len() {
            if (i < vs[j].len()) {
                strs[j] = format!("{:+.6}", vs[j][i] - ans);
            } else {
                strs[j] = String::new();
            }
        }
        table.add_row(row![
            i,
            strs[0],
            strs[1],
            strs[2]
        ]);
    }
    table.printstd();
}

pub fn find_root_search<F: Fn(f64) -> f64>(f: F, x0: f64, mut dx: f64, tol_x: f64) -> (f64, Vec<f64>) {
    let mut v = vec![x0];
    let mut x = x0;
    let f_x0 = f(x0);
    while (true) {
        x += dx;
        v.push(x);
        if (f_x0 * f(x) < 0.0) {
            x -= dx;
            dx /= 2.0;
        }
        if (dx.abs() < tol_x) {
            break;
        }
    }
    return (x, v);
}


pub fn find_root_newton_raphson<F: Fn(f64) -> f64>(f: F, x0: f64, tol_x: f64) -> (f64, Vec<f64>) {
    let mut v = vec![x0];
    let mut x = x0;
    let mut x1;
    while (true) {
        x1 = x - (f(x) / f_derivative_1st(x));
        v.push(x1);
        if ((x1 - x).abs() < tol_x) {
            break;
        }
        x = x1;
    }
    return (x, v);
}

pub fn find_root_secant<F: Fn(f64) -> f64>(f: F, x0: f64, x1: f64, tol_x: f64) -> (f64, Vec<f64>) {
    let mut v = vec![x1];
    let mut x_im1 = x0;
    let mut x_i = x1;
    let mut x_ip1;
    while (true) {
        let k = ((f(x_i) - f(x_im1)) / (x_i - x_im1));
        x_ip1 = x_i - (f(x_i) / k);
        v.push(x_ip1);
        if ((x_ip1 - x_i).abs() < tol_x) {
            break;
        }
        x_im1 = x_i;
        x_i = x_ip1;
    }
    return (x_i, v);
}