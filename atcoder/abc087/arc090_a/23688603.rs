use proconio::input;
use std::cmp::max;
fn main() {
    input! {
        n: i32,
        a1: [i32; n],
        a2: [i32; n],
    }
    let a1: Vec<_> = a1
        .iter()
        .scan(0, |c, x| {
            *c += x;
            Some(*c)
        })
        .collect();
    let a2: Vec<_> = a2
        .iter()
        .scan(0, |c, x| {
            *c += x;
            Some(*c)
        })
        .collect();
    let mut ans = 0;
    for i in 0..n as usize {
        let mut cnt = a1[i] + a2[(n - 1) as usize];
        if i != 0 {
            cnt -= a2[(i - 1) as usize];
        }
        ans = max(ans, cnt);
    }
    println!("{}", ans)
}
