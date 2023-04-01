fn main() {
    proconio::input! {
        n: usize,
        a: [i64; n],
    }

    let mut ans = std::i64::MIN;
    let mut min = 0_i64;
    let mut now = 0_i64;

    for ai in a {
        now += ai;
        if now - min > ans {
            ans = now - min;
        }
        if now < min {
            min = now;
        }
    }
    println!("{}", ans);
}
