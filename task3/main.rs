use std::io;

fn gcd(mut a: i64, mut b: i64) -> i64 {
    while b != 0 {
        let t = a % b;
        a = b;
        b = t;
    }
    a.abs()
}

fn powll(base: i64, exp: usize) -> i64 {
    let mut result = 1;
    for _ in 0..exp {
        result *= base;
    }
    result
}

fn get_eulerian(max_a: usize) -> Vec<Vec<i64>> {
    let mut e = vec![vec![0; max_a + 1]; max_a + 1];
    e[0][0] = 1;

    for n in 1..=max_a {
        for k in 0..n {
            e[n][k] = (k as i64 + 1) * e[n - 1][k];

            if k > 0 {
                e[n][k] += (n as i64 - k as i64) * e[n - 1][k - 1];
            }
        }
    }

    e
}

fn main() {
    println!("Введите a и b:");

    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    let nums: Vec<i64> = input
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let a = nums[0] as usize;
    let b = nums[1];

    if b <= 1 {
        println!("infinity");
        return;
    }

    let e = get_eulerian(15);

    let mut numerator = 0;
    let denominator = powll(b - 1, a + 1);

    for k in 0..a {
        numerator += e[a][k] * powll(b, a - k);
    }

    let g = gcd(numerator, denominator);

    println!("{}/{}", numerator / g, denominator / g);
}
