fn ceil_isqrt(x: i64) -> i64 {
    let s = (x as f64).sqrt() as i64;
    for i in std::cmp::max(s - 5, 0)..s + 5 {
        if i * i >= x {
            return i;
        }
    }
    unreachable!();
}

fn ceil_div(a: i64, b: i64) -> i64 {
    return (a + b - 1) / b;
}

fn main() {
    proconio::input! {
        n: i64,
        m: i64
    }

    let mut ans = std::i64::MAX;
    let max = std::cmp::min(n, ceil_isqrt(m));
    for a in 1..=max {
        let b = ceil_div(m, a);
        if b <= n && a * b < ans {
            ans = a * b;
        }
    }
    if ans == std::i64::MAX {
        ans = -1;
    }
    println!("{}", ans);
}
