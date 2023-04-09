use std::mem::swap;

use proconio::input;

fn ceil_div(a: i64, b: i64) -> i64 {
    return (a + b - 1) / b;
}

fn main() {
    input! {
        mut a: i64, mut b: i64,
    }

    let mut ans = 0;
    while a != b {
        if a < b {
            swap(&mut a, &mut b);
        }
        let sub = ceil_div(a - b, b);
        a -= b * sub;
        ans += sub;
    }
    println!("{}", ans);
}
