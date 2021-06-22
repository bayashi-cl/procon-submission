use num::abs;
use proconio::input;

fn main() {
    input! {
        n:i32,
    }
    let mut t = 0;
    let mut x = 0;
    let mut y = 0;
    let mut ans = true;

    for _ in 0..n {
        input! {ti: i32, xi: i32, yi: i32}
        let man_dist = abs(xi - x) + abs(yi - y);
        let lim = ti - t;

        if man_dist > lim {
            ans = false;
            break;
        }
        if man_dist % 2 != lim % 2 {
            ans = false;
            break;
        }

        x = xi;
        y = yi;
        t = ti;
    }
    println!("{}", if ans { "Yes" } else { "No" })
}
