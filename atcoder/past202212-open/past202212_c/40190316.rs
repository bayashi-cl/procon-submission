use std::collections::HashSet;

fn main() {
    proconio::input! {
        n: usize,
        a: [i64; n]
    }
    let mut s: HashSet<i64> = HashSet::new();
    for i in 0..n {
        for j in i + 1..n {
            for k in j + 1..n {
                s.insert(a[i] * a[j] * a[k]);
            }
        }
    }
    println!("{}", s.len());
}
