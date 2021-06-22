use proconio::input;
use std::cmp::Reverse;
fn main() {
    input! {
        n: i32,
        mut a: [i32; n],
    }
    a.sort_by_key(|&x| Reverse(x));
    let mut bob = 0;
    let mut alice = 0;
    for i in 0..n {
        if i % 2 == 0 {
            alice += a[i as usize];
        } else {
            bob += a[i as usize];
        }
    }
    println!("{}", alice - bob)
}
