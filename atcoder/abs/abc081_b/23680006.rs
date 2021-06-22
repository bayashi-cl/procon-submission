use proconio::input;
use std::cmp::min;
fn main() {
    input! {
        n:i32,
        mut a:[i32;n],
    }
    let mut ans = 100000000;
    for mut ai in a {
        let mut cnt = 0;
        loop {
            if ai % 2 == 0 {
                cnt += 1;
                ai /= 2;
            } else {
                break;
            }
        }
        ans = min(ans, cnt);
    }
    println!("{}", ans);
}
