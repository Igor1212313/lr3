use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    let first: Vec<usize> = input
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let n = first[0];
    let m = first[1];

    input.clear();
    io::stdin().read_line(&mut input).unwrap();

    let a: Vec<i64> = input
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let mut pavel: i64 = 0;
    let mut vika: i64 = 0;

    let mut pos: usize = 0;
    let mut last_move: usize = 0;
    let mut pavel_turn = true;

    while pos < n {
        let max_count = std::cmp::min(m, n - pos);

        let mut best_sum: i64 = i64::MIN;
        let mut best_count: usize = 1;
        let mut current_sum: i64 = 0;

        for count in 1..=max_count {
            current_sum += a[pos + count - 1];

            if count == last_move {
                continue;
            }

            if current_sum > best_sum {
                best_sum = current_sum;
                best_count = count;
            }
        }

        if pavel_turn {
            pavel += best_sum;
        } else {
            vika += best_sum;
        }

        pos += best_count;
        last_move = best_count;
        pavel_turn = !pavel_turn;
    }

    if pavel > vika {
        println!("1");
    } else {
        println!("0");
    }
}
