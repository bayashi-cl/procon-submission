use proconio::{input, marker::Chars};

fn main() {
    input! {
        _n: usize,
        s: Chars,
    }
    if s.iter().any(|&c| c == 'o') && s.iter().all(|&c| c != 'x') {
        println!("Yes");
    } else {
        println!("No");
    }
}
