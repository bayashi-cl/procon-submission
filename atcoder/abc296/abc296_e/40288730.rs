use proconio::marker::Usize1;
use std::collections::HashSet;

fn main() {
    proconio::input! {
        n: usize,
        mut a: [Usize1; n]
    }
    for _ in 0..32 {
        let mut aa = vec![0_usize; n];
        for i in 0..n {
            aa[i] = a[a[i]];
        }
        a = aa;
    }
    let s = a.iter().collect::<HashSet<_>>();
    println!("{}", s.len());
}
