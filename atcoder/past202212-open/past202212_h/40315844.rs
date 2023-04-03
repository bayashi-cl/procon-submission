use proconio::{input, marker::Chars};

fn main() {
    input! {
        n: usize,
        ac: Chars,
    }
    let mut a = Vec::new();
    for d in &ac {
        a.push((*d as i64) - '0' as i64)
    }

    a.sort();

    let mut cs = vec![0_i64; n + 1];

    for i in 0..n {
        cs[i + 1] += cs[i] + a[i];
    }

    let mut ans = 0_i64;
    for i in 0..n {
        ans += (cs[n] - cs[i + 1]) - (a[i] * (n - i - 1) as i64)
    }
    println!("{}", ans);
}
