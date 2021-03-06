#![allow(dead_code, unused_parens, unused_imports)]

mod chapter01;

#[macro_use]
extern crate prettytable;

use crate::chapter01::chapter1a::exercise_1_1;
use crate::chapter01::chapter1b::{exercise_1_2, exercise_1_3};

fn main() {
    exercise_1_3();
}
