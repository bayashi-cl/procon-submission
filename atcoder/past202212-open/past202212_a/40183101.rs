fn main() {
    proconio::input! {
        n: i64,
        x: i64,
        y: i64,
    }
    let ans = n / x * y;
    println!("{}", ans);
}
