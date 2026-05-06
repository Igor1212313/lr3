use std::io;

fn f(x: f64) -> f64 {
    if x >= -7.0 && x <= -6.0 {
        (1.0 - (x + 6.0).powi(2)).sqrt()
    } else if x > -6.0 && x <= -3.0 {
        -4.0 / 3.0 * x - 7.0
    } else if x > -3.0 && x <= 2.0 {
        -x.abs() + 1.0
    } else if x > 2.0 && x <= 6.0 {
        x / 4.0 - 2.0
    } else if x > 6.0 && x <= 7.0 {
        1.0 + (1.0 - (x - 6.0).powi(2)).sqrt()
    } else {
        0.0
    }
}

fn main() {
    println!("Введите Xнач, Xкон и dx:");

    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    let nums: Vec<f64> = input
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut x = nums[0];
    let x_end = nums[1];
    let dx = nums[2];

    println!("{:<10} {:<10}", "x", "y");

    while x <= x_end {
        println!("{:<10.3} {:<10.3}", x, f(x));
        x += dx;
    }
}

