use proconio::input;

fn main() {
    input! {n:i32, a:i32, b:i32}
    let mut ans = 0;
    for i in 1..=n {
        let mut num = i;
        let mut dsum = 0;
        while num != 0 {
            dsum += num % 10;
            num /= 10;
        }
        if a <= dsum && dsum <= b {
            ans += i;
        }
    }
    println!("{}", ans);
}
