use im_rc::HashSet;
use proconio::input;

fn main() {
    input! {n:i32};
    let mut s = HashSet::new();
    for _ in 0..n {
        input! {d:i32};
        s.insert(d);
    }
    println!("{}", s.len())
}
