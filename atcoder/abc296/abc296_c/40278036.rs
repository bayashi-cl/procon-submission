use std::collections::HashSet;

fn main() {
    proconio::input! {
        n: usize,
        x: i64,
        a: [i64; n]
    }

    let s: HashSet<_> = a.iter().cloned().collect();
    for ai in a {
        if s.contains(&(x + ai)) {
            println!("Yes");
            return;
        }
    }
    println!("No");
}
