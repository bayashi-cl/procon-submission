use proconio::input;

fn main() {
    input! {
        n: usize, d: i32,
        t: [i32; n],
    }
    for i in 1..n {
        if t[i] - t[i - 1] <= d {
            println!("{}", t[i]);
            return;
        }
    }
    println!("-1");
}
