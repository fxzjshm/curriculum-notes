use prettytable::{Table};

pub fn f(x: f64) -> f64 {
    return (x).sin();
}

pub fn f_derivative_1st(x: f64) -> f64 {
    return (x).cos();
}

pub fn f_derivative_2nd(x: f64) -> f64 {
    return -(x).sin();
}

pub fn f_derivative_3rd(x: f64) -> f64 {
    return -(x).cos();
}

pub fn f_derivative_4th(x: f64) -> f64 {
    return (x).sin();
}

// Exercise 1.1

pub fn exercise_1_1() {
    // template
    /*
    let mut h = 0.5;
    let mut table = Table::new();
    while (h >= 0.00001) {
        h /= 2.0;
    }
    table.printstd();
     */

    derivative_1st();
    derivative_2nd();
    derivative_3rd();
    derivative_4th();
}

pub fn derivative_1st_4p_pos<F: Fn(f64) -> f64>(f: F, x0: f64, h: f64) -> f64 {
    return (-2.0 * f(x0 - h) - 3.0 * f(x0) + 6.0 * f(x0 + h) - f(x0 + 2.0 * h)) / (6.0 * h);
}

pub fn derivative_1st_4p_neg<F: Fn(f64) -> f64>(f: F, x0: f64, h: f64) -> f64 {
    return -(-2.0 * f(x0 + h) - 3.0 * f(x0) + 6.0 * f(x0 - h) - f(x0 - 2.0 * h)) / (6.0 * h);
}

pub fn derivative_2nd_4p<F: Fn(f64) -> f64>(f: F, x0: f64, h: f64) -> f64 {
    return (f(x0 - h) - 2.0 * f(x0) + f(x0 + h)) / (h * h);
}

pub fn derivative_3rd_4p_pos<F: Fn(f64) -> f64>(f: F, x0: f64, h: f64) -> f64 {
    return (-f(x0 - h) + 3.0 * f(x0) - 3.0 * f(x0 + h) + f(x0 + 2.0 * h)) / (h * h * h);
}

pub fn derivative_3rd_4p_neg<F: Fn(f64) -> f64>(f: F, x0: f64, h: f64) -> f64 {
    return -(-f(x0 + h) + 3.0 * f(x0) - 3.0 * f(x0 - h) + f(x0 - 2.0 * h)) / (h * h * h);
}


pub fn derivative_1st_5p<F: Fn(f64) -> f64>(f: F, x0: f64, h: f64) -> f64 {
    return (f(x0 - 2.0 * h) - 8.0 * f(x0 - h) + 8.0 * f(x0 + h) - f(x0 + 2.0 * h)) / (12.0 * h);
}

pub fn derivative_2nd_5p<F: Fn(f64) -> f64>(f: F, x0: f64, h: f64) -> f64 {
    return (-f(x0 - 2.0 * h) + 16.0 * f(x0 - h) - 30.0 * f(x0) + 16.0 * f(x0 + h) - f(x0 + 2.0 * h)) / (12.0 * h * h);
}

pub fn derivative_3rd_5p<F: Fn(f64) -> f64>(f: F, x0: f64, h: f64) -> f64 {
    return (-f(x0 - 2.0 * h) + 2.0 * f(x0 - h) - 2.0 * f(x0 + h) + f(x0 + 2.0 * h)) / (2.0 * h * h * h);
}

pub fn derivative_4th_5p<F: Fn(f64) -> f64>(f: F, x0: f64, h: f64) -> f64 {
    return (f(x0 - 2.0 * h) - 4.0 * f(x0 - h) + 6.0 * f(x0) - 4.0 * f(x0 + h) + f(x0 + 2.0 * h)) / (h * h * h * h);
}

pub fn derivative_1st() {
    let mut h = 0.5;
    let mut table = Table::new();
    table.set_titles(row!["h", "derivative_1st_4p_pos", "derivative_1st_4p_neg","derivative_1st_5p"]);
    while (h >= 0.00001) {
        table.add_row(row![format!("{:+.5}", h),
                                format!("{:+.6}", derivative_1st_4p_pos(f, 1.0, h) - f_derivative_1st(1.0)),
                                format!("{:+.6}", derivative_1st_4p_neg(f, 1.0, h) - f_derivative_1st(1.0)),
                                format!("{:+.6}", derivative_1st_5p(f, 1.0, h) - f_derivative_1st(1.0))]);
        h /= 2.0;
    }
    table.printstd();
}

pub fn derivative_2nd() {
    let mut h = 0.5;
    let mut table = Table::new();

    table.set_titles(row!["h", "derivative_2nd_4p", "derivative_2nd_5p"]);
    while (h >= 0.00001) {
        table.add_row(row![format!("{:+.5}", h),
                                format!("{:+.6}", derivative_2nd_4p(f, 1.0, h) - f_derivative_2nd(1.0)),
                                format!("{:+.6}", derivative_2nd_5p(f, 1.0, h) - f_derivative_2nd(1.0))]);
        h /= 2.0;
    }
    table.printstd();
}

pub fn derivative_3rd() {
    let mut h = 0.5;
    let mut table = Table::new();
    table.set_titles(row!["h", "derivative_3rd_4p_pos", "derivative_3rd_4p_neg","derivative_3rd_5p"]);
    while (h >= 0.00001) {
        table.add_row(row![format!("{:+.5}", h),
                                format!("{:+.6}", derivative_3rd_4p_pos(f, 1.0, h) - f_derivative_3rd(1.0)),
                                format!("{:+.6}", derivative_3rd_4p_neg(f, 1.0, h) - f_derivative_3rd(1.0)),
                                format!("{:+.6}", derivative_3rd_5p(f, 1.0, h) - f_derivative_3rd(1.0))]);
        h /= 2.0;
    }
    table.printstd();
}

pub fn derivative_4th() {
    let mut h = 0.5;
    let mut table = Table::new();

    table.set_titles(row!["h", "derivative_4th_5p"]);
    while (h >= 0.00001) {
        table.add_row(row![format!("{:+.5}", h),
                                format!("{:+.6}", derivative_4th_5p(f, 1.0, h) - f_derivative_4th(1.0))]);
        h /= 2.0;
    }
    table.printstd();
}